#include <GalGui/SystemDialog.hpp>

#ifdef _WIN32
#include <windows.h>
#include <commdlg.h>
#endif

namespace GalGui
{

namespace SystemDialog
{

std::string openFile()
{
    
#ifdef _WIN32
    OPENFILENAMEA ofn;
    char szFile[260] = { 0 };

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;  // Use NULL if no owner window
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "Text Files\0*.TXT\0All Files\0*.*\0";
    ofn.lpstrTitle = "Open File";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&ofn)) {
        return ofn.lpstrFile;
    } else {
        return {};
    }

#elif
    return std::string();
#endif 
}


void messageBox(const std::wstring& dialogName,const std::wstring& dialogText, DialogType type)
{
#ifdef _WIN32
    MessageBox(nullptr, dialogText.c_str(), dialogName.c_str(), type | MB_OK);
#elif
#endif
}

}

}