#include <GalGui/HorizontalLayout.hpp>
#include <GalGui/VerticalLayout.hpp>

#include <numeric>

namespace GalGui {

namespace Widget{

void HorizontalLayout::addChild(GuiElement *pGuiElement)
{
    if(containsElement(pGuiElement)) return;
    if(mGuiElements.empty())
    {
        mGuiElements.push_back(pGuiElement);
        pGuiElement->setGlobalPosition(GuiElement::getGlobalPosition());
        return;
    }
    auto last = mGuiElements.back();
    mGuiElements.push_back(pGuiElement);
    pGuiElement->setParent(this);
    const auto lastGlobalPosition = last->getGlobalPosition();
    const auto lastInitialSize = last->getInitialSize();
    pGuiElement->setGlobalPosition({
            lastGlobalPosition.x + lastInitialSize.x  + getSpacing(),
            lastGlobalPosition.y
        });    

    if(!getParent())
    {
       return;
    }
    
    getParent()->configureElemets();
}

void HorizontalLayout::configureElemets()
{
    // If layout is empty, nothing to do
    if(mGuiElements.empty()) return;

    auto it = mGuiElements.begin();
    (*it)->setGlobalPosition(GuiElement::getGlobalPosition());
    ++it;
    for(; it != mGuiElements.end(); ++it)
    {
        (*it)->setGlobalPosition
        ( 
            {
                (*std::prev(it))->getGlobalPosition().x + (*std::prev(it))->getInitialSize().x  + getSpacing(),
                (*std::prev(it))->getGlobalPosition().y
            }
        );
    }
}
    
sf::Vector2f HorizontalLayout::getInitialSize() const
{

    float sizeX = std::accumulate(mGuiElements.begin(), mGuiElements.end(), 0, [](int l, auto& r){
        return l + r->getInitialSize().x;
    });

    sizeX += ( mGuiElements.size() - 1 ) * getSpacing();
    
    auto maxYelement = std::max_element(mGuiElements.begin(), mGuiElements.end(), [](auto& l, auto& r){
        return l->getInitialSize().y < r->getInitialSize().y;
    });

    float sizeY = (*maxYelement)->getInitialSize().y;

    return sf::Vector2f{sizeX, sizeY};
}

sf::Vector2f HorizontalLayout::getGlobalPosition() const
{
    return GuiElement::getGlobalPosition();
}



}

}