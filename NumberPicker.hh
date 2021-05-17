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
    std::string name;
    int number;
    int step;
    char plus_inp;
    char minus_inp;
    int number_min;
    int number_max;
    bool selected_e;

public:
    NumberPicker(Point a, Size b, std::string name_, char plus_inp_, char minus_inp_, int step_, int border_min, int border_max, bool selected);

    NumberPicker(Point a, Size b, std::string name_, char plus_inp_, char minus_inp_, int step_, int border_min, int border_max);

    int get_number();

    void set_number(int new_number);

    void draw() override;

    void handle_event(const genv::event& evt) override;
};


#endif
