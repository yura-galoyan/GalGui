// define this for iostream usage
#define CUSTOM_DEBUG

#include <GalGui/Button.hpp>
#include <GalGui/CheckBox.hpp>
#include <GalGui/TextButton.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode{640,640},"button test");
    sf::Event event;
    window.setKeyRepeatEnabled(false);
    // creating button
    GalGui::Widget::Button btn;
    sf::Font f;

    
    GalGui::Widget::CheckBox cbtn;
    cbtn.setInitialSize(sf::Vector2f{200,200});
    if(!f.loadFromFile("arial.ttf"))
    {
        std::cout  << "could not load " << std::endl;
    }
    GalGui::Widget::TextButton btnText("press me", &f);

    btn.setGlobalPosition(sf::Vector2f(200,200));
    btnText.setGlobalPosition(sf::Vector2f(400,200));




    btn.linkToClicked( [&window]{ std::cout << "done " << std::endl; } );
    btn.linkToOnHold([&window] {  std::cout << "HOLDIIING" << std::endl;  } );



    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // update
        cbtn.update(window,event);
        btn.update(window,event);
        btnText.update(window,event);
        
        // end
        
        window.clear();
        
        // draw
        window.draw(cbtn);
        window.draw(btn);
        window.draw(btnText);
        
        // end
        

        window.display();
    }
}