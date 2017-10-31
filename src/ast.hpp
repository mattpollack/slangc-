#ifndef _AST_H
#define _AST_H

#include "token.hpp"

#include <memory>
#include <string>
#include <vector>

namespace slang {
    namespace AST {
	enum class Type {
	    ERROR,
		FUNC,
		IDENTIFIER,
		LITERAL,
		SIGNATURE,
		PATTERN,

	    // Expression
		EXPRESSION,

	    // NOTE: maybe create a seperate type class for match
	    //       expressions.
	    // More todo here, just using these for now
		MATCH,
		MATCH_EXPRESSION,

	    // Match Expressions
		MATCH_IDENTIFIER,   // foo
		MATCH_LITERAL,      // 1 "foo"
		MATCH_SKIP,         // _
	        MATCH_ARRAY_EMPTY,  // []
		MATCH_ARRAY_MIDDLE, // [l|r]
		MATCH_ARRAY_HEAD,   // [h:t]
		MATCH_ARRAY_EXACT,  // [1 2], like an array literal
	};

        /**
	 * Base
	 */
	class Base {
	protected:
	    Type type;
	public:
	    Base(Type type) : type(type) {}
	    bool is(Type type) { return this->type == type; }
	    virtual std::string toString() { return "Base"; }
	};

	/**
	 * Error
	 */
	class Error : public Base {
	private:
	    std::string msg;
	public:
	    Error(std::string msg)
		: Base(Type::ERROR)
		, msg(msg)
	    {}
	    
	    virtual std::string toString() override { return msg; }
	};

	/**
	 * Identifier
	 */
	class Identifier : public Base {
	private:
	    std::string str;
	public:
	    Identifier(std::string str)
		: Base(Type::IDENTIFIER)
		, str(str)
	    {}

	    virtual std::string toString() override { return str; }
	};

	/**
	 * Literal
	 */
	class Literal : public Base {
	private:
	    Token token;
	public:
	    Literal(Token token)
		: Base(Type::LITERAL)
		, token(token)
	    {}

	    virtual std::string toString() override { return token.toString(); }
	};
	
	/**
	 * Signature
	 */
	class Signature : public Base {
	protected:
	    std::vector<Token> body;
	public:
	    Signature(std::vector<Token> body)
		: Base(Type::SIGNATURE)
		, body(body)
	    {}

	    virtual std::string toString() override {
		std::string res;

		for (std::vector<Token>::iterator it = body.begin() ; it != body.end(); ++it) {
		    res += it->toString() + " ";
		}
		
		return res;
	    }
	};

	/**
	 * Expression
	 */
	enum class ExprType {
	    ERROR,
		APPLICATION,
	};
	
	class Expression : public Base {
	    ExprType expr_type;
	public:
	    Expression(ExprType expr_type)
		: Base(Type::EXPRESSION)
		, expr_type(expr_type)
	    {}
	    bool is(ExprType type) { return this->expr_type == type; }
	    
	    virtual std::string toString() override { return "Expression"; }
	};

	/**
	 * Error
	 */
	class ExprError : public Expression {
	private:
	    std::string msg;
	public:
	    ExprError(std::string msg)
		: Expression(ExprType::ERROR)
		, msg(msg)
	    {}
	    
	    virtual std::string toString() override { return msg; }
	};

	/**
	 * Application
	 */
	class ExprApplication : public Expression {
	private:
	    Identifier id;
	    std::vector<std::shared_ptr<Expression>> args;
	public:
	    ExprApplication(Identifier id, std::vector<std::shared_ptr<Expression>> args)
		: Expression(ExprType::APPLICATION)
		, id(id)
		, args(args)
	    {}
	    
	    virtual std::string toString() override { return "TODO Expression Application tostring"; }
	};
	
	/**
	 * Match Expression
	 * Currently ONLY implemented identifier
	 */
	class MatchExpression : public Base {
	private:
	    Identifier id;
	public:
	    MatchExpression(Identifier id)
		: Base(Type::MATCH_EXPRESSION)
		, id(id)
	    {}

	    virtual std::string toString() override { return "TODO Match Expression tostring"; }
	};

	/**
	 * Match 
	 */
	class Match : public Base {
	private:
	    std::vector<MatchExpression> mexprs;
	    Expression body;
	public:
	    Match(std::vector<MatchExpression> mexprs,
		  Expression body)
		: Base(Type::MATCH)
		, mexprs(mexprs)
		, body(body)
	    {}

	    virtual std::string toString() override { return "TODO Match tostring"; }
	};
	
	/**
	 * Pattern
	 */
	class Pattern : public Base {
	private:
	    std::vector<Match> matches;
	public:
	    Pattern(std::vector<Match> matches)
		: Base(Type::PATTERN)
	    {}

	    virtual std::string toString() override { return "TODO Pattern tostring"; }
	};

	/**
	 * Function
	 */
	class Func : public Base {
	private:
	    Identifier id;
	    Signature  signature;
	    Pattern    pattern;
	public:
	    Func(Identifier id,
		 Signature  signature,
		 Pattern    pattern)
		: Base(Type::FUNC)
		, id(id)
		, signature(signature)
		, pattern(pattern)
	    {}
	    std::string toString() override { return "TODO Function tostring"; }
	};
    };
};

#endif
