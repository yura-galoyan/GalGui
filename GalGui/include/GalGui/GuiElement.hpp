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

    
    /// @brief override this function in derived classes, but call it in the first line of that function
    virtual void update(sf::RenderWindow& window, sf::Event& event) = 0;

    // override this function to implement view of element
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

    // get functions
    virtual const sf::Vector2f&  getGlobalPosition();
    virtual const sf::Vector2f&  getInitialSize();

    // set functions
    virtual void setGlobalPosition( sf::Vector2f n_pos);
    virtual void setInitialSize( sf::Vector2f n_size);

    /// By default stretch is disabled, if stretch is enabled elements may not work correctly
    static void setStretch(bool bEnabled);

protected:
    sf::RectangleShape m_rectangle;


private:
    inline static bool m_bIsEnabled{false};

};

inline GuiElement::GuiElement(sf::Vector2f n_Position, sf::Vector2f n_Size)
    : m_rectangle{ n_Size }
{
    m_rectangle.setPosition(n_Position);
}

inline void GuiElement::update(sf::RenderWindow &window, sf::Event &event)
{

    if(event.type == sf::Event::Resized)
    {
        if(!m_bIsEnabled)
        {
            // update the view to the new size of the window
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(visibleArea));
        }
    }
}

inline const sf::Vector2f&  GuiElement::getGlobalPosition() 
{
    return m_rectangle.getPosition(); 
}

inline const sf::Vector2f&  GuiElement::getInitialSize() 
{
    return m_rectangle.getSize(); 
}


inline void GuiElement::setGlobalPosition( sf::Vector2f n_pos) 
{
    m_rectangle.setPosition(n_pos); 
}
inline void GuiElement::setInitialSize( sf::Vector2f n_size) 
{
    m_rectangle.setSize(n_size); 
}

inline void GuiElement::setStretch(bool bEnabled)
{
    m_bIsEnabled = false;
}


}

}

}

#endif //GALGUI_GUIELEMENT_HPP