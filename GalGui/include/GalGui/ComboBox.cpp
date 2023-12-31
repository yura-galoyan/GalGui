#include "ComboBox.hpp"

namespace GalGui {

namespace Widget {

ComboBox::ComboBox(const sf::Font *font, sf::Vector2f n_GlobalPosition, sf::Vector2f n_InitialSize)
    : TextButton("", font, n_GlobalPosition, n_InitialSize)
{
    setOutLineThickness(1);
}

void ComboBox::append(const std::string &value)
{
    TextButton btn(value, getFont());
    btn.linkToClicked( 
        [this, value](){
            m_bIsPressed = false;
            onSetCurrentText(value);
        }
    );
    m_values.push_back(btn);
    setGlobalPosition(getGlobalPosition());
}

void ComboBox::remove(const std::string &value)
{
    m_values.erase( std::remove_if( m_values.begin(), m_values.end(), [&value](const auto& val){ return val.getText() == value; }));
    setGlobalPosition(getGlobalPosition());
    
}

void ComboBox::setGlobalPosition(sf::Vector2f n_pos)
{
    TextButton::setGlobalPosition(n_pos);
    unsigned i{0};
    for(auto& value : m_values)
    {
        value.setGlobalPosition(n_pos + sf::Vector2f( 0, n_pos.y + value.getInitialSize().y * (i++)  ));
    }
}

void ComboBox::setInitialSize(sf::Vector2f n_size)
{    
    TextButton::setInitialSize(n_size);
    for(auto& value : m_values)
    {
        value.setInitialSize(n_size);
    }

}

bool ComboBox::setCurrentText(const std::string &newText)
{
    auto it = std::find_if(m_values.begin(), m_values.end(), [&newText](const auto& val){
        return val.getText() == newText;
    });

    if(it != m_values.end())
    {
        setText(newText);
        return true;
    }
    return false;
}

std::string ComboBox::getCurrentText() const
{
    return getText();
}

// override this function to implement logic of element
void ComboBox::update(sf::RenderWindow& window, sf::Event& event)
{
    if(getIsVisible())
    {
        Button::update(window,event);
        auto pos = getGlobalPosition();
        auto size = getInitialSize();
        auto mousePos = sf::Mouse::getPosition(window);
        // mousePos = window.mapCoordsToPixel(static_cast<sf::Vector2f(mousePos));
        auto isOnComboBox = [=]() -> bool {
            return mousePos.x > pos.x && mousePos.x < pos.x + size.x &&
                   mousePos.y > pos.y && mousePos.y < pos.y + size.y;
        };
        if(event.type == sf::Event::MouseButtonPressed)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
            {
                if(isOnComboBox())
                {
                    starting = true;
                }        
            }
        }
        if(event.type == sf::Event::MouseButtonReleased)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
            {
                if(isOnComboBox())
                {
                    if(starting)
                    {
                        m_bIsPressed = !m_bIsPressed;
                        starting = false;
                    }
                }  
            }
        }
        if(m_bIsPressed)
        {
            for(auto& val : m_values)
            {
                val.update(window,event);
            }
        }
    }
}

// override this function to implement view of element
void ComboBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(getIsVisible())
    {
        TextButton::draw(target, states);

        if(m_bIsPressed)
        {
            for(const auto& val : m_values)
            {
                val.draw(target, states);
            }
        }
    }
}

void ComboBox::onSetCurrentText(const std::string &text)
{
    setText(text);
    for(const auto& cb : m_callBacks)
    {
        cb(text);
    } 
}

void ComboBox::linkOnSetCurrentText(const CallBack_t &callBack)
{
    m_callBacks.push_back(callBack);
}

}

}
