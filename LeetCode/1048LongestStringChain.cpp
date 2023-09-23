class Solution {
public:
    int longestStrChain(vector<string>& words) {
        vector<vector<string>> chains;
        // sort based on length of the string
        sort(words.begin(), words.end(), [](auto &left, auto &right){
            return (left.length() < right.length());
        }); 

        // print sorted words
        for(int i = 0 ; i < words.size(); i++){
            cout << words[i] << " ";
        }
        cout << "end of sorted words \n";

        unordered_map<string,int> chainMap;
        int max = 0;
        for( auto word: words){
            chainMap[word] = 1; // assume a chain length of 1 
            for(int i = 0; i < word.size() ;i++){ //iterate over every char in the word 
                string prev = word.substr(0,i) + word.substr(i + 1); // generate a potential predecessor
                if (chainMap.find(prev) != chainMap.end()){// search for predecrssor in the map
                    chainMap[word] = (chainMap[word] < (chainMap[prev] + 1 ))? (chainMap[prev] + 1) : chainMap[word];
                } 
            }
            max = (max < chainMap[word]) ? chainMap[word] : max;
        }
        return max;
    }

};
