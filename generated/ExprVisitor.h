
// Generated from /Users/romfed/Documents/translators/Expr.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "ExprParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by ExprParser.
 */
class  ExprVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ExprParser.
   */
    virtual std::any visitProgram(ExprParser::ProgramContext *context) = 0;

    virtual std::any visitExpr(ExprParser::ExprContext *context) = 0;

    virtual std::any visitSum(ExprParser::SumContext *context) = 0;

    virtual std::any visitComp(ExprParser::CompContext *context) = 0;

    virtual std::any visitNum(ExprParser::NumContext *context) = 0;


};

