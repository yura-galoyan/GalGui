#define CUSTOM_DEBUG

#include <GalGui/Button.hpp>


#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode{640,640},"button test");




    sf::Event event;

    GalGui::Widget::Button btn;
    btn.link( []{ std::cout << "button is clicked" << std::endl; } );

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