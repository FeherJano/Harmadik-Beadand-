#ifndef BACKGROUND_HH
#define BACKGROUND_HH

#include "graphics.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Widget.hh"
#include "Button.hh"

class Background: public Widget {
public:
    Background(Point pos_, Size size_);

    void draw() override;
};


#endif
