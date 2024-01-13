#include <GalGui/Button.hpp>
namespace GalGui {

namespace Widget {

Button::Button(sf::Vector2f n_GlobalPosition, sf::Vector2f n_InitialSize)
    : Detail::GuiElement{n_GlobalPosition, n_InitialSize}
{
    m_rectangle.setOutlineColor(sf::Color{104,104,104 });
    m_ButtonState = State::Idle;
    m_rectangle.setFillColor(getIdleColor());
    m_rectangle.setOutlineThickness(3);
}

Button::Button(const Button &other) : GuiElement(other)
{
    m_text = other.m_text;
    m_idleColor = other.m_idleColor;
    m_HoverColor = other.m_HoverColor;
    m_PressColor = other.m_PressColor;
    m_ButtonState = other.m_ButtonState;
    m_bPressedOnce = other.m_bPressedOnce;
    m_clicked_callBacks = other.m_clicked_callBacks;
    m_onHold_callBacks = other.m_onHold_callBacks;
}

void Button::update(sf::RenderWindow& window, sf::Event& event)
{
    if(getIsVisible())
    {
        GuiElement::update(window,event);
        checkState(window, event);
    }
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(getIsVisible())
    {
        GuiElement::draw(target, states);
        target.draw(m_rectangle);
    }
}

void Button::checkState(sf::RenderWindow& window, sf::Event& event)
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
            if(m_bPressedOnce)
            {
                if(m_bOnHold)
                {
                    onHold();
                }
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
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            if(isOnButton())
            {
                m_ButtonState = State::Pressed;
                m_rectangle.setFillColor(getPressColor());
                m_bPressedOnce = true;
                m_bOnHold = true;
                onHold();
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
                if(m_bPressedOnce)
                {
                    m_ButtonState = State::Hovered;
                    m_rectangle.setFillColor(getHoverColor());
                    m_bPressedOnce = false;
                    clicked();
                }
            }
            else 
            {
                m_ButtonState = State::Idle;
                m_rectangle.setFillColor(getIdleColor());
                m_bPressedOnce = false;
            }
            m_bOnHold = false;
        }
    }
}

Button::State Button::getState() const
{
    return m_ButtonState;
}

void Button::setState(State isPressed)
{
    m_ButtonState = isPressed;
}

void Button::setOutlineColor(sf::Color newColor)
{
    m_rectangle.setOutlineColor(newColor);
}

void Button::setIdleColor(sf::Color newColor)
{
    m_idleColor = newColor;
}

void Button::setHoverColor(sf::Color newColor)
{
    m_HoverColor = newColor;
}

void Button::setPressColor(sf::Color newColor)
{
    m_PressColor = newColor;
}

void Button::setText(std::string content)
{
    m_text = content;
}

void Button::setOutLineThickness(float value)
{
    m_rectangle.setOutlineThickness(value);
}

void Button::setPressedOnce(bool enabled)
{
    m_bPressedOnce = enabled;
}

sf::Color Button::getOutlineColor()
{
    return m_rectangle.getOutlineColor();
}

sf::Color Button::getIdleColor()
{
    return m_idleColor;
}

sf::Color Button::getHoverColor()
{
    return m_HoverColor;
}

sf::Color Button::getPressColor()
{
    return m_PressColor;
}

std::string Button::getText()
{
    return m_text;
}

float Button::getOutlineThickness()
{
    return m_rectangle.getOutlineThickness();
}

bool Button::getPressedOnce()
{
    return m_bPressedOnce;
}

void Button::linkToClicked(const CallBack_t &callBack)
{
    m_clicked_callBacks.push_back(callBack);
}

void Button::linkToOnHold(const CallBack_t &callBack)
{
    m_onHold_callBacks.push_back(callBack);
}

void Button::clicked() const
{
    for(const auto& callBack : m_clicked_callBacks)
    {
        callBack();
    }
}

void Button::onHold() const
{
    for(const auto& callBack : m_onHold_callBacks)
    {
        callBack();
    }
}

}

}
