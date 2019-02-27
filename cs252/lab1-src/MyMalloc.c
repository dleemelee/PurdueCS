//
// CS252: MyMalloc Project
//
// The current implementation gets memory from the OS
// every time memory is requested and never frees memory.
//
// You will implement the allocator as indicated in the handout.
// 
// Also you will need to add the necessary locking mechanisms to
// support multi-threaded programs.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>
#include <errno.h>
#include <stdbool.h>
#include "MyMalloc.h"

#define ALLOCATED 1
#define NOT_ALLOCATED 0
#define ARENA_SIZE 2097152

pthread_mutex_t mutex;

static bool verbose = false;

extern void atExitHandlerInC()
{
  if (verbose)
    print();
}

static void * getMemoryFromOS(size_t size)
{
  // Use sbrk() to get memory from OS
  _heapSize += size;
 
  void *mem = sbrk(size);

  if(!_initialized){
      _memStart = mem;
  }

  return mem;
}


/*
 * @brief retrieves a new 2MB chunk of memory from the OS
 * and adds "dummy" boundary tagints
 * @param size of the request
 * @return a FreeObject pointer to the beginning of the chunk
 */
static FreeObject * getNewChunk(size_t size)
{
  void *mem = getMemoryFromOS(size);

  // establish fence posts
  BoundaryTag *fencePostHead = (BoundaryTag *)mem;
  setAllocated(fencePostHead, ALLOCATED);
  setSize(fencePostHead, 0);

  char *temp = (char *)mem + size - sizeof(BoundaryTag);
  BoundaryTag *fencePostFoot = (BoundaryTag *)temp;
  setAllocated(fencePostFoot, ALLOCATED);
  setSize(fencePostFoot, 0);
 
  return (FreeObject *)((char *)mem + sizeof(BoundaryTag));
}

/**
 * @brief If no blocks have been allocated, get more memory and 
 * set up the free list
 */
static void initialize()
{
  verbose = true;

  pthread_mutex_init(&mutex, NULL);

  // print statistics at exit
  atexit(atExitHandlerInC);

  FreeObject *firstChunk = getNewChunk(ARENA_SIZE);

  // initialize the list to point to the firstChunk
  _freeList = &_freeListSentinel;
  setSize(&firstChunk->boundary_tag, ARENA_SIZE - (2*sizeof(BoundaryTag))); // ~2MB
  firstChunk->boundary_tag._leftObjectSize = 0;
  setAllocated(&firstChunk->boundary_tag, NOT_ALLOCATED);

  // link list pointer hookups
  firstChunk->free_list_node._next = _freeList;
  firstChunk->free_list_node._prev = _freeList;
  _freeList->free_list_node._prev = firstChunk;
  _freeList->free_list_node._next = firstChunk;

  _initialized = 1;
}

/**
 * @brief TODO: PART 1
 * This function should perform allocation to the program appropriately,
 * giving pieces of memory that large enough to satisfy the request. 
 * Currently, it just sbrk's memory every time.
 *
 * @param size size of the request
 *
 * @return pointer to the first usable byte in memory for the requesting
 * program
 */
static void * allocateObject(size_t size)
{
  if(size == 0)
	return NULL;
  int split = 0;
  int nc = 0;
  // Make sure that allocator is initialized
  if (!_initialized)
    initialize();
  // Round up size
  if(size%8 != 0){
	size += (8-(size%8));
  }
  size += sizeof(BoundaryTag);
  if(size < 32) {
	size = 32;
  }
  // check for upper limit of size
  if(size > (ARENA_SIZE-3*sizeof(BoundaryTag))){
	errno = ENOMEM;
	return NULL;
  }  
  //Flip through FreeObjects to see which one can fill in size first
  //n is the freeobject, and b is its boundary tag
  FreeObject * n = &_freeListSentinel;
  BoundaryTag * b;
  for(n = n->free_list_node._next; n != &_freeListSentinel; n = n->free_list_node._next) {
	b = &(n->boundary_tag);
	//check size of the freeobject
	if(getSize(b) >= size){
	  if(getSize(b) - size >= 8+sizeof(FreeObject)){
		split = 1;
	  }
	  else{
		split = 0;
	  }
	  break;
	}
  }
  //allocated is the memory space of the soon to be allocated address
  void * allocated = (void*) n;
  //get a new chunk if you haven't found a free object of the right size
  if(n == &_freeListSentinel) {
	split = 1;
	FreeObject * new_chunk = getNewChunk(ARENA_SIZE);
	new_chunk->free_list_node._next = _freeList->free_list_node._next;
	new_chunk->free_list_node._prev = _freeList;
	_freeList->free_list_node._next = new_chunk;
	b = &(new_chunk->boundary_tag);
	setSize(b, ARENA_SIZE-(2*sizeof(BoundaryTag)));
	allocated = (void*)new_chunk;
	nc = 1;
  }
  int leftSize=0; 
  if(split){
	BoundaryTag * right = (BoundaryTag *)((char*)allocated+getSize(b));
    allocated = (void *)((char *)allocated + (getSize(b) - size));
	setSize(b, getSize(b)-size);
	leftSize = getSize(b)-size;
	if(getSize(right)){
		right->_leftObjectSize = size;
	}
  }
  else{
	//dont split
	n->free_list_node._prev->free_list_node._next = n->free_list_node._next;
	n->free_list_node._next->free_list_node._prev = n->free_list_node._prev;
	return (void*)((char*)n+sizeof(BoundaryTag));
  }
	BoundaryTag * newObj = (BoundaryTag *)allocated;
	setSize(newObj, size);
	setAllocated(newObj,1);
  if(split&&!nc){
	newObj->_leftObjectSize = leftSize;
  }

  pthread_mutex_unlock(&mutex);
  return (void*)(newObj+1);
}

