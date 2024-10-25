#include <GalGui/EditLine.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

namespace GalGui
{

namespace Widget
{

EditLine::EditLine(sf::Vector2f n_GlobalPosition, sf::Vector2f n_InitialSize)
    : GuiElement(n_GlobalPosition, n_InitialSize)
{
    setGlobalPosition(n_GlobalPosition);
    setInitialSize(n_InitialSize);

    textCursor.loadFromSystem(sf::Cursor::Text);
    m_rectangle.setFillColor(sf::Color{200,200,200});
    m_rectangle.setOutlineColor(sf::Color{55,55,55});
    m_rectangle.setOutlineThickness(2);
    mTextView.setCharacterSize(20);
    mTextView.setFillColor(sf::Color::Black);
    mLiveText = mCurrText;
    if (!mLiveText.empty())
        cursorIt = mLiveText.end();
    else
        cursorIt = mLiveText.begin();
}


void EditLine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(!getIsVisible()) return;

    GuiElement::draw(target, states);

    target.draw(m_rectangle, states);

    if(m_bInputMode)
    {
        if(blinkClock.getElapsedTime().asSeconds() > mBlinkDelay)
        {
            m_bShowBlinkCursor = !m_bShowBlinkCursor;
            blinkClock.restart();
        }

        if(m_bShowBlinkCursor)
        {
            cursorIt = mLiveText.insert(cursorIt, '|');
            mTextView.setString(mLiveText);
            cursorIt = mLiveText.erase(cursorIt);
        }
        else
            mTextView.setString(mLiveText);
    }
    target.draw(mTextView, states);
}

void EditLine::update(sf::RenderWindow& window, sf::Event& event)
{
    if(!getIsVisible()) return;

    GuiElement::update(window,event);

    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(isOnGuiElement(window))
        {
            startWriting();
        }
        else
        {
            finishWriting();
        }
    }
    if(m_bInputMode)
    {
        if(event.type == sf::Event::TextEntered)
        {
            switch (event.text.unicode)
            {
            case '\b':
                {
                    // delete last character
                    if(!mLiveText.empty())
                    {
                        if(cursorIt == mLiveText.begin())
                            break;

                        if(!mLiveText.empty())
                            std::advance(cursorIt, -1);
                        cursorIt = mLiveText.erase(cursorIt);
                    }
                }
                break;
            case '\n':
                {
                    // skip
                }
                break;
            case '\r':
                {
                    // skip
                }
                break;
            default:
                {
                    if(event.text.unicode > 128) break;
                    // insert character
                    cursorIt = mLiveText.insert(cursorIt, static_cast<char>(event.text.unicode));
                    std::advance(cursorIt, 1);
                }
                break;
            }
            onTextChanged();
            mTextView.setString(mLiveText);
            blinkClock.restart();
            m_bShowBlinkCursor = true;
        }
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Left)
            {
                // Move cursor left 
                if(cursorIt != mLiveText.begin())
                    std::advance(cursorIt, -1);
            }
            else if(event.key.code == sf::Keyboard::Right)
            {
                // Move cursor right
                if(cursorIt != mLiveText.end())
                    std::advance(cursorIt, 1);
                
            }
            else if(event.key.code == sf::Keyboard::Escape)
            {
                cancelWriting();
            }
            else if(event.key.code == sf::Keyboard::Enter)
            {
                if (event.key.shift)
                {
                    cursorIt = mLiveText.insert(cursorIt,'\n');
                    std::advance(cursorIt, 1);
                }
                else
                {
                    finishWriting();
                }
            }
            blinkClock.restart();
            m_bShowBlinkCursor = true;
        }
    }
}

void EditLine::setOutlineColor(sf::Color newColor)
{
    m_rectangle.setOutlineColor(newColor);
}

void EditLine::setBackgroundColor(sf::Color newColor)
{

}

void EditLine::setTextColor(sf::Color newColor)
{
    mTextView.setFillColor(newColor);
}

void EditLine::setFont(const sf::Font& font)
{
    mTextView.setFont(font);
}

void EditLine::showBlinkCursor()
{
    m_bShowBlinkCursor = true;
}

void EditLine::hideBlinkCursor()
{
    m_bShowBlinkCursor = false;
}

std::string EditLine::getText() const
{
    return mLiveText;
}

void EditLine::setText(const std::string& text)
{
    mTextView.setString(text);
    mLiveText = text;
}

void EditLine::onTextChanged()
{
    for(auto& fun : mCallBacksTextChanged)
    {
        fun();
    }
}

void EditLine::linkToEntered(const CallBack_t& callback)
{
    mCallBacksTextEntered.push_back(callback);
}

void EditLine::linkToChanged(const CallBack_t& callback)
{
    mCallBacksTextChanged.push_back(callback);
}

void EditLine::onEntered()
{
    for(auto& fun : mCallBacksTextEntered)
    {
        fun();
    }
}

void EditLine::setBlinkDelay(const float delay)
{
    mBlinkDelay = delay;
}

void EditLine::clear()
{
    mLiveText.clear();
    mTextView.setString("");
}

void EditLine::startWriting()
{
    m_bInputMode = true;
    blinkClock.restart();
    setOutlineColor(sf::Color::Blue);
}

void EditLine::finishWriting()
{
    m_bInputMode = false;
    mTextView.setString(mLiveText);
    mBackupText = mLiveText;
    setOutlineColor(sf::Color{55,55,55});
    onEntered();
}

void EditLine::cancelWriting()
{
    m_bInputMode = false;
    mTextView.setString(mBackupText);
    mLiveText = mBackupText;
    if (!mLiveText.empty())
        cursorIt = mLiveText.end();
    else
        cursorIt = mLiveText.begin();
    setOutlineColor(sf::Color{55,55,55});
}

void EditLine::setInitialSize(sf::Vector2f newSize)
{
    GuiElement::setInitialSize(newSize);
}

void EditLine::setGlobalPosition(sf::Vector2f newPos)
{
    GuiElement::setGlobalPosition(newPos);
    mTextView.setPosition(newPos + sf::Vector2f{3,3});
}


void EditLine::enterEvent(sf::RenderWindow& window)
{
    window.setMouseCursor(textCursor);
}

void EditLine::leaveEvent(sf::RenderWindow& window)
{
    window.setMouseCursor(getDefaultCursor());
}

}

}