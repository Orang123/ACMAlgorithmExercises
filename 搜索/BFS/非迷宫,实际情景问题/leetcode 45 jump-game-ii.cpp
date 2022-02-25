/*
题意:给你一个非负整数数组 nums ，你最初位于数组的第一个位置。
数组中的每个元素代表你在该位置可以跳跃的最大长度。
你的目标是使用最少的跳跃次数到达数组的最后一个位置。
假设你总是可以到达数组的最后一个位置。
1 <= nums.length <= 104
0 <= nums[i] <= 1000
链接:https://leetcode-cn.com/problems/jump-game-ii/
思路:bfs枚举扩展状态,vis标记去重
*/
//时间复杂度O(nums.length)
#define N 10010
class Solution {
public:
    struct State{
        int pos,step;
        State(int pos=0,int step=0):pos(pos),step(step){}
    };
    int vis[N];
    int bfs(vector<int>& nums){
        if(nums.size() <= 1)
            return 0;
        queue<State> Q;
        vis[0]=1;
        Q.push(State(0,0));
        int u,v;
        State tp;
        while(!Q.empty()){
            tp=Q.front();
            Q.pop();
            for(int i=1;i<=nums[tp.pos];i++){
                if(tp.pos+i>=nums.size()-1)
                    return tp.step+1;
                if(!vis[tp.pos+i]){
                    vis[tp.pos+i]=1;
                    Q.push(State(tp.pos+i,tp.step+1));
                }
            }
        }
        return -1;
    }

    int jump(vector<int>& nums) {
        return bfs(nums);
    }
};
