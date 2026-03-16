#include<stdio.h>
#include<string.h>


int states = 5;
int transition[5][2]= {
	{3,1}, {2,3}, {3,4},{3,3}, {4,4}
};

char alphabet[2] = "ab";

int final[5] = {0,0,0,0,1};


int DFA(char *str){
	int curr_state = 0;

	for(int i=0;1;i++){
		if(str[i] =='\0')break;
		int j;
		for(j=0;j<strlen(alphabet);j++){
			if(alphabet[j]==str[i])break;
		}
		curr_state = transition[curr_state][j];
	}
	return final[curr_state];
}

int main(){
	char str[20];
	while(1){
		printf("enter string : ");
		scanf("%s",str);
		printf("%d\n",DFA(str));
	}
	
}