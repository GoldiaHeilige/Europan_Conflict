// InputManager.cpp
#include "InputManager.h"
#include <windows.h>
#include <iostream>

USING_NS_CC;

void InputManager::setCursor(const std::string& cursorFilePath)
{
    std::wstring wCursorFilePath(cursorFilePath.begin(), cursorFilePath.end());

    HCURSOR hCursor = (HCURSOR)LoadImage(
        nullptr,
        wCursorFilePath.c_str(),
        IMAGE_CURSOR,
        0,
        0,
        LR_LOADFROMFILE
    );

    if (hCursor)
    {
        SetCursor(hCursor);
    }
    else
    {
        std::cerr << "Failed to load cursor image: " << cursorFilePath << std::endl;
    }
}
