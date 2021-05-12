#ifndef BULLET_HH
#define BULLET_HH

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <math.h>
#include "graphics.hpp"
#include "Widget.hh"

struct Velocity{
    float x;
    float y;
};


class Bullet: public Widget {
private:
    float pos_x;
    float pos_y;
    Velocity velo;
    int angle;
    int type;
    float power;
    static constexpr float GRAVITY = 0.008;
    float wind;

public:

    Bullet(Point a, int angle_, float power, float wind_, int type_);

    void draw() override;

    void do_logic() override;

    Velocity get_velo();
};


#endif
