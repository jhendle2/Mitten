#include "console.hpp"

#include <iostream>

void Console::Erro(const std::string& msg) {
    std::cerr << "\n[ERRO] " << msg << "\n\n";
    exit(EXIT_FAILURE);
}
void Console::Erro(const std::string& msg, const Token& token) {
    std::cerr << "\n[ERRO] " << msg << "\n";
    std::cerr << token << "\n\n";
    exit(EXIT_FAILURE);
}
void Console::Erro(const std::string& msg, const FileLine& fl) {
    std::cerr << "\n[ERRO] " << msg << "\n";
    std::cerr << fl << "\n\n";
    exit(EXIT_FAILURE);
}
void Console::Erro(const std::string& msg, const FileLines& fls) {
    std::cerr << "\n[ERRO] " << msg << "\n";
    for (const auto& fl : fls)
        std::cerr << fl << "\n";
    std::cerr << "\n";
    exit(EXIT_FAILURE);
}

void Console::Warn(const std::string& msg) {
    std::cerr << "\n[WARN] " << msg << "\n\n";
}
void Console::Warn(const std::string& msg, const Token& token) {
    std::cerr << "\n[WARN] " << msg << "\n";
    std::cerr << token << "\n\n";
}
void Console::Warn(const std::string& msg, const FileLine& fl) {
    std::cerr << "\n[WARN] " << msg << "\n";
    std::cerr << fl << "\n\n";
}

void Console::Info(const std::string& msg) {
    std::cerr << "[INFO] " << msg << "\n";
}
void Console::Info(const std::string& msg, const Token& token) {
    std::cerr << "[INFO] " << msg << "\n";
    std::cerr << token << "\n";
}
void Console::Info(const std::string& msg, const FileLine& fl) {
    std::cerr << "[INFO] " << msg << "\n";
    std::cerr << fl << "\n";
}