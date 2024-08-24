
// define this for iostream usage
#define CUSTOM_DEBUG

#include <GalGui/Button.hpp>
#include <GalGui/ComboBox.hpp>
#include <GalGui/CheckBox.hpp>
#include <GalGui/TextButton.hpp>
#include <GalGui/Label.hpp>
#include <GalGui/Slider.hpp>
#include <GalGui/LineEdit.hpp>

#include <GalGui/HorizontalLayout.hpp>
#include <GalGui/VerticalLayout.hpp>
#include <GalGui/Frame.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


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


int main()
{
    namespace GG = GalGui::Widget;
    sf::RenderWindow window(sf::VideoMode{640,640},"button test");
    sf::Event event;
    window.setKeyRepeatEnabled(true);

    GG::LineEdit txt;
    txt.linkToChanged([&txt](){
        std::cout << txt.getContent() << std::endl;
    });
    sf::Font font;
    font.loadFromFile("fonts/menu_font.ttf");
    txt.setFont(&font);

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }

            txt.update(window, event);
        }


        window.clear();
        
        window.draw(txt);

        window.display();
    }
}