#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <list>

namespace sf
{
    class Font;
}

namespace GalGui
{
namespace Widget
{
    class GuiElement;
}

/// @brief RAII class that manages all gui elements resources
class Gui : public sf::Drawable
{
public:
    Gui();
    ~Gui();
    void add(GalGui::Widget::GuiElement* pGuiElement);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void handleEvents(sf::RenderWindow& window, sf::Event event);

    const sf::Font* getDefaultFont();

private:
    void cleanup();

private:
    std::list<GalGui::Widget::GuiElement*> mGuiElements;
    sf::Font* defFont;
};

}