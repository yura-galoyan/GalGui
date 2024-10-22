#include <GalGui/VerticalLayout.hpp>
#include <numeric>

namespace GalGui {

namespace Widget{

void VerticalLayout::addChild(GuiElement *pGuiElement)
{
    if(containsElement(pGuiElement))
    {
        std::cout << "duplicate value" << std::endl;
        return;
    }

    if(mGuiElements.empty())
    {
        mGuiElements.push_back(pGuiElement);
        pGuiElement->setParent(this);
        pGuiElement->setGlobalPosition(GuiElement::getGlobalPosition() + sf::Vector2f{0,1});
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
    float sizeY = std::accumulate(mGuiElements.begin(), mGuiElements.end(), 0, [](int l, auto& r){
        return l + r->getInitialSize().y;
    });

    sizeY += ( mGuiElements.size() - 1 ) * getSpacing();
    
    auto maxXelement = std::max_element(mGuiElements.begin(), mGuiElements.end(), [](auto& l, auto& r){
        return l->getInitialSize().x < r->getInitialSize().x;
    });

    float sizeX = (*maxXelement)->getInitialSize().x;

    return sf::Vector2f{sizeX, sizeY};
}

sf::Vector2f VerticalLayout::getGlobalPosition() const
{
    return GuiElement::getGlobalPosition();
}

}

}