#ifndef TEXT_BUTTON_HPP
#define TEXT_BUTTON_HPP

#include "Button.hpp"

#include <SFML/Graphics/Text.hpp>

namespace GalGui {

namespace Widget {

class TextButton : public Button 
{
public:
    TextButton(const std::string& text = "Button", const sf::Font* font = nullptr, sf::Vector2f m_GlobalPosition = sf::Vector2f{10,10}, sf::Vector2f m_InitialSize = sf::Vector2f{100,50});

    // overridinig this fucntino to also write text in it
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setFont(const sf::Font* font);
    void setText(const std::string& string);
    void setTextColor(sf::Color);
    void setCharacterSize(unsigned h);
    void setAutoAdjustSize(bool bEnabled);


    const sf::Font* getFont();
    std::string getText();
    sf::Color getTextColor();
    unsigned getCharacterSize();

// overriden seters
public:
    virtual void setGlobalPosition( sf::Vector2f n_pos) override;
    virtual void setInitialSize(sf::Vector2f n_size) override;

private:
    sf::Text m_text;
    const sf::Font* defFont;
    bool m_bAutoAdjustEnabled{true};
};

TextButton::TextButton(const std::string& text, const sf::Font* font, sf::Vector2f m_GlobalPosition, sf::Vector2f m_InitialSize )
    : Button(m_GlobalPosition, m_InitialSize), defFont{font}
{
    setText(text);
    setTextColor(sf::Color{255,0,0});
    setGlobalPosition(m_GlobalPosition);
    setInitialSize(m_InitialSize);
    if(!font)
    {
        std::cout << "no font was provided, or it wasn't properly loaded" << std::endl;
    }

    m_text.setOutlineColor(sf::Color::Black);
    
    setFont(defFont);

}

inline void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
    Button::draw(target,states);
    target.draw(m_text);
}

void TextButton::setFont(const sf::Font* font)
{
    m_text.setFont(*font);
}

void TextButton::setText(const std::string& string)
{
    m_text.setString(string);
}

inline void TextButton::setTextColor(sf::Color color)
{
    m_text.setFillColor(color);
}

inline void TextButton::setCharacterSize(unsigned h)
{
    m_text.setCharacterSize(h);
}

inline void TextButton::setAutoAdjustSize(bool bEnabled)
{
    m_bAutoAdjustEnabled = bEnabled;
}

inline void TextButton::setGlobalPosition(sf::Vector2f n_pos)
{
    GuiElement::setGlobalPosition(n_pos);
    setInitialSize(getInitialSize());
}

inline void TextButton::setInitialSize(sf::Vector2f n_size)
{
    if(m_bAutoAdjustEnabled)
    {
        Button::setInitialSize(n_size);
        setCharacterSize( n_size.y / 4  );
        m_text.setPosition( getGlobalPosition() + sf::Vector2f{n_size.x /3 , n_size.y / 3  }     );
    }
    else
    {
        Button::setInitialSize(n_size);
    }
}

const sf::Font* TextButton::getFont()
{
    return m_text.getFont();
}

std::string TextButton::getText()
{
    return m_text.getString();
}

inline sf::Color TextButton::getTextColor()
{
    return m_text.getFillColor();
}

inline unsigned TextButton::getCharacterSize()
{
    return m_text.getCharacterSize();
}

}

}


#endif //TEXT_BUTTON_HPP