#pragma once

#include <string>
#include <ostream>
#include <vector>

#include "file_reader.hpp"

struct Token {
    size_t offset;
    std::string text;
    FileLine origin;

    Token();
    Token(const size_t& offset, const std::string& text, const FileLine& origin);
    friend std::ostream& operator<<(std::ostream& os, const Token& token);

    bool operator==(const std::string& right) const;
};

using Tokens = std::vector<Token>;
Tokens tokenizeLine(const FileLine& fileline);

#include <memory>

struct Node;
using NodePtr = std::shared_ptr<Node>;

struct Node : public std::enable_shared_from_this<Node> {
    Tokens tokens;
    
    NodePtr parent;
    std::vector<NodePtr> children;

    Node();
    Node(const Tokens& tokens);
    Node(const FileLine& fl);

    [[nodiscard]] static NodePtr create();
    [[nodiscard]] static NodePtr create(const Tokens& tokens);
    [[nodiscard]] static NodePtr create(const FileLine& fl);
    NodePtr getPtr();

    FileLine getOrigin() const;

    friend std::ostream& operator<<(std::ostream& os, const Node& node);
    friend std::ostream& operator<<(std::ostream& os, const NodePtr& nodeptr);

    bool hasParent() const;
    NodePtr getParent() const;
    void setParent(const NodePtr& parent);
    void addChild(NodePtr& child);

    void dump(const size_t& lvl);

    bool isOpen() const;
    bool isClose() const;

    static NodePtr createLexerTree(const FileLines& fls);
};
