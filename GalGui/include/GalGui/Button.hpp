#ifndef GALGUI_BUTTON_HPP
#define GALGUI_BUTTON_HPP

#include <string>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "GuiElement.hpp"


namespace GalGui {

namespace Widget {


// Standart button
class Button : public Detail::GuiElement
{
public:
    enum class State
    {
        Idle, Pressed, Hovered 
    };

public:
    Button() = default;
    Button(sf::Vector2f m_GlobalPosition = sf::Vector2f{0,0}, sf::Vector2f m_InitialSize = sf::Vector2f{100,50});

    // override this function to implement logic of element
    virtual void update(sf::RenderWindow& window, sf::Event& event);

    // override this function to implement view of element
    virtual void draw(sf::RenderTarget& target);


public:
    void setState(State isPressed);
    void setOutlineColor(sf::Color newColor);
    void setIdleColor(sf::Color newColor);
    void setHoverColor(sf::Color newColor);
    void setText(std::string content);

    State getState();
    sf::Color getOutlineColor();
    sf::Color getIdleColor();
    sf::Color getHoverColor();
    std::string getText();


private:
    std::string m_text;
    sf::Color m_idleColor{sf::Color(171,171,171)};
    sf::Color m_HoverColor{sf::Color(196,196,196)};


private:
    void checkState(sf::RenderWindow& window, sf::Event& event);

private:
    State m_ButtonState;

};

inline Button::Button(sf::Vector2f m_GlobalPosition, sf::Vector2f m_InitialSize)
    : Detail::GuiElement{m_GlobalPosition, m_InitialSize}
{
    m_rectangle.setOutlineColor(sf::Color{104,104,104 });
}

inline void Button::update(sf::RenderWindow& window, sf::Event& event)
{
    checkState(window, event);
}

inline void Button::draw(sf::RenderTarget& target)
{
    target.draw(m_rectangle);


    if(m_ButtonState == State::Hovered)
    {
        m_rectangle.setFillColor(getHoverColor());
        target.draw(m_rectangle);
    }


}

inline void Button::checkState(sf::RenderWindow& window, sf::Event& event)
{
    auto pos = getGlobalPosition();
    auto size = getInitialSize();

    auto mousePos = sf::Mouse::getPosition(window);

    auto isOnButton = [=]() -> bool {
        return mousePos.x > pos.x && mousePos.x < pos.x + size.x &&
               mousePos.y > pos.y && mousePos.y < pos.y + size.y;
    };

    if(event.type == sf::Event::MouseMoved)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            if(isOnButton())
            {
                m_ButtonState = State::Hovered;
            }
            else 
            {
                m_ButtonState = State::Idle;
            }
                     
        }
    }
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            if(isOnButton())
            {
                m_ButtonState = State::Pressed;
            }
            else 
            {
                m_ButtonState = State::Idle;
            }
                     
        }
    }
    if(event.type == sf::Event::MouseButtonReleased)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            if(isOnButton())
            {
                m_ButtonState = State::Hovered;
            }
            else 
            {
                m_ButtonState = State::Idle;
            }
                     
        }
    }
}

inline auto Button::getState() -> State
{
    return m_ButtonState;
}

inline void Button::setState(State isPressed)
{
    m_ButtonState = isPressed;
}

inline void Button::setOutlineColor(sf::Color newColor)
{
    m_rectangle.setOutlineColor(newColor);
}

inline void Button::setIdleColor(sf::Color newColor)
{
    m_idleColor = newColor;
}

inline void Button::setHoverColor(sf::Color newColor)
{
    m_HoverColor = newColor;
}

inline void Button::setText(std::string content)
{
    m_text = content;
}

inline sf::Color Button::getOutlineColor()
{
    return m_rectangle.getOutlineColor();
}

inline sf::Color Button::getIdleColor()
{
    return m_idleColor;
}

inline sf::Color Button::getHoverColor()
{
    return m_HoverColor;
}

inline std::string Button::getText()
{
    return m_text;
}




}

}

#endif //GALGUI_BUTTON_HPP