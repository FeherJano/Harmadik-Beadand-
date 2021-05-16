#include "Bullet.hh"
#include "graphics.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace genv;

#define PI 3.14159265

Bullet::Bullet(Point a, int angle_, float power_, float wind_, int type_) : Widget(a, {5,5}){
    angle = angle_;
    type = type_;
    pos_x = a.x;
    pos_y = a.y;
    power = power_/1.7;
    velo.x = cos((float)angle_*PI/180) * power;
    velo.y = -sin((float)angle_*PI/180) * power;
    wind = wind_/3;
}

void Bullet::draw(){
    Size size = get_size();
    Point pos = get_pos();
    gout << move_to(pos.x, pos.y)
        << color(255,0,0)
        //<< line(velo.x, velo.y)
        << box(size.w,size.h);

}

void Bullet::do_logic() {
    pos_x += velo.x*4 + wind;
    pos_y += velo.y*4;

    set_pos({pos_x, pos_y});
    velo.y += GRAVITY*4;

}

Velocity Bullet::get_velo() {
    return velo;
}
