#ifndef GALGUI_BUTTON_HPP
#define GALGUI_BUTTON_HPP

#include <string>
#include <vector>

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
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
    Button(sf::Vector2f n_GlobalPosition = sf::Vector2f{10,10}, sf::Vector2f n_InitialSize = sf::Vector2f{100,50});
    virtual ~Button() = default;

    Button(const Button& button);

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
    void setPressedOnce(bool enabled);

    State getState() const;
    sf::Color getOutlineColor();
    sf::Color getIdleColor();
    sf::Color getHoverColor();
    sf::Color getPressColor();
    std::string getText();
    float getOutlineThickness();
    bool getPressedOnce();

public:
    // Link functors to button with this functions
    // @param callBack signature is void()
    void linkToClicked(const CallBack_t& callBack);
    
    // Link functors to button with this functions
    // @param callBack signature is void()
    void linkToOnHold(const CallBack_t& callBack);

    // kinda signal
    void clicked() const;

    void onHold() const;
    

private:
    void checkState(sf::RenderWindow& window, sf::Event& event);

private:
    std::string m_text;
    sf::Color m_idleColor{sf::Color(171,171,171)};
    sf::Color m_HoverColor{sf::Color(196,196,196)};
    sf::Color m_PressColor{sf::Color(128,128,128)};
    State m_ButtonState;
    bool m_bPressedOnce;
    bool m_bOnHold;
private:
    CallBackVector m_clicked_callBacks;
    CallBackVector m_onHold_callBacks;

};

}

}

#endif //GALGUI_BUTTON_HPP