#ifndef _KMEANS_HPP
#define _KMEANS_HPP
#include <vector>

int kmeans_rand();
void kmeans_srand(unsigned int seed);
void randomCentroids(int k, int num_points, std::vector<std::vector<double>>* points, int seed);
void kmeans(std::vector<std::vector<double>>* points, struct options_t* opts);

#endif
