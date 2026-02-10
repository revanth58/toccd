#include<stdio.h>
#include<stdlib.h>

char *stk[100];
int top = -1;

void push_stk(char *str){
	top++;
	stk[top] = str;
}

void pop_stk(){
	top--;
	//free(stk[top+1]);
}

char *str = "b+a$";
int match(int *, char );
int D2(int *next);
int D1(int *next);
int D(int *next);
int S2(int *next);
int S1(int *next);
int S(int *next);
int Sp(int *next);

int match(int *next, char x){
	printf("trying to match %d with %c\n", *next,str[*next]);
	if(str[*next] == x){(*next)++;return 1;}
	return 0;
}

int D2(int *next){
	printf("trying D --> b\n");
	return match(next, 'b');
}

int D1(int *next){
	printf("trying D --> a\n");
	return match(next, 'a');
}

int D(int *next){
	int save = *next;
	int sav_top = top;
	return ((*next = save),push_stk("D --> a"), D1(next)) || ((*next = save),top = sav_top,push_stk("D --> b"), D2(next));
}

int S2(int *next){
	printf("trying S --> D\n");
	return D(next);
}

int S1(int *next){
	printf("trying S --> D+S\n");
	return D(next)&&match(next,'+')&&S(next);
}

int S(int *next){
    int save = *next;
    int sav_top = top;
    return ((*next = save),push_stk("S --> D+S"), S1(next)) || ((*next = save),top=sav_top,push_stk("S --> D") ,S2(next));
}

int Sp(int *next){
	return S(next)&&match(next,'$');
}

int main(){
	int a=0;int *n=&a;
	printf("%d ",Sp(n));
	printf("%d\n",a);
	for(int i=0;i<=top;i++){
		printf("%s\n",stk[i]);
	}
}
