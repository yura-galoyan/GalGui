#include <GalGui/Slider.hpp>

namespace GalGui {

namespace Widget{


// overridinig this fucntino to also write text in it
void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}
    
/// @brief override this function in derived classes, but call it in the first line of that function
void Slider::update(sf::RenderWindow& window, sf::Event& event)
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