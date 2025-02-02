#ifndef _AST_UTILS_H_
#define _AST_UTILS_H_

#include <clang-c/Index.h>
#include <string>
#include "ast_node_info.h"


Location getCursorLocation(CXCursor cursor);


std::string getCursorSpelling(CXCursor cursor);


std::string getTypeSpelling(CXType type);

#endif
