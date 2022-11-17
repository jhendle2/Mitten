#include "lexer.hpp"

#include <iostream>

#include "ops_delims.hpp"
#include "console.hpp"

Token::Token() :
offset(0), text(""), origin(FileLine()) {}

Token::Token(const size_t& offset, const std::string& text, const FileLine& origin) 
: offset(offset), text(std::move(text)), origin(origin) {}

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << token.origin.origin << ":" << token.origin.line_number << ":" << token.offset << ": " << token.text;
    return os;
}

bool Token::operator==(const std::string& right) const {
    return (this->text == right);
}

/************************************/

Tokens tokenizeLine(const FileLine& fileline) {
    Tokens tokens;
    Token temp;
    size_t offset = 0;
    temp.origin = fileline;

    auto addToken = [&tokens, &temp, &offset]() {
        if (temp.text.length() > 0) {
            temp.offset = offset - temp.text.length();
            tokens.push_back(temp);
            temp.text = "";
        }
    };

    auto appendToToken = [&temp](const char& c) {
        temp.text += c;
        temp.offset++;
    };

    bool in_string = false;
    for (size_t i = 0; i<fileline.text.length(); i++) {
        const char c = fileline.text[i];
        offset++;

        
        if (c == Delims::Quote::Single) {
            if (in_string) {
                appendToToken(c);
                addToken();
            } else {
                addToken();
                appendToToken(c);
            }
            in_string = !in_string;
            continue;
        }

        if (in_string && c == Delims::Escape) {
            appendToToken(c);
            if (i == fileline.text.length() - 1) {
                Console::Erro("Bad escape sequence. No escape char after escape", fileline);
            }
            const char escape_c = fileline.text[++i];
            if (!Delims::isEscape(escape_c)) {
                Console::Erro("Bad escape sequence. Unrecognized char", fileline);
            }
            appendToToken(escape_c);
            continue;
        }

        if (in_string) {
            appendToToken(c);
            continue;
        }

        if (isspace(c)) {
            addToken();
            continue;
        }

        if (Delims::isDelim(c)) {
            addToken();
            appendToToken(c);
            addToken();
            continue;
        }

        appendToToken(c);
    }

    if (in_string) {
        Console::Erro("Forgot to close a string literal", temp);
    }
    addToken();

    return tokens;
}

/*************************************/

Node::Node() : parent(nullptr) {

}
Node::Node(const Tokens& tokens) : tokens(tokens), parent(nullptr) {

}
Node::Node(const FileLine& fl) : tokens(tokenizeLine(fl)), parent(nullptr) {

}

NodePtr Node::create() {
    return (NodePtr)(new Node());
}
NodePtr Node::create(const Tokens& tokens) {
    return (NodePtr)(new Node(tokens));
}
NodePtr Node::create(const FileLine& fl) {
    return (NodePtr)(new Node(fl));
}
NodePtr Node::getPtr() {
    return shared_from_this();
}

FileLine Node::getOrigin() const {
    if (this->tokens.size() > 0)
        return tokens[0].origin;
    return FileLine();
}

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << node.getOrigin();
    return os;
}
std::ostream& operator<<(std::ostream& os, const NodePtr& nodeptr) {
    os << nodeptr->getOrigin();
    return os;
}

bool Node::hasParent() const {
    return this->parent != nullptr;
}

NodePtr Node::getParent() const {
    return this->parent;
}

void Node::setParent(const NodePtr& parent) {
    this->parent = parent;
}

void Node::addChild(NodePtr& child) {
    child->setParent(this->getPtr());
    children.push_back(child);
}

void Node::dump(const size_t& lvl=0) {
    for (size_t i = 0; i<lvl; i++) std::cout << "* ";
    std::cout << getPtr() << "\n";
    for (const auto& child : children) {
        child->dump(lvl+1);
    }
}

#include "keywords.hpp"

bool Node::isOpen() const {
    return
    (
        this->tokens.size() > 0 &&
        (
            this->tokens[0] == Keywords::Function::Open ||
            this->tokens[0] == Keywords::While::Open ||
            this->tokens[0] == Keywords::If::Open ||
            0
        )
    );
}
bool Node::isClose() const {
    return
    (
        this->tokens.size() > 0 &&
        (
            this->tokens[0] == Keywords::Function::Close ||
            this->tokens[0] == Keywords::While::Close ||
            this->tokens[0] == Keywords::If::Close ||
            0
        )
    );
}

#include <algorithm>
static bool arePair(const std::string& a, const std::string& b) {
    std::string a_rev = std::move(a);
    std::reverse(a_rev.begin(), a_rev.end());
    std::cout << "a_rev=`" << a_rev << "`, b=`" << b << "`\n";
    return (a_rev == b);
}

NodePtr Node::createLexerTree(const FileLines& fls) {
    NodePtr master = Node::create(FileLine(0,0,fls[0].origin,"MASTER"));
    NodePtr current = master;

    FileLine last_open_line, last_close_line;
    std::vector<std::string> last_open, last_close;

    for (const auto& fl : fls) {

        NodePtr child = Node::create(fl);
        current->addChild(child);

        const std::string& text = child->tokens[0].text;

        if (child->isClose()) {
            last_close.push_back(text);
            last_close_line = fl;

            if (!arePair(last_open.back(), last_close.back())) {
                Console::Erro("Attempted to close a block with an incompatible keyword",
                                {last_open_line, last_close_line});
            }

            if (!current->hasParent()) {
                Console::Erro("Attempted to close a block which was not opened", fl);
            }
            current = current->getParent();

            /* Remove tokens from the stacks */
            last_close.pop_back();
            last_open.pop_back();
        }

        if (child->isOpen()) {
            last_open.push_back(text);
            last_open_line = fl;
            current = child;
        }

    }

    return master;
}