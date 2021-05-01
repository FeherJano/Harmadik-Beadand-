#include "Bullet.hh"
#include "graphics.hpp"
#include "Widget.hh"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace genv;

#define PI 3.14159265

Bullet::Bullet(Point a, int angle_, float power_, int type_) : Widget(a, {5,5}){
    angle = angle_;
    type = type_;
    pos_x = a.x;
    pos_y = a.y;
    power = power_/1.7;
    velo.x = cos(angle_*PI/180) * power;
    velo.y = -sin(angle_*PI/180) * power;

}

void Bullet::draw(){
    Size size = get_size();
    Point pos = get_pos();
    gout << move_to(pos.x, pos.y)
        << color(0,255,0)
        //<< line(velo.x, velo.y)
        << box(size.w,size.h);

}

void Bullet::do_logic() {
    pos_x += velo.x;
    pos_y += velo.y;

    set_pos({pos_x, pos_y});
    velo.y += GRAVITY;

}
