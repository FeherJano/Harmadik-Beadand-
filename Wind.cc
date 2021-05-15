#include "Wind.hh"
#include "graphics.hpp"
#include "Widget.hh"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace genv;

Wind::Wind(int canvas_x, int canvas_y, int clouds_number) : canvas_x(canvas_x), canvas_y(canvas_y){
    Point cloud;
    set_active(false);
    for(int i=0; i<clouds_number; i++){
        cloud.x = rand() % canvas_x;
        cloud.y = rand() % canvas_y/2;
        clouds.push_back(cloud);
    }
    wind_refresh();
};

void Wind::draw(){
    for(size_t i=0; i<clouds.size(); i++){
        gout << move_to(clouds[i].x, clouds[i].y)
            << color(255,255,255)
            << box(120,40);
    }
}

void Wind::do_logic() {
    for(size_t i=0; i<clouds.size(); i++){
        if(0 > clouds[i].x){
            clouds[i].x = canvas_x;
            clouds[i].y = rand() % canvas_y/3;
        }
        else if(960 < clouds[i].x){
            clouds[i].x = 0;
            clouds[i].y = rand() % canvas_y/3;
        }

        clouds[i].x += strength;
    }
}

void Wind::wind_refresh() {
    strength = (rand() % 5) - 2;
    //strength = 0;
}

int Wind::get_strength(){
    return strength;
}
