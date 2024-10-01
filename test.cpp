
// define this for iostream usage
#define CUSTOM_DEBUG

#include <GalGui/Button.hpp>
#include <GalGui/ComboBox.hpp>
#include <GalGui/CheckBox.hpp>
#include <GalGui/TextButton.hpp>
#include <GalGui/Label.hpp>
#include <GalGui/Slider.hpp>
#include <GalGui/LineEdit.hpp>
#include <GalGui/TextBox.hpp>
#include <GalGui/Dialog.hpp>

#include <GalGui/HorizontalLayout.hpp>
#include <GalGui/VerticalLayout.hpp>
#include <GalGui/Frame.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


#include <iomanip>

namespace GG = GalGui::Widget;

class myWidget : public GalGui::Widget::Frame
{
public:
    myWidget()
    {
        draw.setOutlineColor(sf::Color::Red);
        draw.setOutLineThickness(1);

        erase.setOutlineColor(sf::Color::Yellow);
        erase.setOutLineThickness(1);

        pick.setOutlineColor(sf::Color::Blue);
        pick.setOutLineThickness(1);
        

        setLayout(&hl);

        hl.setSpacing(10);
        hl.addChild(&draw);
        hl.addChild(&erase);
        hl.addChild(&pick);
    }


private:
    GalGui::Widget::HorizontalLayout hl;
    GalGui::Widget::TextButton draw;
    GalGui::Widget::TextButton erase;
    GalGui::Widget::TextButton pick;
};

class CommandPane : public GG::Frame
{
public:
    CommandPane(GG::Layout* parent = nullptr)
        : GG::Frame( parent )
    {
        
        font.loadFromFile("fonts/menu_font.ttf");
        vLayout.addChild(&box);
        vLayout.addChild(&lineEdit);
        vLayout.setSpacing(20);

        setLayout(&vLayout);
        box.setFont(&font);
        box.setCharacterSize(36);
        box.setAllTextColor(sf::Color::White);
        lineEdit.setFont(&font);
        lineEdit.linkToEntered([this](){
            box.appendText(lineEdit.getContent());
            lineEdit.clear();
        });

        box.appendText("1", sf::Color::Red);
        box.appendText("2", sf::Color::Yellow);
        box.appendText("3", sf::Color::Green);
        box.appendText("4", sf::Color::Blue);
            

    }

private:
    sf::Font font;
    GG::LineEdit lineEdit;
    GG::VerticalLayout vLayout;
    GG::TextBox box;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode{1600,900},"button test");
    sf::Event event;

    sf::Font f;
    f.loadFromFile("fonts/menu_font.ttf");

    GG::Dialog dialog({10,10},{550,200});

    dialog.setFont(&f);
    dialog.setText(" The font argument    refers to a font that must "
        "exist as long as the text uses it. Indeed, the text "
        "doesn't store its own copy of the font, but rather keeps "
        "a pointer to the one that you passed to this function. "
        "If the font is destroyed and the text tries to "
        "use it, the behavior is undefined. ");

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }


        window.clear();
        
        window.draw(dialog);

        window.display();
    }
}