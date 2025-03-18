#include <iostream>
#include <fstream>
#include <string>
#include "antlr4-runtime.h"
#include "ExprLexer.h"
#include "ExprParser.h"
#include "ExprBaseVisitor.h"

class ExprTreeVisitor : public ExprBaseVisitor {
public:
    // Implementation for tree traversal/visualization
    antlrcpp::Any visitProgram(ExprParser::ProgramContext *ctx) override {
        std::cout << "Program:" << std::endl;
        return visitChildren(ctx);
    }

    antlrcpp::Any visitExpr(ExprParser::ExprContext *ctx) override {
        std::cout << "  Expression: ";
        // Print the full expression for clarity
        for (auto child : ctx->children) {
            std::cout << child->getText() << " ";
        }
        std::cout << std::endl;
        return visitChildren(ctx);
    }

    antlrcpp::Any visitSum(ExprParser::SumContext *ctx) override {
        std::cout << "    Sum: " << ctx->getText() << std::endl;
        return visitChildren(ctx);
    }

    antlrcpp::Any visitComp(ExprParser::CompContext *ctx) override {
        std::cout << "    Comparison operator: " << ctx->getText() << std::endl;
        return visitChildren(ctx);
    }

    antlrcpp::Any visitNum(ExprParser::NumContext *ctx) override {
        std::cout << "      Number: " << ctx->getText() << std::endl;
        return visitChildren(ctx);
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " input_file" << std::endl;
        return 1;
    }
    
    // Open input file
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file " << argv[1] << std::endl;
        return 1;
    }
    
    // Read entire file content
    std::string input((std::istreambuf_iterator<char>(inputFile)),
                       std::istreambuf_iterator<char>());
    inputFile.close();
    
    // Create input stream from string
    antlr4::ANTLRInputStream inputStream(input);
    
    // Create lexer and token stream
    ExprLexer lexer(&inputStream);
    antlr4::CommonTokenStream tokens(&lexer);
    
    // Create parser and parse the input
    ExprParser parser(&tokens);
    antlr4::tree::ParseTree* tree = parser.program();
    
    // Print parse tree structure for debugging
    std::cout << "Parse tree: " << tree->toStringTree(&parser) << std::endl << std::endl;
    
    // Visit the parse tree
    ExprTreeVisitor visitor;
    visitor.visit(tree);
    
    return 0;
} 