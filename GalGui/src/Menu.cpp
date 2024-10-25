#include <GalGui/Menu.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GalGui {

namespace Widget {

Menu::Menu(const std::string& title, const sf::Font *font, sf::Vector2f n_GlobalPosition, sf::Vector2f n_InitialSize)
    : TextButton("", font, n_GlobalPosition, n_InitialSize)
{
    setOutLineThickness(2);
    setType(ElementType::Menu);
}

void Menu::append(const std::string &value)
{
    m_values.push_back(TextButton(value, getFont()));
    m_values.back().setInitialSize(getInitialSize());
    m_values.back().linkToClicked([this](){ m_bIsPressed = false;});
    setGlobalPosition(getGlobalPosition());
}

void Menu::remove(const std::string &value)
{
    m_values.erase( std::remove_if( m_values.begin(), m_values.end(), [&value](const auto& val){ return val.getText() == value; }));
    setGlobalPosition(getGlobalPosition());
}

void Menu::setTitle(const std::string& name)
{
    setText(name);
}

std::string Menu::getTitle() const
{
    return getText();
}

void Menu::setGlobalPosition(sf::Vector2f n_pos)
{
    TextButton::setGlobalPosition(n_pos);
    unsigned i{0};
    for(auto& value : m_values)
    {
        value.setGlobalPosition(n_pos + sf::Vector2f( 0, value.getInitialSize().y * (++i)  ));
    }
}

void Menu::setInitialSize(sf::Vector2f n_size)
{    
    TextButton::setInitialSize(n_size);
    for(auto& value : m_values)
    {
        value.setInitialSize(n_size);
    }
    refresh();
}

std::string Menu::getCurrentText() const
{
    return getText();
}

TextButton& Menu::getActionByName(const std::string& name)
{
    auto it = std::find_if(m_values.begin(), m_values.end(), [&name](const auto& val){
        return val.getText() == name;
    });

    if(it == m_values.end())
    {
        throw std::out_of_range("Action with given name is not found: " + name);
    }
    return *it;
}

// override this function to implement logic of element
void Menu::update(sf::RenderWindow& window, sf::Event& event)
{
    if(!getIsVisible()) return;

    Button::update(window,event);

    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            if(isOnGuiElement(window))
            {
                starting = true;
            }        
        }
    }
    if(event.type == sf::Event::MouseButtonReleased)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            if(isOnGuiElement(window))
            {
                if(starting)
                {
                    m_bIsPressed = !m_bIsPressed;
                    starting = false;
                }
            }  
        }
    }
    if(m_bIsPressed)
    {
        for(auto& val : m_values)
        {
            val.update(window,event);
        }
    }
}

// override this function to implement view of element
void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(!getIsVisible()) return;

    TextButton::draw(target, states);
    if(m_bIsPressed)
    {
        for(const auto& val : m_values)
        {
            val.draw(target, states);
        }
    }
}

}

}
