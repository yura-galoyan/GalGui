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
    m_bIsVisible = other.m_bIsVisible;
    if(other.m_pLabel)
    {
        m_bDeleteLabel = true;
        m_pLabel = new Label (*(other.m_pLabel));
    }
    else{
        m_bDeleteLabel = false;
        m_pLabel =  nullptr;
    }
    
}

Detail::GuiElement::~GuiElement()
{
    if(m_bDeleteLabel)
    {
        delete m_pLabel;
    }
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

void GuiElement::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(m_pLabel) target.draw(*m_pLabel, states);
}


void GuiElement::setLabel(Label* label, LabelAlignment alignment)
{
    m_alignment = alignment;
    m_pLabel = label;
    setGlobalPosition(getGlobalPosition());
}

void GuiElement::setLabelAlignment(LabelAlignment alignment)
{
    m_alignment = alignment;
}

std::string GuiElement::getLabelText()
{
    return m_pLabel->getText();
}

const sf::Vector2f& GuiElement::getGlobalPosition() const
{
    return m_rectangle.getPosition(); 
}

const sf::Vector2f&  GuiElement::getInitialSize() const
{
    return m_rectangle.getSize(); 
}

void GuiElement::setGlobalPosition( sf::Vector2f n_pos) 
{
    if(m_pLabel)
    {
        auto pos = getGlobalPosition();
        auto size = getInitialSize();
        switch (m_alignment)
        {
        case LabelAlignment::OnTop:
        {
            auto labelPos_y = pos.y - m_pLabel->getInitialSize().y;
            m_pLabel->setGlobalPosition(sf::Vector2f{pos.x, labelPos_y});
        }
            break;

        case LabelAlignment::InCenter:
        {

        }
            break;

        case LabelAlignment::OnBottom:
        {

        }
            break;


        case LabelAlignment::None:
        {

        }
            break;
        default:
            break;
        }
    }

    m_rectangle.setPosition(n_pos); 
}
void GuiElement::setInitialSize( sf::Vector2f n_size) 
{
    m_rectangle.setSize(n_size); 
}

void GuiElement::setStretch(bool bEnabled)
{
    m_bIsEnabled = bEnabled;
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
