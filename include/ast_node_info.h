#ifndef _ASTNODEINFO_H
#define _ASTNODEINFO_H

#include <string>
#include <vector>

struct Location {
  std::string filename;
  unsigned line;
  unsigned column;

  std::string toString() const;
};

/*------------------------------------------.
|  Data Structs for AST Nodes' information  |
`__________________________________________*/

struct FunctionDecl {
  std::string name;       // Name of the function
  std::string returnType; // Return type of the function
  std::vector<std::pair<std::string, std::string>>
      parameters;    // List of parameter types and names
  bool isDefinition; // Whether this is a function definition or just a
                     // declaration
  Location location; // Source location of the function
};

struct CallExpr {
  std::string functionName;           // Name of the called function
  std::vector<std::string> arguments; // List of argument expressions
  Location location;                  // Source location of the call
};

struct VarDecl {
  std::string name;      // Name of the variable
  std::string type;      // Type of the variable
  std::string initValue; // Initial value expression (if any)
  Location location;     // Source location of the declaration
};

struct DeclRefExpr {
  std::string name;  // Name of the referenced declaration
  Location location; // Source location of the reference
};

#endif // _ASTNODEINFO_H
