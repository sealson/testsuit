#include "balancer.h"
#include <cstdlib>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

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
    struct hostent *host;

    src_soc = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (src_soc < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        throw EXIT_FAILURE;
    }

    src_addr = {0};
    src_addr.sin_family = AF_INET;
    src_addr.sin_port = htons(portnum);

    host = gethostbyname("192.168.1.137");
    if (!host) {
        std::cerr << "Could not obtain address of " << "192.168.1.137" << std::endl;
        throw EXIT_FAILURE;
    }
    memcpy((void*) &src_addr, host->h_addr_list, host->h_length);
    
    if (bind(src_soc, (struct sockaddr *) &src_addr, sizeof(struct sockaddr))) {
        std::cerr << "Could not bind" << std::endl;
        close(src_soc);
        throw EXIT_FAILURE;
    }
    std::cout << "Listening to " << "192.168.1.137:" << portnum << std::endl;

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
    while(1) {
        
    }
}
