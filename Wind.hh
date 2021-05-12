#ifndef WIND_HH
#define WIND_HH

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <math.h>
#include "graphics.hpp"
#include "Widget.hh"


class Wind: public Widget {
private:
    int canvas_x, canvas_y;
    int strength;
    std::vector<Point> clouds;

public:

    Wind(int canvas_x, int canvas_y, int clouds_number);

    void wind_refresh();

    void draw() override;

    void do_logic() override;

    int get_strength();
};


#endif
