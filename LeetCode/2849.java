/*
2849. Determine if a Cell Is Reachable at a Given Time
Medium

You are given four integers sx, sy, fx, fy, and a non-negative integer t.

In an infinite 2D grid, you start at the cell (sx, sy). Each second, you must move to any of its adjacent cells.

Return true if you can reach cell (fx, fy) after exactly t seconds, or false otherwise.

A cell's adjacent cells are the 8 cells around it that share at least one corner with it. You can visit the same cell several times.

*/

class Solution {
    public boolean isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
        
        int dx = Math.abs(sx - fx);
        int dy = Math.abs(sy - fy);

        if(dy == 0 && dx == 0){
            return (t != 1);
        }

        return dx <= t && dy <= t;
    }



} // end of Solution class
