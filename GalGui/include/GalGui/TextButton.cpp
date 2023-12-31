#include "TextButton.hpp"

namespace GalGui {

namespace Widget {

TextButton::TextButton(const std::string& text, const sf::Font* font, sf::Vector2f n_GlobalPosition, sf::Vector2f n_InitialSize )
    : Button(n_GlobalPosition, n_InitialSize), defFont{font}
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

TextButton::TextButton(const TextButton &other) : Button(other)
{
    m_text = other.m_text;
    defFont =  other.defFont;
    m_bAutoAdjustEnabled =  other.m_bAutoAdjustEnabled;
}

TextButton &TextButton::operator=(TextButton other)
{
    std::swap(m_text, other.m_text);
    std::swap(defFont, other.defFont);
    std::swap(m_bAutoAdjustEnabled, other.m_bAutoAdjustEnabled);
}

void TextButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(getIsVisible())
    {
        Button::draw(target,states);
        target.draw(m_text);
    }
}

void TextButton::setFont(const sf::Font* font)
{
    m_text.setFont(*font);
}

void TextButton::setText(const std::string& string)
{
    m_text.setString(string);
    setInitialSize(getInitialSize());
}

void TextButton::setTextColor(sf::Color color)
{
    m_text.setFillColor(color);
}

void TextButton::setCharacterSize(unsigned h)
{
    m_text.setCharacterSize(h);
}

void TextButton::setAutoAdjustSize(bool bEnabled)
{
    m_bAutoAdjustEnabled = bEnabled;
}

void TextButton::setGlobalPosition(sf::Vector2f n_pos)
{
    GuiElement::setGlobalPosition(n_pos);
    setInitialSize(getInitialSize());
}

void TextButton::setInitialSize(sf::Vector2f n_size)
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

const sf::Font* TextButton::getFont()
{
    return m_text.getFont();
}

std::string TextButton::getText() const
{
    return m_text.getString().toAnsiString();
}

sf::Color TextButton::getTextColor()
{
    return m_text.getFillColor();
}

unsigned TextButton::getCharacterSize()
{
    return m_text.getCharacterSize();
}

}

}
