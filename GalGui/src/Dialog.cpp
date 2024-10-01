#include <GalGui/Dialog.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <sstream>

namespace GalGui::Widget
{

Dialog::Dialog(sf::Vector2f n_Position, sf::Vector2f n_Size)
    : GuiElement(n_Position, n_Size)
{
    setGlobalPosition(n_Position);
    setInitialSize(n_Size);
    showOutline();
    setOutlineColor(sf::Color{104,104,104});
    setCharacterSize(20);
    m_rectangle.setOutlineThickness(1);
}

void Dialog::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    GuiElement::draw(target, states);
    if(m_bShowOutline)
    {
        target.draw(m_rectangle);
    }

    target.draw(mText, states);
}

void Dialog::setGlobalPosition( sf::Vector2f n_pos)
{
    GuiElement::setGlobalPosition(n_pos);

    mText.setPosition(n_pos);
    mText.move({mMargins.left, mMargins.top});
}

void Dialog::setOutlineColor(sf::Color newColor)
{
    m_rectangle.setOutlineColor(newColor);
}

void Dialog::setMargins(float left, float top, float right, float bottom )
{
    mMargins.left = left;
    mMargins.top = top;
    mMargins.right = right;
    mMargins.bottom = bottom;

    setText(getText());
}

void Dialog::setAlignment(Alignment alignment)
{
    mAlignment = alignment;
}

auto Dialog::getAlignment() const -> Alignment
{
    return mAlignment;
}

void Dialog::setFont(sf::Font *font)
{
    if(font)
        mText.setFont(*font);
    else
        std::cerr << "nullptr was provided for a font" << std::endl;
}

void Dialog::setCharacterSize(unsigned h)
{
    mText.setCharacterSize(h);
}

void Dialog::setTextColor(const sf::Color& color)
{
    mText.setFillColor(color);
}

void Dialog::clear()
{
    mText.setString("");
}

void Dialog::setText(const std::string& string)
{
    if(!m_bWordWrap)
    {
        mText.setString(string);
        return;
    }

    std::string newText;

    mRawString = string;

    sf::Text tmpText;
    tmpText.setPosition(getGlobalPosition());
    tmpText.setFont(*getFont());
    tmpText.setCharacterSize(getCharacterSize());
    
    int startIndex = 0;
    int lastSpaceIndex = 0;
    for(int i = startIndex; i < string.size(); ++i)
    {
        if(string[i] == ' ')
        {
            lastSpaceIndex = i;
        } 
        std::string tmpStr = string.substr(startIndex,i - startIndex);
        tmpText.setString(tmpStr);
        auto lastCharPos = tmpText.findCharacterPos(i);
        if(lastCharPos.x + getCharacterSize() >= m_rectangle.getPosition().x + m_rectangle.getSize().x)
        {
            if(i + 1 != string.size())
            {
                if(string[i + 1] != ' ' && string[i + 1] != '\t')
                {
                    tmpStr = string.substr(startIndex, lastSpaceIndex - startIndex);
                    i = lastSpaceIndex ;
                    startIndex = i;
                    newText.append(tmpStr + '\n');
                    continue;
                }
            }
            else 
            {
                newText.append(tmpStr);    
            }
            if(tmpStr.size())    
            newText.append(tmpStr + '\n');
            startIndex = i;
        }
        else if (i + 1 == string.size())
        {
            newText.append(tmpStr);
            break;
        }
    }
    mText.setString(newText);
}

const sf::Font* Dialog::getFont()
{
    return mText.getFont();
}

std::string Dialog::getText() const
{
    return mRawString;
}

sf::Color Dialog::getTextColor()
{
    return mText.getFillColor();
}

unsigned Dialog::getCharacterSize()
{
    return mText.getCharacterSize();
}

void Dialog::showOutline()
{
    m_bShowOutline = true;
}

void Dialog::hideOutline()
{
    m_bShowOutline = false;
}

}