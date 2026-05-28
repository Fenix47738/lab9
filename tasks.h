#pragma once

#include <string>

void task1();
void task2();
int find_first_of(const char* str, const char* s, std::size_t pos, std::size_t n);
std::string process_shortest_word_length(const std::string& str);
bool is_valid_cyrillic_words(const std::string& str);
void create_sample_input_file(const std::string& filename);
