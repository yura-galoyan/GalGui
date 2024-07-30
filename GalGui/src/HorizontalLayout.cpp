#include <GalGui/HorizontalLayout.hpp>

namespace GalGui {

namespace Widget{

void HorizontalLayout::addChild(GuiElement *pGuiElement)
{
    if(mGuiElements.empty())
    {
        mGuiElements.push_back(pGuiElement);
        pGuiElement->setGlobalPosition(getGlobalPosition() + sf::Vector2f{5,0});
        return;
    }
    auto last = mGuiElements.back();
    mGuiElements.push_back(pGuiElement);
    pGuiElement->setGlobalPosition({
        last->getGlobalPosition().x + last->getInitialSize().x + 5,
        last->getGlobalPosition().y
    });
}

void HorizontalLayout::configureElemets()
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
                (*std::prev(it))->getGlobalPosition().x + (*std::prev(it))->getInitialSize().x + 5,
                (*std::prev(it))->getGlobalPosition().y
            }
        );
    }
}



}

}