#include <iostream>
#include <string>

#include "Token.h"
#include "Lexeme.h"
#include "Lexer.h"
#include "Parser.h"
#include "ASTPrinter.h"

using namespace std;

int main(int argc, const char * argv[]) {
    string code = R"code(
x = readint("Enter an int: ");
y = readint("Enter an int: ");
if x > y then
    println("The first int was bigger than the second!");
elseif y > x then
    println("The second int was bigger than the first!");
else
    println("You entered the same value twice!");
end
y = 21045;
while x > 0 do
    print(".");
    x = x - 1;
end
z = [1, 2, 3];
    )code";
    istringstream ins(code);
    try {
        Lexer lexer(ins);
        Parser parser(lexer);
        ASTPrinter printer;
        parser.getAST()->accept(printer);
    } catch (MyPLException &e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << "Program completed" << endl;
    return 0;
}
