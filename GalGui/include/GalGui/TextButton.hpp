#ifndef GALGUI_TEXT_BUTTON_HPP
#define GALGUI_TEXT_BUTTON_HPP

#include "Button.hpp"

#include <SFML/Graphics/Text.hpp>

namespace GalGui {

namespace Widget {

class TextButton : public Button 
{
public:
    TextButton(const std::string& text = "Button", const sf::Font* font = nullptr, sf::Vector2f GlobalPosition = sf::Vector2f{10,10}, sf::Vector2f InitialSize = sf::Vector2f{100,50});

    // overridinig this fucntino to also write text in it
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setFont(const sf::Font* font);
    void setText(const std::string& string);
    void setTextColor(sf::Color);
    void setCharacterSize(unsigned h);
    void setAutoAdjustSize(bool bEnabled);


    const sf::Font* getFont();
    std::string getText() const;
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

TextButton::TextButton(const std::string& text, const sf::Font* font, sf::Vector2f GlobalPosition, sf::Vector2f InitialSize )
    : Button(GlobalPosition, InitialSize), defFont{font}
{
    setText(text);
    setTextColor(sf::Color{37,37,37});
    setFont(defFont);
    setGlobalPosition(getGlobalPosition());
    if(!font)
    {
        std::cout << "no font was provided, or it wasn't properly loaded" << std::endl;
    }
}

inline void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
    Button::draw(target,states);
    target.draw(m_text);
}

inline void TextButton::setFont(const sf::Font* font)
{
    m_text.setFont(*font);
}

inline void TextButton::setText(const std::string& string)
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
        setCharacterSize( n_size.y < n_size.x ? n_size.y / 3 : n_size.x / 5  );
        m_text.setPosition( getGlobalPosition() + sf::Vector2f{ (n_size.x - m_text.getGlobalBounds().width)/2  , n_size.y / 3  }  );
    }
    else
    {
        Button::setInitialSize(n_size);
    }
}

inline const sf::Font* TextButton::getFont()
{
    return m_text.getFont();
}

inline std::string TextButton::getText() const
{
    return m_text.getString().toAnsiString();
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


#endif //GALGUI_TEXT_BUTTON_HPP