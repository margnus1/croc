#include "console.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

void Console::moveCursorUp(int lines) {
#ifdef _WIN32
  std::cout << std::flush;
  CONSOLE_SCREEN_BUFFER_INFO sbi;
  HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
  GetConsoleScreenBufferInfo(console, &sbi);
  COORD newPos = {0, sbi.dwCursorPosition.Y - lines};
  SetConsoleCursorPosition(console, newPos);
#else
  std::cout << "\x1B[" << lines << "F";
#endif
};
