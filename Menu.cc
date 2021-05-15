#include "Menu.hh"
#include "graphics.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace genv;

Menu::Menu(Point a, Size b, bool& exit_, bool& game_): Widget(a, b, true), exit(exit_), game(game_) {
    widgets.push_back(new Button({ 450, 400 }, { 60, 40 }, "Quit", [&](event evt) { exit = true;}));
    widgets.push_back(new Button({ 440, 340 }, { 80, 40 }, "START", [&](event evt) {
        game = true;
    }));
};

void Menu::draw(){
    Size size = get_size();
    Point pos = get_pos();

    gout << move_to(pos.x,pos.y)
        << color(250,235,215)
        << box(size.w,size.h);

    for(size_t i=0; i<widgets.size();i++){
        widgets[i]->draw();
    }
}


void Menu::handle_event(const event& evt) {

    for(size_t i=0; i<widgets.size();i++){
        widgets[i]->handle_event(evt);
    }
}

