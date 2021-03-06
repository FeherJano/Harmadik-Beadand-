#ifndef PARTICLES_HH
#define PARTICLES_HH

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <math.h>
#include "graphics.hpp"
#include "Widget.hh"


class Particles: public Widget {
private:
    std::vector<int> particles;
    Color color;
    int counter = 0;
    float range = 0;

    int number_of_particles = 50;

public:

    Particles(Point a, Color color_, int bullet_type_);

    void draw() override;

    int get_counter();
};


#endif
