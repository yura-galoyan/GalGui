#include <algorithm>

#include <Galgui/Layout.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GalGui {

namespace Widget{

Layout::Layout(Layout* pParent)
    : GuiElement(pParent)
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
    if(!getIsVisible()) return;
    
    GuiElement::draw(target, states);

    for(auto& pGuiElement : mGuiElements)
    {
        target.draw(*pGuiElement, states);
    }    
    for(auto& pGuiElement : mGuiElements)
    {
        if(pGuiElement->getType() == ElementType::ComboBox)
            target.draw(*pGuiElement, states);
    }
}

/// @brief override this function in derived classes, but call it in the first line of that function
void Layout::update(sf::RenderWindow& window, sf::Event& event) 
{
    if(!getIsVisible()) return;
    
    GuiElement::update(window, event);

    for(auto& pGuiElement : mGuiElements)
    {
        pGuiElement->update(window, event);
    }
}



GuiElement* Layout::getLowestElement() const
{
    auto lowestElement =  std::max_element(mGuiElements.begin(), mGuiElements.end(), [](GuiElement* l, GuiElement* r){
        return l->getGlobalPosition().y < r->getGlobalPosition().y;
    });

    return *lowestElement;
}

GuiElement* Layout::getRightestElement() const
{
    auto rightestElement =  std::max_element(mGuiElements.begin(), mGuiElements.end(), [](GuiElement* l, GuiElement* r){
        return l->getGlobalPosition().x < r->getGlobalPosition().x;
    });

    return *rightestElement;
}

bool Layout::containsElement(GuiElement *pGuiELement) const
{
    return std::find(mGuiElements.begin(), mGuiElements.end(), pGuiELement) != mGuiElements.end();
}
void Layout::setSpacing(float spacing)
{
    mSpacing = spacing;
    configureElemets();
}
    
float Layout::getSpacing() const
{
    return mSpacing;
}

}

}