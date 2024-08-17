#include <GalGui/VerticalLayout.hpp>
#include <cassert>

namespace GalGui {

namespace Widget{

void VerticalLayout::addChild(GuiElement *pGuiElement)
{
    if(mGuiElements.empty())
    {
        mGuiElements.push_back(pGuiElement);
        pGuiElement->setGlobalPosition(getGlobalPosition() + sf::Vector2f{0,1});
        return;
    }
    auto last = mGuiElements.back();
    mGuiElements.push_back(pGuiElement);
    pGuiElement->setParent(this);
    pGuiElement->setGlobalPosition({
        last->getGlobalPosition().x ,
        last->getGlobalPosition().y + last->getInitialSize().y  + getSpacing()
    });

    if(!getParent())
    {
        std::cout << "parent is nullptr" << std::endl;
        return;
    }
    

    getParent()->configureElemets();

}

void VerticalLayout::configureElemets()
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
                (*std::prev(it))->getGlobalPosition().x,
                (*std::prev(it))->getGlobalPosition().y + (*std::prev(it))->getInitialSize().y + getSpacing()
            }
        );
    }
}
    
sf::Vector2f VerticalLayout::getInitialSize() const
{
    if (mGuiElements.empty())
    {
        return GuiElement::getInitialSize();
    }

    auto lowest = std::max_element(mGuiElements.begin(), mGuiElements.end(), [](const auto& l, const auto &r){
        return l->getInitialSize().y < r->getInitialSize().y;
    });

    return (*lowest)->getInitialSize();
}

sf::Vector2f VerticalLayout::getGlobalPosition() const
{
    if (mGuiElements.empty())
    {
        return GuiElement::getGlobalPosition();
    }

    auto maxHeightElem = std::max_element(mGuiElements.begin(), mGuiElements.end(), [](const auto& l, const auto &r){
        return l->getInitialSize().y < r->getInitialSize().y;
    });

    return (*maxHeightElem)->getGlobalPosition();
}



}

}