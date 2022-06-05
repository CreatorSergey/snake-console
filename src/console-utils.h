#pragma once
#include <cstdlib>
#include <windows.h>
#include <stdio.h>

namespace utils {

/**
 * @brief Очитка экрана
 */
void ClearScreen() {
   system("cls");
}

/**
 * @brief Установить видимость курсора
 * @param visible - видимость
 */
void SetCursorVisible(bool visible) {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = visible;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

} // namespace utils

