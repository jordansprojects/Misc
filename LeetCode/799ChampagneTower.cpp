class Solution {
public:
   /*
   @param poured: How many cups poured
   @param query_row: the row being asked about 
   @param query_glass: the glass being asked about (the column)
   */
    double champagneTower(int poured, const int query_row, const int query_glass) {
        vector<vector<double>> glasses(101, vector<double>(101, 0));
        glasses[0][0] = poured;
        for(int i = 0; i < query_row; i++){
            for(int j = 0 ; j <= i; j++){
                // subtract 1 because we are not counting the cup that is filling the champagne glass
               double pouredOver = max (0.0, glasses[i][j] - 1.0 ) / 2;  
               if (pouredOver > 0){
                   glasses[i + 1][j] += pouredOver;
                   glasses[i+1][j+1] +=pouredOver;
               }
            }
        }
    
       return min(1.0, glasses[query_row][query_glass]);
      
    }
      
    


};
