
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
        box.setTextColor(sf::Color::White);
        lineEdit.setFont(&font);
        lineEdit.linkToEntered([this](){
            box.appendText(lineEdit.getContent());
            lineEdit.clear();
        });

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
    window.setKeyRepeatEnabled(true);




    CommandPane pane;

    pane.setGlobalPosition({50,300});


    pane.hide();

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Tilde)
                {
                    pane.show();
                }
                if(event.key.code == sf::Keyboard::Escape)
                {
                    pane.hide();
                }
            }

            pane.update(window, event);
        }


        window.clear();
        
        window.draw(pane);

        window.display();
    }
}