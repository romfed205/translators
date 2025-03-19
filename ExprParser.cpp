#include <iostream>
#include <fstream>
#include <string>
#include "antlr4-runtime.h"
#include "ExprLexer.h"
#include "ExprParser.h"
#include "ExprBaseVisitor.h"

class ExprTreeVisitor : public ExprBaseVisitor {
public:
    // обход дерева разбора
    antlrcpp::Any visitProgram(ExprParser::ProgramContext *ctx) override {
        std::cout << "Program:" << std::endl;
        return visitChildren(ctx);
    }

    antlrcpp::Any visitExpr(ExprParser::ExprContext *ctx) override {
        std::cout << "  Expression: ";
        // вывод полной выражения для ясности
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
    
    // открытие входного файла
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file " << argv[1] << std::endl;
        return 1;
    }
    
    // чтение всего содержимого файла
    std::string input((std::istreambuf_iterator<char>(inputFile)),
                       std::istreambuf_iterator<char>());
    inputFile.close();
    
    // создание входного потока из строки
    antlr4::ANTLRInputStream inputStream(input);
    
    // создание лексера и потока токенов
    ExprLexer lexer(&inputStream);
    antlr4::CommonTokenStream tokens(&lexer);
    
    // создание парсера и разбора входного текста
    ExprParser parser(&tokens);
    antlr4::tree::ParseTree* tree = parser.program();
    
    // вывод структуры дерева разбора для отладки
    std::cout << "Parse tree: " << tree->toStringTree(&parser) << std::endl << std::endl;
    
    // обход дерева разбора
    ExprTreeVisitor visitor;
    visitor.visit(tree);
    
    return 0;
} 