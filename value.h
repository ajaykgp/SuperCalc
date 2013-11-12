/*
  value.h
  SuperCalc

  Created by C0deH4cker on 10/21/13.
  Copyright (c) 2013 C0deH4cker. All rights reserved.
*/

#ifndef _SC_VALUE_H_
#define _SC_VALUE_H_


typedef struct Value Value;
#include "fraction.h"
#include "unop.h"
#include "binop.h"
#include "funccall.h"
#include "variable.h"
#include "context.h"
#include "error.h"


typedef enum {
	VAL_END = -3,
	VAL_ERR = -2,
	VAL_NEG = -1,
	VAL_INT = 0,
	VAL_REAL,
	VAL_FRAC,
	VAL_EXPR,
	VAL_UNARY,
	VAL_CALL,
	VAL_VAR
} VALTYPE;


struct Value {
	VALTYPE type;
	union {
		long long ival;
		double rval;
		Fraction* frac;
		UnOp* term;
		BinOp* expr;
		FuncCall* call;
		char* name;
		Error* err;
	};
};

/* Value constructors */
Value* ValEnd(void);
Value* ValErr(Error* err);
Value* ValNeg(void);
Value* ValInt(long long val);
Value* ValReal(double val);
Value* ValFrac(Fraction* frac);
Value* ValExpr(BinOp* expr);
Value* ValUnary(UnOp* term);
Value* ValCall(FuncCall* call);
Value* ValVar(const char* name);

/* Destructor */
void Value_free(Value* val);

/* Copying */
Value* Value_copy(Value* val);

/* Evaluation */
Value* Value_eval(Value* expr, Context* ctx);

/* Conversion */
double Value_asReal(Value* val);

/* Tree generator */
Value* Value_parse(const char** expr);

/* Parsing */
Value* Value_next(const char** expr);

/* Printing */
char* Value_verbose(Value* val, int indent);
char* Value_repr(Value* val);

#endif