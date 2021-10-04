#ifndef PARSER_PARSER_HEADER_FILE
#define PARSER_PARSER_HEADER_FILE

#include<vector>
#include<string>

namespace parser
{
class Program;
class Def;
class ListDef;
class Arg;
class ListArg;
class ListStm;
class Stm;
class Dec;
class ListDec;
class Type;
class ListType;
class Exp;
class ListExp;
class AddOp;
class MulOp;
class RelOp;
class Length;
class ListLength;
class Struct;
class Field;
class ListField;
class Member;
class ListMember;
typedef union
{
  int    _int;
  char   _char;
  double _double;
  char*  _string;
  Program* program_;
  Def* def_;
  ListDef* listdef_;
  Arg* arg_;
  ListArg* listarg_;
  ListStm* liststm_;
  Stm* stm_;
  Dec* dec_;
  ListDec* listdec_;
  Type* type_;
  ListType* listtype_;
  Exp* exp_;
  ListExp* listexp_;
  AddOp* addop_;
  MulOp* mulop_;
  RelOp* relop_;
  Length* length_;
  ListLength* listlength_;
  Struct* struct_;
  Field* field_;
  ListField* listfield_;
  Member* member_;
  ListMember* listmember_;
} YYSTYPE;

Program* pProgram(FILE *inp);
Program* pProgram(const char *str);
}

#define PARSER__ERROR_ 258
#define _SYMB_10 259
#define _SYMB_22 260
#define _SYMB_16 261
#define _SYMB_11 262
#define _SYMB_0 263
#define _SYMB_1 264
#define _SYMB_28 265
#define _SYMB_14 266
#define _SYMB_13 267
#define _SYMB_7 268
#define _SYMB_4 269
#define _SYMB_9 270
#define _SYMB_8 271
#define _SYMB_29 272
#define _SYMB_27 273
#define _SYMB_15 274
#define _SYMB_23 275
#define _SYMB_5 276
#define _SYMB_17 277
#define _SYMB_18 278
#define _SYMB_6 279
#define _SYMB_21 280
#define _SYMB_19 281
#define _SYMB_20 282
#define _SYMB_25 283
#define _SYMB_24 284
#define _SYMB_26 285
#define _SYMB_30 286
#define _SYMB_31 287
#define _SYMB_32 288
#define _SYMB_33 289
#define _SYMB_34 290
#define _SYMB_35 291
#define _SYMB_36 292
#define _SYMB_37 293
#define _SYMB_38 294
#define _SYMB_39 295
#define _SYMB_40 296
#define _SYMB_41 297
#define _SYMB_42 298
#define _SYMB_43 299
#define _SYMB_44 300
#define _SYMB_45 301
#define _SYMB_2 302
#define _SYMB_12 303
#define _SYMB_3 304
#define PARSER__STRING_ 305
#define PARSER__CHAR_ 306
#define PARSER__INTEGER_ 307
#define PARSER__DOUBLE_ 308
#define PARSER__IDENT_ 309

extern parser::YYSTYPE parseryylval;

#endif
