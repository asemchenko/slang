#ifndef AST_CLASSES_HPP_INCLUDED
#define AST_CLASSES_HPP_INCLUDED
#include <vector>
#include <string>
#include <cstdio>
namespace slang_AST_NODES {
	class Operator {
		public:
			virtual ~Operator() {}
			virtual void print(FILE *stream, int indentLevel) = 0;
			void printIndent(int level, FILE *stream) {
				while(level--) fprintf(stream, "\t");
			}
	};
	class Expression {
		public:
			virtual ~Expression() {}
			virtual void print(FILE *stream) = 0;
	};
	class Operators: public Operator {
		std::vector<Operator*> operators;
		public:
			void push_back(Operator* op) {
				operators.push_back(op);
			}
			void print(FILE *stream, int indentLevel) override {
				for(auto oper: operators) {
					oper->print(stream, indentLevel);
					fprintf(stream, "\n");
				}
			}
	};
	class OpExpression: public Operator {
		public:
			OpExpression(Expression *e): expr(e) {}
			void print(FILE *stream, int indentLevel) override {
				printIndent(indentLevel, stream);
				expr->print(stream);
				fprintf(stream, ";\n");
			}
		private:
			Expression *expr;
	};
	class OpReturn: public Operator {
		public:
			OpReturn(Expression *e): expr(e) {}
			void print(FILE *stream, int indentLevel) override {
				printIndent(indentLevel, stream); fprintf(stream, "return ");
				expr->print(stream);
				fprintf(stream, "\n");
			}
		private:
			Expression *expr;
	};
	class OpIF: public Operator {
		public:
			OpIF(Expression *cond,Operator *ifOp_, Operator *elseOp_): condition(cond), ifOp(ifOp_), elseOp(elseOp_) {}
			void print(FILE *stream, int indentLevel) {
				printIndent(indentLevel, stream);
				fprintf(stream, "if("); condition->print(stream); fprintf(stream, ") {\n");
				ifOp->print(stream, indentLevel + 1);
				printIndent(indentLevel, stream);
				fprintf(stream, "}\n");
				if(elseOp) {
					printIndent(indentLevel, stream);
					fprintf(stream,"else { \n");
					elseOp->print(stream, indentLevel + 1);
					printIndent(indentLevel, stream);
					fprintf(stream, "}\n");
				}
			}
		private:
			Expression *condition;
			Operator *ifOp;
			Operator *elseOp;
	};
	class Identifier: public Expression {
		public:
			Identifier(const std::string value_): value(value_) {}
			void print(FILE *stream) override {
				fprintf(stream, "%s", value.c_str());
			}
		private:
			std::string value;
			
	};
	class Literal: public Expression {
		private:
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
		public:
			Literal(const int val) {
				type = INT;
				value.integerV = val;
			}
			Literal(const double val) {
				type = FLOAT;
				value.floatV = val;
			}
			Literal(const bool val) {
				type = BOOL;
				value.boolV = val;
			}
			Literal(const std::string val) {
				type = STRING;
				value.stringV = new std::string(val);
			}
			Literal(const char val) {
				type = CHAR;
				value.charV = val;
			}
			~Literal() {
				if(STRING == type) delete value.stringV;
			}
			Literal(const Literal&) = delete;
			Literal(const Literal&&) = delete;
			Literal& operator = (const Literal&) = delete;
			Literal& operator = (const Literal&&) = delete;
			void print(FILE *stream) override {
				fprintf(stream, "EXPRESSION");
			}
	};
	class BinaryOperation: public Expression {
		public:
			enum Type {ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION, MODULO, POW, ASSIGN, EQUAL, NON_EQUAL, GREAT, GREAT_EQUAL, LEAST, LEAST_EQUAL, AND, OR};
			BinaryOperation(Type type_,Expression *firstOperand_, Expression *secondOperand_): firstOperand(firstOperand_), secondOperand(secondOperand_), type(type_)  {}
			void print(FILE *stream) override {
				firstOperand->print(stream);
				fprintf(stream, " OP ");
				secondOperand->print(stream);
			}
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
			void print(FILE *stream) override {
				fprintf(stream, "%s(", name.c_str());
				if(arguments.size()) {
					arguments.front()->print(stream);
					for(auto e = arguments.begin(); e != arguments.end();++e) {
						fprintf(stream, ",");
						(*e)->print(stream);
					}
				}
				fprintf(stream, ")");
			}
	};
	class WhileLoop: public Operator {
		private:
			Expression *condition;
			Operator *body;
		public:
			WhileLoop(Expression *condition_, Operator *body_): condition(condition_), body(body_) {}
			void print(FILE *stream, int indentLevel) override {
				printIndent(indentLevel, stream);
				fprintf(stream, "while("); condition->print(stream); fprintf(stream, ") { \n");
				body->print(stream, indentLevel + 1);
				printIndent(indentLevel, stream);
				fprintf(stream, "}\n");
			}
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
			void print(FILE *stream, int indentLevel) override {
				printIndent(indentLevel, stream);
				fprintf(stream, "for("); firstExpression->print(stream);
				fprintf(stream, ","); secondExpression->print(stream);
				fprintf(stream, ","); thirdExpression->print(stream);
				fprintf(stream, ") { \n"); body->print(stream, indentLevel + 1 );
				printIndent(indentLevel, stream);
				fprintf(stream, "}\n");
			}
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
