#include "Parser.h"

#include <iostream>
#include <sstream>

using namespace std;

const bool USE_CONTEXTLOG = false;

class ContextLog {
public:
    ContextLog(string p, const Lexeme &lex):
    part(p),
    l(lex.line),
    c(lex.col) {
        if (USE_CONTEXTLOG)
            cout << "Entering " << part << "(" << l << ":" << c << ")" << endl;
    }
    ~ContextLog() {
        if (USE_CONTEXTLOG)
            cout << "Exiting " << part << "(" << l << ":" << c << ")" << endl;
    }
private:
    string part;
    int l;
    int c;
};

Parser::Parser(Lexer &lex): lexer(lex) {
    advance();
    syntaxTree = stmts();
}

shared_ptr<ASTNode> Parser::getAST() {
    return syntaxTree;
}

void Parser::advance() {
    currentLexeme = lexer.next();
}

void Parser::eat(Token token, std::string message) {
    if (currentLexeme.token == token) {
        advance();
    } else {
        error(message);
    }
}

void Parser::error(std::string message) {
    cout << "Error found" << endl;
    ostringstream oss;
    oss << message << ", found " << currentLexeme << " instead";
    throw ParserException(oss.str());
}

std::shared_ptr<ASTStatementList> Parser::stmts(std::shared_ptr<ASTStatementList> lst) {
    ContextLog clog("stmts", currentLexeme);
    if (!lst) lst = make_shared<ASTStatementList>();
    switch (currentLexeme.token) {
        case Token::PRINT:
        case Token::PRINTLN:
        case Token::ID:
        case Token::IF:
        case Token::WHILE:
            lst->statements.push_back(stmt());
            stmts(lst);
            break;
        default:
            // May be empty
            break;
    }
    return lst;
}
std::shared_ptr<ASTStatement> Parser::stmt() {
    ContextLog clog("stmt", currentLexeme);
    switch (currentLexeme.token) {
        case Token::PRINT:
        case Token::PRINTLN:
            return output();
            break;
        case Token::ID:
            return assign();
            break;
        case Token::IF:
            return cond();
            break;
        case Token::WHILE:
            return loop();
            break;
        default:
            error("Expected statement");
    }
}

std::shared_ptr<ASTPrintStatement> Parser::output() {
    ContextLog clog("output", currentLexeme);
    auto ans = std::make_shared<ASTPrintStatement>();
    if (currentLexeme.token == Token::PRINT) {
        eat(Token::PRINT, "Expected print");
        ans->isPrintln = false;
    } else {
        eat(Token::PRINTLN, "Expected print or println");
        ans->isPrintln = true;
    }
    eat(Token::LPAREN, "Expected '('");
    ans->expression = expr();
    eat(Token::RPAREN, "Expected ')'");
    eat(Token::SEMICOLON, "Expected ';'");
    return ans;
}

std::shared_ptr<ASTReadExpression> Parser::input() {
    ContextLog clog("input", currentLexeme);
    auto ans = std::make_shared<ASTReadExpression>();
    // TODO
    
    if (currentLexeme.token == Token::READINT){
        eat(Token::READINT, "Expected READINT");
        eat(Token::LPAREN, "Expected '('");
        eat(Token::STRING, "Expected string");
        eat(Token::RPAREN, "Expected ')'");
    }
    else if (currentLexeme.token == Token::READSTR){
        eat(Token::READSTR, "Expected READSTR");
        eat(Token::LPAREN, "Expected '('");
        eat(Token::STRING, "Expected string");
        eat(Token::RPAREN, "Expected ')'");
    }
    else{
        eat(Token::READINT, "Expected READINT or READSTR");
    }
    return ans;
}

std::shared_ptr<ASTAssignmentStatement> Parser::assign() {
    ContextLog clog("assign", currentLexeme);
    auto ans = make_shared<ASTAssignmentStatement>();
    // TODO
    
    eat(Token::ID, "Expected identifier");
    listindex(); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! LEFT OFF HERE
    eat(Token::ASSIGN, "Expected '='");
    expr();
    eat(Token::SEMICOLON, "Expected ';'");
    
    return ans;
}

std::shared_ptr<ASTExpression> Parser::listindex() {
    ContextLog clog("listindex", currentLexeme);
    // TODO
    return nullptr;
}

std::shared_ptr<ASTExpression> Parser::expr() {
    ContextLog clog("expr", currentLexeme);
    // TODO
    return nullptr;
}
void Parser::exprt(std::shared_ptr<ASTComplexExpression> expression) {
    ContextLog clog("exprt", currentLexeme);
    // TODO
}

bool isTokenAValue(Token token) {
    switch (token) {
        case Token::ID:
        case Token::STRING:
        case Token::INT:
        case Token::BOOL:
        case Token::READINT:
        case Token::READSTR:
        case Token::LBRACKET:
            return true;
            break;
        default:
            return false;
    }
}

std::shared_ptr<ASTExpression> Parser::value() {
    ContextLog clog("value", currentLexeme);
    switch (currentLexeme.token) {
        case Token::ID:
        {
            // TODO
            return nullptr;
            break;
        }
        case Token::STRING:
        {
            auto ans = make_shared<ASTLiteral>();
            ans->type = MPLType::STRING;
            ans->value = currentLexeme.text;
            advance();
            return ans;
            break;
        }
        case Token::INT:
        {
            auto ans = make_shared<ASTLiteral>();
            // TODO
            return ans;
            break;
        }
        // TODO
        default:
            error("Expected a value");
    }
}

std::shared_ptr<ASTListLiteral> Parser::exprlist() {
    ContextLog clog("exprlist", currentLexeme);
    auto ans = make_shared<ASTListLiteral>();
    // TODO
    return ans;
}
void Parser::exprtail(std::shared_ptr<ASTListLiteral> list) {
    ContextLog clog("exprtail", currentLexeme);
    // TODO
}

std::shared_ptr<ASTIfStatement> Parser::cond() {
    ContextLog clog("cond", currentLexeme);
    auto ans = make_shared<ASTIfStatement>();
    // TODO
    return ans;
}

void Parser::condt(std::shared_ptr<ASTIfStatement> statement) {
    ContextLog clog("condt", currentLexeme);
    // TODO
}

std::shared_ptr<ASTBoolExpression> Parser::bexpr() {
    ContextLog clog("bexpr", currentLexeme);
    // TODO
    return nullptr;
}

void Parser::bexprt(std::shared_ptr<ASTComplexBoolExpression> expression) {
    ContextLog clog("bexprt", currentLexeme);
    switch (currentLexeme.token) {
        case Token::EQUAL:
        case Token::LESS_THAN:
        case Token::GREATER_THAN:
        case Token::LESS_THAN_EQUAL:
        case Token::GREATER_THAN_EQUAL:
        case Token::NOT_EQUAL:
            expression->relation = currentLexeme.token;
            break;
        default:
            error("Internal error: expected relational operator");
    }
    advance();
    expression->second = expr();
    bconnect(expression);
}

void Parser::bconnect(std::shared_ptr<ASTComplexBoolExpression> expression) {
    ContextLog clog("bconnect", currentLexeme);
    // TODO
}

std::shared_ptr<ASTWhileStatement> Parser::loop() {
    ContextLog clog("loop", currentLexeme);
    auto ans = make_shared<ASTWhileStatement>();
    // TODO
    return ans;
}
