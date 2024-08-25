#pragma once

#include <GalGui/GuiElement.hpp>
#include <GalGui/Label.hpp>

#include <vector>

namespace GalGui::Widget
{

class TextBox : public GuiElement
{
public:
    enum class Alignment
    {
        Left, Right, Top, Bottom
    };

public:
    TextBox(sf::Vector2f n_Position = {0,0}, sf::Vector2f n_Size = {300,300});

    // overridinig this fucntino to also write text in it
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setAlignment(Alignment alignment);

    Alignment getAlignment() const;

    void appendText(std::string mNewText);

    virtual void setGlobalPosition( sf::Vector2f n_pos) override;

    void setFont(sf::Font* font);
    void setText(const std::string& string);
    void setTextColor(sf::Color);
    void setCharacterSize(unsigned h);
    
    const sf::Font* getFont();
    std::string getText() const;
    sf::Color getTextColor();
    unsigned getCharacterSize();

    void clear();

    void showOutline();
    void hideOutline();

private:
    std::vector<Label> mContentVector;
    Alignment mAlignment{Alignment::Bottom};

private:
    sf::Color mColor{sf::Color{104,104,104}};
    unsigned int mCharacterSize{12};
    bool m_bShowOutline{false};
    sf::Font* mFont;


};

}