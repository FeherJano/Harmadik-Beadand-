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

Tank::Tank(Point a, Size b, int angle_, bool turn_, bool& first_, Wind& wind, Tank* target_) : Widget(a, b, false), first(first_), wind(wind), target(target_){
    turn = turn_;
    tube_angle = angle_;
}

void Tank::barrel_draw(){
    Point pos = get_pos();
    gout << move_to(pos.x+12, pos.y)
        << color(100,255,100);
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            gout << move_to(pos.x+12+i, pos.y+j)
                 << line(cos((float)tube_angle*PI/180) * 20, -sin((float)tube_angle*PI/180) * 20);
        }
    }
}

void Tank::draw(){
    Size size = get_size();
    Point pos = get_pos();
    gout << move_to(pos.x, pos.y)
        << color(100,255,100)
        //<< line(velo.x, velo.y)
        << box(size.w,size.h);
    barrel_draw();
    if(bullet != nullptr) {
        bullet->draw();
    }
    if(particles != nullptr) {
        particles->draw();
    }


    gout << move_to(pos.x,300)
        << color(250,0,0)
        << text("power: " + to_string(power) + "\n" + "angle: " + to_string(tube_angle));

}

void Tank::set_target(Tank* target_){
    target = target_;
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
    if(bullet != nullptr) {
        bullet->do_logic();
        Point p = {bullet->get_pos().x, bullet->get_pos().y};
        //cout << bullets[i]->get_pos().y << endl;
        if(bullet->get_velo().y > 0 && p.x >= target->get_pos().x-5 && p.x <= target->get_pos().x+5+target->get_size().w && p.y >= target->get_pos().y-5 && p.y <= target->get_pos().y+5+target->get_size().h){
            temp++;
            cout << temp << endl;
            if(particles == nullptr){
                particles = new Particles(bullet->get_pos(), {255,255,0});
            }
            next_turn();
        }
        else if(p.y >= 700){
            if(particles == nullptr){
                particles = new Particles(bullet->get_pos(), {255,0,0});
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
        if(evt.type == ev_key && evt.keycode == key_enter && bullet == nullptr){
            bullet = new Bullet({pos.x + size.w/3, pos.y}, tube_angle, power, wind.get_strength() , 1);
        }

        if(evt.type == ev_key && evt.keycode == 'w' && tube_angle < 170){
            tube_angle += 5;
        }
        if(evt.type == ev_key && evt.keycode == 's' && tube_angle > 10){
            tube_angle -= 5;
        }

        if(evt.type == ev_key && evt.keycode == 'e' && power < 5){
            power += 1;
        }
        if(evt.type == ev_key && evt.keycode == 'q' && power > 1){
            power -= 1;
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
