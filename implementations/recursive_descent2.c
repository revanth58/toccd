#include<stdio.h>
#include<stdlib.h>

// the string we are trying to parse
char *str = "(a*(a)+((a)+b)*b)$";

/*
 	contains the stack of the valid production rules 
	we use in our leftmost derivation inorder
*/
char *stk[100];
int top = -1;

void push_stk(char *str){
	top++;
	stk[top] = str;
}

/*
	function prototype declarations :-

	since we use multiple functions with interconnected 
	recursions and cant determine the order we have to write 
	them, we just write prototypes at the start
*/
int match(int *, char );
int F3(int *next);
int F2(int *next);
int F1(int *next);
int F(int *next);
int D2(int *next);
int D1(int *next);
int D(int *next);
int S2(int *next);
int S1(int *next);
int S(int *next);
int Sp(int *next);

/*
	match : just verify if current terminal symbol on leftmost 
	position is matching with the terminal symbol in the input
	 string and if so increment the next pointer
*/
int match(int *next, char x){
	//printf("trying to match %d with %c\n", *next,str[*next]);
	if(str[*next] == x){(*next)++;return 1;}
	return 0;
}

/*
	write a function for every non-terminal, and 
	every non-terminal's every production rule

	every production function like F1,F2,F3 for all 3 production for F
	they will try if that is the valid production at that point

	and F will call all F1,F2,F3 inorder and if one fails, 
	next one is tried. until one of them is the valid rule at that stage

	also at every nonterminal's function push which production
	rule we are using into our current stack. ignore the one you
	previously used, just by overwriting at the same saved index
*/
int F3(int *next){
	//printf("trying F --> (S)\n");
	return match(next, '(')&&S(next)&&match(next, ')');
}

int F2(int *next){
	//printf("trying F --> b\n");
	return match(next,'b');
}

int F1(int *next){
	//printf("trying F --> a\n");
	return match(next, 'a');
}

int F(int *next){
	int save = *next;
	int sav_top = top;
	return ((*next = save),push_stk("F --> a"), F1(next)) || ((*next = save),top = sav_top,push_stk("F --> b"), F2(next)) || ((*next = save),top = sav_top,push_stk("F --> (S)"), F3(next));
}

int D2(int *next){
	//printf("trying D --> F\n");
	return F(next);
}

int D1(int *next){
	//printf("trying D --> F*D\n");
	return F(next)&&match(next, '*')&&D(next);
}

int D(int *next){
	int save = *next;
	int sav_top = top;
	return ((*next = save),push_stk("D --> F*D"), D1(next)) || ((*next = save),top = sav_top,push_stk("D --> F"), D2(next));
}

int S2(int *next){
	//printf("trying S --> D\n");
	return D(next);
}

int S1(int *next){
	//printf("trying S --> D+S\n");
	return D(next)&&match(next,'+')&&S(next);
}

int S(int *next){
    int save = *next;
    int sav_top = top;
    return ((*next = save),push_stk("S --> D+S"), S1(next)) || ((*next = save),top = sav_top,push_stk("S --> D"), S2(next));
}

/*
	S' --> S$ is an extra rule we are using where S is our
	actual starting nonterminal
*/
int Sp(int *next){
	return S(next)&&match(next,'$');
}

int main(){
	//n will be our next pointer we pass, whose value will be in a
	int a=0;int *n=&a;

	//call S(n)
	printf("%d ",Sp(n));
	printf("%d\n",a); // a just represents where the cursor is at the end

	//print the productions we have in our stack
	for(int i=0;i<=top;i++){
		printf("%s\n",stk[i]);
	}
}

/*
	the grammar we are implementing :
	S --> D+S | D
	D --> F*D | F
	F --> a | b | (S)

	at end additionally we have
	S' --> S$
*/
