#include <string>

// definition of token value
// If undefined string, return 0 to 255(ASCII code)
enum Token {
    // EOF
    tokenEof = -1,

    // token value of reserved word
    tokenDef = -2,
    tokenExtern = -3,

    // primary tokens(identifier, literal, etc...)
    tokenIdentifier = -4,
    tokenNumber = -5,
};

static std::string identifier_str;
static double num_val;

// lexer
// gettok - return next token from stdin
static int get_token() {
    static int last_char = ' ';

    // skip spaces
    while (isspace(last_char)) last_char = getchar();

    // recognize identifier token
    if (isalpha(last_char)) {  // identifier: [a-zA-Z][a-zA-Z0-9]*
        // combine characters
        while (isalnum((last_char = getchar()))) identifier_str += last_char;

        // check if string is "reserved word"
        if (identifier_str == "def") return tokenDef;
        if (identifier_str == "extern") return tokenExtern;
        return tokenIdentifier;  // NOT "reserved word"
    }

    // recognize number token
    if (isdigit(last_char) || last_char == '.') {  // number: [0-9.]+
        // FIXME: 1.23.45.76 is read
        std::string num_str = "";
        do {
            num_str += last_char;
            last_char = getchar();  // input next [0-9] or [.]
        } while (isdigit(last_char) || last_char == '.');
        num_val = strtod(num_str.c_str(), 0);
        return tokenNumber;
    }

    // recognize comments line
    // lines beginning with a # are comments
    if (last_char == '#') {
        // read line to the end of the line
        do {
            last_char = getchar();
        } while (last_char != EOF && last_char != '\n' && last_char != '\r');

        if (last_char != EOF) return get_token();  // get next token
    }

    // recognize EOF
    if (last_char == EOF) return tokenEof;

    // recognize undefined identifier token, e.g. '+'
    // return ASCII code value
    int tmp_char = last_char;  // ASCII value
    last_char = getchar();
    return tmp_char;
}
