#include "graphics.hpp"
#include "TextLabel.hh"

using namespace genv;


TextLabel::TextLabel(std::string text_) {
    set_text(text_);
}

std::string TextLabel::get_text() {
    return text;
}

void TextLabel::set_text(std::string new_text) {
    text = new_text;
    int text_height = gout.cascent() + gout.cdescent();
    int text_width = gout.twidth(text);

    set_size(Size { text_width, text_height });
}

void TextLabel::draw() {
    Point pos = get_pos();

    gout << move_to(pos.x, pos.y)
         << color(255, 255, 255)
         << genv::text(text);
}