/**
 * @brief TODO: PART 2
 * This funtion takes a pointer to memory returned by the program, and
 * appropriately reinserts it back into the free list.
 * You will have to manage all coalescing as needed
 *
 * @param ptr
 */
static void freeObject(void *ptr)
{
	int isLeft = 0;
	int isRight = 0;
	ptr = (void*)((char*)ptr-sizeof(BoundaryTag));
	FreeObject * new_free_object = (FreeObject* )ptr;
	BoundaryTag * free = &(new_free_object->boundary_tag);
	setAllocated(free, 0);
	FreeObject * left = (FreeObject *) ((char* )new_free_object - free->_leftObjectSize);
	FreeObject * right = (FreeObject *) ((char* )new_free_object + getSize(free));
	if(!isAllocated(&(right->boundary_tag))) {
		isRight = 1;
		int newSize = getSize(free) + getSize(&(right->boundary_tag));
		setSize(free, newSize);
		right->free_list_node._next->free_list_node._prev = right->free_list_node._prev;
		right->free_list_node._prev->free_list_node._next = right->free_list_node._next;
		if(getSize(&(right->boundary_tag)))
			right->boundary_tag._leftObjectSize = newSize;
	}
	if(!isAllocated(&(left->boundary_tag)) && left != new_free_object) {
		int newSize = getSize(free) + getSize(&(left->boundary_tag));
		setSize(&(left->boundary_tag), newSize);
		right = (FreeObject *) ((char* )free + getSize(free));
		right->boundary_tag._leftObjectSize = newSize;
		isLeft = 1;
	}
	if(isLeft && isRight){
		new_free_object = left;	
	}
	else if(isLeft && !isRight) {
		return;
	}
	
	new_free_object->free_list_node._next = _freeList->free_list_node._next;
	new_free_object->free_list_node._prev = _freeList;
	_freeList->free_list_node._next = new_free_object;
	return;
}

void print()
{
  printf("\n-------------------\n");

  printf("HeapSize:\t%zd bytes\n", _heapSize);
  printf("# mallocs:\t%d\n", _mallocCalls);
  printf("# reallocs:\t%d\n", _reallocCalls);
  printf("# callocs:\t%d\n", _callocCalls);
  printf("# frees:\t%d\n", _freeCalls);

  printf("\n-------------------\n");
}

void print_list()
{
    printf("FreeList: ");
    if (!_initialized) 
        initialize();
    FreeObject *ptr = _freeList->free_list_node._next;
    while (ptr != _freeList) {
        long offset = (long)ptr - (long)_memStart;
        printf("[offset:%ld,size:%zd]", offset, getSize(&ptr->boundary_tag));
        ptr = ptr->free_list_node._next;
        if (ptr != NULL)
            printf("->");
    }
    printf("\n");
}

void increaseMallocCalls() { _mallocCalls++; }

void increaseReallocCalls() { _reallocCalls++; }

void increaseCallocCalls() { _callocCalls++; }

void increaseFreeCalls() { _freeCalls++; }

//
// C interface
//

extern void * malloc(size_t size)
{
  pthread_mutex_lock(&mutex);
  increaseMallocCalls();
  
  return allocateObject(size);
}

extern void free(void *ptr)
{
  pthread_mutex_lock(&mutex);
  increaseFreeCalls();
  
  if (ptr == 0) {
    // No object to free
    pthread_mutex_unlock(&mutex);
    return;
  }
  
  freeObject(ptr);
}

extern void * realloc(void *ptr, size_t size)
{
  pthread_mutex_lock(&mutex);
  increaseReallocCalls();

  // Allocate new object
  void *newptr = allocateObject(size);

  // Copy old object only if ptr != 0
  if (ptr != 0) {

    // copy only the minimum number of bytes
    FreeObject *o = (FreeObject *)((char *) ptr - sizeof(BoundaryTag));
    size_t sizeToCopy = getSize(&o->boundary_tag);
    if (sizeToCopy > size) {
      sizeToCopy = size;
    }

    memcpy(newptr, ptr, sizeToCopy);

    //Free old object
    freeObject(ptr);
  }

  return newptr;
}

extern void * calloc(size_t nelem, size_t elsize)
{
  pthread_mutex_lock(&mutex);
  increaseCallocCalls();
    
  // calloc allocates and initializes
  size_t size = nelem * elsize;

  void *ptr = allocateObject(size);

  if (ptr) {
    // No error
    // Initialize chunk with 0s
    memset(ptr, 0, size);
  }

  return ptr;
}

