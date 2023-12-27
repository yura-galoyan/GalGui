#ifndef GALGUI_BUTTON_HPP
#define GALGUI_BUTTON_HPP

#include <string>
#include <vector>
#include <functional>

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
    using CallBack_t = std::function<void()>;
    using CallBackVector = std::vector<CallBack_t>;

public:
    enum class State
    {
        Idle, Pressed, Hovered 
    };

public:
    Button(sf::Vector2f m_GlobalPosition = sf::Vector2f{10,10}, sf::Vector2f m_InitialSize = sf::Vector2f{100,50});

    // override this function to implement logic of element
    virtual void update(sf::RenderWindow& window, sf::Event& event) override;

    // override this function to implement view of element
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


public:
    void setState(State isPressed);
    void setOutlineColor(sf::Color newColor);
    void setIdleColor(sf::Color newColor);
    void setHoverColor(sf::Color newColor);
    void setPressColor(sf::Color newColor);
    void setText(std::string content);
    void setOutLineThickness(float value);

    State getState();
    sf::Color getOutlineColor();
    sf::Color getIdleColor();
    sf::Color getHoverColor();
    sf::Color getPressColor();
    std::string getText();
    float getOutlineThickness();

public:
    // Link funcntors to button with this functions
    // @param callBack signature is void()
    void link(const CallBack_t& callBack);

    // kinda signal
    void clicked();

private:
    void checkState(sf::RenderWindow& window, sf::Event& event);

private:
    std::string m_text;
    sf::Color m_idleColor{sf::Color(171,171,171)};
    sf::Color m_HoverColor{sf::Color(196,196,196)};
    sf::Color m_PressColor{sf::Color(128,128,128)};
    State m_ButtonState;
    bool m_bPressedOnce;

private:
    CallBackVector m_callBacks;

};

inline Button::Button(sf::Vector2f m_GlobalPosition, sf::Vector2f m_InitialSize)
    : Detail::GuiElement{m_GlobalPosition, m_InitialSize}
{
    m_rectangle.setOutlineColor(sf::Color{104,104,104 });
    m_ButtonState = State::Idle;
    m_rectangle.setFillColor(getIdleColor());
    m_rectangle.setOutlineThickness(3);
}

inline void Button::update(sf::RenderWindow& window, sf::Event& event)
{
    checkState(window, event);
}

inline void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_rectangle);
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
        if(isOnButton())
        {
            m_ButtonState = State::Hovered;
            if(m_bPressedOnce){
                m_rectangle.setFillColor(getPressColor());
            }
            else
            {
                m_rectangle.setFillColor(getHoverColor());
            }
        }
        else 
        {
            m_ButtonState = State::Idle;
            m_rectangle.setFillColor(getIdleColor());
            m_bPressedOnce = false;
        }
    }
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if((event.mouseButton.button == sf::Mouse::Left) && !m_bPressedOnce)
        {
            if(isOnButton())
            {
                m_ButtonState = State::Pressed;
                m_rectangle.setFillColor(getPressColor());
                m_bPressedOnce = true;
                clicked();
                return;
                
            }
            else 
            {
                m_ButtonState = State::Idle;
                m_rectangle.setFillColor(getIdleColor());
                m_bPressedOnce = false;
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
                m_rectangle.setFillColor(getHoverColor());
                m_bPressedOnce = false;
            }
            else 
            {
                m_ButtonState = State::Idle;
                m_rectangle.setFillColor(getIdleColor());
                m_bPressedOnce = false;
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

inline void Button::setPressColor(sf::Color newColor)
{
    m_PressColor = newColor;
}

inline void Button::setText(std::string content)
{
    m_text = content;
}

inline void Button::setOutLineThickness(float value)
{
    m_rectangle.setOutlineThickness(value);
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

inline sf::Color Button::getPressColor()
{
    return m_PressColor;
}

inline std::string Button::getText()
{
    return m_text;
}

inline float Button::getOutlineThickness()
{
    return m_rectangle.getOutlineThickness();
}

inline void Button::link(const CallBack_t &callBack)
{
    m_callBacks.push_back(callBack);
}

inline void Button::clicked()
{
    for(const auto& callBack : m_callBacks)
    {
        callBack();
    }
}

}

}

#endif //GALGUI_BUTTON_HPP