#include "Widget.hh"


Widget::Widget(Point pos_, Size size_, bool active_):
    pos(pos_),
    size(size_),
    active(active_)
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

bool Widget::get_active() const {
    return active;
}

void Widget::set_active(bool is_active) {
    active = is_active;
}

void Widget::do_logic(){}

void Widget::handle_event(const genv::event& evt){}
