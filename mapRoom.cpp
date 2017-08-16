 /*
 * The following code reads data written to a file using roomMapping.ino
 * and draws the corresponding map from that data using the SFML graphics
 * library.
 */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <SFML/Graphics.hpp>

using namespace sf;




int* readData(std::string filename, int* length) {

    std::ifstream infile(filename.c_str());
    if (infile.fail()) {
        throw std::runtime_error("Invalid file path");
    }
    infile >> *length; //read length of file from file
    int* map_data = new int[*length]; //create array to read data into
    int num;
    for (int i=0;i<*length;i++) { //read all data from file into array
        infile >> num;
        map_data[i] = num;
    }
    return map_data;
}

int* getDimensions(int* map_data, int* length) {
    int* dimensions = new int[4];
    int direction = 0; //0 for up, 1 for right, 2 for down, 3 for left
    // using the direction and map data, we will record the dimesions
    // of the map, so we can scale the graphics window accordingly
    for(int i=0; i<*length;) {
        if (map_data[i] == 0) {//if we go straight, then add 1 to that direction
            dimensions[direction] += 1;
        }
        else if (map_data[i] == 1) {     // if we turn right, change the
            direction = (direction+1)%4; // direction and add 1
            dimensions[direction] +=1;
        }
        else if (map_data[i] == 2) {     // if we turn left, change the
            direction = (direction-1)%4;  // direction and add 1
            dimensions[direction] +=1;
        }
    }
    return dimensions;
}

VertexArray makeLines(int* map_data, int* length, int size) {

    int direction = 0; //start direction at 0 (forwards)
    unsigned long linenum = (unsigned long)*length;
    VertexArray lines(LinesStrip, linenum);
    int x = 500;
    int y = 500;

    for (int i=0; i<*length; i++) {

        lines[i].position = Vector2f(x,y);

        if (map_data[i] == 0) { //straight
            if (direction == 0) { //if going staight
                //move position size pixels upwards of previous
                y -= size;
            }
            else if(direction == 1) { // if going right
                //move position size pixels right of previous
                x += size;
            }
            else if(direction == 2) { // if going down
                // move position size pixels down of previous
                y += size;
            }
            else if(direction == 3) {// if going left
                // move position size pixels left of previous
                x -= size;
            }
            //when going straight direction does not change
        }
        else if (map_data[i] == 1) { //right turn
            if (direction == 0) { //if going up
                //move position size pixels right of previous
                x += size;
            }
            else if(direction == 1) {// if going right
                // move position size pixels down of previous
                y += size;
            }
            else if(direction == 2) {// if going down
                // move position size pizels left of previous
                x -= size;
            }
            else if(direction == 3) {// if going left
                // move position size pixels up of previous
                y -= size;
            }
            direction = (direction+1)%4; // change direction for turn
        }
        else if (map_data[i] == 2) { //left turn
            if (direction == 0) { //if going up
                // move position size pixels left of previous
                x -= size;
            }
            else if(direction == 1) { //if going right
                // move position size pixels up of previous
                y -= size;
            }
            else if(direction == 2) { //if going down
                // move position size pixels right of previous
                x += size;
            }
            else if(direction == 3) { //if going left
                // move position size pixels down of previous
                y += size;
            }
            direction = (direction-1)%4; // change direction for turn
        }
    }

    return lines;
}

int main(int argc,char** argv) {
    int* length = NULL;
    std::string filename = argv[1]; //make filename into string
    int* map_data =  readData(filename, length); //get the array of map data

    int* dimensions = NULL;
    dimensions = getDimensions(map_data, length); //get the dimensions of the map
    int width = 0;
    int height = 0;
    dimensions[0] = height; //get the height of the room in terms of "steps"
    dimensions[3] = width;  //get the width of the room in terms of "steps"
    //each step is one rotation of the robot's wheels
    //we are using the left dimension for width as we start on the right side

    int size; //declare the variable for size of each segment
    if (height>80 || width>80) { //if more than 80 segments in any direction
        size = 5; //make segments smaller to fit
    }
    if (height>160 || width>160) { //if more than 160 segments in any direction
        size = 3; //make segments smaller to fit
    }
    if (height>300 || width> 300) { //if more than 300 segments in any direction
        size = 2; //make segments smaller
    }

    VertexArray lines = makeLines(map_data, length, size);

    RenderWindow window(VideoMode(1000,1000), "window");

    while(window.isOpen()) {
        window.clear()      //clear anything from the window
        window.draw(lines); //draw our lines to the window
        window.display();   //display the lines to the window

        Event event;
        while(window.pollEvent(event)) { //check for events in the window
            if (event.type == Closed) {
                window.close(); // if the user closes the window, close it
            }
        }
    }

    //delete all heap arrays free up memory
    delete[] length;
    delete[] map_data;
    delete[] dimensions;


    return 0;
}
