#include <GalGui/LineEdit.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
 
namespace GalGui::Widget
{

LineEdit::LineEdit(const std::string& text, const sf::Font* font, sf::Vector2f n_GlobalPosition, sf::Vector2f n_InitialSize )
    : TextButton(text, font, n_GlobalPosition, n_InitialSize)
{
    
    linkToClicked([this](){
        if(bInputMode) return;
        bInputMode = true;
        m_sBackupText = getText();
        setOutlineColor(sf::Color::Yellow);
        nexText.clear();
        setText("|");
    });

    setAutoAdjustSize(true);
    setAlignment(Alignment::Left);

}

void LineEdit::update(sf::RenderWindow& window, sf::Event& event)
{
    Button::update(window,event);
    if(bInputMode)
    {
        if(event.type == sf::Event::TextEntered)
        {
            if(event.text.unicode != '\b')
                nexText.append(sf::String(event.text.unicode).toAnsiString());
            else
            {   
                if(nexText.size())
                    nexText.pop_back();
            }
            setText(nexText + "_");
            onTextChanged();
        }
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Escape)
            {
                setText(m_sBackupText);

                bInputMode = false;
                setOutlineColor(sf::Color{104,104,104});
            }
            if(event.key.code == sf::Keyboard::Enter)
            {
                setText(nexText);
                onTextEntered();

                bInputMode = false;
                setOutlineColor(sf::Color{104,104,104});
            }
        }

    }
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
    {
        cb();
    }
}

void LineEdit::onTextEntered()
{
    for(auto& cb : mCallBacksTextEntered)
    {
        cb();
    }
}

}