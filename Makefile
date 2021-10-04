# Settings
CXX           = clang++
CC 		      = clang
CXXFLAGS      = -std=c++20 -g -Isrc
CFLAGS        = -g
LIBS          = -lLLVM
FLEXFLAGS     = 
BISONFLAGS    = -Wcounterexamples

# Directories
ODIR          = build/obj
GDIR          = build/generated
SDIR          = src

# Dependencies
_DEPS         = ast/BaseVisitor.hpp				 	\
				ast/Print.hpp					 	\
				ast/Clone.hpp						\
				ast/Destroy.hpp						\
												 	\
				checker/Check.hpp				 	\
				checker/TopDecChecker.hpp 			\
				checker/State.hpp				 	\
				checker/FunctionChecker.hpp			\
				checker/StatementChecker.hpp		\
				checker/DeclaratorChecker.hpp		\
				checker/ExpressionChecker.hpp		\
				checker/IdentTypeChecker.hpp		\
				checker/ClassDescriptor.hpp			\
				checker/StructChecker.hpp			\
				checker/ClassChecker.hpp			\
				checker/MemberChecker.hpp			\
				checker/ClassMethodChecker.hpp		\
				checker/MethodChecker.hpp			\
				checker/MemberAccessChecker.hpp		\
												 	\
				common/Exceptions.hpp 		 	 	\
				common/BoolLitDeducer.hpp			\
				common/TypeDeducer.hpp				\
				common/OperatorDeducer.hpp 			\
													\
				compiler/Compile.hpp				\
				compiler/State.hpp					\
				compiler/TopDecCompiler.hpp			\
				compiler/TypeCompiler.hpp			\
				compiler/FunctionCompiler.hpp		\
				compiler/StatementCompiler.hpp		\
				compiler/ExpressionCompiler.hpp		\
				compiler/DeclaratorCompiler.hpp		\
				compiler/Allocate.hpp				\
				compiler/StructCompiler.hpp			\
				compiler/ClassDescriptor.hpp		\
				compiler/ClassCompiler.hpp			\
				compiler/MemberCompiler.hpp			\
				compiler/ClassMethodCompiler.hpp	\
				compiler/MethodCompiler.hpp			\
				compiler/MemberAccessCompiler.hpp	\

# Object files
_OBJ          = main.o 								\
													\
			  	parser/Absyn.o 						\
			  	parser/Buffer.o 					\
			  	parser/Printer.o 					\
				parser/Parser.o 					\
				parser/Lexer.o 						\
													\
				ast/BaseVisitor.o 					\
				ast/Print.o							\
				ast/Clone.o							\
				ast/Destroy.o						\
													\
				checker/Check.o						\
				checker/TopDecChecker.o 			\
				checker/State.o						\
				checker/FunctionChecker.o			\
				checker/StatementChecker.o			\
				checker/DeclaratorChecker.o			\
				checker/ExpressionChecker.o			\
				checker/IdentTypeChecker.o 			\
				checker/ClassDescriptor.o			\
				checker/StructChecker.o				\
				checker/ClassChecker.o				\
				checker/MemberChecker.o				\
				checker/ClassMethodChecker.o		\
				checker/MethodChecker.o				\
				checker/MemberAccessChecker.o		\
													\
				common/Exceptions.o 				\
				common/BoolLitDeducer.o				\
				common/TypeDeducer.o				\
				common/OperatorDeducer.o 			\
													\
				compiler/Compile.o					\
				compiler/State.o					\
				compiler/TopDecCompiler.o			\
				compiler/TypeCompiler.o				\
				compiler/FunctionCompiler.o			\
				compiler/StatementCompiler.o		\
				compiler/ExpressionCompiler.o		\
				compiler/DeclaratorCompiler.o		\
				compiler/Allocate.o					\
				compiler/StructCompiler.o			\
				compiler/ClassDescriptor.o			\
				compiler/ClassCompiler.o			\
				compiler/MemberCompiler.o			\
				compiler/ClassMethodCompiler.o		\
				compiler/MethodCompiler.o			\
				compiler/MemberAccessCompiler.o		\

ODIRS         = parser ast checker common ir llvm compiler

GDIRS         = parser

# Makefile code, do not change below this line
RDIRS         = $(GDIR) $(ODIR)
DIRS          = $(RDIRS) $(patsubst %,$(ODIR)/%,$(ODIRS)) $(patsubst %,$(GDIR)/%,$(GDIRS))
OBJ           = $(patsubst %,$(ODIR)/%,$(_OBJ))
DEPS 		  = $(patsubst %,$(SDIR)/%,$(_DEPS))

all: jlc

zip:
	tar -czf partA-1.tar.gz src doc lib Makefile

.PHONY: clean
clean:
	rm -r $(RDIRS) || true

.PHONY: bear
bear: clean
	bear -- make all

jlc: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

$(ODIR)/parser/Lexer.o: $(SDIR)/parser/Javalette.l | $(DIRS)
	flex -o $(GDIR)/parser/Lexer.C $(SDIR)/parser/Javalette.l $(FLEXFLAGS)
	$(CXX) -c -o $(ODIR)/parser/Lexer.o $(GDIR)/parser/Lexer.C $(CXXFLAGS) -I$(SDIR)/parser

$(ODIR)/parser/Parser.o: $(SDIR)/parser/Javalette.l | $(DIRS)
	bison -o $(GDIR)/parser/Parser.C $(SDIR)/parser/Javalette.y $(BISONFLAGS)
	$(CXX) -c -o $(ODIR)/parser/Parser.o $(GDIR)/parser/Parser.C $(CXXFLAGS) -I$(SDIR)/parser

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS) | $(DIRS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/%.o: $(SDIR)/%.C $(DEPS) | $(DIRS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(DIRS):
	mkdir -p $@