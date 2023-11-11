#pragma once

#include <fstream>
#include <string>

namespace json
{
enum class TOKEN
{
    CURLY_OPEN,
    CURLY_CLOSE,
    COLON,
    STRING,
    NUMBER,
    ARRAY_OPEN,
    ARRAY_CLOSE,
    COMMA,
    BOOLEAN,
    NULL_TYPE
};

struct Token
{
    std::string value;
    TOKEN type;

    std::string toString() const
    {
        switch (type)
        {
        case TOKEN::CURLY_OPEN: {
            return "Curly open";
        }
        case TOKEN::CURLY_CLOSE: {
            return "Curly close";
        }
        case TOKEN::COLON: {
            return "COLON";
        }
        case TOKEN::NUMBER: {
            return "Number: " + value;
        }
        case TOKEN::STRING: {
            return "String: " + value;
        }
        case TOKEN::ARRAY_OPEN: {
            return "Array open";
        }
        case TOKEN::ARRAY_CLOSE: {
            return "Array close";
        }
        case TOKEN::COMMA: {
            return "Comma";
        }
        case TOKEN::BOOLEAN: {
            return "Boolean: " + value;
        }
        case TOKEN::NULL_TYPE: {
            return "null";
        }
        }

        return "";
    }
};

class Tokenizer
{
    public:
        Tokenizer(std::string fileName);
        Tokenizer(const Tokenizer &other) = delete;
        ~Tokenizer();

        char getWithoutWhiteSpace();
        Token getToken();
        bool hasMoreTokens() const;
        void rollBackToken() ;

    private:
        std::fstream file;
        size_t prevPos;
};
} // namespace json
