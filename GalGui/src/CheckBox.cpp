#include <GalGui/CheckBox.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GalGui {

namespace Widget {

CheckBox::CheckBox(sf::Vector2f n_GlobalPosition, sf::Vector2f n_InitialSize)
    : Detail::GuiElement{n_GlobalPosition, n_InitialSize}
{
    m_CheckBoxState = State::Unchecked;
    m_rectangle.setFillColor(sf::Color{170,170,170});

    CheckBox::setGlobalPosition(GuiElement::getGlobalPosition());
    CheckBox::setInitialSize(GuiElement::getInitialSize());

    setFlagColor(sf::Color{50,50,50});

}

void CheckBox::update(sf::RenderWindow& window, sf::Event& event)
{
    if(getIsVisible())
    {
        GuiElement::update(window,event);
        checkState(window, event);
    }
}

void CheckBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(getIsVisible())
    {
        GuiElement::draw(target, states);
        target.draw(m_rectangle);
        if( m_CheckBoxState == State::Checked  ) target.draw(m_flag);
    }
}

void CheckBox::checkState(sf::RenderWindow& window, sf::Event& event)
{
    auto pos = getGlobalPosition();
    auto size = getInitialSize();

    auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getDefaultView());
    // mousePos = window.mapCoordsToPixel(static_cast<sf::Vector2f(mousePos));

    auto isOnCheckBox = [=]() -> bool {
        return mousePos.x > pos.x && mousePos.x < pos.x + size.x &&
               mousePos.y > pos.y && mousePos.y < pos.y + size.y;
    };

    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
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
void CheckBox::setGlobalPosition( sf::Vector2f n_pos)
{
    m_rectangle.setPosition(n_pos);
    m_flag.setPosition(n_pos + sf::Vector2f{2,2});
}

void CheckBox::setInitialSize( sf::Vector2f n_size)
{
    m_rectangle.setSize(n_size);
    m_flag.setSize(n_size - sf::Vector2f{4,4});
}


auto CheckBox::getState() -> State
{
    return m_CheckBoxState;
}

void CheckBox::setState(State isPressed)
{
    m_CheckBoxState = isPressed;
}

void CheckBox::setOutlineColor(sf::Color newColor)
{
    m_rectangle.setOutlineColor(newColor);
}

void CheckBox::setFillColor(sf::Color newColor)
{
    m_rectangle.setFillColor(newColor);
}

void CheckBox::setText(std::string content)
{
    m_text = content;
}

void CheckBox::setOutLineThickness(float value)
{
    m_rectangle.setOutlineThickness(value);
}

void CheckBox::setChecked()
{
    m_CheckBoxState = State::Checked;
    clicked( true  );
}

void CheckBox::setUnChecked()
{
    m_CheckBoxState = State::Unchecked;
    clicked( false );
}

void CheckBox::setFlagColor(sf::Color color)
{
    m_flag.setFillColor(color);
}

sf::Color CheckBox::getOutlineColor()
{
    return m_rectangle.getOutlineColor();
}

sf::Color CheckBox::getFillColor()
{
    return m_rectangle.getFillColor();
}

std::string CheckBox::getText()
{
    return m_text;
}

float CheckBox::getOutlineThickness()
{
    return m_rectangle.getOutlineThickness();
}

sf::Color CheckBox::getFlagColor()
{
    return m_flag.getFillColor();
}

void CheckBox::linkToClicked(const CallBack_t &callBack)
{
    m_clicked_callBacks.push_back(callBack);
}

void CheckBox::clicked(bool state) const
{
    for(const auto& callBack : m_clicked_callBacks)
    {
        callBack(state);
    }
}

}

}
