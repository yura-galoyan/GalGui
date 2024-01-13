#ifndef GALGUI_SLIDER_HPP
#define GALGUI_SLIDER_HPP

#include "GuiElement.hpp"

namespace GalGui {

namespace Widget{

class Slider : public GuiElement
{
public:

public:
    Slider(sf::Vector2f GlobalPosition = sf::Vector2f{10,10}, sf::Vector2f InitialSize = sf::Vector2f{100,50});
    ~Slider() = default;

    Slider(const Slider& other);

    // overridinig this fucntino to also write text in it
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    /// @brief override this function in derived classes, but call it in the first line of that function
    void update(sf::RenderWindow& window, sf::Event& event) override ;

    // overriden set functions
    virtual void setGlobalPosition(sf::Vector2f n_pos) override ;
    virtual void setInitialSize(sf::Vector2f n_size) override ;

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
    

};

}

}

#endif //GALGUI_SLIDER_HPP
