#pragma once

#include <string>

namespace Delims {
    using Delim = const char;

    Delim Comment = '#';

    Delim Dot = '.';
    Delim Comma = ',';
    
    Delim Plus = '+';
    Delim Minus = '-';
    Delim Mult = '*';
    Delim Div = '/';

    Delim Equals = '=';

    Delim Escape = '\\';

    namespace Quote {
        Delim Single = '\'';
        Delim Double = '\"';
    }

    namespace Brace {
        Delim Open = '{';
        Delim Close = '}';
    }

    namespace Paren {
        Delim Open = '(';
        Delim Close = ')';
    }

    bool isEscape(const char& c);
    bool isDelim(const char& c);

    const std::string Whitespace = " \t\n\r";
};