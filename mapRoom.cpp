/*
 *
 */

#include <SFML/Graphics.hpp>
#include <fstream>
#include <stdexcept>

using namespace std;


int* readCard(std::string filename) {
    ifstream infile(filename.c_str());
    if (infile.fail())) {
        throw runtime_error("Invalid file path");
    }
    int length;
    int* map_data = NULL;
    infile>>legth;
    map_data = new int[length];
    int num;
    for (int i=0;i<length;i++) {
        infile>>num;
        map_data[i] = num;
    }
}
