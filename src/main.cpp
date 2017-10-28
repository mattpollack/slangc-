#include "parser.hpp"

#include <string>
#include <vector>
#include <iostream>

using namespace slang;

int main(int argc, char ** argv) {
    std::cout << "slang 0.0.0\n\n";
    
    std::string raw =
	"func add (int int)\n"
	"| x y = x + y\n"
	"\n"
	"func fib (int)\n"
	"| 0 = 1\n"
	"| 1 = 1\n"
	"| n = fib (n - 1) + fib (n - 2)\n";

    std::cout << raw << std::endl;
    
    Parser parser;
    std::vector<std::shared_ptr<AST::Base>> ast = parser.parse(raw);

    for (std::vector<std::shared_ptr<AST::Base>>::iterator it = ast.begin(); it != ast.end(); ++it) {
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
 
  

func fib (int)
| 0 = 1
| 1 = 1
| n = fib (n - 1) + fib (n - 2)



IDEA::

Build an allocator based on data strategies, for helping with pattern
matching



*/

    
