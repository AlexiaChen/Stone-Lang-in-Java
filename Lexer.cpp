#include "Lexer.h"


std::string Lexer::regex_pattern =
"\\s*((//.*)|([0-9]+)|(\"(\\\\\"|\\\\\\\\|\\\\n|[^\"])*\")"// comment or integer literal or string literal or identifier
"|"
"[A-Z_a-z][A-Z_a-z0-9]*|==|<=|>=|&&|\\|\\||[[:punct:]])?";//variable_identifier or == or <= or >= or == or || or punctuation


