#include <vector>

class RWLock {

public:
    static const int ERROR_ALREADY_HOLDING_READ_LOCK = 1;
    static const int ERROR_ALREADY_HOLDING_WRITE_LOCK = 2;
    static const int ERROR_NOT_HOLDING_READ_LOCK = 3;
    static const int ERROR_NOT_HOLDING_WRITE_LOCK = 4;
    static const int LOCK_BUSY = 5;
	
	RWLock();

	int read_lock();
	int try_read_lock();
	int read_unlock();

	int write_lock();
	int try_write_lock();
	int write_unlock();

    int write_to_read();


private:
	pthread_mutex_t m1;
	pthread_mutex_t m2;
	pthread_mutex_t m3;
	//sem_t sem;
	pthread_cond_t cv;
	int nReaders;
	int nThreads;
	
	std::vector<pthread_t> rLocks;
	std::vector<pthread_t> wLocks;
};

