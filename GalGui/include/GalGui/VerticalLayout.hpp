#pragma once

#include <Galgui/Layout.hpp>

namespace GalGui {

namespace Widget{

/// @brief Thic class implements Layout class, it aligns elements horizontally
class VerticalLayout : public Layout
{
public:
    VerticalLayout(Layout* pParent = nullptr)
        : Layout(pParent)
    {
        setType(ElementType::VerticalLayout);
    }

    /// @brief add element to layout
    void addChild(GuiElement* pGuiElement) override;
    
    sf::Vector2f getInitialSize() const override;

    sf::Vector2f getGlobalPosition() const override;

protected:
    /// @brief Change positions of all gui elements to keep alignment
    void configureElemets() override;
};

}

}