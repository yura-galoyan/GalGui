#include <GalGui/LineEdit.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
 
namespace GalGui::Widget
{

LineEdit::LineEdit(const std::string& text, const sf::Font* font, sf::Vector2f n_GlobalPosition, sf::Vector2f n_InitialSize )
    : TextButton(text, font, n_GlobalPosition, n_InitialSize)
{
    
    linkToClicked([this](){
        if(bInputMode) return;
        setInputMode(true);
    });

    setAutoAdjustSize(true);
    setAlignment(Alignment::Left);

}

void LineEdit::clear()
{
    nexText.clear();
    setText(nexText);
}

void LineEdit::setInputMode(bool bEnabled)
{
    bInputMode = bEnabled;
    if(bInputMode)
    {
        m_sBackupText = getText();
        setOutlineColor(sf::Color::Yellow);
        nexText.clear();
        setText("|");
    }
    else
    {
        setOutlineColor(sf::Color{104,104,104});
    }
}

void LineEdit::update(sf::RenderWindow& window, sf::Event& event)
{
    if(!getIsVisible()) return;
    
    Button::update(window,event);
    if(bInputMode)
    {
        if(event.type == sf::Event::TextEntered)
        {
            switch (event.text.unicode)
            {
            case '\b':
                {
                    // delete last character
                    if(nexText.size())
                        nexText.pop_back();
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
                    // insert character
                    nexText.append(sf::String(event.text.unicode).toAnsiString());
                }
                break;
            }
            setText(nexText);
            onTextChanged();
        }
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Escape)
            {
                setText(m_sBackupText);
                setInputMode(false);
            }
            if(event.key.code == sf::Keyboard::Enter)
            {
                onTextEntered();
            }
        }

    }
}

void LineEdit::setInitialSize(sf::Vector2f n_size)
{
    TextButton::setInitialSize(n_size);
    setCharacterSize(n_size.y/2);
}
    
std::string LineEdit::getContent() const
{
    return nexText;
}

void LineEdit::linkToChanged(CallBack_t cb)
{
    mCallBacksTextChanged.push_back(cb);
}

void LineEdit::linkToEntered(CallBack_t cb)
{
    mCallBacksTextEntered.push_back(cb);
}

void LineEdit::onTextChanged()
{
    for(auto& cb : mCallBacksTextChanged)
        cb();
}

void LineEdit::onTextEntered()
{
    for(auto& cb : mCallBacksTextEntered)
        cb();
}

}