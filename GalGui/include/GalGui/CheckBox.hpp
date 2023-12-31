#ifndef GALGUI_CHECKBOX_HPP
#define GALGUI_CHECKBOX_HPP

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

// Standart CheckBox
class CheckBox : public Detail::GuiElement
{
public:
    using CallBack_t = std::function<void(bool)>;
    using CallBackVector = std::vector<CallBack_t>;

public:
    enum class State
    {
        Unchecked, Checked 
    };

public:
    CheckBox(sf::Vector2f n_GlobalPosition = sf::Vector2f{10,10}, sf::Vector2f n_InitialSize = sf::Vector2f{15,15});

    // override this function to implement logic of element
    virtual void update(sf::RenderWindow& window, sf::Event& event) override;

    // override this function to implement view of element
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

//  seters
public:
    void setState(State isPressed);
    void setOutlineColor(sf::Color newColor);
    void setFillColor(sf::Color newColor);
    void setText(std::string content);
    void setOutLineThickness(float value);
    void setChecked();
    void setUnChecked();
    void setFlagColor(sf::Color);

//  geters
public:
    State getState();
    sf::Color getOutlineColor();
    sf::Color getFillColor();
    sf::Color getFlagColor();
    std::string getText();
    float getOutlineThickness();

// overriden seters
public:
    virtual void setGlobalPosition( sf::Vector2f n_pos) override;
    virtual void setInitialSize( sf::Vector2f n_size) override;

public:
    // Link funcntors to CheckBox with this functions
    // @param callBack signature is void(bool)
    void linkToClicked(const CallBack_t& callBack);

    // kinda signal
    void clicked(bool state) const;
    
private:
    void checkState(sf::RenderWindow& window, sf::Event& event);

private:
    std::string m_text;
    State m_CheckBoxState;
    bool starting{false};

private:
    sf::RectangleShape m_flag;

private:
    CallBackVector m_clicked_callBacks;

};

// implementation

inline CheckBox::CheckBox(sf::Vector2f n_GlobalPosition, sf::Vector2f n_InitialSize)
    : Detail::GuiElement{n_GlobalPosition, n_InitialSize}
{
    m_CheckBoxState = State::Unchecked;
    m_rectangle.setFillColor(sf::Color{170,170,170});

    CheckBox::setGlobalPosition(GuiElement::getGlobalPosition());
    CheckBox::setInitialSize(GuiElement::getInitialSize());

    setFlagColor(sf::Color{50,50,50});

}

inline void CheckBox::update(sf::RenderWindow& window, sf::Event& event)
{
    GuiElement::update(window,event);
    checkState(window, event);
}

inline void CheckBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_rectangle);
    if( m_CheckBoxState == State::Checked  ) target.draw(m_flag);
}

inline void CheckBox::checkState(sf::RenderWindow& window, sf::Event& event)
{
    auto pos = getGlobalPosition();
    auto size = getInitialSize();

    auto mousePos = sf::Mouse::getPosition(window);
    // mousePos = window.mapCoordsToPixel(static_cast<sf::Vector2f(mousePos));

    auto isOnCheckBox = [=]() -> bool {
        return mousePos.x > pos.x && mousePos.x < pos.x + size.x &&
               mousePos.y > pos.y && mousePos.y < pos.y + size.y;
    };

    if(event.type == sf::Event::MouseButtonPressed)
    {
        if((event.mouseButton.button == sf::Mouse::Left))
        {
            if(isOnCheckBox())
            {
                starting = true;
            }        
        }
    }
    if(event.type == sf::Event::MouseButtonReleased)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            if(isOnCheckBox())
            {
                if(starting)
                {
                    m_CheckBoxState = m_CheckBoxState == State::Checked ? State::Unchecked : State::Checked;
                    clicked( m_CheckBoxState == State::Checked ? true : false  );
                    starting = false;
                }
            }  
        }
    }
}


    // set functions
inline void CheckBox::setGlobalPosition( sf::Vector2f n_pos)
{
    m_rectangle.setPosition(n_pos);
    m_flag.setPosition(n_pos + sf::Vector2f{2,2});
}

inline void CheckBox::setInitialSize( sf::Vector2f n_size)
{
    m_rectangle.setSize(n_size);
    m_flag.setSize(n_size - sf::Vector2f{4,4});
}


inline auto CheckBox::getState() -> State
{
    return m_CheckBoxState;
}

inline void CheckBox::setState(State isPressed)
{
    m_CheckBoxState = isPressed;
}

inline void CheckBox::setOutlineColor(sf::Color newColor)
{
    m_rectangle.setOutlineColor(newColor);
}

inline void CheckBox::setFillColor(sf::Color newColor)
{
    m_rectangle.setFillColor(newColor);
}

inline void CheckBox::setText(std::string content)
{
    m_text = content;
}

inline void CheckBox::setOutLineThickness(float value)
{
    m_rectangle.setOutlineThickness(value);
}

inline void CheckBox::setChecked()
{
    m_CheckBoxState = State::Checked;
    clicked( true  );
}

inline void CheckBox::setUnChecked()
{
    m_CheckBoxState = State::Unchecked;
    clicked( false );
}

inline void CheckBox::setFlagColor(sf::Color color)
{
    m_flag.setFillColor(color);
}

inline sf::Color CheckBox::getOutlineColor()
{
    return m_rectangle.getOutlineColor();
}

inline sf::Color CheckBox::getFillColor()
{
    return m_rectangle.getFillColor();
}

inline std::string CheckBox::getText()
{
    return m_text;
}

inline float CheckBox::getOutlineThickness()
{
    return m_rectangle.getOutlineThickness();
}

inline sf::Color CheckBox::getFlagColor()
{
    return m_flag.getFillColor();
}

inline void CheckBox::linkToClicked(const CallBack_t &callBack)
{
    m_clicked_callBacks.push_back(callBack);
}

inline void CheckBox::clicked(bool state) const
{
    for(const auto& callBack : m_clicked_callBacks)
    {
        callBack(state);
    }
}

}

}

#endif //GALGUI_CHECKBOX_HPP