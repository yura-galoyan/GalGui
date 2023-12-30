// define this for iostream usage
#define CUSTOM_DEBUG

#include <GalGui/Button.hpp>
#include <GalGui/CheckBox.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode{640,640},"button test");
    sf::Event event;
    window.setKeyRepeatEnabled(false);
    // creating button
    GalGui::Widget::Button btn;
    btn.setGlobalPosition(sf::Vector2f(200,200));
    std::vector<GalGui::Widget::CheckBox> checkboxes;
    // creating checkboxes
    for(int i = 0; i < 15; ++i)
    {
        GalGui::Widget::CheckBox chbox(sf::Vector2f(30*i,10) );
        checkboxes.push_back(chbox);   
    }
    checkboxes[0].linkToClicked([&checkboxes](bool st) {
        if (st) checkboxes[5].setChecked();
        else checkboxes[5].setUnChecked();
    });
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
        for(auto & c : checkboxes) { c.update(window,event); }
        btn.update(window,event);
        window.clear();
        for(auto & c : checkboxes)
        {
            window.draw(c);
        }
        window.draw(btn);
        window.display();
    }
}