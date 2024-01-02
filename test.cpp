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


    sf::Font font;

    
    if(!font.loadFromFile("../Arial.ttf"))
    {
        std::cout  << "could not load " << std::endl;
    }

    GalGui::Widget::ComboBox box(&font);

    box.setGlobalPosition(sf::Vector2f(200,50));

    box.append("name1");
    box.append("name2");
    box.append("name3");
    box.append("name4");
    box.append("name5");

    

    GalGui::Widget::Button btn(sf::Vector2f(150,300));

    
    GalGui::Widget::TextButton btnT("press me", &font);
    GalGui::Widget::CheckBox cbox;
    
    GalGui::Widget::Label lbl("start", &font);
    lbl.setTextColor(sf::Color::Red);
    btnT.setGlobalPosition(sf::Vector2f(300,300));

    btn.linkToClicked([&box, &btnT, &cbox](){
        if(cbox.getState() == GalGui::Widget::CheckBox::State::Checked)
        {
            btnT.setText(box.getCurrentText()); 
        }
    });

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

        lbl.update(window,event);
        btn.update(window,event);
        btnT.update(window,event);
        box.update(window,event);
        cbox.update(window,event);
        
        
        
        window.clear();
        
        window.draw(cbox);
        window.draw(btnT);
        window.draw(box);
        window.draw(btn);
        window.draw(lbl);
        

        window.display();
    }
}