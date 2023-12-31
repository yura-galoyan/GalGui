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

    TextButton(const TextButton& other);

    TextButton& operator=(TextButton other);

    virtual ~TextButton() = default;
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


}

}


#endif //GALGUI_TEXT_BUTTON_HPP