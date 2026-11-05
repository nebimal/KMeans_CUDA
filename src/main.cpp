#include <iostream>
#include "argparse.h"

using namespace std;

int main(int argc, char **argv){

    struct options_t opts;
    get_opts(argc, argv, &opts);
     std::cout << "num_cluster: " << opts.num_cluster << '\n'
               << "dims: " << opts.dims << '\n'
               << "input_filename: " << opts.input_filename << '\n'
               << "max_num_iter: " << opts.max_num_iter << '\n'
               << "threshold: " << opts.threshold << '\n'
               << "flag: " << opts.flag << '\n'
               << "seed: " << opts.seed << '\n';
}