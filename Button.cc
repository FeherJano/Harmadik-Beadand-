#include "Button.hh"
#include "Widget.hh"
#include "graphics.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace genv;

Button::Button(Point a, Size b, string button_name, function<void(event)> do_action) : Widget(a, b), action(do_action) {
    name = button_name;
}

void Button::draw(){
    int name_w = gout.twidth(name);
    int name_h = gout.cascent();
    int mid_h = pos.y + size.h/4 + (size.h/2 + name_h)/2;

    //cout << name_h << ' ' << mid_h << endl;

    gout << move_to(pos.x,pos.y)
        << color(100,100,100)
        << box(size.w,size.h);
    gout << move_to(pos.x+2,pos.y+2)
        << color(200,185,165)
        << box(size.w-4,size.h-4);
    gout << move_to(pos.x + size.w/4 + (size.w/2 - name_w)/2, mid_h)
        << color(0,0,0)
        << text(name);
}

void Button::set_name(std::string new_name){
    name = new_name;
}

void Button::handle_event(const event& evt) {
    Size size = get_size();
    Point pos = get_pos();
    if(evt.type == ev_mouse && evt.button > 0){
        if (evt.pos_x > pos.x && evt.pos_x < pos.x + size.w && evt.pos_y > pos.y && evt.pos_y < pos.y + size.h) {
        action(evt);
        }
    }
}
