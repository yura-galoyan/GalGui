
// define this for iostream usage
#define CUSTOM_DEBUG

#include <GalGui/Button.hpp>
#include <GalGui/ComboBox.hpp>
#include <GalGui/CheckBox.hpp>
#include <GalGui/TextButton.hpp>
#include <GalGui/Label.hpp>
#include <GalGui/Slider.hpp>
#include <GalGui/LineEdit.hpp>
#include <GalGui/TextBox.hpp>

#include <GalGui/HorizontalLayout.hpp>
#include <GalGui/VerticalLayout.hpp>
#include <GalGui/Frame.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


#include <iomanip>


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
        hl.addChild(&erase);
        hl.addChild(&pick);
    }


private:
    GalGui::Widget::HorizontalLayout hl;
    GalGui::Widget::TextButton draw;
    GalGui::Widget::TextButton erase;
    GalGui::Widget::TextButton pick;
};


int main()
{
    namespace GG = GalGui::Widget;
    sf::RenderWindow window(sf::VideoMode{1600,900},"button test");
    sf::Event event;
    window.setKeyRepeatEnabled(true);

    GG::LineEdit lineEdit;

    sf::Font font;
    font.loadFromFile("fonts/menu_font.ttf");

    GG::VerticalLayout vLayout;

    GG::TextBox box;


    vLayout.addChild(&box);
    vLayout.addChild(&lineEdit);

    vLayout.setSpacing(20);

    vLayout.setGlobalPosition({150,150});;
    
    box.setFont(&font);
    box.setCharacterSize(36);
    box.setTextColor(sf::Color::White);

    lineEdit.setFont(&font);
    lineEdit.linkToEntered([&lineEdit, &box](){
        std::cout << " lineEdit.getContent().size() : " << lineEdit.getContent().size() << std::endl;
        std::cout << "appending " << std::quoted(lineEdit.getContent()) << std::endl; 
        box.appendText(lineEdit.getContent());
        lineEdit.clear();
    });


    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }

            vLayout.update(window, event);
        }


        window.clear();
        
        window.draw(vLayout);

        window.display();
    }
}