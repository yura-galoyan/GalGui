// define this for iostream usage
#define CUSTOM_DEBUG

#include <GalGui/Button.hpp>
#include <GalGui/ComboBox.hpp>
#include <GalGui/CheckBox.hpp>
#include <GalGui/TextButton.hpp>
#include <GalGui/Label.hpp>
#include <GalGui/Slider.hpp>

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
    }


private:
    GalGui::Widget::HorizontalLayout hl;
    GalGui::Widget::TextButton draw;
    GalGui::Widget::TextButton erase;
    GalGui::Widget::TextButton pick;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode{640,640},"button test");
    sf::Event event;
    window.setKeyRepeatEnabled(false);


    GalGui::Widget::VerticalLayout vl;
    vl.setSpacing(10);

    myWidget wgt1;
    myWidget wgt2;
    myWidget wgt3;

    vl.addChild(&wgt1);
    vl.addChild(&wgt2);
    vl.addChild(&wgt3);

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        vl.update(window, event);

        window.clear();
        
        window.draw(vl);

        window.display();
    }
}