#include <GalGui/GuiElement.hpp>

#include <GalGui/Label.hpp>

namespace GalGui {

namespace Widget{

GuiElement::GuiElement(sf::Vector2f n_Position, sf::Vector2f n_Size)
    : m_rectangle{ n_Size }, m_pLabel{nullptr}
{
    m_rectangle.setPosition(n_Position);
    m_rectangle.setFillColor(sf::Color::Transparent);
    m_rectangle.setOutlineColor(sf::Color::Green);
}

Detail::GuiElement::GuiElement(const GuiElement &other)
{
    m_rectangle = other.m_rectangle;
    m_bIsEnabled = other.m_bIsEnabled;
    m_bIsVisible = other.m_bIsVisible;
    m_pLabel = other.m_pLabel ? std::make_unique<Label>(*(other.m_pLabel)) : nullptr;
}

Detail::GuiElement::~GuiElement()
{
}

void GuiElement::update(sf::RenderWindow &window, sf::Event &event)
{
    if(getIsVisible())
    {
        if(event.type == sf::Event::Resized)
        {
            if(!m_bIsEnabled)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }
    }
}


void GuiElement::setLabel(std::unique_ptr<Label> label)
{
    m_pLabel = std::move(label);
}

std::string GuiElement::getLabelText()
{
    return m_pLabel->getText();
}


const sf::Vector2f&  GuiElement::getGlobalPosition() 
{
    return m_rectangle.getPosition(); 
}

const sf::Vector2f&  GuiElement::getInitialSize() 
{
    return m_rectangle.getSize(); 
}


void GuiElement::setGlobalPosition( sf::Vector2f n_pos) 
{
    switch (m_alignment)
    {
    case LabelAlignment::OnTop:
    {

    }
        break;
    case LabelAlignment::InCenter:
    {

    }

    case LabelAlignment::None:
    {

    }
        break;
    default:
        break;
    }


    m_rectangle.setPosition(n_pos); 
}
void GuiElement::setInitialSize( sf::Vector2f n_size) 
{
    m_rectangle.setSize(n_size); 
}

void GuiElement::setStretch(bool bEnabled)
{
    m_bIsEnabled = false;
}

void GuiElement::show()
{
    m_bIsVisible = true;
}

void GuiElement::hide()
{
    m_bIsVisible = false;
}

bool GuiElement::getIsVisible() const
{
    return m_bIsVisible;
}


}

}
