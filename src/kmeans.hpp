#ifndef _KMEANS_HPP
#define _KMEANS_HPP
#include <vector>

int kmeans_rand();
void kmeans_srand(unsigned int seed);
void randomCentroids(int k, int num_points, std::vector<std::vector<double>>* points, int seed);
void kmeans(std::vector<std::vector<double>>* points, struct options_t* opts);
double euclideanDistance(std::vector<double>& point, std::vector<double>& centroid, int dim);
void nearestCentroid(int k, int num_points, std::vector<std::vector<double>>* points, int dim);


#endif
