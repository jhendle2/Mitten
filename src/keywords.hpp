#pragma once

#include <string>

namespace Keywords {
    using Keyword = const std::string;

    Keyword Return = "ret";

    namespace Function {
        Keyword Open = "fn";
        Keyword Close = "nf";
    };

    namespace While {
        Keyword Open = "whl";
        Keyword Close = "lhw";
    };

    namespace If {
        Keyword Open = "if";
        Keyword Close = "fi";
    };
};