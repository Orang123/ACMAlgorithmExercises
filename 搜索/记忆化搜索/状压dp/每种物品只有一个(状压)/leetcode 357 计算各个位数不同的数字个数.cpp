/*
����һ���Ǹ����� n�������λ���ֶ���ͬ������ x �ĸ��������� 0 �� x < 10^n ��
����:https://leetcode-cn.com/problems/count-numbers-with-unique-digits/
*/
//���仯���� ״ѹdp
class Solution {
public:
    int dp[1<<20];
    int dfs(int k,int sta,int len){
        if(k == len)
            return dp[sta]=1;
        if(dp[sta])
            return dp[sta];
        for(int i=0;i<=9;i++){
            if(!k && !i)
                continue;
            if(sta & (1<<i))
                continue;
            dp[sta]+=dfs(k+1,sta | 1<<i,len);
        }
        return dp[sta];
    }
    int countNumbersWithUniqueDigits(int n) {
        int ans=1;
        for(int i=1;i<=n;i++){
            memset(dp,0,sizeof(dp));
            ans+=dfs(0,0,i);
        }
        return ans;
    }
};

//�˷�ԭ��
// class Solution {
// public:
//     int countNumbersWithUniqueDigits(int n) {
//         int ans=1,res=9;//n=0ʱ ans=1 x=0
//         for(int i=1;i<=n;i++){
//             ans+=res;
//             res*=(10-i);
//         }
//         return ans;
//     }
// };
//dfs+״ѹ
// class Solution {
// public:
//     int ans=1;
//     void dfs(int k,int sta,int len){
//         if(k == len){
//             ans++;
//             return;
//         }
//         for(int i=0;i<=9;i++){
//             if(!k && !i)
//                 continue;
//             if(sta & (1<<i))
//                 continue;
//             dfs(k+1,sta | 1<<i,len);
//         }
//     }
//     int countNumbersWithUniqueDigits(int n) {
//         for(int i=1;i<=n;i++)
//             dfs(0,0,i);
//         return ans;
//     }
// };
