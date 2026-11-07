#include "kmeans.hpp"
#include "argparse.hpp"


static unsigned long int next = 1;
static unsigned long kmeans_rmax = 32767;
std::vector<std::vector<double>> centroids;

int kmeans_rand() {
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % (kmeans_rmax+1);
}

void kmeans_srand(unsigned int seed) {
    next = seed;
}

// 1st Step: Randomly select 'k' starting points.
void randomCentroids(int k, int num_points, std::vector<std::vector<double>>* points, int seed)
{
    centroids.resize(k);
    kmeans_srand(seed);
    int index;
    for (int i = 0; i < k; i++)
    {
        index = kmeans_rand() % num_points; 
        centroids[i] = (*points)[index];
    }
}

void kmeans(std::vector<std::vector<double>>* points, struct options_t* opts) {

    int num_points = static_cast<int>(points->size());
    randomCentroids(opts->num_cluster, num_points, points, opts->seed); // Need the
    // book-keeping
    for (int c = 0; c < opts->num_cluster; ++c) {
        std::cout << "Centroid " << c << ": ";

        for (double coordinate : centroids[c]) {
            std::cout << coordinate << ' ';
        }

        std::cout << '\n';
    }
    /*
    int iterations = opts->max_num_iter;
    oldCentroids = null;

    // core algorithm
    while(!done) {

        oldCentroids = centroids;
        iterations++;

        // labels is a mapping from each point in the dataset 
        // to the nearest (euclidean distance) centroid
        labels = findNearestCentroids(dataSet, centroids);

        // the new centroids are the average 
        // of all the points that map to each 
        // centroid
        centroids = averageLabeledCentroids(dataSet, labels, k);
        done = iterations > MAX_ITERS || converged(centroids, oldCentroids);
    }*/
}
/*
struct options_t { // we will get the pointer of this.
    int     num_cluster;
    int     dims;
    char   *input_filename;
    int     max_num_iter;
    double  threshold;
    bool    flag;
    int     seed;
};
*/