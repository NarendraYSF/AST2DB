# Code2SQL

Code2SQL uses `clang` to parse C/C++ code and stores AST node information into an SQLite database.

## Dependencies
- [clang](https://clang.llvm.org/)

## Development Environment

Current development is completed in the following environment:
- **Operating System**: linux-x86_64
- **Compiler**: g++ (gcc version 14.2.1)
- **Dependencies**
  - **clang**: clang version 19.1.7

## Usage
```bash
$ make # Compile
$ make help # View help information
$ ./build/demo <Target C/CPP File> # Run
```

### Example
Using `./tests/slight.cc` as the target file for testing:
```bash
$ ./build/demo ./tests/slight.cc
```

## Features
- [ ] Parse C/C++ code
  - [x] Record variable declaration & reference nodes
  - [x] Record function declaration & call nodes
  ...
- [ ] Store AST node information in an SQLite database
- [ ] Support exporting query results as CSV files
...

