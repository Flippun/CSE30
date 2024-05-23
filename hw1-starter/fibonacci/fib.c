// Returns the nth term in the fibonacci sequence.
// The sequence should be 0-indexed, i.e. F(0) = 0, F(1) = 1, F(2) = 1, ...
//
// `n`: index of term to return

int get_nth_fib(int n) {
    
    int prev0 = 0;
    int prev1 = 1;
    int fibNum = 0;

	if (n == 0) {
		return prev0;
	}
        
	if (n == 1) {
		return prev1;
	}
   	
	for (int i = 2; i <= n; i++) {  
        fibNum = prev0 + prev1; 
        prev0 = prev1; 
        prev1 = fibNum; 
	}
    
    return fibNum;
}
