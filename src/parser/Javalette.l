/* This FLex file was machine-generated by the BNF converter */
%option prefix="parseryy"
%{
#include <string.h>
#include "Parser.H"
extern int parseryy_mylinenumber ;

/* BEGIN extensible string buffer */

#include "Buffer.H"

/* The initial size of the buffer to lex string literals. */
#define LITERAL_BUFFER_INITIAL_SIZE 1024

/* The pointer to the literal buffer. */
static Buffer literal_buffer = NULL;

/* Initialize the literal buffer. */
#define LITERAL_BUFFER_CREATE() literal_buffer = newBuffer(LITERAL_BUFFER_INITIAL_SIZE)

/* Append characters at the end of the buffer. */
#define LITERAL_BUFFER_APPEND(s) bufferAppendString(literal_buffer, s)

/* Append a character at the end of the buffer. */
#define LITERAL_BUFFER_APPEND_CHAR(c) bufferAppendChar(literal_buffer, c)

/* Release the buffer, returning a pointer to its content. */
#define LITERAL_BUFFER_HARVEST() releaseBuffer(literal_buffer)

/* In exceptional cases, e.g. when reaching EOF, we have to free the buffer. */
#define LITERAL_BUFFER_FREE() freeBuffer(literal_buffer)

/* END extensible string buffer */

%}

LETTER [a-zA-Z]
CAPITAL [A-Z]
SMALL [a-z]
DIGIT [0-9]
IDENT [a-zA-Z0-9'_]
%START YYINITIAL CHAR CHARESC CHAREND STRING ESCAPED COMMENT

%%  /* Rules. */

<YYINITIAL>"("      	 return _SYMB_0;
<YYINITIAL>")"      	 return _SYMB_1;
<YYINITIAL>"{"      	 return _SYMB_2;
<YYINITIAL>"}"      	 return _SYMB_3;
<YYINITIAL>","      	 return _SYMB_4;
<YYINITIAL>";"      	 return _SYMB_5;
<YYINITIAL>"="      	 return _SYMB_6;
<YYINITIAL>"++"      	 return _SYMB_7;
<YYINITIAL>"--"      	 return _SYMB_8;
<YYINITIAL>"-"      	 return _SYMB_9;
<YYINITIAL>"!"      	 return _SYMB_10;
<YYINITIAL>"&&"      	 return _SYMB_11;
<YYINITIAL>"||"      	 return _SYMB_12;
<YYINITIAL>"+"      	 return _SYMB_13;
<YYINITIAL>"*"      	 return _SYMB_14;
<YYINITIAL>"/"      	 return _SYMB_15;
<YYINITIAL>"%"      	 return _SYMB_16;
<YYINITIAL>"<"      	 return _SYMB_17;
<YYINITIAL>"<="      	 return _SYMB_18;
<YYINITIAL>">"      	 return _SYMB_19;
<YYINITIAL>">="      	 return _SYMB_20;
<YYINITIAL>"=="      	 return _SYMB_21;
<YYINITIAL>"!="      	 return _SYMB_22;
<YYINITIAL>":"      	 return _SYMB_23;
<YYINITIAL>"[]"      	 return _SYMB_24;
<YYINITIAL>"["      	 return _SYMB_25;
<YYINITIAL>"]"      	 return _SYMB_26;
<YYINITIAL>"."      	 return _SYMB_27;
<YYINITIAL>")null"      	 return _SYMB_28;
<YYINITIAL>"->"      	 return _SYMB_29;
<YYINITIAL>"boolean"      	 return _SYMB_30;
<YYINITIAL>"class"      	 return _SYMB_31;
<YYINITIAL>"double"      	 return _SYMB_32;
<YYINITIAL>"else"      	 return _SYMB_33;
<YYINITIAL>"extends"      	 return _SYMB_34;
<YYINITIAL>"false"      	 return _SYMB_35;
<YYINITIAL>"for"      	 return _SYMB_36;
<YYINITIAL>"if"      	 return _SYMB_37;
<YYINITIAL>"int"      	 return _SYMB_38;
<YYINITIAL>"new"      	 return _SYMB_39;
<YYINITIAL>"return"      	 return _SYMB_40;
<YYINITIAL>"struct"      	 return _SYMB_41;
<YYINITIAL>"true"      	 return _SYMB_42;
<YYINITIAL>"typedef"      	 return _SYMB_43;
<YYINITIAL>"void"      	 return _SYMB_44;
<YYINITIAL>"while"      	 return _SYMB_45;

<YYINITIAL>"#"[^\n]* ; // BNFC: comment "#";
<YYINITIAL>"//"[^\n]* ; // BNFC: comment "//";
<YYINITIAL>"/*" BEGIN COMMENT; // BNFC: block comment "/*" "*/";
<COMMENT>"*/" BEGIN YYINITIAL;
<COMMENT>.    /* skip */;
<COMMENT>[\n] ++parseryy_mylinenumber;

<YYINITIAL>"\""        	 LITERAL_BUFFER_CREATE(); BEGIN STRING;
<STRING>\\             	 BEGIN ESCAPED;
<STRING>\"             	 parseryylval._string = LITERAL_BUFFER_HARVEST(); BEGIN YYINITIAL; return PARSER__STRING_;
<STRING>.              	 LITERAL_BUFFER_APPEND_CHAR(yytext[0]);
<ESCAPED>n             	 LITERAL_BUFFER_APPEND_CHAR('\n'); BEGIN STRING;
<ESCAPED>\"            	 LITERAL_BUFFER_APPEND_CHAR('"');  BEGIN STRING;
<ESCAPED>\\            	 LITERAL_BUFFER_APPEND_CHAR('\\'); BEGIN STRING;
<ESCAPED>t             	 LITERAL_BUFFER_APPEND_CHAR('\t'); BEGIN STRING;
<ESCAPED>.             	 LITERAL_BUFFER_APPEND(yytext);    BEGIN STRING;
<STRING,ESCAPED><<EOF>>	 LITERAL_BUFFER_FREE(); return PARSER__ERROR_;
<YYINITIAL>"'" 	BEGIN CHAR;
<CHAR>\\      	 BEGIN CHARESC;
<CHAR>[^']      	 BEGIN CHAREND; parseryylval._char = yytext[0]; return PARSER__CHAR_;
<CHARESC>n      	 BEGIN CHAREND; parseryylval._char = '\n';     return PARSER__CHAR_;
<CHARESC>t      	 BEGIN CHAREND; parseryylval._char = '\t';     return PARSER__CHAR_;
<CHARESC>.      	 BEGIN CHAREND; parseryylval._char = yytext[0]; return PARSER__CHAR_;
<CHAREND>"'"      	 BEGIN YYINITIAL;
<YYINITIAL>{DIGIT}+"."{DIGIT}+("e"(\-)?{DIGIT}+)?      	 parseryylval._double = atof(yytext); return PARSER__DOUBLE_;
<YYINITIAL>{DIGIT}+      	 parseryylval._int = atoi(yytext); return PARSER__INTEGER_;
<YYINITIAL>{LETTER}{IDENT}*      	 parseryylval._string = strdup(yytext); return PARSER__IDENT_;
\n  ++parseryy_mylinenumber ;
<YYINITIAL>[ \t\r\n\f]      	 /* ignore white space. */;
<YYINITIAL>.      	 return PARSER__ERROR_;
%%
void parserinitialize_lexer(FILE *inp) { yyrestart(inp); BEGIN YYINITIAL; }
int yywrap(void) { return 1; }

