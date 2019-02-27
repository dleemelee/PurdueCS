#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linkedlist.h"

#define PASS 1
#define FAIL 0

// Create a linked list
int test1() {
    linkedlist_t *list = create_linkedlist();
    
    if(list == NULL)
        return FAIL;

    if(list->head != NULL || list->tail != NULL)
        return FAIL;

    free_linkedlist(list);

    return PASS;
}

// Add and find a node
int test2() {
    linkedlist_t *list = create_linkedlist();
    int ret1 = add_node(list, create_node(0, 0, NULL, NULL, 0));
    int ret2 = add_node(list, create_node(1, 0, NULL, NULL, 0));
    int ret3 = add_node(list, create_node(2, 0, NULL, NULL, 0));

    if(ret1 != 0 || ret2 != 0 || ret3 != 0)
        return FAIL;

    if(find_node(list, 1) == NULL)
        return FAIL;

    free_linkedlist(list);

    return PASS;
}


// Remove a node
int test3() {
    linkedlist_t *list = create_linkedlist();
    node_t* node0 = create_node(0, 0, NULL, NULL, 0);
    node_t* node1 = create_node(1, 0, NULL, NULL, 0);
    node_t* node2 = create_node(2, 0, NULL, NULL, 0);

    int ret1 = add_node(list, node0);
    int ret2 = add_node(list, node1);
    int ret3 = add_node(list, node2);
    int ret4 = remove_node(list, node1);

    if(ret1 != 0 || ret2 != 0 || ret3 != 0 || ret4 != 0)
        return FAIL;


    if(find_node(list, 1) != NULL)
        return FAIL;

    free_linkedlist(list);
    delete_node(node1);

    return PASS;
}

/******** Instructor tests begin **********/

// Test 4, 5, 6 Simple adding of nodes
int test4() {
    linkedlist_t *list = create_linkedlist();
    if(add_node(list, create_node(0, 0, NULL, NULL, 0)) != 0)
        return FAIL;

    if(list->head == NULL || list->tail == NULL)
        return FAIL;

    free_linkedlist(list);
    return PASS;
}

int test5() {
    linkedlist_t *list = create_linkedlist();
    int ret1 = add_node(list, create_node(0, 0, NULL, NULL, 0));
    int ret2 = add_node(list, create_node(1, 0, NULL, NULL, 0));

    if(ret1 != 0 || ret2 != 0)
        return FAIL;

    if(list->head == NULL || list->tail == NULL)
        return FAIL;

    if(list->head->timestamp != 0 || list->tail->timestamp != 1)
        return FAIL;

    free_linkedlist(list);

    return PASS;
}


int test6() {
    linkedlist_t *list = create_linkedlist();
    int ret1 = add_node(list, create_node(0, 0, NULL, NULL, 0));
    int ret2 = add_node(list, create_node(100, 0, NULL, NULL, 0));
    int ret3 = add_node(list, create_node(3, 0, NULL, NULL, 0));

    if(ret1 != 0 || ret2 != 0 || ret3 != 0)
        return FAIL;

    if(list->head == NULL || list->tail == NULL)
        return FAIL;

    if(list->head->timestamp != 0 || list->tail->timestamp != 3)
        return FAIL;

    free_linkedlist(list);
    return PASS;
}

// Delete a list with only one node
int test7() {
    linkedlist_t *list = create_linkedlist();
    node_t* node = create_node(0, 0, NULL, NULL, 0);
    int ret1 = add_node(list, node);
    int ret2 = remove_node(list, node);

    if(ret1 != 0 || ret2 != 0)
        return FAIL;

    if(list->head != NULL || list->tail != NULL)
        return FAIL;

    delete_node(node);
    free_linkedlist(list);
    return PASS;
}

// Remove the head
int test8() {
    linkedlist_t *list = create_linkedlist();
    node_t* head = create_node(0, 0, NULL, NULL, 0);
    node_t* tail = create_node(1, 0, NULL, NULL, 0);
    int ret1 = add_node(list, head);
    int ret2 = add_node(list, tail);
    
    int ret3 = remove_node(list, head);

    if(ret1 != 0 || ret2 != 0 || ret3 != 0)
        return FAIL;

    if(list->head != tail || list->tail != tail)
        return FAIL;

    free_linkedlist(list);
    delete_node(head);
    return PASS;
}

/**
 * Remove the tail
 */
