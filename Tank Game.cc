#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "graphics.hpp"
#include "MultipleChoice.hh"
#include "NumberPicker.hh"
#include "Menu.hh"
#include "Tank.hh"

using namespace genv;
using namespace std;

void clr_scr(int x, int y){
    gout << move_to(0,0)
        << color(0,0,0)
        << box (x,y);
}


int main() {
    Point canvas_ = {960, 720};
    bool exit = false;
    bool start_game = false;

    gout.open(canvas_.x, canvas_.y);

    vector<Widget*> widgets;

    Wind* wind = new Wind(960, 720, 15);

    bool first = true;
    Tank* tank1 = new Tank({100,700}, {30,10}, 45, true, first, *wind, nullptr);
    Tank* tank2 = new Tank({840,700}, {30,10}, 135, false, first, *wind, nullptr);

    tank1->set_target(tank2);
    tank2->set_target(tank1);

    widgets.push_back(new Menu({0, 0}, {canvas_.x, canvas_.y}, exit, start_game));
    widgets.push_back(wind);
    widgets.push_back(tank1);
    widgets.push_back(tank2);

    //widgets.push_back(new NumberPicker({0, 0}, {200, 100}, -64, 64, false));

    for(size_t i=0; i<widgets.size();i++){
        if(widgets[i]->get_active()){
            widgets[i]->draw();
        }
    }
    gout << refresh;

    event evt;
    while (!exit) {
        if (gin >> evt){
            if (evt.type == ev_key && evt.keycode == key_escape) {
            exit = true;
            }
        }

        if(start_game){
            for(size_t i=0; i < widgets.size(); i++){
                widgets[i]->set_active(!widgets[i]->get_active());
            }
            start_game = false;
        }

        for(size_t i=0; i < widgets.size(); i++){
            if(widgets[i]->get_active()){
                widgets[i]->handle_event(evt);
                widgets[i]->do_logic();
            }
        }

        clr_scr(canvas_.x, canvas_.y);
        for(size_t i=0; i<widgets.size();i++){
            if(widgets[i]->get_active()){
                widgets[i]->draw();
            }
        }

        gout<<refresh;

    gin.timer(10);
    }


    return 0;
}
