#include <GalGui/Slider.hpp>

namespace GalGui {

namespace Widget{

Slider::Slider(sf::Vector2f globalPosition, sf::Vector2f initialSize)
    : GuiElement(globalPosition, initialSize),
    m_value{50},
    m_maxValue{100},
    m_minValue{0},
    m_incValue{1}
{
    // initialize slider controller
    m_sliderController.setPosition(globalPosition);
    m_sliderController.setSize(sf::Vector2f(initialSize.x / 10, initialSize.y));
    m_initialPositionOfSlider = m_sliderController.getPosition();
    m_sliderController.setOutlineColor(sf::Color{104,104,104 });
    m_sliderController.setFillColor(getIdleColor());
    m_sliderController.setOutlineThickness(3);

    // set state
    m_ButtonState = Button::State::Idle;

    // set value, this functions sets slider to its correct position
    setValue(m_value);

    // initilze m_slider line
    m_sliderLine.setFillColor(getIdleColor());

    // this functions sets m_sliderLine to its correct position, according go m_globalPosition
    setInitialSize(getInitialSize());
}

// overridinig this fucntino to also write text in it
void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(getIsVisible())
    {
        GuiElement::draw(target, states);
        target.draw(m_sliderLine);
        target.draw(m_sliderController);
    }
        
}
    
/// @brief override this function in derived classes, but call it in the first line of that function
void Slider::update(sf::RenderWindow& window, sf::Event& event)
{
    GuiElement::update(window,event);

    auto pos = m_sliderController.getPosition();
    auto size = m_sliderController.getSize();

    auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getDefaultView());

    auto isOnButton = [=]() -> bool {
        return mousePos.x > pos.x && mousePos.x < pos.x + size.x &&
               mousePos.y > pos.y && mousePos.y < pos.y + size.y;
    };

    m_ButtonState = Button::State::Idle;
    m_sliderController.setFillColor(getIdleColor());

    if(event.type == sf::Event::MouseMoved)
    {
        if(isOnButton())
        {
            m_ButtonState = Button::State::Hovered;
            m_sliderController.setFillColor(getHoverColor());
        }
        if(m_bPressedOnce)
        {
            if(m_bOnHold)
            {
                auto valDiff = getMaxValue() - getMinValue();
                auto diffCoords_x = mousePos.x - m_initialPositionOfMouse.x;
                double newValue = (diffCoords_x / getInitialSize().x) * ( valDiff) + m_value;
                if(newValue < getMinValue()) newValue = getMinValue();
                if(newValue > getMaxValue()) newValue = getMaxValue();
                setValue(newValue);
                m_initialPositionOfMouse = sf::Vector2f(mousePos);
            }
            m_sliderController.setFillColor(getPressColor());
        }
    }
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Left) 
        {
            if(isOnButton())
            {
                m_ButtonState = Button::State::Pressed;
                m_sliderController.setFillColor(getPressColor());
                m_bPressedOnce = true;
                m_initialPositionOfMouse = sf::Vector2f(sf::Mouse::getPosition(window));
                m_initialPositionOfSlider = m_sliderController.getPosition();
                m_bOnHold = true;
            }
            else 
            {
                m_ButtonState = Button::State::Idle;
                m_sliderController.setFillColor(getIdleColor());
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
                    m_ButtonState = Button::State::Hovered;
                    m_sliderController.setFillColor(getHoverColor());
                    m_bPressedOnce = false;
                }
            }
            else 
            {
                m_ButtonState = Button::State::Idle;
                m_sliderController.setFillColor(getIdleColor());
                m_bPressedOnce = false;
            }
            m_bOnHold = false;
        }
    }
}

void Slider::linkToValueChanged(const CallBack_t& callBack)
{
    m_callBacks.push_back(callBack);
}

void Slider::valueChanged(double val)
{
    for(auto& cb : m_callBacks)
    {
        cb(val);
    }
}

// overriden set functions
void Slider::setGlobalPosition(sf::Vector2f n_pos)
{
    GuiElement::setGlobalPosition(n_pos);
    m_sliderController.setPosition(sf::Vector2f( n_pos.x + ((getInitialSize().x * m_value) / (m_maxValue - m_minValue)),n_pos.y ));
    m_sliderLine.setPosition(n_pos.x, n_pos.y + getInitialSize().y/4);
}

void Slider::setInitialSize(sf::Vector2f n_size)
{
    GuiElement::setInitialSize(n_size);
    m_sliderController.setSize(sf::Vector2f( n_size.x / 10 ,n_size.y ));
    m_sliderLine.setSize(sf::Vector2f(n_size.x, n_size.y / 4));
    setGlobalPosition(getGlobalPosition());
}

void Slider::setOutlineColor(sf::Color newColor)
{
    m_rectangle.setOutlineColor(newColor);
}

void Slider::setIdleColor(sf::Color newColor)
{
    m_idleColor = newColor;
}

void Slider::setHoverColor(sf::Color newColor)
{
    m_HoverColor = newColor;
}

void Slider::setPressColor(sf::Color newColor)
{
    m_PressColor = newColor;
}

void Slider::setOutLineThickness(float value)
{
    m_rectangle.setOutlineThickness(value);
}

sf::Color Slider::getOutlineColor()
{
    return m_rectangle.getOutlineColor();
}

sf::Color Slider::getIdleColor()
{
    return m_idleColor;
}

sf::Color Slider::getHoverColor()
{
    return m_HoverColor;
}

sf::Color Slider::getPressColor()
{
    return m_PressColor;
}

float Slider::getOutlineThickness()
{
    return m_rectangle.getOutlineThickness();
}

double Slider::getValue() const
{
    return m_value;
}

double Slider::getMaxValue() const
{
    return m_maxValue;
}

double Slider::getMinValue() const
{
    return m_minValue;
}

double Slider::getIncValue() const
{
    return m_incValue;
}

void Slider::setValue(double val)
{
    m_value = val;
    
    auto diff = getMaxValue() - getMinValue();

    auto pos = getGlobalPosition().x + (m_value / diff) * getInitialSize().x   ;

    m_sliderController.setPosition(pos, getGlobalPosition().y);

    valueChanged(val);

}

void Slider::setMaxValue(double val)
{
    m_maxValue = val;
}

void Slider::setMinValue(double val)
{
    m_minValue = val;
}

void Slider::setIncValue(double val)
{
    m_incValue = val;
}

}

}