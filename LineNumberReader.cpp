#include "LineNumberReader.h"



LineNumberReader::LineNumberReader(const std::string& file):
m_infile(file),
m_current_line_number(0)
{

}

LineNumberReader::~LineNumberReader()
{

}

std::string LineNumberReader::readLine()
{
    std::string line;
    std::getline(m_infile, line);
    m_current_line_number++;
    return line;
}

uint32_t LineNumberReader::getLineNumber() const
{
    return m_current_line_number;
}