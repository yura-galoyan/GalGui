#pragma once

#include <GalGui/GuiElement.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/System/Clock.hpp>

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
    EditLine(sf::Vector2f n_GlobalPosition = sf::Vector2f{10,10}, sf::Vector2f n_InitialSize = sf::Vector2f{150,30});
    
    // override this function to implement logic of element
    virtual void update(sf::RenderWindow& window, sf::Event& event) override;

    // override this function to implement view of element
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void setOutlineColor(sf::Color newColor);
    void setBackgroundColor(sf::Color newColor);
    void setTextColor(sf::Color newColor);
    void setTextHighlightColor(sf::Color newColor);

    void setInitialSize(sf::Vector2f newSize);
    void setGlobalPosition(sf::Vector2f newPos);

    void startWriting();
    void finishWriting();
    void cancelWriting();

    virtual void enterEvent(sf::RenderWindow& window);
    virtual void leaveEvent(sf::RenderWindow& window);

    std::string getText() const;
    void setText(const std::string& text);
    void clear();

    void setBlinkDelay(const float delay);

    void setFont(const sf::Font& font);

    void showBlinkCursor();
    void hideBlinkCursor();

    void linkToEntered(const CallBack_t& callback);
    void linkToChanged(const CallBack_t& callback);

private:
    /// @brief Slots
    ///
    void onTextChanged();
    void onEntered();
    ///

private:
    bool m_bInputMode{false};
    std::string mBackupText;
    std::string mLiveTextWithCursor;
    std::string mCurrText;

    /// Mouse cursors
    sf::Cursor textCursor;

    /// This variable is made mutable so it can have blinking cursor animation
    mutable sf::Text mTextView;
    mutable std::string mLiveText;
    mutable sf::Clock blinkClock;
    mutable std::string::iterator cursorIt;
    mutable bool m_bShowBlinkCursor{true};
    float mBlinkDelay{0.7f};

    CallBackVector mCallBacksTextChanged;
    CallBackVector mCallBacksTextEntered;

};

}

}