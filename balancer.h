#pragma once

#include <pthread.h>

class balancer {

public:
    balancer();
    ~balancer();
    void initListener(int portnum);

    void _listener_routine(void);
    void _loadfreq_sv_routine(void);
private:
	pthread_t listen_thid;
	pthread_t loadfreq_sv_thid;

};