int test9() {
    linkedlist_t *list = create_linkedlist();
    node_t* head = create_node(0, 0, NULL, NULL, 0);
    node_t* tail = create_node(1, 0, NULL, NULL, 0);
    int ret1 = add_node(list, head);
    int ret2 = add_node(list, tail);
    int ret3 = remove_node(list, tail);

    if(ret1 != 0 || ret2 != 0 || ret3 != 0)
        return FAIL;

    if(list->head != head || list->tail != head)
        return FAIL;

    free_linkedlist(list);
    delete_node(tail);

    return PASS;
}

/**
 * Remove a node in the middle
 */
int test10() {
    linkedlist_t *list = create_linkedlist();
    node_t* head = create_node(0, 0, NULL, NULL, 0);
    node_t* mid = create_node(5, 0, NULL, NULL, 0);
    node_t* tail = create_node(10, 0, NULL, NULL, 0);
    int ret1 = add_node(list, head);
    int ret2 = add_node(list, mid);
    int ret3 = add_node(list, tail);
    int ret4 = remove_node(list, mid);

    if(ret1 != 0 || ret2 != 0 || ret3 != 0 || ret4 != 0)
        return FAIL;

    if(list->head != head || list->tail != tail)
        return FAIL;

    free_linkedlist(list);
    delete_node(mid);

    return PASS;
}

/**
 * Find a node in trivial list
 */
int test11() {
    linkedlist_t *list = create_linkedlist();
    node_t* head = create_node(0, 0, NULL, NULL, 0);
    if(add_node(list, head))
        return FAIL;
    
    node_t* node = find_node(list, 0);

    if(node == NULL || node->timestamp != 0)
        return FAIL;

    free_linkedlist(list);
    return PASS;
}

/**
 * Look for a node that doesn't exist
 */
int test12() {
    linkedlist_t *list = create_linkedlist();
    node_t* head = create_node(0, 0, NULL, NULL, 0);
    if(add_node(list, head))
        return FAIL;
    
    node_t* node = find_node(list, 1000);

    if(node != NULL)
        return FAIL;

    free_linkedlist(list);
    return PASS;
}

/**
 * Find a node at the head
 */
int test13() {
    linkedlist_t *list = create_linkedlist();
    node_t* head = create_node(0, 0, NULL, NULL, 0);
    node_t* tail = create_node(1, 0, NULL, NULL, 0);
    int ret1 = add_node(list, head);
    int ret2 = add_node(list, tail);

    if(ret1 != 0 || ret2 != 0)
        return FAIL;
    
    node_t* node = find_node(list, 0);

    if(node == NULL || node->timestamp != 0)
        return FAIL;

    free_linkedlist(list);
    return PASS;
}

/**
 * Find a node at the tail
 */
int test14() {
    linkedlist_t *list = create_linkedlist();
    node_t* head = create_node(0, 0, NULL, NULL, 0);
    node_t* tail = create_node(1, 0, NULL, NULL, 0);
    int ret1 = add_node(list, head);
    int ret2 = add_node(list, tail);
    node_t* node = find_node(list, 1);

    if(ret1 != 0 || ret2 != 0)
        return FAIL;

    if(node == NULL || node->timestamp != 1)
        return FAIL;

    free_linkedlist(list);
    return PASS;
}

/** 
 * Find a node in the middle
 */
int test15() {
    linkedlist_t *list = create_linkedlist();
    node_t* head = create_node(0, 0, NULL, NULL, 0);
    node_t* mid = create_node(5, 0, NULL, NULL, 0);
    node_t* tail = create_node(10, 0, NULL, NULL, 0);
    int ret1 = add_node(list, head);
    int ret2 = add_node(list, mid);
    int ret3 = add_node(list, tail);
    node_t* node = find_node(list, 5);

    if(ret1 != 0 || ret2 != 0 || ret3 != 0)
        return FAIL;

    if(node == NULL || node->timestamp != 5)
        return FAIL;

    free_linkedlist(list);
    return PASS;
}

/**
 * Create a simple node
 */
int test16() {
    node_t* node = create_node(0, 0, NULL, NULL, 0);

    if(     node == NULL 
        || node->timestamp != 0 
        || node->transaction_type != 0
        || node->company1 != NULL
        || node->company2 != NULL
        || node->value != 0
        )
        return FAIL;

    delete_node(node);
    return PASS;
}

/**
 * Create a node with some features
 */
int test17() {
    node_t* node = create_node(1, 5, "test1", "test2", 10);

    if(     node == NULL 
        || node->timestamp != 1
        || node->transaction_type != 5
        || node->company1 == NULL
        || strcmp(node->company1, "test1")
        || node->company2 == NULL
        || strcmp(node->company2, "test2")
        || node->value != 10
        )
        return FAIL;

    delete_node(node);
    return PASS;
}

/**
 * Create a node to a string that changes
 */
