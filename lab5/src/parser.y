%{
    #include <stdarg.h>
    #include <stdio.h>
    #include "shared_values.h"
    #define YYSTYPE char *
    extern int yylineno;
    int yylex();
    void yyerror(const char *s);
    int yydebug = 1;
    int indent = 0;
    char *iden_dum;
%}

// Tokens Definition
%token START_OF_COMMENT
%token END_OF_COMMENT
%token IF
%token ELSE
%token INT
%token RETURN
%token VOID
%token WHILE
%token PLUS
%token MINUS
%token MULTIPLY
%token DIVIDE
%token LESS_THAN
%token LESS_OR_EQUAL
%token GREATER_THAN
%token GREATER_OR_EQUAL
%token EQUALS
%token ASSIGNMENT
%token NOT_EQUALS
%token EOL
%token COMMA
%token LEFT_PARANTHESIS
%token RIGHT_PARANTHESIS
%token LEFT_BRACKET
%token RIGHT_BRACKET
%token LEFT_SQR_BRACKET
%token RIGHT_SQR_BRACKET
%token ID
%token NUM

// Grammar Rules for CFG
%%

program: declaration_list {printf("Програма\n");};

declaration_list: declaration_list declaration {printf("Список оголошень\n");};
| declaration {printf("Оголошення\n");};

declaration: var_declaration {printf("Оголошення змінної\n");};
| fun_declaration {printf("Оголошення функції\n");};

var_declaration: type_specifier ID EOL {printf("Оголошення змінної: \n");};
| type_specifier ID LEFT_SQR_BRACKET NUM RIGHT_SQR_BRACKET EOL {printf("Оголошення змінної(множини): \n");};

type_specifier: INT {printf("Визначення типу: int\n");};
| VOID {printf("Тип: void\n");};

fun_declaration: type_specifier ID LEFT_BRACKET params RIGHT_BRACKET compound_stmt {printf("Оголошення функції:\n");};

params: param_list {printf("Список параметрів\n");};
| VOID {printf("Без параметрів\n");};

param_list: param_list COMMA param;
| param {printf("Параметр\n");};

param: type_specifier ID {printf("Параметр: \n");};
| type_specifier ID LEFT_SQR_BRACKET RIGHT_SQR_BRACKET {printf("Параметр(множина): \n");};

compound_stmt: LEFT_PARANTHESIS local_declarations statement_list RIGHT_PARANTHESIS {printf("Зʼєднування\n");};

local_declarations: local_declarations var_declaration {printf("Локальне оголошення\n");};
| %empty {printf("Без локальних оголошень\n");};

statement_list: statement_list statement {printf("Список обʼявлень\n");};
| %empty {printf("Без обʼявлень\n");};

statement: expression_stmt {printf("Обʼявлення виразу\n");};
| compound_stmt {printf("Обʼявлення зʼєднання\n");};
| selection_stmt {printf("Обʼявлення вибору\n");};
| iteration_stmt {printf("Обʼявлення ітерації\n");};
| return_stmt {printf("Обʼявлення повернення\n");};

expression_stmt: expression EOL {printf("Обʼявлення виразу\n");};
| EOL {printf("Обʼявлення пустого виразу\n");};

selection_stmt: IF LEFT_BRACKET expression RIGHT_BRACKET statement {printf("If stmt\n");};
| IF LEFT_BRACKET expression RIGHT_BRACKET statement ELSE statement {printf("If-else stmt\n");};

iteration_stmt: WHILE LEFT_BRACKET expression RIGHT_BRACKET statement {printf("While loop\n");};

return_stmt: RETURN EOL {printf("Повернення\n");};
| RETURN expression EOL {printf("Повернення виразу\n");};

expression: var ASSIGNMENT expression {printf("Присвоєння\n");};
| simple_expression {printf("Простий вираз\n");};

var: ID {printf("Змінна\n");};
| ID LEFT_SQR_BRACKET expression RIGHT_SQR_BRACKET {printf("Розгортання множини\n");};

simple_expression: additive_expression relop additive_expression {printf("Бінарний вираз\n");};
| additive_expression {printf("Унарний вираз\n");};

relop: LESS_THAN {printf("<\n");};
| LESS_OR_EQUAL {printf("<=\n");};
| GREATER_THAN {printf(">\n");};
| GREATER_OR_EQUAL {printf(">=\n");};
| EQUALS {printf("==\n");};
| NOT_EQUALS {printf("!=\n");};

additive_expression: additive_expression addop term {printf("Додавання/віднімання\n");};
| term {printf("Term\n");};

addop: PLUS {printf("+");};
| MINUS {printf("-");};

term: term mulop factor {printf("Множення/ділення\n");};
| factor {printf("Factor\n");};

mulop: MULTIPLY {printf("*");};
| DIVIDE {printf("/");};

factor: LEFT_BRACKET expression RIGHT_BRACKET {printf("Вираз в дужках\n");};
            | var {printf("var factor \n");}
            | call {printf("call factor \n");}
            | NUM {printf("NUM factor \n");};
call: ID LEFT_BRACKET args RIGHT_BRACKET {printf("Аргумент в дужках \n");};
args: arg_list {printf("arg list \n");}
            | %empty {printf("no factor \n");};
arg_list: arg_list COMMA expression {printf(", \n");}
            | expression {printf("expr \n");};

%%                                                                              
int main (void) {     
  yyparse ();
}
