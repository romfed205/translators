cmake_minimum_required(VERSION 3.14)
project(ExprParser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find ANTLR
find_package(ANTLR QUIET)
if(NOT ANTLR_FOUND)
    message(STATUS "ANTLR not found via find_package, using manual configuration")
    # Homebrew paths for macOS
    set(ANTLR_INCLUDE_DIRS "/opt/homebrew/include/antlr4-runtime")
    set(ANTLR_LIBRARIES "/opt/homebrew/lib/libantlr4-runtime.dylib")
endif()

# Generate ANTLR parser
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/generated)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/generated)
endif()

# Command for generating ANTLR files
add_custom_command(
    OUTPUT
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/ExprLexer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/ExprParser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/ExprBaseVisitor.cpp
    COMMAND
        java -jar ${CMAKE_CURRENT_SOURCE_DIR}/antlr-4.11.1-complete.jar -Dlanguage=Cpp -visitor -no-listener -o generated ${CMAKE_CURRENT_SOURCE_DIR}/Expr.g4
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/Expr.g4
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT
        "Generating ANTLR parser"
)

# Include generated files
include_directories(
    ${ANTLR_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/generated
)

# Add main executable
add_executable(expr_parser
    ExprParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/ExprLexer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/ExprParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/generated/ExprBaseVisitor.cpp
)

target_link_libraries(expr_parser ${ANTLR_LIBRARIES}) 