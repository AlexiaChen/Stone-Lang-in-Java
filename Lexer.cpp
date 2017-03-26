#include "Lexer.h"

#include "StrCommon.hpp"


std::string Lexer::regex_pattern =
"\\s*((//.*)|([0-9]+)|(\"(\\\\\"|\\\\\\\\|\\\\n|[^\"])*\")"// comment or integer literal or string literal or identifier
"|"
"[A-Z_a-z][A-Z_a-z0-9]*|==|<=|>=|&&|\\|\\||[[:punct:]])?";//variable_identifier or == or <= or >= or == or || or punctuation

Lexer::Lexer(const std::string& file) :
m_hasMore(true),
m_reader(std::make_shared<LineNumberReader>(file)),
m_pattern(Lexer::regex_pattern)
{

}

Lexer::~Lexer()
{

}

Lexer::TokenPtr Lexer::read()
{
	if (fillQueue(0))
	{
		TokenPtr token_ptr = m_queue[0];
		m_queue.erase(std::begin(m_queue));
		return token_ptr;
	}
	else
	{
		return Token::EOF_TOEKN;
	}
}

void Lexer::readLine()
{
	std::string line;
	line = m_reader->readLine();

	if (line.empty())
	{
		m_hasMore = false;
		return;
	}

	uint32_t line_number = m_reader->getLineNumber();

	std::vector<std::string> tokens = StrCommon::split(line, "\\s+");

	for (const auto& token : tokens)
	{
		if (std::regex_match(token, m_pattern))
		{
			addToken(line_number, token);
		}
		else
		{
			throw ParseException("bad token at line " + std::to_string(line_number));
		}
	}

	m_queue.push_back(std::make_shared<IdentifierToken>(line_number, Token::EOL_TOKEN));

}

void Lexer::addToken(uint32_t line_num, const std::string& token)
{
	static const std::string comments_pattern = "//.*";
	static const std::string number_pattern = "[0-9]+";
	static const std::string str_pattern = "\"(\\\\\"|\\\\\\\\|\\\\n|[^\"])*\"";
	static const std::string id_pattern = "[A-Z_a-z][A-Z_a-z0-9]*|==|<=|>=|&&|\\|\\||[[:punct:]]";

	// exclude comment
	std::regex regex(comments_pattern);
	if (!std::regex_match(token, regex) && !token.empty())
	{
		std::shared_ptr<Token> token_ptr(nullptr);
		
		if (std::regex_match(token, regex.assign(number_pattern)))
		{
			token_ptr = std::make_shared<NumToken>(line_num, std::stoi(token));
		}
		else if (std::regex_match(token,regex.assign(str_pattern)))
		{
			token_ptr = std::make_shared<StringToken>(line_num, toStringLiteral(token));
		}
		else
		{
			token_ptr = std::make_shared<IdentifierToken>(line_num, token);
		}

		m_queue.push_back(token_ptr);
	}


}

std::string Lexer::toStringLiteral(const std::string& str)
{
	std::ostringstream stringStream;
	stringStream << "\"" << str << "\"";
	return stringStream.str();
}

bool Lexer::fillQueue(uint32_t i)
{
	while (i >= m_queue.size())
	{
		if (m_hasMore)
		{
			readLine();
		}
		else
		{
			return false;
		}
	}
		
	return true;
}


