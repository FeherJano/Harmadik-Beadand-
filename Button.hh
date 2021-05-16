#ifndef BUTTON_HH
#define BUTTON_HH

#include "graphics.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include "Widget.hh"

class Button: public Widget {
private:
    Size size = get_size();
    Point pos = get_pos();
    std::string name;
    std::function<void(genv::event)> action;

public:
    Button(Point a, Size b, std::string name, std::function<void(genv::event)> do_action);

    void draw() override;

    void set_name(std::string new_name);

    void handle_event(const genv::event& evt) override;

};


#endif
