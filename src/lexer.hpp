#ifndef _LEXER_H
#define _LEXER_H

#include "token.hpp"
#include <string>
#include <vector>

namespace slang {
    class Lexer {
    private:
	std::string &source;
	int          i;
	int          l;
	int          c;
    public:
        Lexer(std::string& source)
	    : source(source)
	    , i(0)
	    , l(1)
	    , c(0)
	{}
	Lexer& operator=(const Lexer&);
	Token peek();
	Token next();
	static std::vector<Token> tokenize(std::string&);
    };
};

#endif
