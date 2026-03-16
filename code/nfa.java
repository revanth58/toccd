import java.util.Scanner;
import java.util.Arrays;

class n{

	public int states=6;
	public int[][][]  transition= {	{{0,1},{0}}, {{2},{2}}, {{3},{3}}, {{4},{4}}, {{5},{5}}, {{},{}} };
	public String alphabet = "ab";

	public int start_state[] = {0};

	public int final_state[] = {5};

	public int NFA(String str){
		int curr_states[] = new int[states];
		for(int i=0;i<start_state.length;i++){
			curr_states[start_state[i]] = 1;
		}
		for(int i=0;i<str.length();i++){
			int j;
			for(j=0;true;j++){
				if(str.charAt(i)==alphabet.charAt(j))break;
			}
			int new_curr_states[] = new int[states];
			for(int z=0;z<states;z++){
				if(curr_states[z]==1){
					for(int k=0;k<transition[z][j].length;k++){
						new_curr_states[transition[z][j][k]]=1;
					}
				}
			}
			curr_states = Arrays.copyOf(new_curr_states,new_curr_states.length);
		}
		for(int i=0;i<final_state.length;i++){
			if(curr_states[final_state[i]] == 1)return 1;
		}return 0;
	}

	public void main(String[] args){
		Scanner sc = new Scanner(System.in);
		while(true){
			System.out.print("enter string : ");
			String str = sc.nextLine();
			System.out.println(NFA(str));
		}
	}
}