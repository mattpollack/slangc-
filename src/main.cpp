#include "parser.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <ctime>

using namespace slang;
using namespace std;

void execute(std::string raw) {
    //cout << raw << endl;
    
    Parser parser;
    vector<shared_ptr<AST::Base>> ast = parser.parse(raw);

    if (ast.size() == 0)
	cout << "Something unexpected happened..." << endl;
    else if (ast[0]->is(AST::Type::ERROR)) {
	cout << dynamic_cast<AST::Error*>(ast[0].get())->toString() << endl;
	return;
    }

    cout << "Ok!" << endl;
}

int main(int argc, char ** argv) {
    // Timer Begin
    clock_t begin = clock();
    
    cout << "slang 0.0.0\n";
    
    execute("(derp derp derp derp)");
    
    execute("func random (int int)\n"
	    "| x y = \n"
	    "  (add \n"
	    "    (sub x y) \n"
	    "    (dub y x)) \n");

    // Timer End
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout << "Elapsed " << elapsed_secs << "(s)" << endl;
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

    
