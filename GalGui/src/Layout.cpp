#pragma once

#include <algorithm>

#include <Galgui/Layout.hpp>

namespace GalGui {

namespace Widget{

Layout::Layout()
{

}

void Layout::removeChild(GuiElement* pGuiElement)
{
    mGuiElements.erase(std::remove(mGuiElements.begin(), mGuiElements.end(), pGuiElement));

    configureElemets();
}

/// @brief calls base class setGlobalPosition, then configures child elememnts
/// @param n_pos 
void Layout::setGlobalPosition( sf::Vector2f n_pos)
{
    GuiElement::setGlobalPosition(n_pos);

    configureElemets();
}

void Layout::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    GuiElement::draw(target, states);

    for(auto& pGuiElement : mGuiElements)
    {
        target.draw(*pGuiElement, states);
    }
}

/// @brief override this function in derived classes, but call it in the first line of that function
void Layout::update(sf::RenderWindow& window, sf::Event& event) 
{
    GuiElement::update(window, event);

    for(auto& pGuiElement : mGuiElements)
    {
        pGuiElement->update(window, event);
    }
}

void Layout::setSpacing(float spacing)
{
    mSpacing = spacing;
}
    
float Layout::getSpacing() const
{
    return mSpacing;
}

}

}