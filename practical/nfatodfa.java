import java.util.Scanner;
import java.util.Arrays;
import java.util.HashMap;


class n{

	//nfa representation  for L = { x | size of x is a multiple of 3 or 5} where Σ = {a}
	public int states=8;
	public int[][][]  transition= {	{{1}},{{2}},{{3}},{{4}},{{0}},{{6}},{{7}},{{5}} };
	public String alphabet = "a";
	public int start_state[] = {0,5};
	public int final_state[] = {0,5};


	//dfa representation THIS WILL BE RE WRITTEN WHEN WE CALL nfatodfa function
	// starting state will always be state-0
	// final state or not is represented using dfa_final
	// transition function represented using dfa_transition
	int dfa_states = 5;
	int[][] dfa_transition = {
	    {3,1}, {2,3}, {3,4}, {3,3}, {4,4}
	};
	String dfa_alphabet = "ab";
	int[] dfa_final = {0,0,0,0,1};

	public void print_dfa(){
		System.out.println("no of states : " + dfa_states);
		for(int i=0;i<dfa_states;i++){
			System.out.print("for state " + i + " : ");
			for(int j=0;j<dfa_alphabet.length();j++){
				System.out.print(dfa_transition[i][j] + " ");
			}
			System.out.println("");
		}
		System.out.print("Set of final states : ");
		for(int i=0;i<dfa_final.length;i++){
			if(dfa_final[i]==1)System.out.print(i + " ");
		}
		System.out.println("");
	}

	//helper functions for nfa to dfa conversion
	public String states_to_string(int curr_states[]){
		String s="";
		for(int i=0;i<states;i++){
			if(curr_states[i]==1)s+="1";
			else s+="0";
		}
		return s;
	}

	public int[] string_to_states(String str){
		int []arr = new int[states];
		for(int i=0;i<states;i++){
			if(str.charAt(i)=='0')arr[i]=0;
			else arr[i]=1;
		}
		return arr;
	}

	
	//nfa to dfa conversion function
	public void nfatodfa(){
		HashMap<String,Integer> map = new HashMap<>();
		int curr_states[] = new int[states];
		for(int i=0;i<start_state.length;i++){
			curr_states[start_state[i]] = 1;
		}
		String sts[] = new String[(int)Math.pow(2,states)];
		int discovered;
		int explored=0;
		sts[0]=states_to_string(curr_states);
		discovered=1;
		int[][] dfa_transition_function = new int[(int)Math.pow(2,states)][alphabet.length()];
		map.put(sts[0],0);
		while(explored < discovered){
			int[] present_states=string_to_states(sts[explored]);
			//System.out.println("---- for " +sts[explored]+ "----");

			for(int i=0;i<alphabet.length();i++){

				int next_states[] = new int[states];
				for(int z=0;z<states;z++){
					if(present_states[z]==1){
						for(int k=0;k<transition[z][i].length;k++){
							next_states[transition[z][i][k]]=1;
						}
					}
				}
				String x = states_to_string(next_states);
				//System.out.println(i + "--" + x);
				if(map.containsKey(x)){
					dfa_transition_function[explored][i]=map.get(x);
				}
				else {
					sts[discovered]=x;
					discovered++;
					map.put(x,discovered-1);
					dfa_transition_function[explored][i]=discovered-1;
				}
			}
			explored++;
		}
		//System.out.println(discovered + " " +explored);
		dfa_states = explored;
		dfa_alphabet = alphabet;
		dfa_transition = new int[explored][];
		for(int i=0;i<explored;i++){
			dfa_transition[i] = Arrays.copyOf(dfa_transition_function[i],dfa_transition_function[i].length);
		}
		dfa_final = new int[explored];
		for(int i=0;i<explored;i++){
			for(int j=0;j<final_state.length;j++){
				if(sts[i].charAt(final_state[j])=='1'){
					dfa_final[i]=1;break;
				}
			}
		}
		print_dfa();
	}

	public void main(String[] args){
		Scanner sc = new Scanner(System.in);
		nfatodfa();
	}
}