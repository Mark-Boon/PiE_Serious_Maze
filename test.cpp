#include <windows.h>

int main() {
  system("mode 80,50");   //Set mode to ensure window does not exceed buffer size
  SMALL_RECT WinRect = {0, 0, 20, 10};   //New dimensions for window in 8x12 pixel chars
  SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &WinRect);   //Set new size for window

  system("PAUSE");
  return 0;
}