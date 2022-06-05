#include "game.h"

/**
 * @brief Старт приложения
 * @return int - код ошибки
 */
int main() {
   Game intance;
   intance.Init();
   intance.Run();
   return 0;
}