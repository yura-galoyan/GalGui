#pragma once

#include <GalGui/Frame.hpp>
#include <Galgui/Layout.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GalGui
{

namespace Widget

{
Frame::Frame(Layout* layout)
    : mLayout{layout}
{
    setType(ElementType::Frame);
}

Layout* Frame::getLayout()
{
    return mLayout;
}

void Frame::setLayout(Layout* layout)
{
    mLayout = layout;
}
    
sf::Vector2f Frame::getInitialSize() const
{
    std::cout << "here sze" << std::endl;
    return mLayout->getInitialSize();
}

sf::Vector2f Frame::getGlobalPosition() const
{
    std::cout << "here " << std::endl;
    return mLayout->getGlobalPosition();
}

/// @brief Calls base class draw function, and draws all child gui elements
void Frame::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*mLayout, states);
}
    
/// @brief Calls base class update function, and updates all child gui elements
/// @param window Window to draw in
/// @param event Pass here event object
void Frame::update(sf::RenderWindow& window, sf::Event& event)
{
    mLayout->update(window, event);
}

Layout* Frame::getParent() const
{
    return mLayout->getParent();
}

void Frame::setParent(Layout* pParent)
{
    mLayout->setParent(pParent);
}

}

}