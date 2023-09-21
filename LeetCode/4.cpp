class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> merged;

        vector<int>::iterator it1 = nums1.begin();
        vector<int>::iterator it2 = nums2.begin();
        
        while(it1 != nums1.end() && it2 != nums2.end()){
          // find smaller value
          if (*it1 < *it2){
              merged.push_back(*it1);
              it1++;
          }else{
              merged.push_back(*it2);
              it2++;
          }
        }
        // finish pushing values from the longer vectors
        while(it1 != nums1.end()){
            merged.push_back(*it1);
            it1++;
        }
        while(it2 != nums2.end()){
            merged.push_back(*it2);
            it2++;
        }

        if(merged.size() % 2 != 0 ){ // odd number of items 
            return merged[merged.size()/2];
        }
        
        // even number of items 
        double middleItem1 = merged[merged.size()/2];
        double middleItem2 = merged[(merged.size()/2) - 1];
        return (middleItem1 + middleItem2)/2;
    }
   
};
