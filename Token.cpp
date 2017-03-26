#include "Token.h"

const std::shared_ptr<Token> Token::EOF_TOEKN = std::make_shared<Token>(-1);
const std::string Token::EOL_TOKEN = std::string("\\n");