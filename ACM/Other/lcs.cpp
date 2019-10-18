    #include <bits/stdc++.h>
    using namespace std;
     
    string A,B;
    int mistakesPossible;
    int X[100005];
    int Y[100005];
     
     
    int lcs(int m, int n, int mistakes)
    {
        if(mistakes > mistakesPossible){
            return 0;
        }
        if (m == 0 || n == 0)
            return 0;
        if (A[m-1] == B[n-1])
            return 1 + lcs(m-1, n-1, mistakes);
        else
            return max(lcs(m, n-1,mistakes+1), lcs(m-1, n,mistakes+1));
    }
     
    // better memory
    int lcs_length(int m, int n)
    {
        for (int i = m; i >= 0; i--)
        {
            int tmp1 = min(n,i+mistakesPossible);
            int tmp2 = max(0,i-mistakesPossible-1);
            for (int j = tmp1; j >= tmp2; j--)
            {
                if (i == m || j == n) X[j] = 0;
                else if (A[i] == B[j]) X[j] = 1 + Y[j+1];
                else X[j] = max(Y[j], X[j+1]);
            }
            for(int k=tmp1;k>=tmp2;k--) //assume m=n
            {
                Y[k] = X[k];
            }
        }
        return X[0];
    }
    
    
    int lcs_length(char * A, char * B)
    {
	allocate storage for one-dimensional arrays X and Y
	for (i = m; i >= 0; i--)
	{
	    for (j = n; j >= 0; j--)
	    {
		if (A[i] == '\0' || B[j] == '\0') X[j] = 0;
		else if (A[i] == B[j]) X[j] = 1 + Y[j+1];
		else X[j] = max(Y[j], X[j+1]);
	    }
	    Y = X;
	}
	return X[0];
    }
     
    int main()
    {
        cin>>A>>B;
     
        int m = A.length();
        mistakesPossible = m/100;
        int res = lcs_length( m, m);
        if(res >= m-mistakesPossible){
            cout << "Long lost brothers D:" << endl;
        }
        else{
            cout << "Not brothers :(" << endl;
        }
        return 0;
    }
