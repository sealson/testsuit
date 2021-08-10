#include "config.h"
#include <asm-generic/errno-base.h>
#include <cstddef>
#include <iostream>
#include <regex>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <sys/types.h>
#include <vector>


const char default_config_path[] = "/etc/testsuit.conf";

const char comment = '#';
const char valueis = '=';
const char portdelim = ':';
const char space[] = {
    ' ',
    '\t'
};
const std::string src_port = "SRC_PORT";
const std::string load_freq = "LOAD_FREQ";
const std::string udp_endpoint = "ENDPOINT";

config::config()
{
    mConfig_path = default_config_path;
}

config::~config()
{

}

int config::parseFile(const char *path)
{
    size_t pos;
    std::string line;
    std::ifstream instream(path);
    if (!instream) {
        return -ENOENT;
    }

    while (std::getline(instream, line)) {
        while((pos = line.find(comment)) != std::string::npos) {
            line.erase(pos, line.length());
        }
        if((pos = line.find(valueis)) != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + sizeof(valueis), line.length() - pos);
            this->parseAgrument(key, value);
        }
    }
    return 0;
}

bool config::isConfigChanged(const char *path)
{
    return false;
}

void config::setConfigPath(const char *path)
{
    mConfig_path = path;
}
void config::setLogLevel(int lvl)
{
    mLoglevel = lvl;
}
const char *config::configPath(void)
{
    return mConfig_path;
}

int config::logLevel(void)
{
    return mLoglevel;
}

size_t config::endpointsCount()
{
    return mEndpts.size();
}

struct udp_endpoint * config::endpoint(size_t num)
{
    return &mEndpts.at(num);
}

int config::parseAgrument(std::string &key, std::string &value)
{
    size_t pos;
    int buf;

    if (key.find(src_port) != std::string::npos) {
        try {
            buf = std::stoi(value);
        }
        catch (...) {
            std::cout << "Wrong src port in config file: " << value << std::endl;
            return -EINVAL;
        }
        mSrcPort = buf;
        return 0;
    }

    if (key.find(load_freq) != std::string::npos) {
        try {
            buf = std::stoi(value);
        }
        catch (...) {
            std::cout << "Wrong load frequency in config file: " << value << std::endl;
            return -EINVAL;
        }
        mLoadFreq = buf;
    }

    if (key.find(udp_endpoint) != std::string::npos) {
        if ((pos = value.find(portdelim)) != std::string::npos) {
            std::string ip = value.substr(0, pos);
            std::string port = value.substr(pos + sizeof(portdelim), value.length() - pos);

            if(check_ipv4(ip)) {
                std::cout << "Wrong ip in config file: " << ip << std::endl;
                return -EINVAL;
            } 
            try {
                buf = stoi(port);
            }
            catch (...) {
                std::cout << "Wrong port in config file: " << port << std::endl;
                return -EINVAL;
            }

            mEndpts.push_back({ ip, buf });
            return 0;
        }
    }

#if 0
    std::cout << "Count: " << mEndpts.capacity() << std::endl;
    for(auto endpt : mEndpts) {
        std::cout << endpt.ip << std::endl;
        std::cout << endpt.port << std::endl;
    }
#endif

    return 0;
}

int config::check_ipv4(const std::string &ip)
{
    std::regex ipv4_regex("(\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3})");
    if (!std::regex_match(ip, ipv4_regex))
        return -EINVAL;
    return 0;
}
