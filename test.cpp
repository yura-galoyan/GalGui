// define this for iostream usage
#define CUSTOM_DEBUG

#include <GalGui/Button.hpp>
#include <GalGui/ComboBox.hpp>
#include <GalGui/CheckBox.hpp>
#include <GalGui/TextButton.hpp>
#include <GalGui/Label.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode{640,640},"button test");
    sf::Event event;
    window.setKeyRepeatEnabled(false);



    GalGui::Widget::Button btn;

    btn.setInitialSize(sf::Vector2f(50,100));
    
    //  make on hold to be triggered even when mouse is moving, thats more logical
    btn.linkToOnHold(
        [](){
            static int a{0};
            std::cout << "holding: " << ++a << std::endl;
        }
    );

    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        btn.update(window,event);
        
        
        
        window.clear();
        
        window.draw(btn);    

        window.display();
    }
}