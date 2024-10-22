#include <GalGui/EditLine.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

namespace GalGui
{

namespace Widget
{

EditLine::EditLine(sf::Vector2f n_GlobalPosition, sf::Vector2f n_InitialSize)
    : GuiElement(n_GlobalPosition, n_InitialSize)
{

}

void EditLine::update(sf::RenderWindow& window, sf::Event& event)
{
    if(!getIsVisible()) return;

    GuiElement::update(window,event);

    auto pos = getGlobalPosition();
    auto size = getInitialSize();

    auto startMousePos = sf::Mouse::getPosition(window);
    auto mousePos = window.mapPixelToCoords(startMousePos);

    const auto isOnButton = [=]() -> bool {
        return mousePos.x > pos.x && mousePos.x < pos.x + size.x &&
               mousePos.y > pos.y && mousePos.y < pos.y + size.y;
    };

    if(event.type == sf::Event::MouseMoved)
    {
        if(isOnButton())
        {
            
        }
    }

}

}

}