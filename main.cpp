#include <iostream>
#include <string>
#include <locale>

#include "TokenList.h"
#include "Error.h"
#include "InfiniteNumber.h"

int main()
{
    InfiniteNumber a("1234.5678");
    a.writeToStream(std::cout);
    return 0; // TEST
    setlocale(LC_ALL, "");

    std::cout << "Bienvenue dans cette calculatrice créer par Thomas Chevalier.\n"
                "Pour l'instant seuls les operations suivantes sont supportés : + - * / ^.\n\n";
    std::cout << "Entrez votre opération ";

    std::string expression;
    while(expression != "exit")
    {
        std::cout << "> ";
        getline(std::cin, expression);

        if(expression == "exit")
            break;

        TokenList l(expression);
        bool evaluate = true;

        try{
            l.checkExpression();
        }
        catch(Error& err)
        {
            int pos = err.getPosition();
            std::cerr << err.what();
            if(pos != -1){
                std::cout << "Position : " << pos;
            }
            std::cout << "\n";
            evaluate= false;
        }

        if(evaluate)
        {
            auto res = l.eval();
            std::cout << "= " << res << '\n';
        }
    }

    return 0;
}
