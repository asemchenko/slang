#include <vector>
#include <string>
namespace slang_AST_NODES {
	class Operator {
		virtual ~Operator();
	};
	class Expression {
		virtual ~Expression();
	};
	class Operators: public Operator {
		std::vector<Operator*> operators;
	};
	class OpExpression: public Operator {
		Expression *expr;
	};
	class OpReturn: public Operator {
		Expression *expr;
	};
	class OpIF: public Operator {
		Expression *statement;
		Operator *ifOP;
		Operator *elseOP;
	};
	class Identifier: public Expression {
		std::string value;
	};
	class [[deprecated("Destructor should be written!!1")]] Literal: public Expression {
		enum TYPE {INT, FLOAT, BOOL, STRING, CHAR };
		union VALUE {
			int integerV;
			double floatV;
			bool boolV;
			std::string *stringV;
		        char charV;	
		};
		VALUE value;
		TYPE type;
	};
	class BinaryOperation: public Expression {
		enum TYPE {ADDITION, SUBSTRUCTION, MULTIPLICATION, DIVISION, MODULO, POW, ASSIGN, EQUAL, NON_EQUAL, GREAT, GREAT_EQUAL, LEAST, LEAST_EQUAL, AND, OR};
		Expression *firstOperand;
		Expression *secondOperand;
	};
	class FunctionCall: public Expression {
		std::string funcionName;
		std::vector<Expression*> arguments;
	};
	class WhileLoop: public Operator {
		Expression *condition;
		Operator *body;
	};
	class ForLoop: public Operator {
		Expression *firstExpression;
		Expression *secondExpression;
		Expression *thirdExpression;
		Operator *body;
	};
	class Function {
		std::vector<Identifier*> parametersName;
		Operator *body;
	};
}
