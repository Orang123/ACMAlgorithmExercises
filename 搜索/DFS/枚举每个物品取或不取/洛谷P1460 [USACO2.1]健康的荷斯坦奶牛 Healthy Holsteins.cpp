/*
题意:农民 John 以拥有世界上最健康的奶牛为傲。他知道每种饲料中所包含的牛
所需的最低的维他命量是多少。请你帮助农夫喂养他的牛，以保持它们的健康，
使喂给牛的饲料的种数最少。给出牛所需的最低的维他命量，输出喂给牛需要哪些
种类的饲料，且所需的饲料剂量最少。维他命量以整数表示，每种饲料最多只能对
牛使用一次，数据保证存在解。
维他命种类<=25,饲料种类<=15.
说明:实际答案并没有要求在个数相同时 剂量最少.
链接:https://www.luogu.com.cn/problem/P1460
思路:
解法1:dfs
dfs,只不过是将饲料的提供的维他命分开看成一个整体,判断的条件是所有维他命
的种类是否达标.

解法2:bfs.
状态可以用二进制位运算表示已经选取的饲料,每次扩展只选取一个还未选取的饲料(按照字典序),
然后结束的条件是当前所有维他命的指标已经达标,第一个达标的就是数量最小,字典序最小的方案.
bfs更耗费空间.
*/
//ac dfs
#include<cstdio>
#include<algorithm>
using namespace std;
int a[20][30],b[30],c[20],ans[20];
int v,g,cnt,num=100;
/*
这里只是对于每种饲料 选取或不选取(和选取的顺序无关,之和组合具体的种类有关,因此无需再考虑前面取消的标记),
不需要用vis做标记,顺着u+1的顺序 回溯时 本身就能覆盖所有情况,除非是全排列那种 不选取某个位置后,
选取某数的顺序也对结果有影响时,深度遍历也需要考虑前面取消的标记数.
*/
void dfs(int u,int k){
    int flag=0;
    for(int i=1;i<=v;i++){
        if(b[i]>a[0][i]){
            flag=1;
            break;
        }
    }
    if(!flag){
        if(k-1<num){
            num=k-1;
            //只有当有更少种类的饲料满足情况时才更新答案,dfs本身就是按照字典序去统计结果的,在饲料个数相同情况下,后面遍历出来的结果 字典序较小
            for(int i=1;i<=num;i++)
                ans[i]=c[i];
        }
        return;
    }
    if(u == g+1) return;
    for(int j=1;j<=v;j++)
        a[0][j]+=a[u][j];
    c[k]=u;
    dfs(u+1,k+1);
    for(int j=1;j<=v;j++)
        a[0][j]-=a[u][j];
    dfs(u+1,k);//之所以需要不选u这个 往后遍历,是因为有可能字典序较大 但是选取的饲料种类较少.
}

int main(){
    scanf("%d",&v);
    for(int i=1;i<=v;i++)
        scanf("%d",&b[i]);
    scanf("%d",&g);
    for(int i=1;i<=g;i++)
        for(int j=1;j<=v;j++)
            scanf("%d",&a[i][j]);
    dfs(1,1);
    printf("%d",num);
    for(int i=1;i<=num;i++)
        printf(" %d",ans[i]);
    printf("\n");
    return 0;
}

/*
//ac 二进制枚举选取状态
//摘自洛谷网友
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int v,need[30],g,a[20][30],ans,minn=0x7fffffff,t[30];

int count(int x);

int main()
{
    int i,j,k;
    bool flag;

    cin>>v;

    for (i=0;i<v;++i)
    {
        cin>>need[i];
    }

    cin>>g;

    for (i=1;i<=g;++i)
    {
        for (j=0;j<v;++j)
        {
            cin>>a[i][j];
        }
    }

    for (i=(1<<g)-1;i>=0;--i) //二进制枚举子集
    {
        if (count(i)<minn) //若当前子集的饲料数大于等于当前的最优解则当前子集一定不是答案
        {
            memset(t,0,sizeof(t));
            for (j=0;j<g;++j)
            {
                if ((1<<j)&i) //i的右数第j+1位为1代表饲料g-j在当前枚举的子集中
                {
                    for (k=0;k<v;++k)
                    {
                        t[k]+=a[g-j][k];
                    }
                }
            }
            flag=true;
            for (j=0;j<v;++j) //判断当前方案是否合法
            {
                if (t[j]<need[j])
                {
                    flag=false;
                    break;
                }
            }
            if (flag) //因为已经判断过当前子集饲料数小于当前最优解，若当前方案合法则直接更新最优解
            {
                minn=count(i);
                ans=i;
            }
        }
    }

    cout<<minn;

    for (i=g-1;i>=0;--i) //输出方案
    {
        if ((1<<i)&ans)
        {
            cout<<" "<<g-i;
        }
    }

    return 0;
}

int count(int x) //数1的个数
{
    int out=0;
    while (x)
    {
        out+=x&1;
        x>>=1;
    }
    return out;
}
*/

/*
//ac BFS版本
//洛谷网友摘来的一个版本
#include<iostream>
#include<queue>
using namespace std;
int a[30][30],b[30];
int n,m;
struct node{
	int wss[30];
	int num[30];
	int ans;
}q;
void bfs()
{
	queue<node>que;
	q=que.front();
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
			q.wss[j]=a[i][j];//第一个选入的种类 按照1到m一次枚举入队
		q.num[1]=i;//num是接下来要选的饲料从哪个下标开始
		q.ans=1;//ans是选择饲料的次序
		que.push(q);
	}
	while(!que.empty())
	{
		node s,t;
		s=que.front();
		t=que.front();
		que.pop();
		bool w=1;
		for(int i=1;i<=n;i++)
		{
			if(s.wss[i]<b[i])
			{
				w=0;
				break;
			}
		}
		if(w==1)
		{
			cout<<s.ans<<' ';
			for(int i=1;i<=s.ans;i++)cout<<s.num[i]<<" ";
			return;
		}
//从s.num[s.ans]+1开始枚举长度为s.ans+1饲料种类组合(第s.ans+1个饲料是num+1到m之间的任何一个,分别入队),
//这样就保证了队列出队的顺序 是按照种类最少 并且按照字典序排序的,那么第一次满足情况的就是所要求的的解 可直接退出
		for(int i=s.num[s.ans]+1;i<=m;i++)
		{
			for(int j=1;j<=n;j++)
				t.wss[j]=s.wss[j]+a[i][j];
			t.ans=s.ans+1;
			t.num[t.ans]=i;
			que.push(t);
		}
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>b[i];
	cin>>m;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	bfs();
	return 0;
}
*/