int test18() {
    char* str1 = strdup("test1");
    char* str2 = strdup("test2");
    node_t* node = create_node(1, 5, str1, str2, 10);
    str1[0] = 'h';
    str2[0] = 'z';

    if(     node == NULL 
        || node->timestamp != 1
        || node->transaction_type != 5
        || node->company1 == NULL
        || strcmp(node->company1, "test1")
        || node->company2 == NULL
        || strcmp(node->company2, "test2")
        || node->value != 10
        )
        return FAIL;

    free(str1);
    free(str2);
    delete_node(node);
    return PASS;
}

/* for the following tests, figure out how to grab the signal instead of a segfault */
int test19() {
    
    free_linkedlist(NULL);
    return PASS;
}

/**
 * Test bad parameter for delete_node()
 */
int test20() {
    
    delete_node(NULL);
    return PASS;
}

/**
 * Test bad parameter for find_node()
 */
int test21() {
    
    if(find_node(NULL, 0) != NULL)
        return FAIL;

    return PASS;
}

/**
 * Test bad parameter for add_node()
 */
int test22()
{
    linkedlist_t *list = create_linkedlist();
    node_t *node = create_node(0, 0, NULL, NULL, 0);

    if(add_node(NULL, node) != -1 || add_node(list, NULL) != -1)
        return FAIL;

    free_linkedlist(list);
    delete_node(node);
    return PASS;
}

/**
 * Test bad parameter for remove_node()
 */
int test23()
{
    linkedlist_t *list = create_linkedlist();
    node_t *node = create_node(0, 0, NULL, NULL, 0);

    if(remove_node(NULL, node) != -1 || remove_node(list, NULL) != -1)
        return FAIL;

    free_linkedlist(list);
    delete_node(node);
    return PASS;
}


/**
 * Test for people with global variables
 */
int test24()
{
    linkedlist_t *list1 = create_linkedlist();
    linkedlist_t *list2 = create_linkedlist();
    linkedlist_t *list3 = create_linkedlist();
    linkedlist_t *list4 = create_linkedlist();

    // Test sequential insertion
    add_node(list1, create_node(1, 0, "company1", "company2", 1));
    add_node(list1, create_node(2, 0, "company1", "company2", 2));
    add_node(list1, create_node(3, 0, "company1", "company2", 3));
    add_node(list1, create_node(4, 0, "company1", "company2", 4));
    add_node(list2, create_node(5, 0, "company3", "company4", 5));
    add_node(list2, create_node(6, 0, "company3", "company4", 6));
    add_node(list2, create_node(7, 0, "company3", "company4", 7));
    add_node(list2, create_node(8, 0, "company3", "company4", 8));

    // Test alternate insertion
    add_node(list3, create_node(9, 0, "company5", "company6", 9));
    add_node(list4, create_node(10, 0, "company7", "company8", 10));
    add_node(list3, create_node(11, 0, "company5", "company6", 11));
    add_node(list4, create_node(12, 0, "company7", "company8", 12));
    add_node(list3, create_node(13, 0, "company5", "company6", 13));
    add_node(list4, create_node(14, 0, "company7", "company8", 14));
    add_node(list3, create_node(15, 0, "company5", "company6", 15));
    add_node(list4, create_node(16, 0, "company7", "company8", 16));


    // Check for correct lists now
    int i = 1;
    node_t* node = list1->head;
    if(node->prev != NULL)
        return FAIL;
    for(i = 1; i < 5; i++)
    {
        if(i != node->timestamp || strcmp("company1", node->company1) || strcmp("company2", node->company2) || i != node->value)
            return FAIL;
        node = node->next;
    }
    if(node!= NULL)
        return FAIL;


    node = list2->head;
    if(node->prev != NULL)
        return FAIL;
    for(i = 5; i < 9; i++)
    {
        if(i != node->timestamp || strcmp("company3", node->company1) || strcmp("company4", node->company2) || i != node->value)
            return FAIL;
        node = node->next;
    }
    if(node != NULL)
        return FAIL;

    node = list3->head;
    if(node->prev != NULL)
        return FAIL;
    for(i = 9; i < 17; i += 2)
    {
        if(i != node->timestamp || strcmp("company5", node->company1) || strcmp("company6", node->company2) || i != node->value)
            return FAIL;
        node = node->next;
    }
    if(node != NULL)
        return FAIL;

    node = list4->head;
    if(node->prev != NULL)
        return FAIL;
    for(i = 10; i < 18; i+= 2)
    {
        if(i != node->timestamp || strcmp("company7", node->company1) || strcmp("company8", node->company2) || i != node->value)
            return FAIL;
        node = node->next;
    }
    if(node != NULL)
        return FAIL;


    free_linkedlist(list1);
    free_linkedlist(list2);
    free_linkedlist(list3);
    free_linkedlist(list4);
    return PASS;
}


