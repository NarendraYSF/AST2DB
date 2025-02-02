#include "ast_analyzer.h"
#include "ast_node_info.h"
#include "utils/ast_utils.h"

std::string Location::toString() const {
  return filename + ":" + std::to_string(line) + ":" + std::to_string(column);
}

namespace ast {
ASTAnalyzer::ASTAnalyzer() : index(nullptr), unit(nullptr) {
  index = clang_createIndex(0, 0);
}

ASTAnalyzer::~ASTAnalyzer() {
  if (unit)
    clang_disposeTranslationUnit(unit);
  if (index)
    clang_disposeIndex(index);
}

bool ASTAnalyzer::parseFile(const std::string &filename) {
  
  const char *args[] = {"-x", "c++", "-std=c++11"};

  unit = clang_parseTranslationUnit(index, filename.c_str(), args, 3, nullptr,
                                    0, CXTranslationUnit_None);

  if (!unit)
    return false;

  CXCursor cursor = clang_getTranslationUnitCursor(unit);
  clang_visitChildren(cursor, visitNode, this);
  return true;
}


CXChildVisitResult ASTAnalyzer::visitNode(CXCursor cursor, CXCursor parent,
                                          CXClientData clientData) {
  ASTAnalyzer *analyzer = static_cast<ASTAnalyzer *>(clientData);

  switch (clang_getCursorKind(cursor)) {
  case CXCursor_FunctionDecl:
    analyzer->handleFunctionDecl(cursor);
    break;
  case CXCursor_CallExpr:
    analyzer->handleCallExpr(cursor);
    break;
  case CXCursor_VarDecl:
    analyzer->handleVarDecl(cursor);
    break;
  case CXCursor_DeclRefExpr:
    analyzer->handleDeclRefExpr(cursor);
    break;
  default:
    
    break;
  }

  return CXChildVisit_Recurse;
}


void ASTAnalyzer::handleFunctionDecl(CXCursor cursor) {
  FunctionDecl func;
  func.name = getCursorSpelling(cursor);
  func.returnType = getTypeSpelling(clang_getCursorResultType(cursor));
  func.isDefinition = clang_isCursorDefinition(cursor);
  func.location = getCursorLocation(cursor);

  
  int argCount = clang_Cursor_getNumArguments(cursor);
  for (int i = 0; i < argCount; ++i) {
    CXCursor arg = clang_Cursor_getArgument(cursor, i);
    std::string argName = getCursorSpelling(arg);
    std::string argType = getTypeSpelling(clang_getCursorType(arg));
    func.parameters.push_back({argName, argType});
  }

  functions.push_back(func);
}


void ASTAnalyzer::handleCallExpr(CXCursor cursor) {
  CallExpr call;
  call.functionName = getCursorSpelling(cursor);
  call.location = getCursorLocation(cursor);

  
  int argCount = clang_Cursor_getNumArguments(cursor);
  for (int i = 0; i < argCount; ++i) {
    CXCursor arg = clang_Cursor_getArgument(cursor, i);
    call.arguments.push_back(getCursorSpelling(arg));
  }

  calls.push_back(call);
}


void ASTAnalyzer::handleVarDecl(CXCursor cursor) {
  VarDecl var;
  var.name = getCursorSpelling(cursor);
  var.type = getTypeSpelling(clang_getCursorType(cursor));
  var.location = getCursorLocation(cursor);

  
  CXCursor init = clang_Cursor_getArgument(cursor, 0);
  if (!clang_Cursor_isNull(init)) {
    var.initValue = getCursorSpelling(init);
  }

  variables.push_back(var);
}


void ASTAnalyzer::handleDeclRefExpr(CXCursor cursor) {
  DeclRefExpr ref;
  ref.name = getCursorSpelling(cursor);
  ref.location = getCursorLocation(cursor);

  references.push_back(ref);
}


const std::vector<FunctionDecl> &ASTAnalyzer::getFunctions() const {
  return functions;
}

const std::vector<CallExpr> &ASTAnalyzer::getCalls() const { return calls; }

const std::vector<VarDecl> &ASTAnalyzer::getVariables() const {
  return variables;
}

const std::vector<DeclRefExpr> &ASTAnalyzer::getReferences() const {
  return references;
}

} 
