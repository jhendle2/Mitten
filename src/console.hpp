#pragma once

#include <string>

#include "lexer.hpp"

namespace Console {
    
    void Erro(const std::string& msg);
    void Erro(const std::string& msg, const Token& token);
    void Erro(const std::string& msg, const FileLine& fl);
    void Erro(const std::string& msg, const FileLines& fls);

    void Warn(const std::string& msg);
    void Warn(const std::string& msg, const Token& token);
    void Warn(const std::string& msg, const FileLine& fl);

    void Info(const std::string& msg);
    void Info(const std::string& msg, const Token& token);
    void Info(const std::string& msg, const FileLine& fl);

};