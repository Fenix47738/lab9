// Головна точка входу для консольного застосунку.
// Ця програма використовує просте меню для виклику task1 або task2.
#include <iostream>
#include <limits>
#include "tasks.h"

int main()
{
    // Неодноразово показувати користувачеві меню, доки він не вирішить вийти.
    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1 - Task 1: find_first_of\n";
        std::cout << "2 - Task 2: shortest Cyrillic word length\n";
        std::cout << "0 - Exit\n";
        std::cout << "Enter choice: ";

        int choice = -1;
        if (!(std::cin >> choice)) {
            // Обробляємо нецілочисельний вхід, очищуючи потік та ігноруючи решту рядка.
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        // Очищаємо символ нового рядка зліва, зчитуючи числовий вибір.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                task1();
                break;
            case 2:
                task2();
                break;
            case 0:
                // Exit the program cleanly.
                std::cout << "Exiting.\n";
                return 0;
            default:
                // Handle any invalid menu option.
                std::cout << "Please choose 0, 1, or 2.\n";
                break;
        }
    }
}
