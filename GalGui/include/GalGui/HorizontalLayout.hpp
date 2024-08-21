#pragma once

#include <Galgui/Layout.hpp>

namespace GalGui {

namespace Widget{

/// @brief Thic class implements Layout class, it aligns elements horizontally
class HorizontalLayout : public Layout
{
public:
    HorizontalLayout(Layout* pParent = nullptr)
        : Layout(pParent)
    {
        setType(ElementType::HorizontalLayout);
    }

    /// @brief add element to layout
    void addChild(GuiElement* pGuiElement) override;

    /// @brief traverses through childrens, and returns the size of leftest element
    /// @return return size of leftest element
    sf::Vector2f getInitialSize() const override;

    /// @return return position of leftest element 
    sf::Vector2f getGlobalPosition() const override;

protected:
    /// @brief Change positions of all gui elements to keep alignment
    void configureElemets() override;
};

}

}