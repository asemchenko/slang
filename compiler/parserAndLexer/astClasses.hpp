#ifndef AST_CLASSES_HPP_INCLUDED
#define AST_CLASSES_HPP_INCLUDED
#include <vector>
#include <string>
namespace slang_AST_NODES {
	class Operator {
		public:
			virtual ~Operator() {}
	};
	class Expression {
		public:
			virtual ~Expression() {}
	};
	class Operators: public Operator {
		std::vector<Operator*> operators;
		public:
			void push_back(Operator* op) {
				operators.push_back(op);
			}
	};
	class OpExpression: public Operator {
		public:
			OpExpression(Expression *e): expr(e) {}
		private:
			Expression *expr;
	};
	class OpReturn: public Operator {
		public:
			OpReturn(Expression *e): expr(e) {}
		private:
			Expression *expr;
	};
	class OpIF: public Operator {
		public:
			OpIF(Expression *cond,Operator *ifOp_, Operator *elseOp_): condition(cond), ifOp(ifOp_), elseOp(elseOp_) {}
		private:
			Expression *condition;
			Operator *ifOp;
			Operator *elseOp;
	};
	class Identifier: public Expression {
		public:
			Identifier(const std::string value_): value(value_) {}
		private:
			std::string value;
			
	};
	class [[deprecated("Destructor should be written!!1")]] Literal: public Expression {
		public:
			enum TYPE {INT, FLOAT, BOOL, STRING, CHAR };
			union VALUE {
				int integerV;
				double floatV;
				bool boolV;
				std::string *stringV;
			        char charV;	
			};
			VALUE & setValue() {return value;}
		private:
			VALUE value;
			TYPE type;
	};
	class BinaryOperation: public Expression {
		public:
			enum Type {ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION, MODULO, POW, ASSIGN, EQUAL, NON_EQUAL, GREAT, GREAT_EQUAL, LEAST, LEAST_EQUAL, AND, OR};
			BinaryOperation(Type type_,Expression *firstOperand_, Expression *secondOperand_): firstOperand(firstOperand_), secondOperand(secondOperand_), type(type_)  {}
		private:
			Expression *firstOperand;
			Expression *secondOperand;
			Type type;
	};
	class FunctionCall: public Expression {
		private:
			std::string name;
			std::vector<Expression*> arguments;
		public:
			FunctionCall(std::string name_, std::vector<Expression*> arguments_): name(name_), arguments(arguments_) {}
	};
	class WhileLoop: public Operator {
		private:
			Expression *condition;
			Operator *body;
		public:
			WhileLoop(Expression *condition_, Operator *body_): condition(condition_), body(body_) {}
	};
	class ForLoop: public Operator {
		private:
			Expression *firstExpression;
			Expression *secondExpression;
			Expression *thirdExpression;
			Operator *body;
		public:
			ForLoop(Expression *firstExpr_, Expression *secondExpr_, Expression *thirdExpr_ ,Operator *body_): firstExpression(firstExpr_), secondExpression(secondExpr_),
		       		thirdExpression(thirdExpr_), body(body_) {}
	};
	class Function {
		private:
			std::string name;
			std::vector<Identifier*> parametersName;
			Operator *body;
		public:
			Function(std::string name_, std::vector<Identifier*> parametersName_, Operator *body_): name(name_), parametersName(parametersName_), body(body_) {}
			virtual ~Function() {}
	};
}
#endif
