#include "config.h"
#include <cstddef>
#include <iostream>
#include <regex>
#include <fstream>
#include <sstream>
#include <vector>

const char comment = '#';
const char valueis = '=';
const char space[] = {
    ' ',
    '\t'
};
const std::string src_port = "SRC_PORT";
const std::string load_freq = "LOAD_FREQ";
const std::string udp_endpoint = "ENDPOINT";

config::config()
{

}

config::~config()
{

}

int config::parseFile(const char *path)
{
    std::ifstream instream(path);
    std::string line;
    size_t pos;

    //TODO kulibyaka
    while (std::getline(instream, line)) {
        while((pos = line.find(comment)) != std::string::npos) {
            line.erase(pos, line.length());
        }
        if((pos = line.find(valueis)) != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + sizeof(valueis), line.length());
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
    
int config::parseAgrument(std::string key, std::string value)
{
    size_t pos;
    if (key.find(src_port) != std::string::npos) {
        for (auto ch : space) {
            while ((pos = value.find(ch)) != std::string::npos) {

            }
        }
    }

}

int config::check_ipv4(const std::string &ip)
{
    std::regex ipv4_regex("(\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3})");
    if (!std::regex_match(ip, ipv4_regex))
        return -EINVAL;
    return 0;
}
