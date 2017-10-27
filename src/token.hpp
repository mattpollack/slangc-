#ifndef _TOKEN_H
#define _TOKEN_H

#include <string>

namespace slang {
    enum class TokenType {
	TOKEN_START,
	    TOKEN_END,
	    TOKEN_ERROR,
	    
	    TOKEN_FUNC,
	    TOKEN_NAMESPACE,

	    TOKEN_GTE,
	    TOKEN_LTE,
	    TOKEN_GT,
	    TOKEN_LT,
	    
	    TOKEN_ADD,
	    TOKEN_SUBTRACT,
	    TOKEN_MULTIPLY,
	    TOKEN_DIVIDE,
	    TOKEN_EQUAL,
	    
	// control
	    TOKEN_OPEN_PAREN,
	    TOKEN_CLOSE_PAREN,
	    
	    TOKEN_OPEN_BRACKET,
	    TOKEN_CLOSE_BRACKET,
	    
	    TOKEN_OPEN_BRACE,
	    TOKEN_CLOSE_BRACE,
	    TOKEN_BAR,
	    TOKEN_UNDERSCORE,
	    
	// literal
	    TOKEN_IDENTIFIER,
	    TOKEN_STRING,
	    TOKEN_INTEGER,
	    TOKEN_FLOAT,
    };
    
    class Token {
    private:
        std::string& source;
	std::string  error_msg;
	int          i;
	int          l;
	int          c;
	
	TokenType    type;
	int          length;
    public:
	Token(std::string& source,
	      int i,
	      int l,
	      int c,
	      TokenType type,
	      int length)
	    : source(source)
	    , error_msg("")
	    , i(i)
	    , l(l)
	    , c(c)
	    , type(type)
	    , length(length)
	{}
	Token(std::string error_msg,
	      int i,
	      int l,
	      int c)
	    : error_msg(error_msg)
	    , source(this->error_msg)
	    , i(i)
	    , l(l)
	    , c(c)
	    , type(TokenType::TOKEN_ERROR)
	    , length(0)
	{}
	
	bool is(TokenType type) {
	    return this->type == type;
	}
	
	std::string toString() {
	    switch (this->type) {
	    case TokenType::TOKEN_START:
		return "start";
	    case TokenType::TOKEN_END:
		return "end";
	    case TokenType::TOKEN_ERROR:
		return this->error_msg;
	    case TokenType::TOKEN_FUNC:
		return "func";
	    case TokenType::TOKEN_NAMESPACE:
		return "namespace";

		
	    case TokenType::TOKEN_GTE:
		return ">=";
	    case TokenType::TOKEN_LTE:
		return "<=";
	    case TokenType::TOKEN_GT:
		return ">";
	    case TokenType::TOKEN_LT:
		return ">";
		
	    case TokenType::TOKEN_ADD:
		return "+";
	    case TokenType::TOKEN_SUBTRACT:
		return "-";
	    case TokenType::TOKEN_MULTIPLY:
		return "*";
	    case TokenType::TOKEN_DIVIDE:
		return "/";
	    case TokenType::TOKEN_EQUAL:
		return "=";
	    
	    case TokenType::TOKEN_OPEN_PAREN:
		return "(";
	    case TokenType::TOKEN_CLOSE_PAREN:
		return ")";
	    case TokenType::TOKEN_OPEN_BRACKET:
		return "[";
	    case TokenType::TOKEN_CLOSE_BRACKET:
		return "]";
	    case TokenType::TOKEN_OPEN_BRACE:
		return "{";
	    case TokenType::TOKEN_CLOSE_BRACE:
		return "}";
	    case TokenType::TOKEN_BAR:
		return "|";
	    case TokenType::TOKEN_UNDERSCORE:
		return "_";

		// Length based tokens
	    case TokenType::TOKEN_IDENTIFIER:
	    case TokenType::TOKEN_STRING:
	    case TokenType::TOKEN_INTEGER: 
	    case TokenType::TOKEN_FLOAT:
		return this->source.substr(this->i , this->length);
		
	    default:
		return "Not implemented";
	    }
	}
    };
};

#endif
