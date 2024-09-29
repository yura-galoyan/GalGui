#pragma once

#include <GalGui/TextButton.hpp>

namespace GalGui::Widget
{

class LineEdit : public TextButton
{
public:
    LineEdit(const std::string& text = "", const sf::Font* font = nullptr,
     sf::Vector2f GlobalPosition = sf::Vector2f{10,10}, sf::Vector2f InitialSize = sf::Vector2f{300,30});

    // override this function to implement logic of element
    void update(sf::RenderWindow& window, sf::Event& event) override;

    void setInitialSize(sf::Vector2f n_size) override;
    void setInputMode(bool bEnabled);
    
    void linkToChanged(CallBack_t cb);
    void linkToEntered(CallBack_t cb);

    std::string getContent() const;
    void clear();

private:
    void onTextChanged();
    void onTextEntered();

private:
    bool bInputMode{false};
    std::string m_sBackupText;
    CallBackVector mCallBacksTextChanged;
    CallBackVector mCallBacksTextEntered;
};

}





















// #include <GalGui/GuiElement.hpp>

// namespace GalGui::Widget
// {

// /// @class LineEdit
// /// @brief Single line to input text
// class LineEdit : public GuiElement
// {
// public:
//     using CallBack_t = std::function<void()>;
//     using CallBackVector = std::vector<CallBack_t>;

// public:
//     enum class State
//     {
//         InputingText, Idle
//     };

// public:
//     LineEdit(sf::Vector2f n_GlobalPosition = sf::Vector2f{10,10}, sf::Vector2f n_InitialSize = sf::Vector2f{50,20});

//     // override this function to implement logic of element
//     virtual void update(sf::RenderWindow& window, sf::Event& event) override;

//     // override this function to implement view of element
//     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

// private:
//     State m_LineEditState;
// };

// LineEdit::LineEdit(sf::Vector2f n_GlobalPosition, sf::Vector2f n_InitialSize)
//     : Detail::GuiElement{n_GlobalPosition, n_InitialSize}
// {
//     m_rectangle.setOutlineColor(sf::Color{104,104,104 });
//     m_LineEditState = State::Idle;
//     m_rectangle.setFillColor();
//     m_rectangle.setOutlineThickness(2);
// }


// void LineEdit::update(sf::RenderWindow& window, sf::Event& event)
// {
//     if(getIsVisible())
//     {
//         GuiElement::update(window,event);
//         checkState(window, event);
//     }
// }



// void LineEdit::draw(sf::RenderTarget& target, sf::RenderStates states) const
// {
//     if(getIsVisible())
//     {
//         GuiElement::draw(target, states);
//         target.draw(m_rectangle);
//     }
// }



// }