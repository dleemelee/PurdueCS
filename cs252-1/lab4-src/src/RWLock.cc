#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/syscall.h> 
#include <assert.h>
#include <pthread.h>
#include <vector>
#include <algorithm>
#include "RWLock.h"


RWLock::RWLock ()
{
	pthread_mutex_init(&m1, NULL);
	pthread_mutex_init(&m2, NULL);
	pthread_mutex_init(&m3, NULL);
	//sem_init(&sem, 0,1);
	pthread_cond_init(&cv,NULL);
	nReaders = 0;
	nThreads = 1;

}

int RWLock::read_lock() 
{

	int i;
	for(i = 0; i <rLocks.size(); i++ ) {
		if(!pthread_equal( rLocks[i], pthread_self())) {
			return 1;
		}
	}
	
	for(i = 0; i < wLocks.size(); i++ ) {
		if(!pthread_equal( wLocks[i], pthread_self())) {
			return 2;
		}
	}

	pthread_mutex_lock(&m1);
	pthread_mutex_lock(&m2);
	if(nReaders == 0){
		//sem_wait(&sem);
		while( nThreads == 0) {
			pthread_cond_wait(&cv,&m3);
		}
		nThreads++;
	}
	nReaders++;
	pthread_mutex_unlock(&m2);
	pthread_mutex_unlock(&m1);

	pthread_mutex_lock(&m2);
	rLocks.push_back(pthread_self());
	pthread_mutex_unlock(&m2);

	return 0;
}

int RWLock::try_read_lock() 
{
	
	return read_lock();
}

int RWLock::read_unlock () 
{
	int exists = 0;
	int i;	
	for(i = 0; i != rLocks.size(); i++) {
		if(!pthread_equal( rLocks[i], pthread_self())) {
			exists = 1;
		}
	}
	if(!exists) {
		return 3;
	}
	exists = 0;
	for(i = 0; i != wLocks.size(); i++) {
		if(!pthread_equal( wLocks[i], pthread_self())) {
			exists = 1;
		}
	}
	if(exists) {
		return 2;	
	}
	pthread_mutex_lock(&m2);
	nReaders--;
	if (nReaders == 0)
		nThreads--;
		while(nThreads==0) {
			pthread_cond_signal(&cv);
		}
		//sem_post(&sem);
	for(i = 0; i != rLocks.size() || exists == 1; i++) {
		if(!pthread_equal( rLocks[i], pthread_self())) {
			exists = 0;
		}
	}
	rLocks.erase(std::remove(rLocks.begin(),rLocks.end(),pthread_self()),rLocks.end());
	pthread_mutex_unlock(&m2);
	return 0;
}

int RWLock::write_lock () 
{
	int i;
	for(i = 0; i != rLocks.size(); i++ ) {
		if(!pthread_equal( rLocks[i], pthread_self())) {
			return 1;
		}
	}
	
	for(i = 0; i != wLocks.size(); i++ ) {
		if(!pthread_equal( wLocks[i], pthread_self())) {
			return 2;
		}
	}

	pthread_mutex_lock(&m1);
	//sem_wait(&sem);
	while(nThreads==0) {
		pthread_cond_wait(&cv,&m3);
	}
	nThreads++;
	wLocks.push_back(pthread_self());
	return 0;
}

int RWLock::try_write_lock () 
{
	return write_lock();
}

int RWLock::write_unlock () 
{

	int exists = 0;
	int i;	
	for(i = 0; i != wLocks.size(); i++) {
		if(!pthread_equal( wLocks[i], pthread_self())) {
			exists = 1;
		}
	}
	if(!exists) {
		return 4;
	}
	exists = 0;
	for(i = 0; i != rLocks.size(); i++) {
		if(!pthread_equal( rLocks[i], pthread_self())) {
			exists = 1;
		}
	}
	if(exists) {
		return 1;	
	}

	nThreads--;
	while(nThreads==0){
		pthread_cond_signal(&cv);
	}
	//sem_post(&sem);
	pthread_mutex_unlock(&m1);
	for(i = 0; i != wLocks.size() || exists == 1; i++) {
		if(!pthread_equal( wLocks[i], pthread_self())) {
			exists = 0;
		}
	}
	i--;
	wLocks.erase(std::remove(rLocks.begin(),rLocks.end(),pthread_self()),rLocks.end());
	return 0;
}

int RWLock::write_to_read () 
{
	return 0;
}
