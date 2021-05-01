#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "graphics.hpp"

using namespace genv;


struct Color {
    int r;
    int g;
    int b;
};

struct Image {
    int width;
    int height;
    std::vector<Color> pixels;

    Image(std::string filename) {
        std::ifstream file(filename);

        std::string line;
        std::getline(file, line);

        int w = 0;
        std::stringstream ss(line);
        ss >> w;

        std::vector<Color> pxs;

        while (std::getline(file, line)) {
            // ss = std::stringstream(line);
            ss.clear();
            ss.str(line);

            for (int i = 0; i < w; i++) {
                Color px;
                ss >> px.r >> px.g >> px.b;
                pxs.push_back(px);
            }
        }

        width = w;
        height = pxs.size() / width;
        pixels = pxs;
    }

    Color &at_xy(int x, int y) {
        int index = y * width + x;

        return pixels[index];
    }

    Color &at_rc(int r, int c) {
        return at_xy(c, r);
    }

    void render() {
        for (int r = 0; r < height; ++r) {
            for (int c = 0; c < width; ++c) {
                Color px = at_rc(r, c);

                gout << move_to(c, r)
                     << color(px.r, px.g, px.b)
                     << dot;
            }
        }
    }
};

int main() {
    Image image("flower1.kep");
    std::cout << "w = " << image.width << ", h = " << image.height << "\n";

    //      0.  1.  2.  3.  4.
    //    +---+---+---+---+---+
    // 0. |  0|  1|rgb|rgb|  4|
    // 1. |  5|rgb|rgb|rgb|  9|  r * w + c = 2 * 5 + 3
    // 2. | 10|rgb|rgb| 13| 14|  r-edik sor c-edik oszlopat
    // 3. |rgb|rgb|rgb|rgb|rgb|

    // Feladat: kep megjelenitese graphics libbel
    gout.open(image.width, image.height);

    image.render();
    gout << refresh;

    event evt;
    while (gin >> evt) {
        if (evt.type == ev_key && evt.keycode == 'q') {
            break;
        }
    }
}
