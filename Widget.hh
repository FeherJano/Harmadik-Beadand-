#ifndef WIDGET_HH
#define WIDGET_HH

#include "graphics.hpp"

struct Color {
    int r,g,b;
};

struct Point {
    int x;
    int y;
};

struct Size {
    int w;
    int h;
};

class Widget {
public:
    Widget(Point pos_ = { 0, 0 }, Size size_ = { 0, 0 });
    virtual ~Widget();

    virtual void draw() = 0;

    virtual void do_logic();

    virtual void handle_event(const genv::event& evt);

    Point get_pos() const;
    void set_pos(Point new_pos);

    Size get_size() const;
    void set_size(Size new_size);


private:
    Point pos;
    Size size;
};

#endif
