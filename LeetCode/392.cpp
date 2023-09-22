class Solution {
public:
    bool isSubsequence(string s, string t) {
        int i, j , matches;
        i = j = matches = 0;

        while(i < t.length() && j < s.length()){
            if (t[i] == s[j]){
                j++;
                matches++;
            }
            i++; 
        }
        return (matches == s.length());
    }
};
