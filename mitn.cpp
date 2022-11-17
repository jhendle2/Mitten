#include <iostream>

#include "file_reader.hpp"
#include "lexer.hpp"

int main() {
    FileLines fls = readFileAsLines("./examples/test.mitn");

    // for (const FileLine& fl : fls) {
    //     std::cout << fl << "\n";
    //     Tokens line_as_tokens = tokenizeLine(fl);
    //     for (const Token& token : line_as_tokens) {
    //         std::cout << " * " << token << "\n";
    //     }
    // }

    NodePtr master = Node::createLexerTree(fls);
    master->dump(0);

    return EXIT_SUCCESS;
}