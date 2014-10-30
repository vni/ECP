#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

/* FIXME: NOT WORKING: int (*prints[])(void); */

/*
 * PSEUDOCODE:
 *
 * utility routines...
 *
 * classify_string
 *     look at the current token and return a value of
 *     "type" "qualifier" or "identifier" in this.type
 *
 * gettoken
 *     read the next token into this.string
 *     if it is alphanumeric, classify_string
 *     else it must be a single character token
 *     this.type = the token itself; terminate this.string
 *     with a nul.
 *
 * read_to_first_identifier
 *     gettoken and push it onto the stack until the first 
 *     identifier is read.
 *     Print "identifier is ", this.string gettoken
 *
 * parsing routines...
 * 
 * deal_with_function_args
 *     read past closing ')' print out "function returning"
 * deal_with_arrays
 *     while you've got "[size]" print it out and read past it
 * deal_with_any_pointers
 *     while you've got "*" on the stack print "pointer to "
 *     and pop it
 * deal_with_declarator
 *     if this.type is '[' deal_with_arrays
 *     if this.type is '(' deal_with_function_args
 *     deal_with_any_pointers
 *     while there's stuff on the stack
 *     if it's a '(' pop it and gettoken; it should be closing ')'
 *     deal_with_declarator
 *     else pop it and print it
 *
 * main routine...
 *
 * main
 *      read_to_first_identifier
 *      deal_with_declarator
 *
 *
 *
 *
 */

#define TRACE printf("%s()\n", __FUNCTION__)

void die(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	exit(1);
}

void die_if(int condition, const char *fmt, ...) {
	if (condition) {
		va_list args;
		va_start(args, fmt);
		vfprintf(stderr, fmt, args);
		va_end(args);
		exit(1);
	}
}

#define MAXTOKENS 64
#define MAXTOKENLEN 128

enum TokenType {
	TYPE,
	QUALIFIER,
	IDENTIFIER,
	NUMBER,
};

const char *type_to_string(int ttype) {
	switch (ttype) {
		case TYPE:
			return "TYPE";
		case QUALIFIER:
			return "QUALIFIER";
		case IDENTIFIER:
			return "IDENTIFIER";
		case NUMBER:
			return "NUMBER";
		case '(':
			return "(";
		case ')':
			return ")";
		case '[':
			return "[";
		case ']':
			return "]";
		case '*':
			return "*";
		case ';':
			return ";";
		default:
			die("ERROR: Unknown type: %d ('%c')", ttype, ttype);
	}
	return NULL;
}

struct token {
	char type;
	char string[MAXTOKENLEN];
};

struct token stack[MAXTOKENS]; /* stack[0] is not used. Maybe in the future it will be used instead of this */
struct token this;
int stackpos;

#define STROP(a, R, b) (strcmp(a, b) R 0)
#define STREQ(a, b) STROP(a, ==, b)

void classify_string(void) {
	static char *types[] = { "char", "int", "long", "signed", "unsigned", "float", "double", NULL };
	static char *qualifiers[] = { "volatile", "const", NULL };
	int i;

	for (i = 0; types[i]; i++)
		if (STREQ(this.string, types[i])) {
			this.type = TYPE;
			return;
		}

	for (i = 0; qualifiers[i]; i++)
		if (STREQ(this.string, qualifiers[i])) {
			this.type = QUALIFIER;
			return;
		}

	this.type = IDENTIFIER;
}

void gettoken(void) {
	int c, len = 0;

	while (isspace(c = fgetc(stdin)))
		;
	die_if(c == EOF, "ERROR: Unexpected end-of-file\n");

	if (isalpha(c)) {
		/* read token */
		do {
			this.string[len++] = c;
			c = fgetc(stdin);
		} while (c != EOF && (isalnum(c) || c == '_') && len < MAXTOKENLEN-1);
		die_if(c == EOF, "ERROR: EOF reached\n");
		die_if(len == MAXTOKENLEN-1, "OOPS, TOO LONG TOKEN IN THE INPUT\n");
		ungetc(c, stdin);
		this.string[len++] = '\0';

		classify_string();

		return;
	} else if (isdigit(c)) {
		do {
			die_if(len >= MAXTOKENLEN, "ERROR: Number is too long to fit into token string\n");
			this.string[len++] = c;
			c = fgetc(stdin);
		} while (isdigit(c));
		die_if(c == EOF, "ERROR: during reading a NUMBER: EOF reached\n");
		ungetc(c, stdin);
		this.string[len] = '\0';
		this.type = NUMBER;
	} else if (c == '(' || c == ')' || c == '[' || c == ']' || c == '*' || c == ';' || c == ',') {
		this.string[len++] = c;
		this.string[len] = '\0';
		this.type = c;
	} else {
		die("ERROR: Unexpected input character: '%c'\n", c);
	}
}

void read_to_first_identifier(void) {
	do {
		gettoken();
		die_if(stackpos >= MAXTOKENS, "ERROR: Too many tokens\n");
		stack[++stackpos] = this;
		/*printf("{ %s, %s }\n", type_to_string(this.type), this.string);*/
	} while (this.type != IDENTIFIER);
	stackpos--; /* discard idenfier from the top of the stack. It is in this and needed only here. */

	printf("%s is ", this.string);
	gettoken();
}

void deal_with_arrays(void) {
	gettoken();
	if (this.type == ']') {
		printf("array of ");
		gettoken();
	} else if (this.type == NUMBER) { 
		printf("array of %d ", atoi(this.string));
		gettoken();
		die_if(this.type != ']', "ERROR: expected ']' after NUMBER in %s\n", __FUNCTION__);
		gettoken();
	} else {
		die("ERROR: deal_with_arrays got unexpected token: %s\n", type_to_string(this.type));
	}
}

/* deal_with_function_args do not parse function arguments, just reads till the closing ')' */
void deal_with_function_args(void) {
	do {
		gettoken();
	} while (this.type != ')');
	printf("function returning ");
	/*gettoken();*/
}

void deal_with_any_pointers(void) {
	while (stackpos && stack[stackpos].type == '*') {
		printf("pointer to ");
		stackpos--;
	}
}

void deal_with_declarator(void) {
	while (this.type == '[')
		deal_with_arrays();
	if (this.type == '(')
		deal_with_function_args();
	deal_with_any_pointers();
	while (stackpos) {
		if (stack[stackpos].type == '(') {
			printf("stack[stackpos].type == '('; this.type == '%c'\n", this.type);
			/*gettoken();*/
			die_if(this.type != ')', "ERROR: ')' expected, but got '%c'\n", this.type);
			gettoken();
			deal_with_declarator();
		} else {
			printf("%s ", stack[stackpos].string);
			/*printf("<HOW TO PRINT IT?> { %s, %s }\n", type_to_string(stack[stackpos].type), stack[stackpos].string);*/
		}
		stackpos--;
	}
}

int main(void) {
	printf("> ");
	fflush(stdout);
	read_to_first_identifier();
	deal_with_declarator();
	printf("\n");
	return 0;
}
