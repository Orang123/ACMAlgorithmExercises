/*
题意:摘自网上
一个有n个节点的无向图，要求对每个节点进行染色，
使得相邻两个节点颜色都不同，问最少需要多少种颜色？
n<=26.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1373
思路:贪心,初始设置颜色数目为1,只有当当前节点染色时,所有
颜色都不能满足和相邻节点颜色不同时,增加一种颜色,直到将
所有节点染色完成,当前颜色的数目就是最少的.
实际这个做法 直接2层循环也能做,并不需要dfs回溯.
因为dfs(cur+1,num) 实际并不会回溯
*/
//ac 0ms dfs暴力枚举
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 30
using namespace std;

int n,mp[N][N],col[N],flag,ans;
char str[N];

int check(int cur,int x){
    for(int i=0;i<n;i++){//这里实际应该是i<cur,因为i>cur的部分还未染色
        if(mp[cur][i] && col[i] == x)
            return 0;
    }
    return 1;
}

void dfs(int cur,int num){
    if(cur == n){
        flag=1;
        return;
    }
    //较前驱的节点的num是较少的,基本就是i == num的时候,只有在 现有颜色冲突的时候 才会增加一种颜色
    for(int i=1;i<=num;i++){
        if(check(cur,i)){//判断相邻节点是否有 染i颜色的,若没有则可以染
            col[cur]=i;
            dfs(cur+1,num);//实际这里不会有回溯(回溯也没有用,因为前驱节点也没有别的颜色可选),只有没有颜色满足相邻不同色时,进入下面的增加一种颜色dfs(cur,ans)
            if(flag) return;//染色成功后直接 返回
        }
    }
    //这里是当前num种颜色都不能满足cur和cur相邻节点颜色不同时,再增加一种颜色.
    //实际这里并不是回溯回来的,而是上面的dfs(cur+1,num) 没有满足条件时才会增加颜色数目dfs(cur,ans)
    ans++;
    dfs(cur,ans);
}

int main(){
    int u,v,len;
    while(scanf("%d",&n) && n){
        memset(mp,0,sizeof(mp));
        memset(col,0,sizeof(col));
        for(int i=1;i<=n;i++){
            scanf("%s",str);
            u=str[0]-'A';
            len=strlen(str);
            for(int j=2;j<len;j++){
                v=str[j]-'A';
                mp[u][v]=1;
            }
        }
        flag=0;
        ans=1;//至少需要一种颜色.
        dfs(0,1);
        if(ans == 1)
            printf("1 channel needed.\n");
        else
            printf("%d channels needed.\n",ans);
    }
    return 0;
}

/*
//ac 0ms 非递归,2层循环 贪心+暴力枚举.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 30
using namespace std;

int n,mp[N][N],col[N],flag,ans;
char str[N];

int check(int cur,int x){
    for(int i=0;i<n;i++){
        if(mp[cur][i] && col[i] == x)
            return 0;
    }
    return 1;
}

int main(){
    int u,v,len;
    while(scanf("%d",&n) && n){
        memset(mp,0,sizeof(mp));
        memset(col,0,sizeof(col));
        for(int i=1;i<=n;i++){
            scanf("%s",str);
            u=str[0]-'A';
            len=strlen(str);
            for(int j=2;j<len;j++){
                v=str[j]-'A';
                mp[u][v]=1;
            }
        }
        ans=1;//至少需要一种颜色.
        for(int i=0;i<n;i++){
        	flag=0;
        	for(int j=1;j<=ans;j++){
        		if(check(i,j)){
        			col[i]=j;
        			flag=1;
        			break;
				}
			}
			if(!flag){//没有一种颜色满足相邻节点 颜色不同,增加一种颜色,重新判断该点i 染色情况
				i--;
				ans++;
			}
		}
        if(ans == 1)
            printf("1 channel needed.\n");
        else
            printf("%d channels needed.\n",ans);
    }
    return 0;
}
*/

/*
//四色定理
//摘自博客:https://blog.csdn.net/lyy289065406/article/details/6647986
//Memory Time
//184K   0MS

#include<iostream>
using namespace std;

typedef class
{
	public:
		int next[27];  //直接后继
		int pn;   //next[]指针（后继个数）
}point;

int main(int i,int j,int k)
{
	int n;
	while(cin>>n)
	{
		if(!n)
			break;

		getchar();  //n的换行符

		point* node=new point[n+1];  //结点


		for(i=1;i<=n;i++)
		{
			getchar();  //结点序号
			getchar();  //冒号

			if(node[i].pn<0)   //初始化指针
				node[i].pn=0;

			char ch;
			while((ch=getchar())!='\n')
			{
				j=ch%('A'-1);   //把结点字母转换为相应的数字，如A->1  C->3
				node[i].next[ ++node[i].pn ]=j;
			}
		}

		int color[27]={0};  //color[i]为第i个结点当前染的颜色，0为无色（无染色）
		color[1]=1;  //结点A初始化染第1种色
		int maxcolor=1;  //当前已使用不同颜色的种数

		for(i=1;i<=n;i++)  //枚举每个顶点
		{
			color[i]=n+1;  //先假设结点i染最大的颜色
			bool vist[27]={false};  //标记第i种颜色是否在当前结点的相邻结点染过
			for(j=1;j<=node[i].pn;j++) //枚举顶点i的所有后继
			{
				int k=node[i].next[j];
				if(color[k])  //顶点i的第j个直接后继已染色
					vist[ color[k] ]=true;  //标记该种颜色
			}
			for(j=1;i<=n;j++)  //从最小的颜色开始，枚举每种颜色
				if(!vist[j] && color[i]>j) //注意染色的过程是一个不断调整的过程，可能会暂时出现大于4的颜色
				{                          //因此不能单纯枚举4种色，不然会WA
					color[i]=j;
					break;
				}

			if(maxcolor<color[i])
			{
				maxcolor=color[i];
				if(maxcolor==4)   //由四色定理知，最终完成染色后，图上最多只有四种颜色
					break;        //因此当染色过程出现结点的颜色为4时，就可以断定最少要用4种颜色染色
			}
		}

		if(maxcolor==1)
			cout<<1<<" channel needed."<<endl;
		else
			cout<<maxcolor<<" channels needed."<<endl;

		delete node;
	}
	return 0;
}
*/
