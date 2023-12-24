#ifndef GALGUI_GUIELEMENT_HPP
#define GALGUI_GUIELEMENT_HPP
#endif //GALGUI_GUIELEMENT_HPP

#include <SFML/System/Vector2.hpp>


namespace GalGui {

namespace Widget{

namespace Base{

// base class for all gui elements
class GuiElement
{
public:
    GuiElement() = default;
    GuiElement(sf::Vector2<double> m_GlobalPosition, sf::Vector2<double> m_InitialSize);

    //virtual destructor
    virtual ~GuiElement() = 0;

    // override this function to implement logic of element
    virtual void update() = 0;

    // override this function to implement view of element
    virtual void draw() = 0;

    // get functions
    auto getGlobalPosition();
    auto getInitialSize();

    // set functions
    void getGlobalPosition( sf::Vector2<double> n_pos);
    void getInitialSize( sf::Vector2<double> n_size);

private:
    sf::Vector2<double> m_GlobalPosition;
    sf::Vector2<double> m_InitialSize;

};



GuiElement::GuiElement(sf::Vector2<double> n_Position, sf::Vector2<double> n_Size)
    : m_GlobalPosition{ n_Position }, m_InitialSize{ n_Size }
{

}

auto GuiElement::getGlobalPosition() 
{
    return m_GlobalPosition; 
}

auto GuiElement::getInitialSize() 
{
    return m_InitialSize; 
}


void GuiElement::getGlobalPosition( sf::Vector2<double> n_pos) 
{
    m_GlobalPosition = n_pos; 
}
void GuiElement::getInitialSize( sf::Vector2<double> n_size) 
{
    m_InitialSize = n_size; 
}










}

}

}