#include "../include/tokenizer.h"
#include <ios>
#include <iostream>
#include <stdexcept>

namespace json
{
Tokenizer::Tokenizer(std::string fileName)
{
    file.open(fileName, std::ios::in);
    if (!file.good())
    {
        std::cout << "File open error" << std::endl;
        throw std::logic_error("File open error");
    }
}

Tokenizer::~Tokenizer()
{
    file.close();
}

char Tokenizer::getWithoutWhiteSpace()
{
    char c = ' ';
    while ((c == ' ' || c == '\n'))
    {
        file.get(c);
        if ((c == ' ' || c == '\n') && !file.good())
        {
            /* throw std::logic_error("Ran out of tokens (getWithoutWhiteSpace)"); */
            return '\0';
        }

        if (!file.good())
        {
            return c;
        }
    }

    return c;
}

Token Tokenizer::getToken()
{
    if (file.eof())
    {
        std::cout << "Exhausted tokens (getToken)" << std::endl;
    }
    prevPos = file.tellg();
    char c  = getWithoutWhiteSpace();

    struct Token token;
    if (c == '\0')
    {
        token.type  = TOKEN::END_OF_FILE;
        token.value = "";

        return token;
    }

    if (c == '"')
    {
        token.type  = TOKEN::STRING;
        token.value = "";
        file.get(c);
        while (c != '"')
        {
            token.value += c;
            file.get(c);
        }
        return token;
    }

    if (c == '{')
    {
        token.type = TOKEN::CURLY_OPEN;
        return token;
    }

    if (c == '}')
    {
        token.type = TOKEN::CURLY_CLOSE;
        return token;
    }

    if (c == '-' || (c >= '0' && c <= '9'))
    {
        token.type  = TOKEN::NUMBER;
        token.value = "";
        token.value += c;
        std::streampos prevCharPos = file.tellg();
        while ((c == '-') || (c >= '0' && c <= '9') || c == '.')
        {
            prevCharPos = file.tellg();
            file.get(c);

            if (file.eof())
                return token;

            if ((c == '-') || (c >= '0' && c <= '9') || c == '.')
                token.value += c;
            else
                file.seekg(prevCharPos);
        }
        return token;
    }

    if (c == 'f')
    {
        token.type  = TOKEN::BOOLEAN;
        token.value = "False";
        file.seekg(4, std::ios_base::cur);
        return token;
    }

    if (c == 't')
    {
        token.type  = TOKEN::BOOLEAN;
        token.value = "True";
        file.seekg(3, std::ios_base::cur);
        return token;
    }

    if (c == 'n')
    {
        token.type = TOKEN::NULL_TYPE;
        file.seekg(3, std::ios_base::cur);
        return token;
    }

    if (c == '[')
    {
        token.type = TOKEN::ARRAY_OPEN;
        return token;
    }

    if (c == ']')
    {
        token.type = TOKEN::ARRAY_CLOSE;
        return token;
    }

    if (c == ':')
    {
        token.type = TOKEN::COLON;
        return token;
    }

    if (c == ',')
    {
        token.type = TOKEN::COMMA;
        return token;
    }

    return token;
}

bool Tokenizer::hasMoreTokens() const
{
    return !file.eof();
}

void Tokenizer::rollBackToken()
{
    if (file.eof())
    {
        file.clear();
    }

    file.seekg(prevPos);
}
} // namespace json
