#ifndef SCROLL_HH
#define SCROLL_HH

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Widget.hh"

class TextScroller: public Widget{
private:
    std::vector<std::string> lines;
    std::string OriginalText;
    int active_pos=0;
    int active_lines;
    int text_h;

    void text_break();

public:
    TextScroller(Point a, Size b, const std::string& _text);
    TextScroller(Point a, Size b, const std::vector<std::string> lines_vec);

    void draw() override;

    void handle_event(const genv::event& evt) override;
};


#endif
