#include "ops_delims.hpp"

bool Delims::isEscape(const char& c) {
    return (
        c == 'n' ||
        c == 't' ||
        c == 'v' ||
        c == 'r' ||
        c == 'b' ||
        c == '\'' ||
        c == '\"' ||
        c == '\\' ||
        0
    );
}

bool Delims::isDelim(const char& c) {
    return (
        c == Delims::Dot ||
        c == Delims::Comma ||
        c == Delims::Plus ||
        c == Delims::Minus ||
        c == Delims::Mult ||
        c == Delims::Div ||
        c == Delims::Equals ||
        c == Delims::Quote::Double ||
        c == Delims::Quote::Single ||
        c == Delims::Brace::Open ||
        c == Delims::Brace::Close ||
        c == Delims::Paren::Open ||
        c == Delims::Paren::Close ||
        0
    );
}