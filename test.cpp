// define this for iostream usage
#define CUSTOM_DEBUG

#include <GalGui/Button.hpp>
#include <GalGui/ComboBox.hpp>
#include <GalGui/CheckBox.hpp>
#include <GalGui/TextButton.hpp>
#include <GalGui/Label.hpp>
#include <GalGui/Slider.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode{640,640},"button test");
    sf::Event event;
    window.setKeyRepeatEnabled(false);

    GalGui::Widget::Slider sld;

    GalGui::Widget::Button btn;
    sld.linkToValueChanged([](double val)
    {
        std::cout << val << std::endl;
    });

    btn.linkToClicked([&sld]()
    {
        sld.setValue(100);
    });
    
    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        btn.update(window, event);
        sld.update(window,event);

        window.clear();
         
        window.draw(btn);
        window.draw(sld);

        window.display();
    }
}