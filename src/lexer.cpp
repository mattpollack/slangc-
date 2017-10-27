#include "lexer.hpp"
#include <iostream>

#define IS_WS(a)				\
    ((a) == ' '  ||				\
     (a) == '\n' ||				\
     (a) == '\t')

#define IS_ALPHA(a)				\
    (((a) >= 'a'  &&				\
      (a) <= 'z') ||				\
     ((a) >= 'A'  &&				\
      (a) <= 'Z'))

#define IS_NUM(a)				\
    ((a) >= '0' &&				\
     (a) <= '9')

#define CURR (this->source[this->i])

namespace slang {
    const struct { std::string word; TokenType type; } reserved[] = {
	{ .word = "namespace", .type = TokenType::TOKEN_NAMESPACE },
	{ .word = "func",      .type = TokenType::TOKEN_FUNC      },

	{ .word = ">=",        .type = TokenType::TOKEN_GTE },
	{ .word = "<=",        .type = TokenType::TOKEN_LTE },
	{ .word = ">",         .type = TokenType::TOKEN_GT },
	{ .word = "<",         .type = TokenType::TOKEN_LT },
        
	{ .word = "+",         .type = TokenType::TOKEN_ADD },
	{ .word = "-",         .type = TokenType::TOKEN_SUBTRACT },
	{ .word = "*",         .type = TokenType::TOKEN_MULTIPLY },
	{ .word = "/",         .type = TokenType::TOKEN_DIVIDE },
	{ .word = "=",         .type = TokenType::TOKEN_EQUAL },

	{ .word = "(",         .type = TokenType::TOKEN_OPEN_PAREN },
	{ .word = ")",         .type = TokenType::TOKEN_CLOSE_PAREN },
	{ .word = "[",         .type = TokenType::TOKEN_OPEN_BRACKET },
	{ .word = "]",         .type = TokenType::TOKEN_CLOSE_BRACKET },
	{ .word = "{",         .type = TokenType::TOKEN_OPEN_BRACE },
	{ .word = "}",         .type = TokenType::TOKEN_CLOSE_BRACE },
	{ .word = "|",         .type = TokenType::TOKEN_BAR },
	{ .word = "_",         .type = TokenType::TOKEN_UNDERSCORE },

	// ..
	
	{ .word = "",          .type = TokenType::TOKEN_END       }
    };
    
    Lexer& Lexer::operator=(const Lexer& v) {
	this->source = v.source;
	this->i = v.i;
	this->l = v.c;

	return *this;
    }
	
    Token Lexer::peek() {
	Lexer save = *this;
	Token res = this->next();
	*this = save;

	return res;
    }
    
    Token Lexer::next() {
	// Skip WS while counting line and character numbers
	for ( ; IS_WS(CURR); ++this->i, ++this->c) {
	    if (CURR == '\n') {
		++this->l;
		this->c = 0;
	    }
	}

	// Status tokens
	if (CURR == '\0') {
	    return Token(this->source,
			 this->i,
			 this->l,
			 this->c,
			 TokenType::TOKEN_END,
			 0);
	}

	// Reserved
	for (int i = 0; reserved[i].type != TokenType::TOKEN_END; ++i) {
	    if (this->source.substr(this->i, reserved[i].word.size()).compare(reserved[i].word) == 0) {
		int _i = this->i;
		int c  = this->c;

		this->i += reserved[i].word.size();

		return Token(this->source,
			     _i,
			     this->l,
			     c,
			     reserved[i].type,
			     reserved[i].word.size());
	    }
	}

	// Literal
	// Identifier
	if (IS_ALPHA(CURR)) {
	    int c = this->c;
	    int i = this->i;

	    for ( ; IS_ALPHA(CURR); ++this->i, ++this->c);

	    return Token(this->source,
			 i,
			 this->l,
			 c,
			 TokenType::TOKEN_IDENTIFIER,
			 this->i - i);
	}

	// String
	if (CURR == '"') {
	    int c =   this->c;
	    int i = ++this->i;

	    for ( ; CURR != '"'; ++this->c, ++this->i) {
		// If there's a new line, that's an error
		if (CURR == '\n') {
		    return Token("Newline inside string literal",
				 this->i,
				 this->l,
				 this->c);
		}
	    }

	    return Token(this->source,
			 i,
			 this->l,
			 c,
			 TokenType::TOKEN_STRING,
			 this->i++ - i);
	}

	// Integer
	if (IS_NUM(CURR)) {
	    int c = this->c;
	    int i = this->i;

	    for ( ; IS_NUM(CURR); ++this->c, ++this->i);

	    // TODO floating point

	    return Token(this->source,
			 i,
			 this->l,
			 c,
			 TokenType::TOKEN_INTEGER,
			 this->i - i);
	}

	return Token("Unrecognized token",
		     this->i,
		     this->l,
		     this->c);
    }

    std::vector<Token> Lexer::tokenize(std::string& raw) {
	std::vector<Token> result;
	Lexer lexer(raw);

	do {
	    result.push_back(lexer.next());
	} while(!result.back().is(TokenType::TOKEN_END) &&
	        !result.back().is(TokenType::TOKEN_ERROR));

	return result;
    }
};
