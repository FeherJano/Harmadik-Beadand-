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
    Wind& wind;
    Tank* target;
    int health;
    int temp;

    void next_turn();


public:

    Tank(Point a, Size b, int angle_, bool turn_, bool& first_, Wind& wind, Tank* target_);

    void handle_event(const genv::event& evt) override;

    void set_target(Tank* tank);

    void do_logic() override;

    void draw() override;

    void barrel_draw();
};


#endif
