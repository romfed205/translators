#include <iostream>
#include <fstream>
#include <string>
#include "antlr4-runtime.h"
#include "ExprLexer.h"
#include "ExprParser.h"
#include "ExprBaseVisitor.h"

// визитор, который строит дерево + вычисляет значения
class ExprTreeVisitor : public ExprBaseVisitor {
public:
    // метод"программа"
    antlrcpp::Any visitProgram(ExprParser::ProgramContext *ctx) override {
        std::cout << "Program:" << std::endl;
        return visitChildren(ctx);
    }

    // семантический анализ
    antlrcpp::Any visitExpr(ExprParser::ExprContext *ctx) override {
        // получаем текст
        std::string exprText;
        for (auto child : ctx->children) {
            exprText += child->getText() + " ";
        }
        exprText = exprText.substr(0, exprText.length() - 1); // проб
        
        // сумма
        int leftValue = std::any_cast<int>(visit(ctx->sum(0)));
        
        // оператор сравнения
        std::string compOp = ctx->comp()->getText();
        
        // сумма
        int rightValue = std::any_cast<int>(visit(ctx->sum(1)));
        
        // сравниваем и получаем результат
        bool result = false;
        if (compOp == "<") {
            result = leftValue < rightValue;
        } else if (compOp == ">") {
            result = leftValue > rightValue;
        } else if (compOp == "=") {
            result = leftValue == rightValue;
        } else if (compOp == "!=") {
            result = leftValue != rightValue;
        }
        
        // результатич
        std::cout << "  Expression: " << exprText << std::endl;
        std::cout << "    Semantic value: " << leftValue << " " << compOp << " " << rightValue 
                  << " = " << (result ? "true" : "false") << std::endl;
        
        return result;
    }

    // сумма вычисляется
    antlrcpp::Any visitSum(ExprParser::SumContext *ctx) override {
        std::cout << "    Sum: " << ctx->getText() << std::endl;
        
        // значение первого числа
        int result = std::any_cast<int>(visit(ctx->num()));
        
        // если есть операция сложения, вычисляем сумму
        if (ctx->sum()) {
            int rightValue = std::any_cast<int>(visit(ctx->sum()));
            result += rightValue;
        }
        
        std::cout << "      Value: " << result << std::endl;
        return result;
    }

    // оператор сравнения
    antlrcpp::Any visitComp(ExprParser::CompContext *ctx) override {
        std::cout << "    Comparison operator: " << ctx->getText() << std::endl;
        return visitChildren(ctx);
    }

    // метод "число" возвращает числовое значение
    antlrcpp::Any visitNum(ExprParser::NumContext *ctx) override {
        int value = std::stoi(ctx->getText());
        std::cout << "      Number: " << value << std::endl;
        return value;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " input_file" << std::endl;
        return 1;
    }
    
    // открываем входной файл
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file " << argv[1] << std::endl;
        return 1;
    }
    
    // читаем содержимое файла
    std::string input((std::istreambuf_iterator<char>(inputFile)),
                       std::istreambuf_iterator<char>());
    inputFile.close();
    
    // создаем поток ввода
    antlr4::ANTLRInputStream inputStream(input);
    
    // создаем лексер и поток токенов
    ExprLexer lexer(&inputStream);
    antlr4::CommonTokenStream tokens(&lexer);
    
    // создаем парсер и разбираем вход
    ExprParser parser(&tokens);
    antlr4::tree::ParseTree* tree = parser.program();
    
    // выводим структуру дерева разбора для отладки
    std::cout << "Parse tree: " << tree->toStringTree(&parser) << std::endl << std::endl;
    
    // создаем визитор и обходим дерево, выполняя семантический анализ
    ExprTreeVisitor visitor;
    visitor.visit(tree);
    
    return 0;
} 