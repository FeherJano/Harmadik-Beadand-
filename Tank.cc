#include "Tank.hh"
#include "graphics.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace genv;

#define PI 3.14159265

Tank::Tank(Point a, Size b, int angle_, bool turn_, bool& first_, bool& menu_game_, Wind& wind, Tank* target_, int gui_pos, int long_gui_pos) : Widget(a, b, false),
        first(first_), menu_game(menu_game_), wind(wind), target(target_),
        bullet_choice(MultipleChoice({long_gui_pos, 0}, {350, 60}, {"Artillery Gun(dmg:5)" ,"Basic Shot(dmg:2)", "Mortar(dmg:1)"})),
        angle_picker(NumberPicker({gui_pos, 60}, {100, 40}, "Angle", 'w', 's', 5, 10, 170)),
        power_picker(NumberPicker({gui_pos, 100}, {100, 40}, "Power", 'e', 'q', 1, 1, 5)){

    turn = turn_;
    tube_angle = angle_;
    gui_pos_x = gui_pos;

    angle_picker.set_number(tube_angle);
    power_picker.set_number(power);
    bullet_choice.set_selected_index(bullet_type);
}

void Tank::barrel_draw(){
    Point pos = get_pos();
    gout << move_to(pos.x+12, pos.y)
        << color(139,69,19);
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            gout << move_to(pos.x+12+i, pos.y+j)
                 << line(cos((float)tube_angle*PI/180) * 20, -sin((float)tube_angle*PI/180) * 20);
        }
    }
}

void Tank::Hp_draw(int pos_y){
    gout << move_to(gui_pos_x, pos_y)
        << color(165,42,42)
        << box(100, 30);
    int filler=5;
    int pts = 13;
    for(int i=0; i< health ;i++){
        gout << move_to(gui_pos_x + 5+i*filler*1.2 + i*pts ,pos_y+filler)
            <<color(0,255,0)
            <<box(pts,20);
    }
}

void Tank::draw(){
    Size size = get_size();
    Point pos = get_pos();
    if(turn == first){
        gout << move_to(pos.x-2, pos.y-2)
            << color(255,255,255)
            << box(size.w+4,size.h+4);
    }
    gout << move_to(pos.x, pos.y)
        << color(139,69,19)
        << box(size.w,size.h);
    barrel_draw();
    if(bullet != nullptr) {
        bullet->draw();
    }
    if(particles != nullptr) {
        particles->draw();
    }

    angle_picker.draw();
    power_picker.draw();
    bullet_choice.draw();
    Hp_draw(140);
}

void Tank::set_target(Tank* target_){
    target = target_;
}

int Tank::get_health(){
    return health;
}
void Tank::dmg_health(int dmg){
    health -= dmg;
}

int Tank::bullet_dmg(){
    if(bullet_type == 0){
        return 5;
    }
    else if(bullet_type == 1){
        return 2;
    }
    else if(bullet_type == 2){
        return 1;
    }
}

void Tank::next_turn(){
    delete bullet;
    bullet = nullptr;

    if(first){
        first = false;
    }
    else{
        first = true;
    }
    wind.wind_refresh();
}

void Tank::do_logic() {
    tube_angle = angle_picker.get_number();
    power = power_picker.get_number();
    bullet_type = bullet_choice.get_selected_index();

    if(bullet != nullptr) {
        bullet->do_logic();
        Point p = {bullet->get_pos().x, bullet->get_pos().y};
        //cout << bullets[i]->get_pos().y << endl;
        if(bullet->get_velo().y > 0 && p.x >= target->get_pos().x- bullet_type*10 && p.x <= target->get_pos().x+ bullet_type*10 +target->get_size().w
           && p.y >= target->get_pos().y-5 && p.y <= target->get_pos().y+5+target->get_size().h){

            target->dmg_health(bullet_dmg());

            if(target->get_health() <= 0){
                menu_game = true;
            }
            if(particles == nullptr){
                particles = new Particles(bullet->get_pos(), {255,255,0}, bullet_type);
            }
            next_turn();
        }
        else if(p.y >= 700 || p.x < 10 || p.x > 950){
            if(particles == nullptr){
                particles = new Particles(bullet->get_pos(), {255,0,0}, bullet_type);
            }
            next_turn();
        }
    }
    if(particles != nullptr){
        if(particles->get_counter() > 20){
            delete particles;
            particles = nullptr;
        }
    }
}

void Tank::handle_event(const event& evt) {
    Size size = get_size();
    Point pos = get_pos();

    if(turn == first){
        angle_picker.handle_event(evt);
        power_picker.handle_event(evt);
        bullet_choice.handle_event(evt);

        if(evt.type == ev_key && evt.keycode == key_enter && bullet == nullptr){
            bullet = new Bullet({pos.x + size.w/3, pos.y}, tube_angle, power, wind.get_strength() , bullet_type);
        }

        if(evt.type == ev_key && evt.keycode == 'w' && tube_angle < 170){
            tube_angle += 5;
            angle_picker.set_number(tube_angle);
        }
        if(evt.type == ev_key && evt.keycode == 's' && tube_angle > 10){
            tube_angle -= 5;
            angle_picker.set_number(tube_angle);
        }

        if(evt.type == ev_key && evt.keycode == 'e' && power < 5){
            power += 1;
            power_picker.set_number(power);
        }
        if(evt.type == ev_key && evt.keycode == 'q' && power > 1){
            power -= 1;
            power_picker.set_number(power);
        }

        if(evt.type == ev_key && (evt.keycode == '1' || evt.keycode == '2' || evt.keycode == '3')){
            bullet_type = evt.keycode - 48 -1; // A bullet_type-ot egy szorzó ként használom így -1 -el kapok egy nulla szorzót is.
            bullet_choice.set_selected_index(bullet_type);
        }

        if(evt.type == ev_key && evt.keycode == 'd'){
            if(pos.x + size.w < 955){
                if(target->get_pos().x < pos.x){
                    set_pos({pos.x+5, pos.y});
                }
                else if( target->get_pos().x > pos.x + size.w + 5){
                    set_pos({pos.x+5, pos.y});
                }
            }
            if(target->get_pos().x + target->get_size().w < 960 && target->get_pos().x <= pos.x + size.w + 5){
                if(target->get_pos().x > pos.x){
                    target->set_pos({target->get_pos().x + 1, target->get_pos().y});
                    set_pos({pos.x + 1, pos.y});
                }
            }
        }

        if(evt.type == ev_key && evt.keycode == 'a'){
            if(pos.x > 5){
                if(target->get_pos().x > pos.x){
                    set_pos({pos.x-5, pos.y});
                }
                else if(target->get_pos().x < pos.x - size.w - 5){
                    set_pos({pos.x-5, pos.y});
                }
            }

            if(target->get_pos().x > 0 && target->get_pos().x >= pos.x - size.w - 5){
                if(target->get_pos().x < pos.x){
                    target->set_pos({target->get_pos().x - 1, target->get_pos().y});
                    set_pos({pos.x - 1, pos.y});
                }
            }
        }
    }
}

void Tank::reset(int angle_, int health_){
    tube_angle = angle_;
    health = health_;
}
