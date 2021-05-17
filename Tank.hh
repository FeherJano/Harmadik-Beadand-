#ifndef TANK_HH
#define TANK_HH

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <math.h>
#include "graphics.hpp"
#include "Bullet.hh"
#include "Particles.hh"
#include "Wind.hh"
#include "NumberPicker.hh"
#include "MultipleChoice.hh"


class Tank: public Widget {
private:
    int tube_angle = 45;
    int power = 3;
    Bullet* bullet = nullptr;
    int bullet_type = 1;
    Particles* particles = nullptr;
    bool turn;
    bool& first;
    bool& menu_game;
    Wind& wind;
    Tank* target;
    int health = 5;
    int gui_pos_x;

    MultipleChoice bullet_choice;
    NumberPicker angle_picker;
    NumberPicker power_picker;

    void next_turn();


public:

    Tank(Point a, Size b, int angle_, bool turn_, bool& first_, bool& menu_game_, Wind& wind, Tank* target_, int gui_pos, int long_gui_pos);

    void handle_event(const genv::event& evt) override;

    void set_target(Tank* tank);

    int get_health();
    void dmg_health(int dmg); //Nem beállít, hanem kivon.

    int bullet_dmg();

    void do_logic() override;

    void draw() override;

    void barrel_draw();

    void Hp_draw(int pos_y);

    void reset(int angle_, int health_);
};


#endif
