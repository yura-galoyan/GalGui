#ifndef GALGUI_GUIELEMENT_HPP
#define GALGUI_GUIELEMENT_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <memory>
#include <iostream>
#include <functional>

namespace sf
{
    class RenderWindow;
    class RenderTarget;
}

namespace GalGui {

namespace Widget{

class Label;
class Layout;

enum class ElementType
{
    Button, CheckBox, GuiElement, HorizontalLayout, ComboBox,
    Label, VerticalLayout, TextButton, Slider, Frame
};

// base class for all gui elements
class GuiElement : public sf::Drawable
{
    
public: 
    enum class LabelAlignment 
    {
        OnTop, InCenter, AtLeft, AtRight, OnBottom, None
    };

public:
    GuiElement();
    GuiElement(sf::Vector2f globalPosition, sf::Vector2f initialSize);
    GuiElement(const GuiElement& other);
    GuiElement(Layout* pParent);

    void setElementName(const std::string& elementName);

    std::string getElementName() const;

    ///virtual destructor
    virtual ~GuiElement();

    /// @brief override this function in derived classes, but call it in the first line of that function
    virtual void update(sf::RenderWindow& window, sf::Event& event);

    /// override this function to implement view of element
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0 ;

    /// get functions
    virtual sf::Vector2f getGlobalPosition() const ;
    virtual sf::Vector2f getInitialSize() const;

    /// set functions
    virtual void setGlobalPosition( sf::Vector2f n_pos);
    virtual void setInitialSize( sf::Vector2f n_size);

    /// By default stretch is disabled, if stretch is enabled elements may not work correctly
    static void setStretch(bool bEnabled);

    /// show/hide
    void show();
    void hide();

    void setLabel(Label* label, LabelAlignment alignment);
    void setLabelAlignment(LabelAlignment alignment);
    std::string getLabelText();

    virtual Layout* getParent() const;    
    virtual void setParent(Layout* pParent);

    void setType(ElementType type);
    ElementType getType() const;

    bool getIsVisible() const;
    
protected:
    void refresh();
    virtual void enterEvent() { std::cout << "default implemetation" << std::endl; };
    virtual void leaveEvent() { std::cout << "default implemetation" << std::endl; };
protected:
    sf::RectangleShape m_rectangle; 
    Label* m_pLabel{ nullptr };
    LabelAlignment m_alignment{LabelAlignment::None};

private:
    bool m_bIsVisible{true};
    bool m_bDeleteLabel{false};
    bool m_bMouseFirstIn{true};
    inline static bool m_bIsEnabled{false};

    std::string mElementName;
    ElementType mType;
    Layout* mParent;
};

}

}


#endif //GALGUI_GUIELEMENT_HPP