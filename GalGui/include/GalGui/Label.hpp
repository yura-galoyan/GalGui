#ifndef GALGUI_LABEL_HPP
#define GALGUI_LABEL_HPP

#include "GuiElement.hpp"

#include <SFML/Graphics/Text.hpp>

namespace GalGui {

namespace Widget{

class Label : public GuiElement
{
public:
    enum class Alignment
    {
        Left, Right, Center
    };


public:
    Label(const std::string& text = "Button", const sf::Font* font = nullptr, sf::Vector2f GlobalPosition = sf::Vector2f{10,10}, sf::Vector2f InitialSize = sf::Vector2f{100,50});
    virtual ~Label() = default;

    Label(const Label& other);

    // overridinig this fucntino to also write text in it
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    /// @brief override this function in derived classes, but call it in the first line of that function
    virtual void update(sf::RenderWindow& window, sf::Event& event) override ;

    void setFont(const sf::Font* font);
    void setText(const std::string& string);
    void setTextColor(sf::Color);
    void setCharacterSize(unsigned h);

    // get functions
    virtual void setGlobalPosition(sf::Vector2f n_pos) override ;
    virtual void setInitialSize(sf::Vector2f n_size) override ;

    const sf::Font* getFont();
    std::string getText() const;
    sf::Color getTextColor();
    unsigned getCharacterSize();

    void showOutline();
    void hideOutline();

    void setAlignment(Alignment alignment);
    Alignment getAlignment();

private:
    sf::Text m_text;
    const sf::Font* defFont;
    bool m_bShowOutline{false};
    Alignment m_alignment{Alignment::Left};
    
};

}

}

#endif //GALGUI_LABEL_HPP
