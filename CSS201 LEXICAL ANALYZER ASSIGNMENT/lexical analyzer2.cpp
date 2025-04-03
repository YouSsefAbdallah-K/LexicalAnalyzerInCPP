#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>

using namespace std;

int charClass;
string lexeme;
char nextChar;
int lexLen;
int token;
int nextToken;
ifstream in_fp;
vector<pair<int, string>> tokens;
string currentStatement;
stringstream ss; 

void addChar();
void getChar();
void getNonBlank();
int lex();
int lookup(char ch);

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define SEMICOLON 27 
#define EOF_TOKEN -1

int main() {
    in_fp.open("program.txt");
    if (!in_fp.is_open()) {
        cerr << "ERROR - cannot open program.txt \n";
        return 1;
    }

   
    string line;
    while (getline(in_fp, line)) {
        currentStatement += line;
        currentStatement += " ";
    }
    in_fp.close();

   
    ss.str(currentStatement);
    char ch;
    while (ss.get(ch)) {
        nextChar = ch;
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else if (isspace(nextChar))
            charClass = -1; 
        else
            charClass = UNKNOWN;

        lex();
    }
    nextToken = EOF_TOKEN;
    tokens.push_back({nextToken, "EOF"});

    cout << "\nTokens and Lexemes:" << endl;
    for (const auto& tok : tokens) {
        cout << "Token: " << tok.first << ", Lexeme: " << tok.second << endl;
    }

    return 0;
}

int lookup(char ch) {
    lexeme = "";
    lexeme += ch;
    switch (ch) {
        case '(':
            nextToken = LEFT_PAREN;
            break;
        case ')':
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            nextToken = ADD_OP;
            break;
        case '-':
            nextToken = SUB_OP;
            break;
        case '*':
            nextToken = MULT_OP;
            break;
        case '/':
            nextToken = DIV_OP;
            break;
        case '=':
            nextToken = ASSIGN_OP;
            break;
        case ';':
            nextToken = SEMICOLON; 
            break;
        default:
            nextToken = EOF_TOKEN;
            lexeme = "";
            break;
    }
    return nextToken;
}

void addChar() {
    
}

void getChar() {
   
}

void getNonBlank() {
}

int lex() {
    if (charClass == -1) { 
        return nextToken;
    }

    if (charClass == LETTER) {
        lexeme = "";
        lexeme += nextChar;
        while (ss.get(nextChar)) {
            if (isalnum(nextChar)) {
                lexeme += nextChar;
            } else {
                ss.unget();
                break;
            }
        }
        nextToken = IDENT;
        tokens.push_back({nextToken, lexeme});
    } else if (charClass == DIGIT) {
        lexeme = "";
        lexeme += nextChar;
        while (ss.get(nextChar)) {
            if (isdigit(nextChar)) {
                lexeme += nextChar;
            } else {
                ss.unget();
                break;
            }
        }
        nextToken = INT_LIT;
        tokens.push_back({nextToken, lexeme});
    } else if (charClass == UNKNOWN) {
        lookup(nextChar);
        if (nextToken != EOF_TOKEN) {
            tokens.push_back({nextToken, lexeme});
        }
    } else if (charClass == EOF) {
        nextToken = EOF_TOKEN;
        tokens.push_back({nextToken, "EOF"});
    }
    return nextToken;
}