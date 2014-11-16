#include "CharUtility.h"

#include <cctype>

Token getTokenFor(char c) noexcept
{
    if(isOpenBracket(c)){
        return Token('(');
    }else if(isCloseBracket(c)){
        return Token(')');
    }else{
        return Token(c);
    }
}
