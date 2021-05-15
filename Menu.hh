#ifndef MENU_HH
#define MENU_HH

#include "graphics.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Widget.hh"
#include "Button.hh"

class Menu: public Widget {
private:
    bool& exit;
    bool& game;
    std::vector<Widget*> widgets;

public:
    Menu(Point pos_, Size size_, bool& exit_, bool& game_);

    void draw() override;

    void handle_event(const genv::event& evt);
};


#endif
