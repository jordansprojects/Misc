/*
You are given a 0-indexed integer array nums. You have to find the maximum sum of a pair of numbers from nums such that the maximum digit in both numbers are equal.

Return the maximum sum or -1 if no such pair exists.

 

Example 1:

Input: nums = [51,71,17,24,42]
Output: 88
Explanation: 
For i = 1 and j = 2, nums[i] and nums[j] have equal maximum digits with a pair sum of 71 + 17 = 88. 
For i = 3 and j = 4, nums[i] and nums[j] have equal maximum digits with a pair sum of 24 + 42 = 66.
It can be shown that there are no other pairs with equal maximum digits, so the answer is 88.

Example 2:

Input: nums = [1,2,3,4]
Output: -1
Explanation: No pair exists in nums with equal maximum digits.

 

Constraints:

    2 <= nums.length <= 100
    1 <= nums[i] <= 104

*/

#include <iostream>
class Solution {

public:

    int maxSum(vector<int>& nums) {
        int maxDigits[nums.size()];
        /* init maxDigits to -1 */ 
        memset(maxDigits, -1, sizeof(maxDigits));
        int maxSum = 0;
        bool foundPair = false;
        for (int i = 0; i < nums.size(); i++){
            maxDigits[i] = findMaxDigit(nums[i]);

            for (int j = i+1; j < nums.size(); j++  ){
                if (maxDigits[j] == -1 ){ /* if max digit for number in list hasnt been indicated yet */
                    maxDigits[j] = findMaxDigit(nums[j]);
                }
                if (maxDigits[i] == maxDigits[j]){
                    foundPair = true;
                    if ( (nums[i] + nums[j]) > maxSum ){
                        maxSum = nums[i] + nums[j];
                    }
                }
            }


        }
        if ( foundPair == false){
            maxSum = -1;
        }
       return maxSum;
    }

    int findMaxDigit(int num){
        int maxDigit = INT_MIN;
        while(num > 0){
            maxDigit = max(maxDigit, num % 10);
            num /= 10;
        }
        return maxDigit;
    }

};
