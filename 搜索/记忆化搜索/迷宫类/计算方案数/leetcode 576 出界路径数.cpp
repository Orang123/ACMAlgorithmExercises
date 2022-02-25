/*
����һ����СΪ m x n �������һ���������ʼ����Ϊ [startRow, startColumn] ��
����Խ����Ƶ����ĸ����������ڵĵ�Ԫ���ڣ����Դ�������߽絽������֮�⣩��
�� ��� �����ƶ� maxMove ���򡣸���������� m��n��maxMove��startRow �Լ� startColumn ��
�ҳ������ؿ��Խ����Ƴ��߽��·����������Ϊ�𰸿��ܷǳ��󣬷��ض� 109 + 7 ȡ�� ��Ľ����
���ӣ�https://leetcode-cn.com/problems/out-of-boundary-paths
*/
class Solution {
public:
    int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
    //������ͬ��ʱ ������ͬ,����Ҫ��һά���������� ��ά
    int dp[55][55][55];//dp[x][y][s]��ʾ����(x,y)��ʱk�� ���ߵ��߽���ķ�����
    int dfs(int m,int n,int maxMove,int s,int x,int y){
        if(x<0 || x>=m || y<0 || y>=n)
            return 1;
        int &ans=dp[x][y][s];
        if(ans!=-1)
            return ans;
        ans=0;
        int nx,ny;
        for(int i=0;i<4;i++){
            nx=x+dir[i][0];
            ny=y+dir[i][1];
            if(s<maxMove)
                ans=(ans+dfs(m,n,maxMove,s+1,nx,ny))%1000000007;
        }
        return ans;
    }
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        memset(dp,-1,sizeof(dp));//��ʼ״̬Ҫ����Ϊ-1,��Ϊ0Ҳ�� �Ϸ�����
        return dfs(m,n,maxMove,0,startRow,startColumn);
    }
};
