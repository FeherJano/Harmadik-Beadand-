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
    int& switch_count;
    bool& exit;
    bool& game;
    std::vector<Button*> buttons;

public:
    Menu(Point pos_, Size size_, bool& exit_, bool& game_, int& switch_count_);

    void draw() override;

    void do_logic();

    void handle_event(const genv::event& evt);
};


#endif
