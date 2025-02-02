#include "ast_utils.h"
#include <clang-c/Index.h>


Location getCursorLocation(CXCursor cursor) {
  Location loc;
  CXSourceLocation location = clang_getCursorLocation(cursor);
  CXFile file;
  unsigned line, column;
  clang_getSpellingLocation(location, &file, &line, &column, nullptr);

  CXString fileName = clang_getFileName(file);
  loc.filename = clang_getCString(fileName);
  loc.line = line;
  loc.column = column;
  clang_disposeString(fileName);

  return loc;
}


std::string getCursorSpelling(CXCursor cursor) {
  CXString spelling = clang_getCursorSpelling(cursor);
  std::string result = clang_getCString(spelling);
  clang_disposeString(spelling);
  return result;
}


std::string getTypeSpelling(CXType type) {
  CXString spelling = clang_getTypeSpelling(type);
  std::string result = clang_getCString(spelling);
  clang_disposeString(spelling);
  return result;
}
