#pragma once

#include <GalGui/Menu.hpp>

namespace GalGui {

namespace Widget {

class ComboBox : public Menu
{
public:
    void append(const std::string &value);
    bool setCurrentText(const std::string& newText);

// signals
public:
    void onSetCurrentText(const std::string& text);

// slots emits when text is changed
public:
    void linkOnSetCurrentText(const CallBack_t& callBack);

};

}

}