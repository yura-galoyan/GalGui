#include <GalGui/HorizontalLayout.hpp>
#include <GalGui/VerticalLayout.hpp>

namespace GalGui {

namespace Widget{

void HorizontalLayout::addChild(GuiElement *pGuiElement)
{
    if(mGuiElements.empty())
    {
        mGuiElements.push_back(pGuiElement);
        pGuiElement->setGlobalPosition(GuiElement::getGlobalPosition());
        return;
    }
    auto last = mGuiElements.back();
    mGuiElements.push_back(pGuiElement);
    pGuiElement->setParent(this);
    pGuiElement->setGlobalPosition({
            last->getGlobalPosition().x + last->getInitialSize().x  + getSpacing(),
            last->getGlobalPosition().y
        });    

    if(!getParent())
        return;
    
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
    if (mGuiElements.empty())
    {
        return GuiElement::getInitialSize();
    }

    const auto leftestElement = std::max_element(mGuiElements.begin(), mGuiElements.end(), [](const auto& l, const auto &r){
        return l->getGlobalPosition().x < r->getGlobalPosition().x;
    });

    return (*leftestElement)->getInitialSize();
}

sf::Vector2f HorizontalLayout::getGlobalPosition() const
{
    if (mGuiElements.empty())
    {
        return GuiElement::getGlobalPosition();
    }

    const auto maxHeightElem = std::max_element(mGuiElements.begin(), mGuiElements.end(), [](const auto& l, const auto &r){
        return l->getGlobalPosition().x < r->getGlobalPosition().x;
    });

    return (*maxHeightElem)->getGlobalPosition();
}



}

}