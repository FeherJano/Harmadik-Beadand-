#include <string>
#include "Widget.hh"


class TextLabel: public Widget {
public:
    TextLabel(std::string text_);

    std::string get_text();
    void set_text(std::string new_text);

    void draw() override;
private:
    std::string text;
};
