#ifndef _PARSER_H
#define _PARSER_H

#include "ast.hpp"
#include "util.hpp"

#include <map>
#include <memory>

namespace slang {
    class Parser {
    public:
	std::vector<std::shared_ptr<AST::Base>> parse(std::string& raw);
    };
};

#endif
