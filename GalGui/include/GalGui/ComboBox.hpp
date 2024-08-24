#ifndef GALGUI_COMBOBOX_HPP
#define GALGUI_COMBOBOX_HPP

#include <list>

#include "TextButton.hpp"

namespace GalGui {

namespace Widget {

class ComboBox : public TextButton
{
private:
    using CallBack_t = std::function<void(const std::string&)>;
    using CallBackVector = std::vector<CallBack_t>;

public:
    ComboBox(const sf::Font* font = nullptr,
             sf::Vector2f GlobalPosition = sf::Vector2f{10,10}, sf::Vector2f InitialSize = sf::Vector2f{50,20});

    // append value to end of combo box
    void append(const std::string& value);

    // remove value from combo box
    void remove(const std::string& value);
    
    // override this function to implement logic of element
    virtual void update(sf::RenderWindow& window, sf::Event& event) override;

    // override this function to implement view of element
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


// overriden seters
public:
    virtual void setGlobalPosition( sf::Vector2f n_pos) override;
    virtual void setInitialSize(sf::Vector2f n_size) override;

    bool setCurrentText(const std::string& newText);

    std::string getCurrentText() const;


// signals
public:
    void onSetCurrentText(const std::string& text);

// slots emits when text is changed
public:
    void linkOnSetCurrentText(const CallBack_t& callBack);
    
private:
    std::list<TextButton> m_values;
    CallBackVector m_callBacks;
    bool m_bIsPressed{false};
    bool starting{false};
};

}

}

#endif //GALGUI_COMBOBOX_HPP