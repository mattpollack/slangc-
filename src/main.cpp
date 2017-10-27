#include "parser.hpp"

#include <string>
#include <vector>
#include <iostream>

using namespace slang;

int main(int argc, char ** argv) {
    std::cout << "slang 0.0.0\n\n";
    
    std::string raw =
	"func add (int int) x y = x + y\n"
	"func fraction (int int)\n"
	"| _ 0 = none\n"
	"| n d = {\n"
	"  n = n\n"
	"  d = d\n"
	"}";

    std::cout << raw << std::endl;
    
    Parser parser;
    std::vector<std::shared_ptr<AST::Base>> ast = parser.parse(raw);

    for (std::vector<std::shared_ptr<AST::Base>>::iterator it = ast.begin() ; it != ast.end(); ++it) {
	/**/ if (it->get()->is(AST::Type::ERROR)) {
	    AST::Error * node = dynamic_cast<AST::Error *>(it->get());
	    std::cout << node->toString() << std::endl;
	}
	else if (it->get()->is(AST::Type::FUNC)) {
	    AST::Func * node = dynamic_cast<AST::Func *>(it->get());
	    std::cout << node->toString() << std::endl;
	}
    }
}

/*
    std::vector<slang::Token> tokenized = slang::Lexer::tokenize(raw);

    std::cout << raw << std::endl;
    
    for (std::vector<slang::Token>::iterator it = tokenized.begin() ; it != tokenized.end(); ++it) {
	std::cout << it->toString() << std::endl;
	}*/

    
