#include "MultipleChoice.hh"
#include "graphics.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace genv;

MultipleChoice::MultipleChoice(Point a,vector<string> input_choices): Widget(a, {0,0}) {
    choices = input_choices;
    select = false;
    max_w_text = gout.twidth(choices[0]);
    for(size_t i=0; i < choices.size(); i++){
        if(gout.twidth(choices[i]) > max_w_text){
            max_w_text = gout.twidth(choices[i]);
        }
    }
    Size size;
    int choices_h = text_h * choices.size();
    size.h = choices_h +10;
    size.w = max_w_text * 2 + 30;
    set_size({size.w, size.h});
    visible_lines = choices.size();
    selected = false;
};
MultipleChoice::MultipleChoice(Point a, Size b, vector<string> input_choices): Widget(a, b) {
    choices = input_choices;
    select = false;
    for(size_t i=0; i < choices.size(); i++){
        if(gout.twidth(choices[i]) > max_w_text){
            max_w_text = gout.twidth(choices[i]);
        }
    }
    visible_lines = b.h / text_h;
    selected = false;
    //scroller.set_size({max_w_text+10,b.h});
};


void MultipleChoice::draw(){
    Size size = get_size();
    Point pos = get_pos();

    if(selected == true){
        gout << move_to(pos.x-5, pos.y-5)
            << color(114,178,17)
            << box(size.w+10, size.h+10);
    }

    gout << move_to(pos.x,pos.y)
        << color(250,235,215)
        << box(size.w,size.h);
    gout << move_to(pos.x+10, pos.y + text_h)
        << color(0,0,0);

    if(visible_lines > choices.size()){
        visible_lines = choices.size();
    }

    for(size_t i=active_pos; i< visible_lines + active_pos; i++){
        if(active_choice == i) {
            gout << color(0,0,255);
        }
        gout << text(choices[i] + "\n")
            << color(0,0,0);
        //cout << i << ": " << choices[i] << endl;
    }


    if(select){
        //cout << pos.x + max_w_text + 20 << " " << pos.y + size.h/2 + gout.cascent()/2 << endl;
        gout << move_to(pos.x + max_w_text + 20 , pos.y + size.h/2 + gout.cascent()/2 )
            <<color(0,0,0)
            <<text(choices[active_choice]);
    }
}

int MultipleChoice::get_selected_index(){
    return active_choice;
}

string MultipleChoice::get_text(){
    return choices[active_choice];
}

void MultipleChoice::add_choice(string a_choice){
    MultipleChoice::choices.push_back(a_choice);
}

void MultipleChoice::del_choice(int index){
    MultipleChoice::choices.erase(choices.begin() + index);
}

void MultipleChoice::handle_event(const event& evt) {
    Size size = get_size();
    Point pos = get_pos();
    int choices_h = text_h * choices.size();

    if(evt.type == ev_mouse && selected == false){
        if(evt.pos_x > pos.x && evt.pos_x < pos.x + size.w && evt.pos_y > pos.y && evt.pos_y < pos.y + size.h){
            selected = true;
        }
    }

    if(evt.type == ev_mouse && evt.button >= 0 && selected == true && evt.button != btn_wheelup && evt.button != btn_wheeldown){
        if(evt.pos_x < pos.x || evt.pos_x > pos.x + size.w || evt.pos_y < pos.y || evt.pos_y > pos.y + size.h){
            selected = false;
        }
    }
    if(selected){
        if(evt.type == ev_mouse && evt.button > 0){
            if (evt.pos_x > pos.x && evt.pos_x < pos.x + max_w_text+15 && evt.pos_y > pos.y+1 && evt.pos_y < pos.y  + choices_h){
                active_choice = ((evt.pos_y - pos.y) / text_h) + active_pos;
                select = true;
            }
        }

        if (evt.button == btn_wheeldown && active_pos < choices.size() - visible_lines) {
            if(choices.size()*text_h > size.h){
                active_pos++;
                //cout<< evt.pos_x << "," << evt.pos_y  << " " << evt.button << endl;
            }
        }
        if (evt.button == btn_wheelup && active_pos > 0) {
            active_pos--;
            //cout<< evt.pos_x << "," << evt.pos_y <<  " " << evt.button << endl;
        }
    }
}

