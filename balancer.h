#pragma once

#include <pthread.h>
#include <sys/time.h>
#include <netinet/in.h>

class balancer {

public:
    balancer();
    ~balancer();
    void initListener(int portnum);

    void _listener_routine(void);
    void _loadfreq_sv_routine(void);
private:
	pthread_t listen_thid;
	pthread_mutex_t  lock;
	pthread_t loadfreq_sv_thid;
    
    int src_soc;
    struct sockaddr_in src_addr;    /* server address */
    
};
