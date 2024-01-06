#include <GalGui/Label.hpp>

namespace GalGui {

namespace Widget{


Label::Label(const std::string& text, const sf::Font* font, sf::Vector2f n_GlobalPosition, sf::Vector2f n_InitialSize )
    : GuiElement(n_GlobalPosition, n_InitialSize), defFont{font}
{
    setText(text);
    setTextColor(sf::Color{220,220,220});
    setFont(defFont);
    setGlobalPosition(getGlobalPosition());
    if(!font)
    {
        #ifdef CUSTOM_DEBUG
        std::cout << "no font was provided, or it wasn't properly loaded" << std::endl;
        #endif
    }
}

Label::Label(const Label& other) : GuiElement(other)
{
    m_text = other.m_text;
    defFont = other.defFont;
    m_bShowOutline = other.m_bShowOutline;
    m_alignment = other.m_alignment;
}

void Label::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(getIsVisible())
    {
        if(m_bShowOutline)
        {
            target.draw(m_rectangle);
        }
        target.draw(m_text);
    }
}

void Label::update(sf::RenderWindow &window, sf::Event &event)
{
    if(getIsVisible())
    {
        GuiElement::update(window,event);
    }
}

void Label::setFont(const sf::Font *font)
{
    m_text.setFont(*font);
}

void Label::setText(const std::string& string)
{
    m_text.setString(string);
}

void Label::setTextColor(sf::Color color)
{
    m_text.setFillColor(color);
}

void Label::setCharacterSize(unsigned h)
{
    m_text.setCharacterSize(h);
}

void Label::setGlobalPosition(sf::Vector2f n_pos)
{
    GuiElement::setGlobalPosition(n_pos);
    setInitialSize(getInitialSize());
}

void Label::setInitialSize(sf::Vector2f n_size)
{
    GuiElement::setInitialSize(n_size);
    setCharacterSize( n_size.y - 5  );
    m_text.setPosition( getGlobalPosition() );
    setAlignment(getAlignment());
}

const sf::Font* Label::getFont()
{
    return m_text.getFont();
}

std::string Label::getText() const
{
    return m_text.getString().toAnsiString();
}

sf::Color Label::getTextColor()
{
    return m_text.getFillColor();
}

unsigned Label::getCharacterSize()
{
    return m_text.getCharacterSize();
}

void Label::showOutline()
{
    m_bShowOutline = true;
    m_rectangle.setOutlineThickness(1);
}

void Label::hideOutline()
{
    m_bShowOutline = false;
    m_rectangle.setOutlineThickness(0);
}


void Label::setAlignment(Alignment alignment)
{
    m_alignment = alignment;


    auto rectSize = getInitialSize();
    auto rectPos = getGlobalPosition();
    switch (m_alignment)
    {
    case Alignment::Left:
    {
        m_text.setPosition(rectPos);
        
    }
        break;
    case Alignment::Right:
    {
        m_text.setPosition(  sf::Vector2f{ rectPos.x + rectSize.x - m_text.getGlobalBounds().width  ,rectPos.y }  );
    }
        break;
    case Alignment::Center:
    {
        m_text.setPosition(  sf::Vector2f{ rectPos.x + (rectSize.x - m_text.getGlobalBounds().width)/2,rectPos.y }  );
    }
        break;
    default:
        break;
    }



}

Label::Alignment Label::getAlignment()
{
    return m_alignment;
}

}

}