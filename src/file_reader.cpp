#include "file_reader.hpp"

FileLine::FileLine() :
line_number(0), offset(0), origin(""), text("") {}

FileLine::FileLine(const size_t& line_number=0, const size_t& offset=0, const std::string& origin="", const std::string& text="") :
line_number(line_number), offset(offset), origin(std::move(origin)), text(std::move(text)) {}

std::ostream& operator<<(std::ostream& os, const FileLine& fl) {
    os << fl.origin << ":" << fl.line_number << ": " << fl.text;
    // os << fl.origin << ":" << fl.line_number << ":" << fl.offset << ": " << fl.text;
    return os;
}

#include <fstream>
#include <iostream>

#include "ops_delims.hpp"

static void removeComments(std::string& line) {
    if (line.length() == 0) return;
    const size_t comment_index = line.find_first_of(Delims::Comment);
    if (comment_index >= 0) {
        line = line.substr(0, comment_index);
    }
}

static size_t lstrip(std::string& line) {
    if (line.length() == 0) return std::string::npos;
    const size_t last_l_space = line.find_first_not_of(Delims::Whitespace);
    if (last_l_space != std::string::npos) {
        line = line.substr(last_l_space);
    }
    return last_l_space;
}

static void rstrip(std::string& line) {
    if (line.length() == 0) return;
    const size_t last_r_space = line.find_last_not_of(Delims::Whitespace);
    if (last_r_space != std::string::npos) {
        line = line.substr(0, last_r_space+1);
    }
}

FileLines readFileAsLines(const std::string& file_path) {
    std::ifstream file_stream(file_path);
    std::string buf;

    FileLines file_as_lines;
    auto addLine = [&file_as_lines](const FileLine& fl) {
        if (fl.text.length() > 0) {
            file_as_lines.push_back(fl);
            // std::cout << fl << "\n";
        }
    };

    size_t line_number = 0;
    while (std::getline(file_stream, buf)) {
        removeComments(buf);
        rstrip(buf);
        const size_t offset = lstrip(buf);
        line_number++;

        FileLine fl = FileLine(line_number, offset, file_path, buf);
        addLine(fl);
    }

    return file_as_lines;
}