#pragma once

#include <list>

#include "TextButton.hpp"

namespace GalGui {

namespace Widget {

class Menu : public TextButton
{
protected:
    using CallBack_t = std::function<void(const std::string&)>;
    using CallBackVector = std::vector<CallBack_t>;

public:
    Menu(const std::string& title = "Menu", const sf::Font* font = nullptr,
             sf::Vector2f GlobalPosition = sf::Vector2f{10,10}, sf::Vector2f InitialSize = sf::Vector2f{50,20});

#ifdef _DEBUG
    ~Menu() 
    {
        std::cout << "deleting menu: " << getTitle() << std::endl;
    }
#endif

    // append value to end of menu box
    void append(const std::string& value);

    // remove value from menu box
    void remove(const std::string& value);
    
    // override this function to implement logic of element
    virtual void update(sf::RenderWindow& window, sf::Event& event) override;

    // override this function to implement view of element
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setTitle(const std::string& name);

    std::string getTitle() const;

    std::string getCurrentText() const;

    TextButton& getActionByName(const std::string& name);

// overriden seters
public:
    virtual void setGlobalPosition( sf::Vector2f n_pos) override;
    virtual void setInitialSize(sf::Vector2f n_size) override;

protected:
    std::list<TextButton> m_values;
    CallBackVector m_callBacks;
    bool m_bIsPressed{false};
    bool starting{false};
};

}

}