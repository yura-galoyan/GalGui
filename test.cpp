// define this for iostream usage
#define CUSTOM_DEBUG

#include <GalGui/Button.hpp>
#include <GalGui/ComboBox.hpp>
#include <GalGui/CheckBox.hpp>
#include <GalGui/TextButton.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode{640,640},"button test");
    sf::Event event;
    window.setKeyRepeatEnabled(false);


    sf::Font font;

    
    if(!font.loadFromFile("arial.ttf"))
    {
        std::cout  << "could not load " << std::endl;
    }

    GalGui::Widget::ComboBox box;

    std::string name("Yura");
    box.setGlobalPosition(sf::Vector2f(100,50));
    box.append(name);
    box.linkOnSetCurrentText([](const std::string& text){
        std::cout << "in combo box is" << text << std::endl;
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


        box.update(window,event);
        
        
        window.clear();
        
        
        
        window.draw(box);
        

        window.display();
    }
}