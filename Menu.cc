#include "Menu.hh"
#include "graphics.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace genv;

Menu::Menu(Point a, Size b, bool& exit_, bool& game_, int& switch_count_, bool& player1_turn_): Widget(a, b, true),
        exit(exit_), game(game_), switch_count(switch_count_), player1_turn(player1_turn_) {
    buttons.push_back(new Button({ 450, 400 }, { 60, 40 }, "Quit", [&](event evt) { exit = true;}));
    buttons.push_back(new Button({ 440, 340 }, { 80, 40 }, "START", [&](event evt) {
        game = true;
    }));
};

void Menu::draw(){
    Size size = get_size();
    Point pos = get_pos();

    gout << move_to(pos.x,pos.y)
        << color(100,100,100)
        << box(size.w,size.h)
        << move_to(pos.x+5,pos.y+5)
        << color(250,235,215)
        << box(size.w-10,size.h-10);

    title_pos = {pos.x + size.w/2 - gout.twidth(title)/2, pos.y + size.h/2 - 50};
    gout << move_to({title_pos.x, title_pos.y})
        << color(0,0,0)
        << text(title);

    for(size_t i=0; i<buttons.size();i++){
        buttons[i]->draw();
    }
    if(switch_count == 0){
        string guide = "Mivel a jatek korokre osztott, az egyszeruseg\n"
        " kedveert mindket jatekos billentyu kiosztasa azonos.\n"
        " Mozgas balra az 'a', jobbra pedig 'd' gomb. Az agyucso\n"
        " szogenek novelese a 'w', csokkentese az 's' gomb. A loves\n"
        " erejenek csokkentese a 'q', novelese az 'e' gomb. A kulonbozo\n"
        " tipusu lovedekeket az 1-3 gombokkal lehet kivalasztani.\n"
        " Mindezeket kattintassal is meg lehet adni a megfelelo ablakon.";
        gout << move_to(10,600)
            << text(guide);
    }
}

void Menu::do_logic() {
    if(game && switch_count > -1){
        set_pos({220, 200});
        set_size({520, 320});
        buttons[1]->set_name("Rematch");
        if(player1_turn){
            title = "Game Over, Player 1 won";
        }
        else{
            title = "Game Over, Player 2 won";
        }
    }
}

void Menu::handle_event(const event& evt) {

    for(size_t i=0; i<buttons.size();i++){
        buttons[i]->handle_event(evt);
    }
}

