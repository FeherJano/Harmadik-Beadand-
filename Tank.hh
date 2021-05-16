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


class Tank: public Widget {
private:
    int tube_angle = 45;
    int power = 3;
    Bullet* bullet = nullptr;
    Particles* particles = nullptr;
    bool turn;
    bool& first;
    bool& menu_game;
    Wind& wind;
    Tank* target;
    int health = 3;
    int temp;

    void next_turn();


public:

    Tank(Point a, Size b, int angle_, bool turn_, bool& first_, bool& menu_game_, Wind& wind, Tank* target_);

    void handle_event(const genv::event& evt) override;

    void set_target(Tank* tank);

    int get_health();
    void dmg_health(int dmg); //Nem beállít, hanem kivon.

    void do_logic() override;

    void draw() override;

    void barrel_draw();

    void reset(int angle_, int health_);
};


#endif
