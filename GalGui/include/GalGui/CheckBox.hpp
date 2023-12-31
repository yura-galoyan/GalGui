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

}

}

#endif //GALGUI_CHECKBOX_HPP