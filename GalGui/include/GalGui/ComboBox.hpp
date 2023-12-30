#ifndef GALGUI_COMBOBOX_HPP
#define GALGUI_COMBOBOX_HPP

#include <list>

#include "TextButton.hpp"

namespace GalGui {

namespace Widget {

class ComboBox : public TextButton
{
private:
    using CallBack_t = std::function<void(const std::string&)>;
    using CallBackVector = std::vector<CallBack_t>;

public:
    ComboBox(const sf::Font* font = nullptr,
             sf::Vector2f GlobalPosition = sf::Vector2f{10,10}, sf::Vector2f InitialSize = sf::Vector2f{100,50});

    // append value to end of combo box
    void append(const std::string& value);

    // remove value from combo box
    void remove(const std::string& value);

// overriden seters
public:
    virtual void setGlobalPosition( sf::Vector2f n_pos) override;
    virtual void setInitialSize(sf::Vector2f n_size) override;

    // override this function to implement logic of element
    virtual void update(sf::RenderWindow& window, sf::Event& event) override;

    // override this function to implement view of element
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // signals
    void onSetCurrentText(const std::string& text);

    // slots emits when text is changed
    void linkOnSetCurrentText(const CallBack_t& callBack);
    
private:
    std::list<TextButton> m_values;
    CallBackVector m_callBacks;
    bool m_bIsPressed{false};
};

inline ComboBox::ComboBox(const sf::Font *font, sf::Vector2f GlobalPosition, sf::Vector2f InitialSize)
    : TextButton("", font, GlobalPosition, InitialSize)
{
    setOutLineThickness(1);
}

inline void ComboBox::append(const std::string &value)
{
    TextButton btn(value, getFont());
    btn.linkToClicked( 
        [this, value](){
            m_bIsPressed = false;
            onSetCurrentText(value);
        }
    );
    m_values.push_back(btn);

}

inline void ComboBox::remove(const std::string &value)
{
    m_values.erase( std::remove_if( m_values.begin(), m_values.end(), [&value](const auto& val){ return val.getText() == value; }));
}

inline void ComboBox::setGlobalPosition(sf::Vector2f n_pos)
{
    setGlobalPosition(n_pos);
    unsigned i{0};
    for(auto& value : m_values)
    {
        value.setGlobalPosition(n_pos + sf::Vector2f(  n_pos.x, n_pos.y + value.getInitialSize().y * (++i)  ));
    }
}

inline void ComboBox::setInitialSize(sf::Vector2f n_size)
{    
    setInitialSize(n_size);
    for(auto& value : m_values)
    {
        value.setInitialSize(n_size);
    }

}


// override this function to implement logic of element
inline void ComboBox::update(sf::RenderWindow& window, sf::Event& event)
{
    Button::update(window,event);

    if(getState() == State::Pressed)
    {
        m_bIsPressed = !m_bIsPressed;
    }
    

    if(m_bIsPressed)
    {
        for(auto& val : m_values)
        {
            val.update(window,event);
        }
    }
}

// override this function to implement view of element
inline void ComboBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
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

inline void ComboBox::onSetCurrentText(const std::string &text)
{
    for(const auto& cb : m_callBacks)
    {
        cb(text);
    } 
}

inline void ComboBox::linkOnSetCurrentText(const CallBack_t &callBack)
{
    m_callBacks.push_back(callBack);
}

}

}

#endif //GALGUI_COMBOBOX_HPP