#pragma once

#include <list>

#include <Galgui/GuiElement.hpp>

namespace GalGui {

namespace Widget{

/// @brief This is base class for all layouts
/// @class Layout
class Layout : public GuiElement
{
public:
    Layout();

    /// @brief add element to layout
    virtual void addChild(GuiElement* pGuiElement) = 0;

    /// @brief remove element from layout
    virtual void removeChild(GuiElement* pGuiElement);

    /// @brief calls base class setGlobalPosition, then configures child elememnts
    /// @param n_pos 
    virtual void setGlobalPosition( sf::Vector2f n_pos);

    /// @brief Calls base class draw function, and draws all child gui elements
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    /// @brief Calls base class update function, and updates all child gui elements
    /// @param window Window to draw in
    /// @param event Pass here event object
    virtual void update(sf::RenderWindow& window, sf::Event& event) override;

private:
    /// @brief Change positions of all gui elements to keep alignment
    virtual void configureElemets() = 0;

protected:
    std::list<GuiElement*> mGuiElements;

};

}

}