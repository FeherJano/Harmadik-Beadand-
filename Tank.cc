#include "Tank.hh"
#include "graphics.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace genv;


Tank::Tank(Point a, Size b) : Widget(a, b){

}

void Tank::draw(){
    Size size = get_size();
    Point pos = get_pos();
    gout << move_to(pos.x, pos.y)
        << color(100,255,100)
        //<< line(velo.x, velo.y)
        << box(size.w,size.h);
    if(bullet != nullptr) {
        bullet->draw();
    }


    gout << move_to(100,300)
        << color(250,250,250)
        << text("power: " + to_string(power) + "\n" + "angle: " + to_string(tube_angle));

}

void Tank::do_logic() {
    if(bullet != nullptr) {
        bullet->do_logic();
        //cout << bullets[i]->get_pos().y << endl;
        if(bullet->get_pos().y > 700){
            delete bullet;
            bullet = nullptr;
        }
    }

}

void Tank::handle_event(const event& evt) {
    Size size = get_size();
    Point pos = get_pos();

    if(evt.type == ev_key && evt.keycode == key_enter){
        bullet = new Bullet({pos.x + size.w/3, pos.y}, tube_angle, power, 1);
    }

    if(evt.type == ev_key && evt.keycode == 'w' && tube_angle < 180){
        tube_angle += 1;
    }
    if(evt.type == ev_key && evt.keycode == 's' && tube_angle > 0){
        tube_angle -= 1;
    }

    if(evt.type == ev_key && evt.keycode == 'e' && power < 5){
        power += 1;
    }
    if(evt.type == ev_key && evt.keycode == 'q' && power > 1){
        power -= 1;
    }

    if(evt.type == ev_key && evt.keycode == 'd'){
        pos.x +=1;
        set_pos(pos);
    }

    if(evt.type == ev_key && evt.keycode == 'd'){
        pos.x -=1;
        set_pos(pos);
    }
}
