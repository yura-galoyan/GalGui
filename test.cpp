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

int main()
{
    sf::RenderWindow window(sf::VideoMode{640,640},"button test");
    sf::Event event;
    window.setKeyRepeatEnabled(false);

    GalGui::Widget::Button btn1;
    GalGui::Widget::Button btn2;
    GalGui::Widget::Slider btn3;
    GalGui::Widget::Button btn4;
    GalGui::Widget::Button btn5;
    GalGui::Widget::Button btn6;
    
    GalGui::Widget::VerticalLayout vLayout;
    GalGui::Widget::HorizontalLayout hLayout;

    vLayout.setSpacing(10);
    hLayout.setGlobalPosition({ 10,20 });
    hLayout.setSpacing(10);

    
    hLayout.addChild(&btn1);
    hLayout.addChild(&vLayout);
    hLayout.addChild(&btn3);

    vLayout.addChild(&btn4);
    vLayout.addChild(&btn5);
    vLayout.addChild(&btn6);

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        vLayout.update(window, event);
        hLayout.update(window, event);

        window.clear();
        
        window.draw(vLayout);
        window.draw(hLayout);

        window.display();
    }
}