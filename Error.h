#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#include <exception>
#include <string>


class Error : public std::exception
{
public:
    enum ErrCode{
        None,
        MissingBeginBracket,
        MissingCloseBracket,
        TooManyOperator,
        TooManyPunct,
        OperatorError,
        NoKnowToken,
        ExpressionEmpty,
        NumberError,
        DivisionByZero,
        ZeroPowZero};

    Error(ErrCode code, int position = -1):
        m_errCode(code), m_position(position)
    {}

    ~Error() noexcept override
    {

    }

    const char* what() const noexcept override
    {
        return toString().c_str();
    }

    ErrCode getErrorCode() const { return m_errCode; }
    int getPosition() const { return m_position; }

    std::string toString() const
    {
        std::string errStr;
        switch(m_errCode)
        {
        case MissingBeginBracket:
            errStr = "Missing begin bracket.";
            break;
        case MissingCloseBracket:
            errStr = "Missing close bracket.";
            break;
        case TooManyOperator:
            errStr = "There are too many operator.";
            break;
        case TooManyPunct:
            errStr = "There are too many punct.";
            break;
        case OperatorError:
            errStr = "There is an operator error";
            break;
        case NoKnowToken:
            errStr = "Invalid token.";
            break;
        case ExpressionEmpty:
            errStr = "The expression is empty.";
            break;
        case NumberError:
            errStr = "There is a number error";
            break;
        case DivisionByZero:
            errStr = "Answer not real.";
            break;
        case ZeroPowZero:
            errStr = "Answer not real.";
            break;
        case None:
            errStr = "No error";
            break;
        default:
            errStr = "Unknown error.";
        }
        if(m_errCode == DivisionByZero || m_errCode == ZeroPowZero)
            errStr = "Math error : " + errStr;
        else
            errStr = "Syntax error : " + errStr;
        return errStr;
    }

protected:
    const ErrCode m_errCode;
    const int m_position;
};

#endif // ERROR_H_INCLUDED
