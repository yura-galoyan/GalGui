#pragma once

#include <GalGui/GuiElement.hpp>

#include <vector>
#include <functional>

namespace GalGui
{

namespace Widget
{

class EditLine : public GuiElement
{
    using CallBack_t = std::function<void()>;
    using CallBackVector = std::vector<CallBack_t>;
    
public:
    EditLine(sf::Vector2f n_GlobalPosition = sf::Vector2f{10,10}, sf::Vector2f n_InitialSize = sf::Vector2f{50,20});
    
    // override this function to implement logic of element
    virtual void update(sf::RenderWindow& window, sf::Event& event) override;

    // override this function to implement view of element
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setOutlineColor(sf::Color newColor);
    void setBackgroundColor(sf::Color newColor);
    void setTextColor(sf::Color newColor);
    void setTextHighlightColor(sf::Color newColor);

    void setSize(sf::Vector2f newSize);
    void setPosition(sf::Vector2f newPos);

    std::string getText() const;
    void clear();

private:
    /// @brief Slots
    ///
    void onTextChanged();
    void onEntered();
    ///

private:
    bool m_bInputMode{false};
    std::string m_sBackupText;
    CallBackVector mCallBacksTextChanged;
    CallBackVector mCallBacksTextEntered;

};

}

}