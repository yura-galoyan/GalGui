#include <GalGui/VerticalLayout.hpp>

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
    pGuiElement->setGlobalPosition({
        last->getGlobalPosition().x ,
        last->getGlobalPosition().y + last->getInitialSize().y
    });
}

void VerticalLayout::configureElemets()
{
    // If layout is empty, nothing to do
    if(mGuiElements.empty()) return;

    auto it = mGuiElements.begin();
    (*it)->setGlobalPosition(getGlobalPosition());
    ++it;
    for(; it != mGuiElements.end(); ++it)
    {
        (*it)->setGlobalPosition
        ( 
            {
                (*std::prev(it))->getGlobalPosition().x,
                (*std::prev(it))->getGlobalPosition().y + (*std::prev(it))->getInitialSize().y + 1
            }
        );
    }
}



}

}