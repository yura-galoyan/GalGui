#include <GalGui/Gui.hpp>

#include <GalGui/GuiElement.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Font.hpp>
#include <GalGui/Core/Private/DefaultFontData.hpp>

namespace GalGui
{

Gui::Gui()
{
    defFont = new sf::Font;
    defFont->loadFromMemory(defaultFontBytes, sizeof(defaultFontBytes));
}

void Gui::add(GalGui::Widget::GuiElement* pGuiElement)
{
    mGuiElements.push_back(pGuiElement);
}

void Gui::cleanup()
{
    for(auto* pGuiElement : mGuiElements)
    {
       delete pGuiElement;
    }
}

const sf::Font* Gui::getDefaultFont()
{
    return defFont;
}

void Gui::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
    for(auto* pGuiElement : mGuiElements)
    {
        if(pGuiElement)
        {
            target.draw(*pGuiElement, states);
        }
    }
}

void Gui::handleEvents(sf::RenderWindow& window, sf::Event event)
{
    for(auto* pGuiElement : mGuiElements)
    {
        if(pGuiElement)
        {
            pGuiElement->update(window, event);
        }
        
    }
}

Gui::~Gui()
{
    delete defFont;
    cleanup();
}

}