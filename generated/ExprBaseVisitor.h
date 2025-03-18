
// Generated from /Users/romfed/Documents/translators/Expr.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "ExprVisitor.h"


/**
 * This class provides an empty implementation of ExprVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  ExprBaseVisitor : public ExprVisitor {
public:

  virtual std::any visitProgram(ExprParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpr(ExprParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSum(ExprParser::SumContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComp(ExprParser::CompContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNum(ExprParser::NumContext *ctx) override {
    return visitChildren(ctx);
  }


};