/**
 * Test for people with global variables
 */
int test25()
{
    linkedlist_t *list1 = create_linkedlist();
    linkedlist_t *list2 = create_linkedlist();
    linkedlist_t *list3 = create_linkedlist();
    linkedlist_t *list4 = create_linkedlist();

    // Test sequential insertion
    add_node(list1, create_node(1, 0, "company1", "company2", 1));
    add_node(list1, create_node(2, 0, "company1", "company2", 2));
    add_node(list1, create_node(3, 0, "company1", "company2", 3));
    add_node(list2, create_node(5, 0, "company3", "company4", 5));
    add_node(list2, create_node(6, 0, "company3", "company4", 6));
    add_node(list2, create_node(4, 0, "company1", "company2", 4));
    add_node(list2, create_node(7, 0, "company3", "company4", 7));
    add_node(list2, create_node(8, 0, "company3", "company4", 8));

    // Test alternate insertion
    add_node(list3, create_node(9, 0, "company5", "company6", 9));
    add_node(list4, create_node(10, 0, "company7", "company8", 10));
    add_node(list3, create_node(11, 0, "company5", "company6", 11));
    add_node(list4, create_node(12, 0, "company7", "company8", 12));
    add_node(list3, create_node(13, 0, "company5", "company6", 13));
    add_node(list4, create_node(14, 0, "company7", "company8", 14));
    add_node(list4, create_node(15, 0, "company5", "company6", 15));
    add_node(list4, create_node(16, 0, "company7", "company8", 16));


    node_t* node = find_node(list2, 4);
    int ret1 = remove_node(list2, node);
    int ret2 = add_node(list1, node);

    node = find_node(list4, 15);
    int ret3 = remove_node(list4, node);
    int ret4 = add_node(list3, node);

    if(ret1 != 0 || ret2 != 0 || ret3 != 0 || ret4 != 0)
        return FAIL;


    // Check for correct lists now
    int i = 1;
    node = list1->head;
    if(node->prev != NULL)
        return FAIL;
    for(i = 1; i < 5; i++)
    {
        if(i != node->timestamp || strcmp("company1", node->company1) || strcmp("company2", node->company2) || i != node->value)
            return FAIL;
        node = node->next;
    }
    if(node!= NULL)
        return FAIL;


    node = list2->head;
    if(node->prev != NULL)
        return FAIL;
    for(i = 5; i < 9; i++)
    {
        if(i != node->timestamp || strcmp("company3", node->company1) || strcmp("company4", node->company2) || i != node->value)
            return FAIL;
        node = node->next;
    }
    if(node != NULL)
        return FAIL;

    node = list3->head;
    if(node->prev != NULL)
        return FAIL;
    for(i = 9; i < 17; i += 2)
    {
        if(i != node->timestamp || strcmp("company5", node->company1) || strcmp("company6", node->company2) || i != node->value)
            return FAIL;
        node = node->next;
    }
    if(node != NULL)
        return FAIL;

    node = list4->head;
    if(node->prev != NULL)
        return FAIL;
    for(i = 10; i < 18; i+= 2)
    {
        if(i != node->timestamp || strcmp("company7", node->company1) || strcmp("company8", node->company2) || i != node->value)
            return FAIL;
        node = node->next;
    }
    if(node != NULL)
        return FAIL;

    free_linkedlist(list1);
    free_linkedlist(list2);
    free_linkedlist(list3);
    free_linkedlist(list4);
    return PASS;
}

/******** Instructor tests end *************/

int dispatch_test(int (*test)(), int idx) {
    int ret = test();
    if (ret == PASS) fprintf(stderr, "PASS: test%d\n", idx);
    else fprintf(stderr, "FAIL: test%d\n", idx);
    return ret;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <caseid>\n", argv[0]);
        return 1;
    }

    int (*tests[])() = {
        test1, test2, test3, test4,
        test5, test6, test7, test8,
        test9, test10, test11, test12,
        test13, test14, test15, test16,
        test17, test18, test19, test20,
        test21, test22, test23, test24,
        test25
    };
    const int testcount = sizeof(tests)/sizeof(int(*)());
    int testcase = atoi(argv[1]);
    if (testcase == 0) {
        int idx, ret = 1;
        for (idx = 1; idx <= testcount; idx++)
            ret = dispatch_test(tests[idx - 1], idx) && ret;
        return !ret;
    } else {
        return !dispatch_test(tests[testcase - 1], testcase);
    }
}
