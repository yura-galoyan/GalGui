#pragma once

#include <GalGui/GuiElement.hpp>
#include <GalGui/HorizontalLayout.hpp>

#include <SFML/Graphics/RenderStates.hpp>

namespace GalGui
{

namespace Widget
{

class Menu;

class MainWindow : public GuiElement
{
public:
    void draw(sf::RenderTarget&, sf::RenderStates states) const override;
    void update(sf::RenderWindow& window, sf::Event& event) override;
    void addMenu(Menu* pMenu);

#ifdef _DEBUG
    ~MainWindow() 
    {
        std::cout << "deleting MainWindow" << std::endl;
    }
#endif

private:
    HorizontalLayout mMenubar;

    sf::Vector2f getGlobalPosition() const { return {}; };
    sf::Vector2f getInitialSize() const { return {}; };
    void setGlobalPosition( sf::Vector2f n_pos) { };
    void setInitialSize( sf::Vector2f n_size) { };
};

}

}