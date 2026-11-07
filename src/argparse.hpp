#ifndef _ARGPARSE_HPP
#define _ARGPARSE_HPP

#include <getopt.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

struct options_t {
    int     num_cluster;
    int     dims;
    char   *input_filename;
    int     max_num_iter;
    double  threshold;
    bool    flag;
    int     seed;
};

void get_opts(int argc, char **argv, struct options_t *opts);
#endif
