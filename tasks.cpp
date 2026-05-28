#include "tasks.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>

// Користувацька функція, що імітує std::string::find_first_of для рядків у стилі C.
int find_first_of(const char* str, const char* s, std::size_t pos, std::size_t n)
{
    if (!str || !s) return -1;

    std::size_t len = 0;
    while (str[len]) {
        ++len;
    }
    if (pos >= len) {
        // Якщо початкова позиція знаходиться за кінцем, нічого не знайдено.
        return -1;
    }

    for (std::size_t i = pos; i < len; ++i) {
        for (std::size_t j = 0; j < n && s[j]; ++j) {
            if (str[i] == s[j]) {
                return static_cast<int>(i);
            }
        }
    }
    return -1;
}

// Обчислюємо довжину найкоротшого слова в рядку, розділеному пробілами.
std::string process_shortest_word_length(const std::string& str)
{
    std::size_t minLen = std::numeric_limits<std::size_t>::max();
    std::size_t currentLen = 0;

    for (char ch : str) {
        if (ch == ' ') {
            // Кінець слова: оновити мінімальну довжину, якщо потрібно.
            if (currentLen > 0 && currentLen < minLen) {
                minLen = currentLen;
            }
            currentLen = 0;
        } else {
            currentLen++;
        }
    }

    if (currentLen > 0 && currentLen < minLen) {
        minLen = currentLen;
    }

    if (minLen == std::numeric_limits<std::size_t>::max()) {
        return "Line contains no words";
    }

    std::ostringstream oss;
    oss << "Length of shortest word: " << minLen;
    return oss.str();
}

// Перевірити, чи рядок містить лише кириличні слова, розділені пробілами.
bool is_valid_cyrillic_words(const std::string& str)
{
    if (str.empty()) {
        return false;
    }
    if (str.front() == ' ' || str.back() == ' ') {
        // Відхилити початкові або кінцеві пробіли відповідно до умов завдання.
        return false;
    }

    bool hasWord = false;

    for (unsigned char ch : str) {
        if (ch == ' ') {
            continue;
        }
        if (ch < 0x80) {
            // Зустрівся некириличний ASCII-символ.
            return false;
        }
        hasWord = true;
    }

    return hasWord;
}

// Створити вхідний файл зразка за замовчуванням з кириличними рядками, якщо файл не існує.
void create_sample_input_file(const std::string& filename)
{
    std::ifstream ifs(filename);
    if (ifs.good()) {
        return;
    }

    std::ofstream ofs(filename);
    if (!ofs) {
        return;
    }

    ofs << "Привіт світ\n";
    ofs << "Це  приклад\n";
    ofs << "Слово\n";
    ofs << "Найкоротше  слово  тут\n";
    ofs << "Код  пишемо  разом\n";
    ofs << "Учень виконує програму\n";
    ofs << "Українська мова важлива\n";
    ofs << "Максимально      коротке    слово   є\n";
    ofs << "Нехай буде тест\n";
    ofs << "Ще один рядок\n";
    ofs << "Тестувати програму треба\n";
}

// Завдання 1: порівняння std::string::find_first_of з власною реалізацією.
void task1()
{
    std::cout << "\nTask 1: find_first_of (string method vs custom function)\n";
    std::string input;
    std::cout << "Enter a source string: ";
    std::getline(std::cin, input);
    if (input.empty()) {
        std::cout << "Input string is empty.\n";
        return;
    }

    const std::size_t kMaxSize = 2048;
    char buffer[kMaxSize];
    if (input.size() >= kMaxSize) {
        std::cout << "Input string is too long.\n";
        return;
    }

    // Копіювання вхідних даних у масив символів у стилі C з нульовим завершенням.
    for (std::size_t i = 0; i <= input.size(); ++i) {
        buffer[i] = input[i];
    }

    std::string pattern;
    std::cout << "Enter search characters: ";
    std::getline(std::cin, pattern);
    if (pattern.empty()) {
        std::cout << "Search characters cannot be empty.\n";
        return;
    }

    std::string positionInput;
    std::cout << "Enter starting position (0.." << input.size() << "): ";
    std::getline(std::cin, positionInput);
    std::size_t pos = 0;
    try {
        pos = std::stoul(positionInput);
    } catch (...) {
        // Якщо парсинг не вдався, за замовчуванням встановлюється позиція 0.
        pos = 0;
    }
    if (pos > input.size()) {
        pos = input.size();
    }

    std::size_t n = pattern.size();
    // Порівняти вбудований метод рядків з користувацькою реалізацією.
    std::size_t resultString = input.find_first_of(pattern.c_str(), pos, n);
    int resultFunc = find_first_of(buffer, pattern.c_str(), pos, n);

    std::cout << "\nstd::string::find_first_of result: ";
    if (resultString == std::string::npos) {
        std::cout << "npos\n";
    } else {
        std::cout << resultString << "\n";
    }

    std::cout << "custom find_first_of result: ";
    if (resultFunc < 0) {
        std::cout << "npos\n";
    } else {
        std::cout << resultFunc << "\n";
    }

    if ((resultString == std::string::npos && resultFunc < 0) ||
        (resultString != std::string::npos && static_cast<int>(resultString) == resultFunc)) {
        std::cout << "Results match.\n";
    } else {
        std::cout << "Results differ.\n";
    }
}

// Завдання 2: прочитати рядки з файлу, перевірити кириличні слова та записати результати.
void task2()
{
    std::cout << "\nTask 2: shortest Cyrillic word length in each line\n";

    std::string inputFilename;
    std::cout << "Enter input filename (default input.txt): ";
    std::getline(std::cin, inputFilename);
    if (inputFilename.empty()) {
        inputFilename = "input.txt";
    }

    std::string outputFilename;
    std::cout << "Enter output filename (default output.txt): ";
    std::getline(std::cin, outputFilename);
    if (outputFilename.empty()) {
        outputFilename = "output.txt";
    }

    // Переконатися, що є зразок вхідного файлу, якщо запитуваний не існує.
    create_sample_input_file(inputFilename);

    std::ifstream fin(inputFilename);
    if (!fin) {
        std::cerr << "Cannot open input file: " << inputFilename << "\n";
        return;
    }

    std::ofstream fout(outputFilename);
    if (!fout) {
        std::cerr << "Cannot open output file: " << outputFilename << "\n";
        return;
    }

    std::string line;
    int lineNo = 0;
    while (std::getline(fin, line)) {
        ++lineNo;
        if (line.empty()) {
            continue;
        }
        fout << "Line " << lineNo << ": ";
        if (is_valid_cyrillic_words(line)) {
            fout << process_shortest_word_length(line);
        } else {
            fout << "Invalid input line";
        }
        fout << "\n";
    }

    std::cout << "Processed lines from '" << inputFilename << "' and wrote results to '" << outputFilename << "'.\n";
}
