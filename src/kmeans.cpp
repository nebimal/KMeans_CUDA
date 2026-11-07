#include "kmeans.hpp"
#include "argparse.hpp"
#include "operators.hpp"
#include <cmath>
#include <unordered_map>


static unsigned long int next = 1;
static unsigned long kmeans_rmax = 32767;
std::vector<std::vector<double>> centroids;
std::unordered_map<int, int> centroidAssigner;

int kmeans_rand() {
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % (kmeans_rmax+1);
}

void kmeans_srand(unsigned int seed) {
    next = seed;
}

// 1st Step: Randomly select 'k' starting points.
void randomCentroids(int k, int num_points, int seed)
{
    centroids.resize(k);
    kmeans_srand(seed);
    int index;
    for (int i = 0; i < k; i++)
    {
        index = kmeans_rand() % num_points; 
        centroids[i] = points[index];
    }
}

//  2nd Step: Map each point to it's nearest centroid. 
void nearestCentroid(int k, int num_points, int dim)
{
    std::vector<double> distance(k); // This should be size of k.
    centroidAssigner.clear();

    // given 2048 points and 16 centroids. Double for loop I'd assume.
    for (int i = 0; i < num_points; i++)  // For each point.
    {
        int minIndex = 0;
        for (int j = 0; j < k; j++)       // For each centroid.
        {
            // I want to say I need a vector to hold the results from point A and all the other centroids.

            distance[j] = euclideanDistance(points[i], centroids[j], dim);
            // so at centroid 'j', the distance from point 'i' is distance[j].
            // I want an if statement that will give me the index of the smallest distance.
            if (distance[minIndex] > distance[j])
            {
                minIndex = j; // The centroid with the smallest distance from the point.
            }
        }
        // Outside the for loop, we need to assign the point to the centroid with least distance.
        centroidAssigner[i] = minIndex;
    }
}

double euclideanDistance(std::vector<double>& point, std::vector<double>& centroid, int dim)
{
    double sum = 0;
    for (int i = 0; i < dim; i++) {
        double difference = point[i] - centroid[i];
        sum += difference * difference;
    }

    return std::sqrt(sum);
}

// Step 3: Calculate Mean of All Points Assigned to a Centroid.
void centroidsMean(int dims, int k)
{

    std::vector<std::vector<double>> sums(k, std::vector<double>(dims, 0.0));
    std::vector<int> counts(k, 0);

    // Sum each coordinate of points assigned to each cluster.
    for (const auto& entry : centroidAssigner) {
        int pointIndex = entry.first;
        int cluster = entry.second;

        counts[cluster]++;

        for (int d = 0; d < dims; d++) {
            sums[cluster][d] += points[pointIndex][d];
        }
    }

    // Convert coordinate sums into averages.
    for (int c = 0; c < k; c++) {
        if (counts[c] == 0) {
            continue; // Keep the previous center if no points assigned.
        }

        for (int d = 0; d < dims; d++) {
            centroids[c][d] = sums[c][d] / counts[c];
        }
    }
}

void kmeans(struct options_t* opts) {

    int num_points = static_cast<int>(points.size());

    // Step 1: Initialize Centroids
    randomCentroids(opts->num_cluster, num_points, opts->seed);
    
    // Step 2: Map Each Point to it's Nearest Centroid.
    nearestCentroid(opts->num_cluster, num_points, opts->dims);

    // Step 3: Calculate Mean of All Points Assigned to a Centroid Then Move the Centroids Closer to their Destination.
    centroidsMean(opts->dims, opts->num_cluster);


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