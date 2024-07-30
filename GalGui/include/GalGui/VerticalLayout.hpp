#pragma once

#include <Galgui/Layout.hpp>

namespace GalGui {

namespace Widget{

/// @brief Thic class implements Layout class, it aligns elements horizontally
class VerticalLayout : public Layout
{
public:
    
    /// @brief add element to layout
    void addChild(GuiElement* pGuiElement) override;

private:
    /// @brief Change positions of all gui elements to keep alignment
    void configureElemets() override;

};

}

}