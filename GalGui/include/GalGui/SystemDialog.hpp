#pragma once

#include <string>

#ifdef _WIN32
#include <Windows.h>
#include <commdlg.h>
#elif

#endif


namespace GalGui
{

namespace SystemDialog
{

enum DialogType
{
#ifdef _WIN32
    InfoDialog = MB_ICONINFORMATION,
    ErrorDialog = MB_ICONERROR 
#elif

#endif

};

std::string openFile();
void messageBox(const std::wstring& dialogName,const std::wstring& dialogText, DialogType type);

}

}
