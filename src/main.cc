#include "ast_analyzer/ast_analyzer.h"
#include <iostream>


void printSeparator() { std::cout << std::string(50, '-') << "\n"; }

int main(int argc, char *argv[]) {

  
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <source-file>" << std::endl;
    return 1;
  }

  
  ast::ASTAnalyzer analyzer;

  
  if (!analyzer.parseFile(argv[1])) {
    std::cerr << "Failed to parse file" << std::endl;
    return 1;
  }

  
  std::cout << "Functions:\n";
  printSeparator();
  for (const auto &func : analyzer.getFunctions()) {
    std::cout << "Function: " << func.name << "\n"
              << "  Return type: " << func.returnType << "\n"
              << "  Location: " << func.location.toString() << "\n"
              << "  Is definition: " << (func.isDefinition ? "yes" : "no")
              << "\n";

    if (!func.parameters.empty()) {
      std::cout << "  Parameters:\n";
      for (const auto &param : func.parameters) {
        std::cout << "    " << param.second << " " << param.first << "\n";
      }
    }
    std::cout << "\n";
  }

  
  std::cout << "Function Calls:\n";
  printSeparator();
  for (const auto &call : analyzer.getCalls()) {
    std::cout << "Call: " << call.functionName << "\n"
              << "  Location: " << call.location.toString() << "\n";
    if (!call.arguments.empty()) {
      std::cout << "  Arguments: ";
      for (const auto &arg : call.arguments) {
        std::cout << arg << " ";
      }
      std::cout << "\n";
    }
    std::cout << "\n";
  }

  
  std::cout << "Variables:\n";
  printSeparator();
  for (const auto &var : analyzer.getVariables()) {
    std::cout << "Variable: " << var.name << "\n"
              << "  Type: " << var.type << "\n"
              << "  Location: " << var.location.toString() << "\n";
    if (!var.initValue.empty()) {
      std::cout << "  Initial value: " << var.initValue << "\n";
    }
    std::cout << "\n";
  }

  
  std::cout << "Variable References:\n";
  printSeparator();
  for (const auto &ref : analyzer.getReferences()) {
    std::cout << "Reference: " << ref.name << "\n"
              << "  Location: " << ref.location.toString() << "\n\n";
  }

  return 0;
}
