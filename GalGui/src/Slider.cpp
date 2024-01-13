#include <GalGui/Slider.hpp>

namespace GalGui {

namespace Widget{

Slider::Slider(sf::Vector2f globalPosition = sf::Vector2f{10,10}, sf::Vector2f initialSize = sf::Vector2f{100,50})
    : GuiElement(globalPosition, initialSize),
    m_value{50},
    m_maxValue{100},
    m_minValue{0},
    m_incValue{1}
{
    m_sliderButton.linkToOnHold(
        []()
        {

        }
    );
}

// overridinig this fucntino to also write text in it
void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    GuiElement::draw(target,states);
}
    
/// @brief override this function in derived classes, but call it in the first line of that function
void Slider::update(sf::RenderWindow& window, sf::Event& event)
{
    GuiElement::update(window,event);
    m_sliderButton.update(window,event);
}


void Slider::linkToOnHold(const Button::CallBack_t& callBack)
{
    m_sliderButton.linkToOnHold(callBack);
}


void Slider::valueChanged(double val)
{

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