#include "balancer.h"
#include <unistd.h>
#include <iostream>

balancer::balancer()
{

}

balancer::~balancer()
{

}

void* loadfreq_sv_thread(void *args)
{
    if (args == nullptr)
        return args;

    balancer *blncr = static_cast<balancer *>(args);
    blncr->_loadfreq_sv_routine();
    return nullptr;
}

void* listener_thread(void *args)
{
    if (args == nullptr)
        return args;

    balancer *blncr = static_cast<balancer *>(args);
    blncr->_listener_routine();
    return nullptr;
}

void balancer::initListener(int portnum)
{
    int ret;

    std::cout << "Init read thread" << std::endl;
    ret = pthread_create(&listen_thid, NULL, &listener_thread, this);
    if (ret)
        throw ret;

    std::cout << "Init supervisor thread" << std::endl;
    ret = pthread_create(&loadfreq_sv_thid, NULL, &loadfreq_sv_thread, this);
    if (ret)
        throw ret;
}

void balancer::_loadfreq_sv_routine()
{
    while(1) {
        usleep(1e6);
    }
}

void balancer::_listener_routine()
{
    while(1);
}
