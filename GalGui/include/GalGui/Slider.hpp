#ifndef GALGUI_SLIDER_HPP
#define GALGUI_SLIDER_HPP

#include "GuiElement.hpp"

#include <GalGui/Button.hpp>
namespace GalGui {

namespace Widget{

class Slider : public GuiElement
{
public:
    Slider(sf::Vector2f globalPosition = sf::Vector2f{10,10}, sf::Vector2f initialSize = sf::Vector2f{100,50});
    ~Slider() = default;

    Slider(const Slider& other);

    // overridinig this fucntino to also write text in it
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    /// @brief override this function in derived classes, but call it in the first line of that function
    void update(sf::RenderWindow& window, sf::Event& event) override ;

    // overriden set functions
    virtual void setGlobalPosition(sf::Vector2f n_pos) override ;
    virtual void setInitialSize(sf::Vector2f n_size) override ;


    // slots
    void linkToOnHold(const Button::CallBack_t& callBack);


private:
    // signals
    void valueChanged(double val);




    // get functions
    double getValue() const;
    double getMaxValue() const;
    double getMinValue() const;
    double getIncValue() const;
    

    // set functions
    void setValue(double val);
    void setMaxValue(double val);
    void setMinValue(double val);
    void setIncValue(double val);

private:
    double m_value;
    double m_maxValue;
    double m_minValue;
    double m_incValue;


private:
    Button m_sliderButton;

};

}

}

#endif //GALGUI_SLIDER_HPP
