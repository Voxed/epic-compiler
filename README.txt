
                    Extended Javalette Compiler (JLC++) :)                           
________________________________________________________________________________

1. Dependencies

    The compiler has successfully been tested with the standard docker offered
    at https://github.com/myreen/tda283/tree/master/tester/Docker 

    The make script depends on clang with access to the C++20 standard, the LLVM 
    library, and BNFC. If you only have access to gcc, modify the CXX and
    CC options in the make file or set them in your environment.

    An optional dependency is Bear (Build EAR). Bear allows generation of a
    compile_commands.json file using "make bear" which can be used to provide 
    better intellisense together with clangd.

2. Usage

    The compiler reads input from stdin so in order to use it on a given file 
    you'll have to use the bash input redirection operator '<'. The IR code is
    emitted to stdout.

    So, for example, if you wish to compile a Javalette file factorial.jl, you 
    would execute the command "./jlc < factorial.jl > code.ll".

    Afterwards, in order to assemble the llvm ir code run "clang code.ll 
    lib/runtime.ll"

3. Grammer

    The LBNF grammer is located in src/Javalette.cf.

    The grammer contains one shift/reduce conflict located on line 33 and 34.
    When the grammer is applied to something like this, 

        if ( exp ); 
            if ( exp ); 
        else;

    The result is ambigious as the else statement could attach to the first or
    second if statement. However, since Bison by default always chooses to 
    shift in these situations, the result is deterministic and thus not a
    problem. The else will always attach to the innermost if statement.

4. Extensions

    Full llvm support for extensions arrays1, arrays2, pointers, objects1 and 
    objects2.

    The compiler also implements inline pointers from adv_structs

5. Some code clarifications

    Entry point to the program is in main.cpp, entry point for the typechecker
    is in checker/Check.cpp, entry point for the compiler is in 
    compiler/Compile.cpp

    The ClassDescriptor class is not exclusively used by classes. It is also
    used by arrays and structs. It will however only provide a vtable if methods
    were provided before .Finalize() is called. 

    It's important to diffirentiate between code found in the checker:: 
    namespace and code found in the compiler:: namespace as in order to simplify 
    names classes in the namespaces were named the same.
