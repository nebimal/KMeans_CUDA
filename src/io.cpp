#include "io.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

void read_file(char* input_filename, std::vector<std::vector<double>>* points)
{
    std::ifstream in(input_filename);

    if (!in) {
        std::cerr << "Error opening file" << std::endl;
        exit(1);
    }

    std::string line;
    std::getline(in, line);
    int num_points = std::stoi(line);

    points->clear();
    
    for (int i = 0; i < num_points; ++i) {
        std::getline(in, line);
        std::istringstream row(line);

        int id;
        row >> id;

        std::vector<double> coordinates;
        double coordinate;
        while (row >> coordinate) {
            coordinates.push_back(coordinate);
        }
        points->push_back(coordinates);
    }
}