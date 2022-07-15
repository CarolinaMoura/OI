#include <stdlib.h>
#include <string.h>
#include <bits/stdc++.h>
#include "floppy.h"
 
const int LOG=20;
 
using namespace std;
 
void read_array(int subtask_id, const vector<int> &v) {
    string ans;
    stack<int> st;
 
    for(int i = 0; i < v.size();i++){
        while(!st.empty() && st.top() < v[i]){
            st.pop();
            ans.push_back('1');
        }
 
        if(!st.empty())
            ans.push_back('0');
 
        st.push(v[i]);
    }
 
    save_to_floppy(ans);
}
 
vector<int> solve_queries(int subtask_id, int N,
        const string &bits,
        const vector<int> &a, const vector<int> &b) {
 
    vector<int> retDummy(a.size(), 0);
 
 
    vector< vector<int> >dp(LOG, vector<int>(N,-1));
    stack<int> st;
    int ptr = 0;
    st.push(0);
 
    for(int i = 1; i < N; i++){
        while(!st.empty() && bits[ptr] == '1'){
            ptr++;
            st.pop();
        }
 
        if(!st.empty()){
            dp[0][i] = st.top();
            ptr++;
        }
 
        st.push(i);
    }
 
    for(int i= 1; i < LOG; i++)
        for(int j= 0; j < N; j++)
            if(dp[i-1][j] != -1)
                dp[i][j] = dp[i-1][dp[i-1][j]];
 
    vector<int> ret;
 
    for(int i = 0; i < a.size(); i++){
        int l = a[i];
        int r = b[i];
 
        for(int j = LOG-1; j >= 0; j--){
            if(dp[j][r] >= l)
                r = dp[j][r];
        }
 
        ret.push_back(r);
    }
 
    return ret;
}
