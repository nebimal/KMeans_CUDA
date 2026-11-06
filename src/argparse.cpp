#include "argparse.hpp"

void get_opts(int argc,
              char **argv,
              struct options_t *opts)
{
    if (argc == 1)
    {
        std::cout << "Usage:" << std::endl;
        std::cout << "\t-k <int> Number of Clusters" << std::endl;
        std::cout << "\t-d <int> Dimension of the Points" << std::endl;
        std::cout << "\t-i <string> Input Filename" << std::endl;
        std::cout << "\t-m <int> Maximum Number of Iterations" << std::endl;
        std::cout << "\t-t <double> Threshold for the Convergence Test" << std::endl;
        std::cout << "\t-c <flag> Output the Centroids of all Clusters if \"-c\" is Specified" << std::endl;
        std::cout << "\t-s <int> Seed for rand()" << std::endl;
        exit(0);
    }
        
    bool has_k = false, has_d = false, has_i = false;
    bool has_m = false, has_t = false, has_s = false;
    
    opts->flag = false;

    struct option l_opts[] = {
        {"num_clusters",     required_argument, NULL, 'k'},
        {"dims",             required_argument, NULL, 'd'},
        {"input_filename",   required_argument, NULL, 'i'},
        {"max_num_iter",     required_argument, NULL, 'm'},
        {"threshold",        required_argument, NULL, 't'},
        {"seed",             required_argument, NULL, 's'},
        {"flag",             no_argument,       NULL, 'c'},
        { NULL,              0,                 NULL,  0 }
    };

    int ind, c;
    while ((c = getopt_long(argc, argv, ":k:d:i:m:t:s:c", l_opts, &ind)) != -1)
    {
        switch (c)
        {
        case 0:
            break;
        case 'k':
            opts->num_cluster = atoi((char *)optarg);
            has_k = true;
            break;
        case 'd':
            opts->dims = atoi((char *)optarg);
            has_d = true;
            break;
        case 'i':
            opts->input_filename = (char *)optarg;
            has_i = true;
            break;
        case 'm':
            opts->max_num_iter = atoi((char *)optarg);
            has_m = true;
            break;
        case 't':
            opts->threshold = strtod((char *)optarg, nullptr);
            has_t = true;
            break;
        case 'c':
            opts->flag = true;
            break;
        case 's':
            opts->seed = atoi((char *)optarg);
            has_s = true;
            break;
        case ':':
            std::cerr << argv[0] << ": option -" << (char)optopt << " requires an argument." << std::endl;
            exit(1);
        }
    }
    if (!(has_k && has_d && has_i && has_m && has_t && has_s))
    {
        std::cerr << "Missing required options:";
        if (!has_k) std::cerr << " -k";
        if (!has_d) std::cerr << " -d";
        if (!has_i) std::cerr << " -i";
        if (!has_m) std::cerr << " -m";
        if (!has_t) std::cerr << " -t";
        if (!has_s) std::cerr << " -s";
        std::cerr << std::endl;
        exit(1);
    }
}