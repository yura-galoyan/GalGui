
#include <GalGui/Button.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode{640,640},"button test");





    sf::Event event;

    GalGui::Widget::Button btn;

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


        btn.draw(window);


        window.display();


    }
}