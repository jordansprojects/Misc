class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i, j;
        i = j = 0;

        while(i < t.length() && j < s.length()){
            if (t[i] == s[j]){
                j++;
            }
            i++; 
        }
        return ( j == s.length() );
    }
};
