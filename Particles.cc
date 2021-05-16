#include "graphics.hpp"
#include "Particles.hh"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace genv;

#define PI 3.14159265

Particles::Particles(Point a, Color color_, int bullet_type_) : Widget(a, {0,0}), color(color_){
    for(int i=0; i < number_of_particles ; i++){
        particles.push_back(rand() % 360);
    }
    range = bullet_type_*2;
}

void Particles::draw(){
    Point pos = get_pos();

    counter++;
    for(int j=1; j<5; j++){
        if(20 % 5 == 0){
            for(size_t i=0; i<particles.size(); i++){
                float x = cos((float)particles[i]*PI/180);
                float y = -sin((float)particles[i]*PI/180);

                //cout << x * j*100 << " " << y * j*100 << endl;

                gout << move_to(pos.x + x*j, pos.y + y*j)
                    << genv::color({color.r, color.g, color.b})
                    << line(x * j * range, y * j * range)
                    << genv::move(x * j * range, y * j * range)
                    << box(2,2);
            }
        }
    }
}

int Particles::get_counter() {
    return counter;
}
