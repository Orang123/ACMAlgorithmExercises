/*
�����д� 1 �� n �� n ������������Щ��������һ������ perm���±�� 1 ��ʼ����
ֻҪ������������ ֮һ �����������һ�� ���������� ��
perm[i] �ܹ��� i ����
i �ܹ��� perm[i] ����
����һ������ n �����ؿ��Թ���� �������� �� ���� ��
���ӣ�https://leetcode-cn.com/problems/beautiful-arrangement
*/
//״ѹdp ���Ӷ�O(1<<n -1) ǰ������в�ͬ,������ϵ�״̬��ͬ,����δѡȡ���� �����ص������� ���������ӽṹ,���״ѹdp
class Solution {
public:
    int a[16],dp[32768],ans;
    int dfs(int n,int k,int sta){
        if(sta == (1<<n)-1)
            return dp[sta]=1;
        if(dp[sta])
            return dp[sta];
        for(int i=1;i<=n;i++){
            if(sta & (1<<(i-1)))
                continue;
            a[k]=i;
            if(a[k]%k == 0 || k%a[k] == 0)
                dp[sta]+=dfs(n,k+1,sta|1<<(i-1));
        }
        return dp[sta];
    }
    int countArrangement(int n) {
        return dfs(n,1,0);
    }
};

//ö��ȫ����+��֦ ���Ӷ�O(n!)
// class Solution {
// public:
//     int a[16],ans;
//     void dfs(int n,int k,int sta){
//         if(k == n+1){
//             ans++;
//             return;
//         }
//         for(int i=1;i<=n;i++){
//             if(sta & (1<<i))
//                 continue;
//             a[k]=i;
//             if(a[k]%k == 0 || k%a[k] == 0)
//                 dfs(n,k+1,sta|1<<i);
//         }
//     }
//     int countArrangement(int n) {
//         dfs(n,1,0);
//         return ans;
//     }
// };
