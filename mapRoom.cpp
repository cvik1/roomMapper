/*
 * The following code reads data written to a file using roomMapping.ino
 * and draws the corresponding map from that data using the SFML graphics
 * library. 
 */

#include <SFML/Graphics.hpp>
#include <fstream>
#include <stdexcept>




int* readCard(char* filename, int* length) {
    ifstream infile(filename.c_str());
    if (infile.fail())) {
        throw runtime_error("Invalid file path");
    }
    int* map_data = NULL;
    infile>>legth;
    map_data = new int[length];
    int num;
    for (int i=0;i<length;i++) {
        infile>>num;
        map_data[i] = num;
    }
    return map_data;
}

int* dimensions(int* map_data, int length) {
    int dimensions = NULL;
    int* = new int[4];
    int direction = 0; //0 for up, 1 for right, 2 for down, 3 for left

    for(int i=0; i<length;) {
        if (map_data[i] == 0) {
            dimensions[direction] += 1;
        }
        else if (map_data[i] == 1) {
            direction = (direction+1)%4;
            dimensions[direction] +=1;
        }
        else if (map_data[i] == 2) {
            direction = (direction-1)%4
            dimensions[direction] +=1;
        }
    }
    return dimensions;
}

void drawLine(sf::RenderWindow window, sf:Point start, sf:Point end) {
    //draw the line based on the points given in the given window

}

void drawMap(sf::RenderWindow window, sf::Point start_point, int* map_data,
        int length, int size) {

    int direction = 0; //start direction at 0 (forwards)

    sf::Point start = start_point;
    sf::Point end;

    for (int i=0; i<length; i++) {
        if (map_data[i] == 0) { //straight
            if (direction == 0) { //if going staight
                //move end size pixels upwards of start
            }
            else if(direction == 1) { // if going right
                //move end size pixels right of start
            }
            else if(direction == 2) { // if going down
                // move end size pixels down of start
            }
            else if(direction == 3) {// if going left
                // move end size pixels left of start
            }
            //when going straight direction does not change
        }
        else if (map_data[i] == 1) { //right turn
            if (direction == 0) { //if going up
                //move end size pixels right of start
            }
            else if(direction == 1) {// if going right
                // move end size pixels down of start
            }
            else if(direction == 2) {// if going down
                // move end size pizels left of start
            }
            else if(direction == 3) {// if going left
                // move end size pixels up of start
            }
            direction = (direction+1)%4; // change direction for turn
        }
        else if (map_data[i] == 2) { //left turn
            if (direction == 0) { //if going up
                // move end size pixels left of start
            }
            else if(direction == 1) { //if going right
                // move end size pixels up of start
            }
            else if(direction == 2) { //if going down
                // move end size pixels right of start
            }
            else if(dircetion == 3) { //if going left
                // move end size pixels down of start
            }
            direction = (direction-1)%4; // change direction for turn
        }
        drawLine(window, start, end);
        start = end;
    }
}

int main(int argc,char** argv) {
    int* length = NULL;
    int* map_data =  readData(argv[1], length); //get the array of map data

    int* dimensions = NULL;
    dimensions = dimensions(map_data, length); //get the dimensions of the map
    int width, height;
    dimensions[0] = height; //get the height of the room in terms of "steps"
    dimensions[3] = width  //get the width of the room in terms of "steps"
    //each step is one rotation of the robot's wheels
    //we are using the left dimension for width as we start on the right side

    int size; //declare the variable for size of each segment
    if (height>80 || width>80) { //if more than 80 segments in any direction
        int size = 5; //make segments smaller to fit
    }
    if (height>160 || width>160) { //if more than 160 segments in any direction
        int size = 3; //make segments smaller to fit
    }
    if (hieght>300 || width> 300) { //if more than 300 segments in any direction
        int size = 2; //make segments smaller
    }

    sf::RenderWindow window(sf::VideoMode(1000,1000), "window");

    drawMap(window, start_point, map_data, length, size);

    return 0;
}
