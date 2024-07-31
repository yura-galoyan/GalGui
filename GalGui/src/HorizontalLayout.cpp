#include <GalGui/HorizontalLayout.hpp>

namespace GalGui {

namespace Widget{

void HorizontalLayout::addChild(GuiElement *pGuiElement)
{
    std::cout << mGuiElements.size() << "size before inserting " << pGuiElement->getElementName() << std::endl;

    if(mGuiElements.empty())
    {
        mGuiElements.push_back(pGuiElement);
        pGuiElement->setGlobalPosition(getGlobalPosition() + sf::Vector2f{5,0});
        return;
    }
    auto last = mGuiElements.back();
    mGuiElements.push_back(pGuiElement);
    pGuiElement->setGlobalPosition({
            last->getGlobalPosition().x + last->getInitialSize().x  + getSpacing(),
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
                (*std::prev(it))->getGlobalPosition().x + (*std::prev(it))->getInitialSize().x  + getSpacing(),
                (*std::prev(it))->getGlobalPosition().y
            }
        );
    }
}



}

}