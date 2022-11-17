#pragma once

#include <string>
#include <ostream>
#include <vector>

struct FileLine {
    size_t line_number;
    size_t offset;
    std::string origin;
    std::string text;

    FileLine();
    FileLine(const size_t& line_number, const size_t& offset,
                const std::string& origin, const std::string& text);
    friend std::ostream& operator<<(std::ostream& os, const FileLine& fl);
};

using FileLines = std::vector<FileLine>;

FileLines readFileAsLines(const std::string& file_path);