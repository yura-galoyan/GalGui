#include <GalGui/TextBox.hpp>

#include <SFML/Graphics/RenderWindow.hpp>


namespace GalGui::Widget
{

TextBox::TextBox(sf::Vector2f n_Position, sf::Vector2f n_Size)
    :GuiElement(n_Position, n_Size)
{
    showOutline();
    setOutlineColor(sf::Color{104,104,104});
    setCharacterSize(12);
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    GuiElement::draw(target, states);
    if(m_bShowOutline)
    {
        target.draw(m_rectangle);
    }
    if(mAlignment == Alignment::Bottom)
    {
        for(int i = 0; i < mContentVector.size(); ++i)
        {
            target.draw(mContentVector[i], states);
        }
    }
}

void TextBox::setGlobalPosition( sf::Vector2f n_pos)
{
    GuiElement::setGlobalPosition(n_pos);

    auto gPos = getGlobalPosition();
    auto gSize = getInitialSize();
    if(mAlignment == Alignment::Bottom)
    {
        for(int i = mContentVector.size() - 1; i >= 0; --i)
        {
            mContentVector[i].setGlobalPosition( { gPos.x + 2,
             gPos.y + gSize.y - mContentVector[i].getCharacterSize() * (mContentVector.size() - i)  } );
        }
    }
}

void TextBox::setOutlineColor(sf::Color newColor)
{
    m_rectangle.setOutlineColor(newColor);
}

void TextBox::appendText(std::string mNewText, sf::Color color)
{
    mContentVector.push_back(mNewText);
    mContentVector.back().setTextColor(color);
    mContentVector.back().setFont(mFont);
    setCharacterSize(getCharacterSize());
    refresh();
}


void TextBox::setAlignment(Alignment alignment)
{
    mAlignment = alignment;
}

auto TextBox::getAlignment() const -> Alignment
{
    return mAlignment;
}

void TextBox::setFont(sf::Font *font)
{
    mFont = font;
    for(auto& label : mContentVector)
    {
        label.setFont(font);
    }
}

void TextBox::setAllTextColor(sf::Color color)
{
    mColor = color;
    for(auto& label : mContentVector)
    {
        label.setTextColor(color);
    }
}

void TextBox::setCharacterSize(unsigned h)
{
    mCharacterSize = h;
    for(auto& label : mContentVector)
    {
        label.setInitialSize({ getInitialSize().x,   static_cast<float>(h)});
    }
}

void TextBox::clear()
{
    mContentVector.clear();
}

const sf::Font* TextBox::getFont()
{
    return mFont;
}

std::string TextBox::getText() const
{
    return std::string{};
    // return m_text.getString().toAnsiString();
}

sf::Color TextBox::getTextColor()
{
    return mColor;
}

unsigned TextBox::getCharacterSize()
{
    return mCharacterSize;
}

void TextBox::showOutline()
{
    m_bShowOutline = true;
    m_rectangle.setOutlineThickness(1);
}

void TextBox::hideOutline()
{
    m_bShowOutline = false;
    m_rectangle.setOutlineThickness(0);
}




}