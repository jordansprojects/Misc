class Solution {
public:
    
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        vector<pair<int,int>> rowsAndSoldiers;
        for(int i = 0 ; i < mat.size(); i++){
            int sum = 0;
            for(int j = 0 ; j < mat[i].size(); j++){
                sum+=mat[i][j];
            }
            // assign soldier sum to map corresponding to row index
            rowsAndSoldiers.push_back(make_pair(i,sum)); 
          
        }
          std::sort(rowsAndSoldiers.begin(), rowsAndSoldiers.end(), [](auto &left, auto &right) {
             if (left.second == right.second){
                 return (left.first < right.first);
             }
             return (left.second < right.second) ;});

        vector<int> v;
        for(int i = 0 ; i < k ; i++){
            v.push_back(rowsAndSoldiers[i].first);
        }
        return v;
        
    }/*  */
};
