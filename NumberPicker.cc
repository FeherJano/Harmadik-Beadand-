#include "NumberPicker.hh"
#include "graphics.hpp"
#include "Widget.hh"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace genv;

NumberPicker::NumberPicker(Point a, Size b, int border_min, int border_max, bool selected) : Widget(a, b) {
    number_min = border_min;
    number_max = border_max;
    selected_e = selected;
}

NumberPicker::NumberPicker(Point a, Size b, int border_min, int border_max) : Widget(a, b) {
    number_min = border_min;
    number_max = border_max;
    selected_e = true;
}

int NumberPicker::get_number(){
    return number;
}

void NumberPicker::set_number(int new_number){
    number = new_number;
}


void NumberPicker::draw(){
    Size size = get_size();
    Point pos = get_pos();
    string szam = to_string(number);
    int szam_w = gout.twidth(szam);
    int szam_h = gout.cascent();
    int mid_h = pos.y + size.h/4 + (size.h/2 + szam_h)/2;

    if(selected_e == true){
        if(pos.x >= 5 && pos.y >= 5) {
            gout << move_to(pos.x-5, pos.y-5)
                << color(114,178,17)
                << box(size.w+10, size.h+10);
        }
    }

    gout << move_to(pos.x,pos.y)
        << color(250,235,215)
        << box(size.w,size.h);
    gout << move_to(pos.x, pos.y)
        << color(169,169,169)
        << box(size.w/4,size.h)
        << move_to(pos.x + size.w*3/4, pos.y)
        << box(size.w/4,size.h);
    gout << move_to(pos.x + size.w/8, mid_h)
        << color(0,0,0)
        << text('-')
        << move_to(pos.x + size.w*7/8, mid_h)
        << text('+');
    gout << move_to(pos.x + size.w/4 + (size.w/2 - szam_w)/2, mid_h)
        << text(szam);
}

void NumberPicker::handle_event(const event& evt) {
    Size size = get_size();
    Point pos = get_pos();
    if(evt.type == ev_mouse && evt.button > 0 && selected_e == false){
        if(evt.pos_x > pos.x && evt.pos_x < pos.x + size.w && evt.pos_y > pos.y && evt.pos_y < pos.y + size.h){
            selected_e = true;
        }
    }

    if(evt.type == ev_mouse && evt.button > 0 && selected_e == true){
        if(evt.pos_x < pos.x || evt.pos_x > pos.x + size.w || evt.pos_y < pos.y || evt.pos_y > pos.y + size.h){
            selected_e = false;
        }
        if (evt.pos_x > pos.x && evt.pos_x < pos.x + size.w/4 && evt.pos_y > pos.y && evt.pos_y < pos.y + size.h && number > number_min) {
        number--;
        }
        if (evt.pos_x > pos.x + size.w*3/4 && evt.pos_x < pos.x + size.w && evt.pos_y > pos.y && evt.pos_y < pos.y + size.h && number < number_max) {
            number++;
        }
    }
    if(evt.type == ev_key && selected_e == true){
        if(evt.keycode == 's' && number > number_min) { //key_down == 81
            number--;
        }
        if(evt.keycode == 'w' && number < number_max) { // key_up == 82
            number++;
        }
        if(evt.keycode == 'd') { //key_pgdn == 69
            number -= 10;
            if(number < number_min){
                number = number_min;
            }
        }
        if(evt.keycode == 'e') {// key_pgup == 68
            number += 10;
            if(number > number_max){
                number = number_max;
            }
        }

    }

}
