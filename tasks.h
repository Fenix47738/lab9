#pragma once

// Інтерфейс для реалізації завдань та допоміжних функцій.
#include <string>

// Функції завдання меню.
void task1();
void task2();

// Користувацька реалізація string::find_first_of для рядків у стилі C.
int find_first_of(const char* str, const char* s, std::size_t pos, std::size_t n);

// Допоміжні засоби обробки рядків для завдання 2.
std::string process_shortest_word_length(const std::string& str);
bool is_valid_cyrillic_words(const std::string& str);

// Створити вхідний файл за замовчуванням, якщо файлу не існує.
void create_sample_input_file(const std::string& filename);
