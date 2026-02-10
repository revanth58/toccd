#include<stdio.h>
#include<stdlib.h>

//string we are trying to construct a parse tree for
char *str = "a+b*a$";


//stack of production rules we used in order
char *stk[100];
int top= -1;


//pushing items into the stack
void push_stk(char *item){
	top++;
	stk[top] = item;
}

/*
	function prototype declarations :-

	since we use multiple functions with interconnected 
	recursions and cant determine the order we have to write 
	them, we just write prototypes at the start
*/
int match(int *, char );
int E(int *);
int Ep(int *);
int T(int *);
int Tp(int *);
int F(int *);
int S(int *);

/*
	match : just verify if current terminal symbol on leftmost 
	position is matching with the terminal symbol in the input
	 string and if so increment the next pointer
*/
int match(int *next, char c){
	if(str[*next] == c){
		(*next)++;
		return 1;
	}
	return 0;
}

/*
	for every non-terminal, write a function
	it just looks at the lookahead character and
	directly decides which production rule to use based on the LL1 table

	unlike recursive descent, we dont need to write a function for every 
	production rule
*/
int F(int *next){
	if(str[*next] == 'a'){push_stk("F --> a");return match(next,'a');}
	if(str[*next] == 'b'){push_stk("F --> b");return match(next,'b');}
	if(str[*next] == '('){push_stk("F --> (E)");;return match(next,'(')&&E(next)&&match(next,')');}
	return 0;
}

/*
	for e-productions we dont have to match with anything so return 1
	but for others, match every nonterminal in order
*/
int Tp(int *next){
	if(str[*next] == '*'){
		push_stk("T' --> *FT'");
		return match(next,'*')&&F(next)&&Tp(next);
	}
	if(str[*next] == '$' || str[*next] == ')' || str[*next] == '+') {push_stk("T' --> e");return 1;}
	return 0;
}

int T(int *next){
	if(str[*next] == 'a' || str[*next] == 'b' || str[*next] == '('){push_stk("T --> FT'");return F(next)&&Tp(next);}
	return 0;
}

int Ep(int *next){
	if(str[*next] == '+'){
		push_stk("E' --> +TE'");
		return match(next,'+')&&T(next)&&Ep(next);
	}
	if(str[*next] == '$' || str[*next] == ')') {push_stk("E' --> e");return 1;}
	return 0;
}

int E(int *next){
	if(str[*next] == 'a' || str[*next] == 'b' || str[*next] == '('){push_stk("E --> TE'");return T(next)&&Ep(next);}
	return 0;
}

/*
	S --> E$ is an extra rule we are using where E is our
	actual starting nonterminal
*/
int S(int *next){
	return E(next)&&match(next,'$');
}

int main(){
	//n will be our next pointer we pass, whose value will be in a
	int a=0;
	int *n=&a;

	//call S(n)
	printf("%d\n",S(n));

	//print the productions we have in our stack
	for(int i=0;i<=top;i++){
		printf("%s\n",stk[i]);
	}
}

/*
	the grammar we are implementing is :

	E --> TE'
	E' --> +E | e    (empty string)
	T --> FT'
	T' --> *T | e
	F --> a | b | (E)

	additionally S --> E$

	which is just a left factored version of previous one 
	we impemented in recursive descent
*/