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

    void selectText();

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