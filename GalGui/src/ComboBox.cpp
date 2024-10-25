
#include <GalGui/ComboBox.hpp>

namespace GalGui {

namespace Widget {

void ComboBox::append(const std::string &value)
{
    Menu::append(value);
    m_values.back().linkToClicked( 
        [this, value](){
            m_bIsPressed = false;
            onSetCurrentText(value);
        }
    );
}

bool ComboBox::setCurrentText(const std::string &newText)
{
    auto it = std::find_if(m_values.begin(), m_values.end(), [&newText](const auto& val){
        return val.getText() == newText;
    });

    if(it != m_values.end())
    {
        setText(newText);
        return true;
    }
    return false;
}

void ComboBox::onSetCurrentText(const std::string &text)
{
    setText(text);
    for(const auto& cb : m_callBacks)
    {
        cb(text);
    } 
}

void ComboBox::linkOnSetCurrentText(const CallBack_t &callBack)
{
    m_callBacks.push_back(callBack);
}

}

}