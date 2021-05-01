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


class Tank: public Widget {
private:
    int tube_angle = 45;
    int power = 3;
    Bullet* bullet;

public:

    Tank(Point a, Size b);

    void handle_event(const genv::event& evt) override;

    void do_logic() override;

    void draw() override;
};


#endif
