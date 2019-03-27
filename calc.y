%{
#include<stdio.h>
#include<math.h>
int yylex(void);
void yyerror(char *);
%}
%token INTEGER
%left UMINUS
%%

program:
	program expr '\n' { printf("%d\n", $2);	}
	|
	;
expr:  expr '+' expr { $$ = $1 + $3;}
    | expr '-' expr { $$ = $1 - $3;}
    | expr '*' expr {$$ = $1 * $3;}
    | expr '/' expr { if($3==0) yyerror("divide by zero"); else $$ = $1 / $3;}
    | expr '^' expr {$$ = pow($1,$3);}
    | '-' expr {$$= -$2;}
    |  expr '+' '+' {$$ = $1+1;}
    |   '+' '+'  expr {$$ = $3+1;}
    | '(' expr ')' {$$ =$2;}
    
    |INTEGER 	{ $$ = $1;}
    |
    ;
%%

void yyerror(char *s){
	fprintf(stderr,"%s\n",s);
	}
	
	
int main(void){
yyparse();
return 0;
}
