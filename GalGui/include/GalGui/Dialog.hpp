#pragma once

#include <GalGui/GuiElement.hpp>

#include <SFML/Graphics/Text.hpp>

namespace sf
{
    class Font;
}

namespace GalGui::Widget
{

class Dialog : public GuiElement
{
public:
    enum class Alignment
    {
        Left, Right, Top, Bottom
    };

    struct Margins
    {
        float left{0};
        float top{0};
        float right{0};
        float bottom{0};
    };

public:
    Dialog(sf::Vector2f n_Position = {0,0}, sf::Vector2f n_Size = {300,300});

    // overridinig this fucntino to also write text in it
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setAlignment(Alignment alignment);
    Alignment getAlignment() const;

    void setGlobalPosition( sf::Vector2f n_pos) override;

    void setFont(sf::Font* font);
    void setText(const std::string& string);
    void setTextColor(const sf::Color& color);

    void setMargins(float left, float top, float right, float bottom );

    /// @brief 
    /// @param h character size in pixels
    void setCharacterSize(unsigned h);

    /// @brief 
    /// @param newColor color of outline of dialog box
    void setOutlineColor(sf::Color newColor);
    
    const sf::Font* getFont();
    std::string getText() const;
    sf::Color getTextColor();
    unsigned getCharacterSize();

    void clear();

    void showOutline();
    void hideOutline();

private:
    sf::Text mText;
    std::string mRawString;
    Alignment mAlignment;
    Margins mMargins;
    bool m_bShowOutline{true};
    bool m_bWordWrap{false};
};

}