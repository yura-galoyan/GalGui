#ifndef GALGUI_GUIELEMENT_HPP
#define GALGUI_GUIELEMENT_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#ifdef CUSTOM_DEBUG
#include <iostream>
#endif


namespace GalGui {

namespace Widget{

namespace Detail{

// base class for all gui elements
class GuiElement : public sf::Drawable
{
public:
    GuiElement() = default;
    GuiElement(sf::Vector2f m_GlobalPosition, sf::Vector2f m_InitialSize);

    //virtual destructor
    virtual ~GuiElement() = default;

    // override this function to implement logic of element
    virtual void update(sf::RenderWindow& window, sf::Event& event) = 0;

    // override this function to implement view of element
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

    // get functions
    auto getGlobalPosition();
    auto getInitialSize();

    // set functions
    void getGlobalPosition( sf::Vector2f n_pos);
    void getInitialSize( sf::Vector2f n_size);

protected:
    sf::RectangleShape m_rectangle;

};

inline GuiElement::GuiElement(sf::Vector2f n_Position, sf::Vector2f n_Size)
    : m_rectangle{ n_Size }
{
    m_rectangle.setPosition(n_Position);
}

inline auto GuiElement::getGlobalPosition() 
{
    return m_rectangle.getPosition(); 
}

inline auto GuiElement::getInitialSize() 
{
    return m_rectangle.getSize(); 
}


inline void GuiElement::getGlobalPosition( sf::Vector2f n_pos) 
{
    m_rectangle.setPosition(n_pos); 
}
inline void GuiElement::getInitialSize( sf::Vector2f n_size) 
{
    m_rectangle.setSize(n_size); 
}

}

}

}

#endif //GALGUI_GUIELEMENT_HPP