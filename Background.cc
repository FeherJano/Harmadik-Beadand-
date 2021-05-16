#include "Background.hh"
#include "graphics.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace genv;

Background::Background(Point a, Size b): Widget(a, b, false){};

void Background::draw(){
    Size size = get_size();
    Point pos = get_pos();

    gout << move_to(pos.x,pos.y)
        << color(135, 206, 235)
        << box(size.w,size.h);
    gout << move_to(pos.x, pos.y+(size.h - (size.h/36) + 5))
        << color(126,200,80)
        <<box(size.w, size.h/36 - 5);
}


