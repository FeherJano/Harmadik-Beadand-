#ifndef NUMBERPICKER_HH
#define NUMBERPICKER_HH

#include "graphics.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Widget.hh"

class NumberPicker: public Widget {
private:
    int number = 0;
    int number_min;
    int number_max;
    bool selected_e;

public:
    NumberPicker(Point a, Size b, int border_min, int border_max, bool selected);

    NumberPicker(Point a, Size b, int border_min, int border_max);

    int get_number();

    void set_number(int new_number);

    void draw() override;

    void handle_event(const genv::event& evt) override;
};


#endif
