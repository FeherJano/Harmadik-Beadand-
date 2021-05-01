#include "Scroll.hh"
#include "graphics.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace genv;

TextScroller::TextScroller(Point a, Size b, const string& _text): Widget(a, b) {
    OriginalText = _text + ' ';
    text_h = gout.cascent() + gout.cdescent();
    active_lines = b.h / text_h;
    text_break();
};

TextScroller::TextScroller(Point a, Size b, const vector<string> lines_vec){
    text_h = gout.cascent() + gout.cdescent();
    active_lines = b.h / text_h;
    lines = lines_vec;
};

void TextScroller::text_break() {
    Size size = get_size();
    Point pos = get_pos();
    string temporary;
    int temp_i=0;
    bool text_end = false;
    for(size_t i=1; i < OriginalText.length(); i++) {
        if(OriginalText[i] == ' ') {
            if(gout.twidth(OriginalText.substr(0,i)) < size.w-20) {
                temporary = OriginalText.substr(0,i);
                temp_i = i;
            } else {
                temporary += "\n";
                lines.push_back(temporary);
                temporary.clear();
                OriginalText.erase(OriginalText.begin(),OriginalText.begin()+i+1-(i - temp_i));
                //OriginalText.erase(OriginalText.begin(),OriginalText.begin() + i);
                i=0;
            }
        }
        if(gout.twidth(OriginalText) < size.w-20) {
            lines.push_back(OriginalText.substr(0,OriginalText.length()));  //lines.push_back(OriginalText)
            OriginalText.clear();
        }
    }
}

void TextScroller::draw(){
    Size size = get_size();
    Point pos = get_pos();

    gout << move_to(pos.x, pos.y)
        << color(250,235,215)
        << box(size.w, size.h);
    gout << move_to(pos.x+5,pos.y + text_h)
        << color(0,0,0);

    for(size_t i=active_pos; i< active_lines + active_pos; i++){
        gout << text(lines[i]);
        //cout << i << ": " << lines[i] << endl;
    }
}


void TextScroller::handle_event(const event& evt) {
    Size size = get_size();
    Point pos = get_pos();
    if (evt.button == btn_wheeldown && active_pos <= lines.size() - active_lines) {
        if(lines.size()*text_h > size.h){
            active_pos++;
        }
    }
    if (evt.button == btn_wheelup && active_pos > 0) {
        active_pos--;
    }
}
