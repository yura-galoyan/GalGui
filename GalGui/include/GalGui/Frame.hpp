#pragma once

#include <Galgui/Layout.hpp>

namespace GalGui
{

namespace Widget
{

class Frame : public GuiElement
{
public:
    Frame(Layout* layout = nullptr);

    Layout* getLayout();
    void setLayout(Layout* layout);

    /// @brief traverses through childrens, and returns the size of leftest element
    /// @return return size of leftest element
    sf::Vector2f getInitialSize() const override;

    /// @return return position of leftest element 
    sf::Vector2f getGlobalPosition() const override;

    /// set functions
    void setGlobalPosition( sf::Vector2f n_pos) override;
    void setInitialSize( sf::Vector2f n_size) override;

    /// @brief Calls base class draw function, and draws all child gui elements
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    /// @brief Calls base class update function, and updates all child gui elements
    /// @param window Window to draw in
    /// @param event Pass here event object
    void update(sf::RenderWindow& window, sf::Event& event) override;

    Layout* getParent() const override;
    void setParent(Layout* pParent) override;

private:
    Layout* mLayout;
};

}

}