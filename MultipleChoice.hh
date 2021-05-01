#ifndef MULTIPLECHOICE_HH
#define MULTIPLECHOICE_HH

#include "graphics.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Widget.hh"

class MultipleChoice: public Widget {
private:
    std::vector<std::string> choices;
    int active_choice = 0;
    bool select;
    int max_w_text = 0;
    int text_h = (genv::gout.cascent() + genv::gout.cdescent());
    int visible_lines;
    int active_pos = 0;
    bool selected;

public:
    MultipleChoice(Point pos_, Size size_, std::vector<std::string> input_choices);
    MultipleChoice(Point pos_, std::vector<std::string> input_choices);

    void add_choice(std::string a_choice);

    void del_choice(int index);

    int get_selected_index();

    std::string get_text();

    void draw() override;

    void handle_event(const genv::event& evt);
};


#endif
