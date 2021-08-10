#include <getopt.h>
#include <errno.h>
#include <unistd.h>
#include <zconf.h>
#include <zlib.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>

#include "config.h"

#ifndef PROJECT_VERSION
#define PROJECT_VERSION "0.0.1"
#endif
#define CONF_FILE_LINESIZE   120


static struct option longopts[] = {
    { "config",  required_argument, NULL, 'c' },
    { "verbose", no_argument,       NULL, 'v' },
    { "version", no_argument,       NULL, 'V' },
    { "help",    no_argument,       NULL, 'h' }
};

static const char* shortopts = "c:hVv";

static void display_version(FILE *fd)
{
    fprintf(fd,
            "%s version %s\n"
            , program_invocation_short_name
            , PROJECT_VERSION);
}

static void display_help(FILE *fd)
{
    fprintf(fd,
            "%s [OPTIONS...]\n\n"
            "  -c --config <file>   custom *.conf file path\n"
            "  -v --verbose         Verbose mode.\n"
            "  -V --version         Show version\n"
            "  -h --help            Print this message\n"
            , program_invocation_short_name);
}

static int parse_args(config &config, int argc, char *argv[])
{
    int arg;
    while((arg = getopt_long(argc, argv, shortopts, longopts, NULL)) >= 0) {
        switch (arg) {
            case 'h': 
                display_help(stdout);
                exit(EXIT_SUCCESS);
            case 'V':
                display_version(stdout);
                exit(EXIT_SUCCESS);
            case 'c':
                config.setConfigPath(optarg);       
                break;
            default:
                display_help(stderr);
                return -EINVAL;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int ret;
    config cfg;
    
    ret = parse_args(cfg, argc, argv);
    if (ret)
        return ret;
    
    ret = cfg.parseFile(cfg.configPath());
    if (ret)
        return ret;
    
    while (1) {
        if (cfg.isConfigChanged(cfg.configPath())) {
            //TODO reload config
        }
        sleep(10);
    }
error:
    return EXIT_FAILURE;
}
