#include "Widget.hh"

Widget::Widget(Point pos_, Size size_):
    pos(pos_),
    size(size_)
{}

Widget::~Widget() {
}

Point Widget::get_pos() const {
    return pos;
}

void Widget::set_pos(Point new_pos) {
    pos = new_pos;
}

Size Widget::get_size() const {
    return size;
}

void Widget::set_size(Size new_size) {
    size = new_size;
}

void Widget::do_logic(){}

void Widget::handle_event(const genv::event& evt){}
