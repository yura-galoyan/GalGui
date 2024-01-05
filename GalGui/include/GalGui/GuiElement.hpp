#ifndef GALGUI_GUIELEMENT_HPP
#define GALGUI_GUIELEMENT_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <memory>
#include <iostream>


namespace GalGui {

namespace Widget{

class Label;

inline namespace Detail{

// base class for all gui elements
class GuiElement : public sf::Drawable
{
public: 
    enum class LabelAlignment 
    {
        OnTop, InCenter, AtLeft, AtRight, OnBottom, None
    };

public:
    GuiElement() = default;
    GuiElement(sf::Vector2f m_GlobalPosition, sf::Vector2f m_InitialSize);
    GuiElement(const GuiElement& other);

    //virtual destructor
    virtual ~GuiElement();

    /// @brief override this function in derived classes, but call it in the first line of that function
    virtual void update(sf::RenderWindow& window, sf::Event& event) = 0;

    // override this function to implement view of element
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0 ;

    // get functions
    virtual const sf::Vector2f&  getGlobalPosition();
    virtual const sf::Vector2f&  getInitialSize();

    // set functions
    virtual void setGlobalPosition( sf::Vector2f n_pos);
    virtual void setInitialSize( sf::Vector2f n_size);

    /// By default stretch is disabled, if stretch is enabled elements may not work correctly
    static void setStretch(bool bEnabled);

    // show/hide
    void show();
    void hide();

    void setLabel(Label* label, LabelAlignment alignment);
    void setAlignment(LabelAlignment alignment);
    std::string getLabelText();


protected:
    bool getIsVisible() const;

protected:
    sf::RectangleShape m_rectangle; 
    Label* m_pLabel{ nullptr };
    LabelAlignment m_alignment{LabelAlignment::None};

private:
    bool m_bIsVisible{true};
    inline static bool m_bIsEnabled{false};

};

}

}

}

#endif //GALGUI_GUIELEMENT_HPP