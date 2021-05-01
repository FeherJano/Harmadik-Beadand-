#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "graphics.hpp"
#include "MultipleChoice.hh"
#include "Scroll.hh"
#include "NumberPicker.hh"
#include "Tank.hh"

using namespace genv;
using namespace std;

void clr_scr(int x, int y){
    gout << move_to(0,0)
        << color(0,0,0)
        << box (x,y);
}

int main() {
    gout.open(960, 720);
    //gout.load_font("LiberationSerif-Bold.ttf", 18, true);

    vector<Widget*> widgets;

/*
    widgets.push_back(new Bullet({0, 700}, 45, 1, 1));
    widgets.push_back(new Bullet({0, 700}, 45, 2, 1));
    widgets.push_back(new Bullet({0, 700}, 45, 3, 1));
    widgets.push_back(new Bullet({0, 700}, 45, 4, 1));
    widgets.push_back(new Bullet({0, 700}, 70, 5, 1));
*/

    widgets.push_back(new Tank({40,700}, {30,10}));

    widgets.push_back(new NumberPicker({0, 0}, {200, 100}, -64, 64, false));

    for(size_t i=0; i<widgets.size();i++){
        widgets[i]->draw();
    }
    gout << refresh;

    event evt;
    bool exit = false;
    while (!exit) {
        if (gin >> evt){
            if (evt.type == ev_key && evt.keycode == key_escape) {
            exit = true;
            }
        }

        for(size_t i=0; i < widgets.size(); i++){
            widgets[i]->handle_event(evt);
            widgets[i]->do_logic();
        }

        clr_scr(960,720);
        for(size_t i=0; i < widgets.size(); i++){
            widgets[i]->draw();
        }

        gout<<refresh;

    gin.timer(7);
    }


    return 0;
}
