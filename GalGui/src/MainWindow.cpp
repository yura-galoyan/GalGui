#include <GalGui/MainWindow.hpp>
#include <GalGui/Menu.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace GalGui
{

namespace Widget
{

void MainWindow::addMenu(Menu* pMenu)
{
    mMenubar.addChild(pMenu);
}

void MainWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(!getIsVisible()) return;

    GuiElement::draw(target, states);
    target.draw(mMenubar);
}

void MainWindow::update(sf::RenderWindow& window, sf::Event& event)
{
    if(!getIsVisible()) return;

    GuiElement::update(window, event);
    mMenubar.update(window,event);
}

}

}