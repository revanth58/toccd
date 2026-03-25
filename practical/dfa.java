import java.util.Scanner;

class n{

	//dfa representation for L = { x | x starts with 'bab'}
	// starting state will always be state-0
	// final state or not is represented using dfa_final
	// transition function represented using dfa_transition
	int dfa_states = 5;
	int[][] dfa_transition = {
	    {3,1}, {2,3}, {3,4}, {3,3}, {4,4}
	};
	String dfa_alphabet = "ab";
	int[] dfa_final = {0,0,0,0,1};

	//DFA simulation
	// input : x string
	// output : 1/0 whether x belongs to L
	public int DFA(String str){
	    int curr_state = 0;

	    for(int i = 0; i < str.length(); i++){
	        int j;
	        for(j = 0; j < dfa_alphabet.length(); j++){
	            if(dfa_alphabet.charAt(j) == str.charAt(i)) break;
	        }
	        curr_state = dfa_transition[curr_state][j];
	    }
	    return dfa_final[curr_state];
	}

	public void main(String[] args){
		Scanner sc = new Scanner(System.in);
		// repeatedly asks user for a string
		// calls DFA(x)
		// terminates when user types 'exit'
		while(true){
			System.out.print("enter string : ");
			String str = sc.nextLine();
			if(str.equals("exit"))break;
			System.out.println(DFA(str));
		}
	}
}