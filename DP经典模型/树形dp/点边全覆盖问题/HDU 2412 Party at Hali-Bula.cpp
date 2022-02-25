#include<cstdio>
#include<algorithm>
#include<vector>
#include<map>
#include<cstring>
#include<string>
using namespace std;
/*
题意:一些员工参加派对,但是员工不能和他的老板碰面,问最多可以多少人参加,并输出方案是否唯一。
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2412
思路:
dp[root][0]代表root结点不来 only[root][0]root结点不来的方案是否唯一 1代表唯一,0代表不唯一
dp[root][1]代表root结点来 only[root][1]root结点来的方案是否唯一
*/

vector <int> tree[205];
map<string,int> mp;
int dp[205][2],only[205][2];
void dfs(int root){
    int son;
    for(int i=0;i<tree[root].size();i++){
        son=tree[root][i];
        dfs(son);
        //员工来老板一定不能来,员工不来,老板可来可不来.
        dp[root][0]+=max(dp[son][0],dp[son][1]);
        dp[root][1]+=dp[son][0];//老板来,员工一定不来.
        /*按上述转移分开讨论only[root][0] only[root][1]
        若员工来比员工不来人数多,且员工来的方案不唯一;
        若员工不来比员工来人数多,且员工不来的方案不唯一;
        或者员工来和不来人数一样,则说明老板不来的方案不唯一;
        由员工的不唯一性去推导老板的不唯一性.最先开始一定是员工来和不来相等导致的老板不来的不唯一性.
        */
        if((dp[son][1]>dp[son][0]&&!only[son][1])||(dp[son][1]<dp[son][0]&&!only[son][0])||(dp[son][0]==dp[son][1]))
            only[root][0]=0;
        //员工不来的方案不唯一,则老板来的方案也不唯一.因为老板若来,员工一定不能来.
        if(!only[son][0])
            only[root][1]=0;
    }
}
int main(){
    int n,index;
    char str1[10],str2[10];
    while(scanf("%d",&n)&&n){
        index=1;
        for(int i=1;i<=n;i++)//用循环初始化
            for(int j=0;j<2;j++)
                only[i][0]=only[i][1]=1;
        for(int i=0;i<205;i++)
            tree[i].clear();
        mp.clear();
        scanf("%s",str1);
        mp[str1]=index++;//最大大老板 是节点1
        for(int i=1;i<n;i++){
            scanf("%s%s",str1,str2);//str2 是str1的老板
            if(!mp[str2]) mp[str2]=index++;//用map将string对应转化为int的节点编号
            if(!mp[str1]) mp[str1]=index++;
            tree[mp[str2]].push_back(mp[str1]);//构建多叉树
        }
        for(int i=1;i<index;i++){
            dp[i][0]=0;
            dp[i][1]=1;
        }
        dfs(1);
        if(dp[1][1]>dp[1][0]&&only[1][1]==1)
            printf("%d Yes\n",dp[1][1]);
        else if(dp[1][1]<dp[1][0]&&only[1][0]==1)
            printf("%d Yes\n",dp[1][0]);
        else{
            printf("%d No\n",max(dp[1][0],dp[1][1]));
        }
    }
    return 0;
}
