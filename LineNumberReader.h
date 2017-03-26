#ifndef LINE_NUMBER_READER_H
#define LINE_NUMBER_READER_H

#include <string>
#include <sstream>
#include <fstream>
#include <cstdint>

class LineNumberReader
{
public:
	explicit LineNumberReader(const std::string& file);
	~LineNumberReader();
public:
	std::string readLine();
	uint32_t getLineNumber() const;
private:
	std::ifstream m_infile;
	uint32_t m_current_line_number;
};
#endif