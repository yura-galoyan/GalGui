#ifndef GALGUI_SLIDER_HPP
#define GALGUI_SLIDER_HPP

#include "GuiElement.hpp"

#include <GalGui/Button.hpp>
namespace GalGui {

namespace Widget{

class Slider : public GuiElement
{
public:
    Slider(sf::Vector2f globalPosition = sf::Vector2f{220,100}, sf::Vector2f initialSize = sf::Vector2f{200,30});
    ~Slider() = default;

    Slider(const Slider& other);

    // overridinig this fucntino to also write text in it
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    /// @brief override this function in derived classes, but call it in the first line of that function
    void update(sf::RenderWindow& window, sf::Event& event) override ;


    /// @note Change value to val <br>
    /// @note val needs to be in between minValue and maxValue, otherwise
    /// value will be set to maxValue
    /// @param val new value
    void setValue(double val);


    // overriden set functions
    void setGlobalPosition(sf::Vector2f n_pos) override ;
    void setInitialSize(sf::Vector2f n_size) override ;


    // slots
    void linkToValueChanged(const CallBack_t& callBack);


private:
    // signals
    void valueChanged(double val);




    // get functions
    double getValue() const;
    double getMaxValue() const;
    double getMinValue() const;
    double getIncValue() const;
    

    void setMaxValue(double val);
    void setMinValue(double val);
    void setIncValue(double val);

private:
    double m_value;
    double m_maxValue;
    double m_minValue;
    double m_incValue;

public:
    void setOutlineColor(sf::Color newColor);
    void setIdleColor(sf::Color newColor);
    void setHoverColor(sf::Color newColor);
    void setPressColor(sf::Color newColor);
    void setOutLineThickness(float value);

    sf::Color getOutlineColor();
    sf::Color getIdleColor();
    sf::Color getHoverColor();
    sf::Color getPressColor();
    float getOutlineThickness();

private:
    sf::RectangleShape m_sliderController;
    sf::RectangleShape m_sliderLine;


    sf::Color m_idleColor{sf::Color(171,171,171)};
    sf::Color m_HoverColor{sf::Color(196,196,196)};
    sf::Color m_PressColor{sf::Color(128,128,128)};

    sf::Vector2f m_initialPositionOfMouse;
    sf::Vector2f m_initialPositionOfSlider;
    
    bool m_bOnHold;
    bool m_bPressedOnce;
    Button::State m_ButtonState;
    CallBackVector m_callBacks;

};

}

}

#endif //GALGUI_SLIDER_HPP
