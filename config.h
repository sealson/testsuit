#pragma once

#include <string>
#include <vector>
#include <zlib.h>

struct udp_endpoint {
    const char *ip;
    int port;
};

class config {

public:
    config();
    ~config();
    int parseFile(const char *path);
    bool isConfigChanged(const char *path);

    void setConfigPath(const char *path);
    void setLogLevel(int lvl);

    const char *configPath(void);
    int logLevel(void);

private:
    int parseAgrument(std::string key, std::string value);
    int check_ipv4(const std::string &ip);
    
    const char *mConfig_path;
    int mLoglevel;
    uLong mCrc;

    int mSrcPort;
    std::vector<struct udp_endpoint> endpts;
};
