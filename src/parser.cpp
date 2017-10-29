#include "parser.hpp"
#include "lexer.hpp"

#include <iostream>

#define ERROR_NODE(a) (std::make_shared<AST::Error>(AST::Error((a))))

namespace slang {
    typedef std::shared_ptr<AST::Base> base_t;
    
    template<class T>
    T base_cast(base_t b) {
	return *dynamic_cast<T*>(b.get());
    }
    
    base_t parseIdentifier(Lexer& lexer) {
	if (!lexer.peek().is(TokenType::TOKEN_IDENTIFIER)) {
	    return ERROR_NODE("Expected token identifier");
	}
	
	Token token = lexer.next();

	return std::make_shared<AST::Identifier>(
	    AST::Identifier(
		token.toString()));
    }

    bool consumeSignature(std::vector<Token> &list, Lexer &lexer) {
	while (true) {
	    /**/ if (lexer.peek().is(TokenType::TOKEN_OPEN_PAREN)) {
		list.push_back(lexer.next());

		if (!consumeSignature(list, lexer) || !lexer.peek().is(TokenType::TOKEN_CLOSE_PAREN))
		    return false;

		list.push_back(lexer.next());
	    }
	    else if (lexer.peek().is(TokenType::TOKEN_OPEN_BRACKET)) {
		list.push_back(lexer.next());

		if (!consumeSignature(list, lexer) || !lexer.peek().is(TokenType::TOKEN_CLOSE_BRACKET))
		    return false;

		list.push_back(lexer.next());
	    }
	    else if (lexer.peek().is(TokenType::TOKEN_IDENTIFIER)) {
		list.push_back(lexer.next());
	    }
	    else {
		return true;
	    }
	}
    }
    
    base_t parseSignature(Lexer &lexer) {
	if (!lexer.peek().is(TokenType::TOKEN_OPEN_PAREN)) {
	    return ERROR_NODE("Expected token open paren");
	}

	std::vector<Token> list;

	if (consumeSignature(list, lexer)) {
	    return std::make_shared<AST::Signature>(
		AST::Signature(list));
	}
	else {
	    return ERROR_NODE("Ill formatted signature TODO ");
	}
    }

    base_t parseExpression(Lexer& lexer) {
	return ERROR_NODE("TODO Expression");
    }
    
    base_t parseMatchExpression(Lexer& lexer) {
	/*
          ### TODO
	  * Literals
	  - Match Number
	  - Match Float
	  - Match String

	  * Special
	  - skip
	  - none
	  
	  * Array
	    # head, tail
	  - [ (parseMatchExpression)
	    : (parseMatchExpression)
	  - [ (parseMatchExpression)
	    : (parseMatchExpression)
	    : (parseMatchExpression) ]

	    # middle split
	  - [ (parseMatchExpression) 
	    | (parseMatchExpression) ]
	  - [ (parseMatchExpression)
	    | (parseMatchExpression)
	    | (parseMatchExpression) ]

	  ### DONE
	  * Identifier
	  
	 */
	
	// Identifier
	base_t id = parseIdentifier(lexer);

	if (id->is(AST::Type::ERROR))
	    return id;
	if (id->is(AST::Type::IDENTIFIER))
	    return std::make_shared<AST::MatchExpression>(
		AST::MatchExpression(
		    base_cast<AST::Identifier>(id)));
	
	return ERROR_NODE("Unexpected parser end in match expression");
    }

    base_t parseMatch(Lexer& lexer) {
	if (!lexer.peek().is(TokenType::TOKEN_BAR)) {
	    return ERROR_NODE("Match must begin with a '|'");
	}

	lexer.next();

	std::vector<AST::MatchExpression> mexprs;
	
	while (true) {
	    /**/ if (lexer.peek().is(TokenType::TOKEN_EQUAL)) {
		lexer.next();

	        base_t body = parseExpression(lexer);

		if (body->is(AST::Type::ERROR))
		    return body;
		if (body->is(AST::Type::EXPRESSION))
		    return std::make_shared<AST::Match>(
			AST::Match(
			    mexprs,
			    base_cast<AST::Expression>(body)));

	        return ERROR_NODE("Expected match expression body");
	    }
	    else {
		base_t mexpr = parseMatchExpression(lexer);

		if (!mexpr->is(AST::Type::MATCH_EXPRESSION)) return mexpr;

		mexprs.push_back(base_cast<AST::MatchExpression>(mexpr));
	    }
	}
    }

    base_t parsePattern(Lexer& lexer) {
        std::vector<AST::Match> matches;

	do {
	    base_t match = parseMatch(lexer);

	    if (!match->is(AST::Type::MATCH)) return match;
	    
	    matches.push_back(base_cast<AST::Match>(match));
	} while (lexer.peek().is(TokenType::TOKEN_BAR));
	
	return std::make_shared<AST::Pattern>(
	    AST::Pattern(matches));
    }
    
    base_t parseFunc(Lexer& lexer) {
	if (!lexer.next().is(TokenType::TOKEN_FUNC)) {
	    return ERROR_NODE("Attempt to parse unspecified function");
	}

        base_t identifier = parseIdentifier(lexer);
	if (!identifier->is(AST::Type::IDENTIFIER)) return identifier;
	
        base_t signature = parseSignature(lexer);
	if (!signature->is(AST::Type::SIGNATURE)) return signature;

        base_t pattern = parsePattern(lexer);
	if (!pattern->is(AST::Type::PATTERN)) return pattern;

        return std::make_shared<AST::Func>(
	    AST::Func(
		base_cast<AST::Identifier>(identifier),
	        base_cast<AST::Signature>(signature),
		base_cast<AST::Pattern>(pattern)));
    }
    
    std::vector<base_t> Parser::parse(std::string& raw) {
	std::vector<std::shared_ptr<AST::Base>> result;
	Lexer lexer(raw);

	while (true) {
	    Token token = lexer.peek();

	    /**/ if (token.is(TokenType::TOKEN_END)) {
		break;
	    }
	    else if (token.is(TokenType::TOKEN_FUNC)) {
		result.push_back(parseFunc(lexer));
	    }
	    else {
		result.push_back(ERROR_NODE("Unexpected parser end"));;
		break;
	    }
	}
	
	return result;
    }
};
