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
		SIGNATURE,
		PATTERN,
		MATCH,
		EXPRESSION,
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
	class Expression : public Base {
	public:
	    Expression()
		: Base(Type::EXPRESSION)
	    {}

	    virtual std::string toString() override { return "TODO Body tostring"; }
	};

	/**
	 * Match 
	 */
	class Match : public Base {
	private:
	    Expression expression;
	public:
	    Match(Expression expression)
		: Base(Type::MATCH)
		, expression(expression)
	    {}

	    virtual std::string toString() override { return "TODO Type tostring"; }
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
