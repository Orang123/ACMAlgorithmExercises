#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 70
#define M 33000
using namespace std;
//ac 44ms 实际还是按照主件分组的每组至多选取一件物品的分组背包
//每组物品为 主件+该组可能附件组合
//复杂度O(nv) 01背包
/*
题意:n个物品,分为两类,分别是主件和附件,每件物品
有对应的价格v,重要程度p,以及它对应的主件编号q,当
q为0时代表该物品是主件,否则该物品是主件q的附件.想要
买附件就必须先购买该附件所对应的主件,否则无法购买该
附件,每个主件可以有0、1、2个附件,重要度分为1~5.现在
有m元钱,问买n个物品所能获得的价格和重要程度乘积的最
大总和是多少.
注意:主件之间并没有之间的主附关系,主件只能是主件.
链接:https://www.luogu.com.cn/problem/P1064
思路:因为每个主件最多也只有2个附件,因此对于所有的物品
可以从所有的主件开始枚举购买,有5种可能性的方案:
假设该主件有2个附件
1.买该主件
2.不买该主件
3.买该主件以及第1个附件
4.买该主件以及第2个附件
5.买该主件以及其所有的2个附件
如果主件没有附件则只有情况1、2,如果该主件只有1个附件则只有
情况1、2、3.
那么显然可以用01背包模拟这个过程,物品体积为价格,物品价值为
价值与重要度的乘积,代码如下:
扩展:如果每个主件有多个附件,可以直接先放附件再放主件,只是不放主件后,前一状态是
之前所有主件附件的最优解,不包括这组所有的附件.可参考HDU 3449那题.或者直接建成一棵
树,直接用dfs后序遍历再dfs过程中进行01背包.

实际这个做法还是按照主件分组的每组至多选取一件物品的分组背包
每组物品为 主件+该组可能附件组合
*/
int n,m,dp[M];
//mc代表主件
struct Goods{
    int w,val;
    Goods(int w=0,int val=0):w(w),val(val){}
}mc[N];
//ax[i]代表主件i对应的所有附件
struct AX{
    int num;//主件i所对应的附件数量
    Goods gds[3];//一个主件最多有2个附件
}ax[N];

int main(){
    int v,p,q;
    memset(dp,0,sizeof(dp));//尽可能多地装满背包
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&v,&p,&q);
        if(!q)//0 代表该物品是主件
            mc[i]=Goods(v,v*p);
        else{//否则代表该物品是主件q的附件
            ax[q].num++;//主件q的附件数+1
            ax[q].gds[ax[q].num]=Goods(v,v*p);//存放其对应附件的价格和价值
        }
    }
    for(int i=1;i<=n;i++){//n个物品
        //这里只考虑主件,mc[i].w不为0代表第i个物品为主件
        for(int j=m;mc[i].w && j>=mc[i].w;j--){
            //实际就是在第i个主件下的分组情况,主件+1/2个附件的组合 共4种选取情况
            //情况1 2 主件的选取与否 只有主件
            dp[j]=max(dp[j],dp[j-mc[i].w]+mc[i].val);
            //该主件有附件
            if(ax[i].num){//主件+附件
                //情况3 主件和附件1的选取与否
                if(j>=mc[i].w+ax[i].gds[1].w)
                    dp[j]=max(dp[j],dp[j-mc[i].w-ax[i].gds[1].w]+mc[i].val+ax[i].gds[1].val);
                //若该主件的附件数有2个
                if(ax[i].num == 2){
                    //情况4 主件和附件2的选取与否
                    if(j>=mc[i].w+ax[i].gds[2].w)
                        dp[j]=max(dp[j],dp[j-mc[i].w-ax[i].gds[2].w]+mc[i].val+ax[i].gds[2].val);
                    //情况5 主件和附件1以及附件2的选取与否
                    if(j>=mc[i].w+ax[i].gds[1].w+ax[i].gds[2].w)
                        dp[j]=max(dp[j],dp[j-mc[i].w-ax[i].gds[1].w-ax[i].gds[2].w]+mc[i].val+ax[i].gds[1].val+ax[i].gds[2].val);
                }
            }
        }
    }
    printf("%d",dp[m]);
    return 0;
}

/*
//ac 105ms 分组背包每组至多取一件物品简化版本
//以主件分组,每组的物品为主件+(各个可能的附件组合)
//实际可能情况:
//第一个物品的价格和实际权重等于主件；
//第二个物品的价格和实际权重等于第一个物品+第一个附件；
//第三个物品的价格和实际权重等于第一个物品+第二个附件；
//第四个物品的价格和实际权重等于第二个物品+第二个附件；
//可以用一个for循环进行递推计算，每次加入新附件时在遍历已有
//该附件对应主件和该主件其它附件的同时进行累加，将累加后的结果push_back到末端即可
//复杂度O(k*v*num[k])=60*32000=1.92*10^6
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 70
#define M 33000
using namespace std;

int n,m,dp[M];
struct Goods{
    int w,val;
    Goods(int w=0,int val=0):w(w),val(val){}
};
vector<Goods> gds[N];

int main(){
    int v,p,q,len;
    memset(dp,0,sizeof(dp));//尽可能多地装满背包
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&v,&p,&q);
        if(!q)//主件作为一组
            gds[i].push_back(Goods(v,v*p));
        else{
            len=gds[q].size();
            //将主件与各个附件的组合作为该组内独立的物品
            for(int j=0;j<len;j++)
                gds[q].push_back(Goods(v+gds[q][j].w,v*p+gds[q][j].val));
        }
    }
    for(int i=1;i<=n;i++){
        if(!gds[i].size()) continue;//第i个物品不是主件
        for(int j=m;j>=0;j--){
            for(Goods &k : gds[i]){
                if(j>=k.w)
                    dp[j]=max(dp[j],dp[j-k.w]+k.val);
            }
        }
    }
    printf("%d",dp[m]);
    return 0;
}
*/

/*
//ac 83ms 分组背包当前组至少取一件物品与当前组一件物品也不选 比较求取较优值
//以主件分组,每组的物品为主件、附件1、附件2
//采用滚动数组优化 2个数组一个数组只记录前i-1组状态tp,另一个数组记录前i组状态dp
//先考虑购买主件,再考虑在主件已购买的状态下 对剩下的附件购买进行01背包
//复杂度O(k*v*num[k])=60*32000=1.92*10^6
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 70
#define M 33000
using namespace std;

//tp[j]代表前i-1组的状态
//dp[j]代表前i组的状态
int n,m,dp[M],tp[M];
struct Goods{
    int w,val;
    Goods(int w=0,int val=0):w(w),val(val){}
};
vector<Goods> gds[N];

int main(){
    int v,p,q;
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&v,&p,&q);
        if(!q)//主件作为一组
            gds[i].push_back(Goods(v,v*p));
        else
            gds[q].push_back(Goods(v,v*p));
    }
    memset(dp,0,sizeof(dp));//尽可能多地装满背包
    for(int i=1;i<=n;i++){
        if(!gds[i].size()) continue;//第i个物品不是主件
        //将前i-1组的最优解赋值给tp
        for(int j=0;j<=m;j++)
            tp[j]=dp[j];
        //前i组的状态初始化为-INF
        memset(dp,-0x3f,sizeof(dp));
        //先购买主件
        for(int j=m;j>=gds[i][0].w;j--)
            dp[j]=max(dp[j],tp[j-gds[i][0].w]+gds[i][0].val);
        //如果当前组只有主件 gds[i].size()=1 这里会直接退出
        //在dp放入主件基础上 继续放入附件 01背包
        for(int k=1;k<gds[i].size();k++){
            for(int j=m;j>=gds[i][k].w;j--)
                dp[j]=max(dp[j],dp[j-gds[i][k].w]+gds[i][k].val);
        }
        //比较前i组最优解 在选取第i组物品(dp[j])和不选取第i组物品(前i-1组物品tp[j])状态比较 选取最优值
        for(int j=0;j<=m;j++)
            dp[j]=max(dp[j],tp[j]);
    }
    printf("%d",dp[m]);
    return 0;
}
*/

/*
//ac 63ms 提前树形遍历统计出后续遍历次序再进行后序次序的01背包
//复杂度(nv) 标准的01背包复杂度
//这个做法不仅能处理依赖关系为2的依赖关系(金明这题、HDU 3449和USACO Video Game Troubles)
//这个做法是不区分主件和附件的,就是每个物品之间都存在着一定依赖关系,
//依赖关系可以嵌套,依赖关系树高度可以大于2.树高不限制的那种传统的树上分组背包类型的题目.
//如a->b->c->d,要购买d就必须先购买a,b,c,要购买c,就必须先购买a和b.
//但是买a,可以买b也可不买,对于c,d都可买都可不买.
//即:物品间的依赖关系可以处理一棵树的情形,这个做法能处理更为宽泛意义上
//物品依赖关系,而本题对于主件与主件之间并没有依赖关系,它们物品间形成的
//依赖关系是多棵树即:森林.本题是虚拟了一个0节点来连接各个主件形成的森林,
//使其成为一棵根节点为0节点的有向树.利用dfs记录这个物品依赖关系后续遍历
//的次序pNode,并记录每个节点i之前左边兄弟子树的最大的后续次序pre[i].
//按照后续遍历的次序进行01背包,对于第i个节点如果选取则dp[i-1][j-pNode[i].w]+pNode[i].val
//如果不选取第i个节点,那么其子树中的节点就都不能选取,那前一个转态就不是dp[i-1][j],而是
//dp[pre[i]][j],pre[i]是节点i最近的左侧的兄弟子树最大的后续次序.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 70
#define M 33000
using namespace std;
//dp[i][j]表示用j元购买依赖树得到后续遍历次序前i个物品所能得到的最大价值
int id,cnt,head[N],n,m,dp[N][M],pre[N];

struct Node{
    int w,val;
    Node(int w=0,int val=0):w(w),val(val){}
}node[N],pNode[N];

struct Edge{
    int to,next;
}edge[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u){
    int dfn=id;//记录u结点左侧兄弟子树最大的后续遍历次序
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        dfs(v);
    }
    pNode[++id]=node[u];//记录后续遍历的次序节点
    //记录节点u的左侧兄弟子树最大的后续遍历次序
    //作为01背包时不选u节点后的前一状态,因为u节点不选那么u的子树中的节点就都不能选了
    pre[id]=dfn;
}

int main(){
    int v,p,q;
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));//尽可能多地装满背包
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&v,&p,&q);
        node[i]=Node(v,v*p);
        addEdge(q,i);//q=0时,是虚拟根节点0连向主件i
    }
    dfs(0);//0是虚拟根节点 连接着各个主件
    //之所以用二维数组是因为 dp[i][j]的前一状态是dp[pre[i]][j]不是dp[i-1][j],所以不能用滚动数组优化成一维
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){//这里是二维01背包 背包容量升序、降序皆可
            if(j>=pNode[i].w)
                //这里注意pNode[i]并不是输入中的第一个节点,但是在记录状态的时候,
                //后续遍历的第一个状态pNode[1]代表的实际节点就作为实际前1个物品装入时的最优解.
                //这样实际后序遍历的节点顺序之间前i-1个状态和前i个状态之间就是连续的.
                //对于dp[i-1][j-pNode[i].w]+pNode[i].val过程中,对于这样的依赖关系a->b->c->d,
                //在容量有限制情况下如果不能全部装下a、b、c、d 4个物品,也不会出现选取a、d而
                //没选取中间b、c 这种选取子节点而并没有选取子节点的全部祖父节点的情况.
                //因为假设a的体积很大,a的上一状态是b节点,枚举容量j,j-w[a]后的剩下的容量在b中根本
                //装不下b,如果装不下b,在b的dp阶段此时的dp[b][j-w[a]]的状态应该是b的左侧兄弟子树的最后一个后序节点,
                //这里因为不能装下b,自然也不会装下c、d两个节点.
                //eg:三个物品编号1、2、3,体积分别3、2、1 价值3、2、1 依赖关系1->2->3,在容量为4时,在最后一个后序遍历物品1时,
                //4-3=1,1节点上一状态2节点在容量为1时显然装不下2节点本身,那么2的dp阶段在容量为1时,显然继承的是上一阶段pre[2],
                //这个pre[2]肯定是不会含有2的子节点3节点的.因此不会出现选了1、3节点,而没有选3的父节点2节点的情况.
                dp[i][j]=max(dp[pre[i]][j],dp[i-1][j-pNode[i].w]+pNode[i].val);
            else
                dp[i][j]=dp[pre[i]][j];
        }
    }
    printf("%d",dp[n][m]);
    return 0;
}
*/

/*
//ac 73ms dfs过程中模拟后序遍历,在dfs中做01背包 不设置后序数组 pNode,pre记录后序次序
//复杂度(nv) 标准的01背包复杂度
//这个做法不仅能处理依赖关系为2的依赖关系(金明这题、HDU 3449和USACO Video Game Troubles)
//这个做法是不区分主件和附件的,就是每个物品之间都存在着一定依赖关系,
//因为每次深度搜索层数+1时,都会保存上一后续遍次序的状态dp[v][j]=dp[u][j],因此不会出现对于
//a->b->c->d,只选取a、d不选取中间b、c的可能,因为不选取b、c所对应的上一状态一定不含b、c的子节点d.
//依赖关系可以嵌套,依赖关系树高度可以大于2.树高不限制的那种传统的树上分组背包类型的题目.
//这个树形背包(貌似不是传统意义上那个的树上分组背包),dfs只是模拟依赖
//关系树的后续遍历来进行01背包,同样对于节点i不选取,那么i的子树节点都不能选取,
//实际的上一状态就是节点i左侧后续遍历最高的次序即左侧兄弟子树根节点的最优解.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 70
#define M 33000
using namespace std;
//假设i节点在dfs后续遍历得到次序为k
//dp[i][j] 代表dfs后续遍历前k个次序的物品在j元钱限制下所能获得的最大价值
int cnt,head[N],n,m,w[N],val[N],dp[N][M];

struct Edge{
    int to,next;
}edge[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

//实际这棵树是把各个主件和其附件构成的森林中的多棵树通过虚拟节点0链接其它构成一棵有向树
void dfs(int u){
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
		//其实模拟的还是01背包那个过程,pre[v]代表v的左侧兄弟子树后序遍历
		//的最后一个父节点,但是现在没有设置pre[v]这个数组,是通过dfs的回溯
		//过程来模拟01背包前i-1个物品的状态向前i个物品的状态转移.
		//dp[u][j]代表前i个状态,dp[v][j]代表前i-1个状态,因为是dfs深度优先
		//是按照后序遍历次序作为01背包选取物品的顺序
		//这里初始化是因为dfs的后序遍历,左侧子树遍历完后它的右边兄弟子树的叶子节点
		//才是紧接着之前的后序次序+1的下一个状态,因此在遍历右侧子树时要把左侧子树最后一个次序
		//的物品的最优解赋值给当前这棵子树的叶子节点,因此就要dfs这里dp[v][j]=dp[u][j]方便实际
		//叶子节点作为后序遍历的下一个节点在前面状态基础上求解最优解
        for(int j=0;j<=m;j++)
            dp[v][j]=dp[u][j];
        dfs(v);
        //v的子树节点已经遍历完,现在假设u是虚拟0节点,v是主件,
        //考虑选取v节点还是不选取v节点,如果选取v节点,那么v的子节点是v的附件,
        //根据背包剩余容量j的不同,dp[v][j-w[v]]+val[v]最优解中v的附件可能选了也可能不选,都能作为最优解.
        //而dp[u][j]前一状态是虚拟节点下之前后序遍历过的主件和附件构成树的最优解,如果不选取v(主件),
        //那么v的附件也不能选取,所以v的上一状态就是dp[u][j].

        //同样如果u是实际的主件节点,此时dp[u][j]和dp[v][j]实际都表示虚拟节点下之前后序遍历过的主件和附件构成树的最优解
        //而dp[v][j-w[v]]+val[v]正是在前一状态基础上求解最优解
        for(int j=m;j>=w[v];j--)//这里m永远都是 初始背包容量,没有减少,这个过程仍然是01背包的标准过程
            //u和v编号并不一定相差1,可能差很多
            dp[u][j]=max(dp[u][j],dp[v][j-w[v]]+val[v]);
    }
}

int main(){
    int v,p,q;
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));//尽可能多地装满背包
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&v,&p,&q);
        w[i]=v,val[i]=v*p;
        addEdge(q,i);//q=0时,是虚拟根节点0连向主件i
    }
    dfs(0);
    printf("%d",dp[0][m]);
    return 0;
}
*/

/*
//ac 78ms 徐持衡《浅谈几类背包问题》中的做法
//dfs树形后序次序01背包+剪枝
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 70
#define M 33000
using namespace std;

int cnt,head[N],n,m,w[N],val[N],dp[N][M];

struct Edge{
    int to,next;
}edge[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int tot){
    if(tot<=0)//剪枝
        return;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        for(int j=0;j<=tot-w[v];j++)
            dp[v][j]=dp[u][j]+val[v];
        dfs(v,tot-w[v]);
        for(int j=tot;j>=w[v];j--)
            dp[u][j]=max(dp[u][j],dp[v][j-w[v]]);
    }
}

int main(){
    int v,p,q;
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));//尽可能多地装满背包
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&v,&p,&q);
        w[i]=v,val[i]=v*p;
        addEdge(q,i);//q=0时,是虚拟根节点0连向主件i
    }
    dfs(0,m);
    printf("%d",dp[0][m]);
    return 0;
}
*/

/*
//ac 38ms dp[M][2]做法
//摘自洛谷网友
//我们只需分别考虑每个主件以及它所带的附件，我们设dp[k][0]为花掉k元钱但并不购买当前主件（一定不购买附件）可获得的最大收益；
//dp[k][1]为花掉k元钱并购买了当前主件（不一定购买了附件）可获得的最大收益。
//那么现在我们面临着2种情况：
//物品i没有“绑定”附件
//物品i有“绑定”附件
//若物品i没有“绑定”附件,我们直接用传统的0-1背包状态转换方程式(此时的dp[k][0]就相当于dp[k])
//dp[k][0]=max(dp[k][0],dp[k-v[i]][0]+v[i]*w[i]);
//若物品i“绑定”了附件，那么对于附件j状态转移方程式应为
//dp[k][1]=max(dp[k-v[i]][0]+v[i]*w[i],dp[k-v[j]][1]+v[j]*w[j]);
//注意必须要在购买了主件的情况下才能使用 dp[k-v[j]][1]+v[j]*w[j];
//否则会导致WA;最后要将dp[k][0]与dp[k][1]中的最大收益保留到dp[k][0]中。具体操作方法见代码~.~
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define pi pair<int,int>
#define f first
#define s second

using namespace std;

int n,m;
int dp[32001][2];
vector<pi>gp[61];//vector用于记录附件
int cnt,v[61],w[61],id[61];

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		if(c==0){//不含附件
			v[++cnt]=a;
			w[cnt]=b;
			id[cnt]=i;
		}
		else{
			gp[c].push_back(pi(a,b));
		}
	}
	for(int i=1;i<=cnt;i++){
		if(gp[id[i]].size()==0){//没有附件
			for(int j=n;j>=v[i];j--)dp[j][0]=max(dp[j][0],dp[j-v[i]][0]+v[i]*w[i]);
		}
		else{//有附件
			for(int j=n;j>=v[i];j--)dp[j][1]=dp[j-v[i]][0]+v[i]*w[i];
			for(int k=0;k<gp[id[i]].size();k++){
				int vk=gp[id[i]][k].f;//当前附件的价格
				int wk=gp[id[i]][k].s;//当前附件的重要等级
				for(int j=n;j>=v[i]+vk;j--)dp[j][1]=max(dp[j][1],dp[j-vk][1]+vk*wk);//j的边界条件非常重要
			}
			for(int j=n;j>=v[i];j--)dp[j][0]=max(dp[j][1],dp[j][0]);//保留最优解
		}
	}
	printf("%d\n",dp[n][0]);//输出
	return 0;
}
*/

/*
//50分,TLE 树上分组背包 传统树形背包做法 复杂度O(n*v^2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 70
#define M 33000
using namespace std;

int cnt,head[N],n,m,w[N],val[N],dp[N][M];

struct Edge{
    int to,next;
}edge[N];

void addEdge(int from,int to){
    edge[cnt]=(Edge){to,head[from]};
    head[from]=cnt++;
}

void dfs(int u,int tot){
    if(tot<=0)//剪枝
        return;
    for(int i=w[u];i<=tot;i++)
        dp[u][i]=val[u];
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        dfs(v,tot-w[u]);
        for(int j=tot;j>=w[u];j--){
            //这里k的下界就是w[v] 可以确定
            for(int k=w[v];k<=j-w[u];k++)
                dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]);
        }
    }
}

int main(){
    int v,p,q;
    memset(head,-1,sizeof(head));
    memset(dp,0,sizeof(dp));//尽可能多地装满背包
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&v,&p,&q);
        w[i]=v,val[i]=v*p;
        addEdge(q,i);//q=0时,是虚拟根节点0连向主件i
    }
    dfs(0,m);
    printf("%d",dp[0][m]);
    return 0;
}
*/

/*
//ac 182ms 传统树形背包(树上分组背包)做法 将背包容量总钱数和物品价格缩小100倍,降低复杂度.
//不加putin 缩小背包容量 会TLE. 复杂度O(n*v^2)
//摘自洛谷网友
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
using namespace std;
#define ll long long
#define in inline
inline ll read(){
    ll x=0,f=1;char c=getchar();
    while(c>'9'||c<'0'){if(c=='-')f=-f;c=getchar();
    }
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();
    }return x*f;
}
const int mx=1550;
int h[mx],p,f[61][3210],w[mx],v[mx],m;
struct edge{
    int next,v;
}e[4*mx];
inline void add(int a,int b){
    p++;e[p].next=h[a];h[a]=p;e[p].v=b;
}
int n,flag;
inline void putin(){
    m=read();n=read();m/=10;
    for(int i=1,p,x;i<=n;i++){
    	w[i]=read();v[i]=read();p=read();
    	w[i]/=10;
    	if(w[i]%10>0)flag=1;//优化，如果出现不能整出100的就标记。
    	v[i]*=w[i];//我们这里计算v的时候是乘的除以10的w，所以答案乘10。
    	add(p,i);
    }
    if(flag==0){//优化。
    	m/=10;
    	for(int i=1;i<=n;i++)w[i]/=10;
    }

    memset(f,0xcf,sizeof(f));
}
void dfs(int u){
    for(int i=0;i<=w[u];i++)f[u][i]=0;
    for(int i=h[u];i;i=e[i].next){
    	int v=e[i].v;
    	dfs(v);
    	for(int t=m;t>=w[v];t--){//不优化这里会炸
    		for(int j=t;j>=w[v];j--)
    		f[u][t]=max(f[u][t],f[u][t-j]+f[v][j]);
        }
    }
    if(u!=0){
        for(int t=m;t>=w[u];t--)f[u][t]=f[u][t-w[u]]+v[u];
    }
}
int main(){
    putin();
    dfs(0);
     printf("%d",f[0][m]*10);
    return 0;
}
*/

/*
//ac 85ms 泛化物品
参考博客:https://www.luogu.com.cn/blog/user24559/solution-p1064(下面代码是这份博客)
https://www.luogu.com.cn/blog/rocon/solution-p1064(好像不是泛化)
这道题目我们建一个0点，其重量为0，价值为0，然后我们就有一棵以0为根的树了。
选择一个点的规则是：必须选择其父亲。
众所周知，两件泛化物品的和是O(m^2)的（m为体积，在本题中体积为n），这道题我们自然不能用这种方法。

泛化物品的和：把两个泛化物品合并成一个泛化物品的运算，就是枚举体积分配给两个泛化物品，满足：
G[j] = max{ G1[j-k] + G2[k] } (C>=j>=k>=0)
又，众所周知，泛化物品的并是O(m)的，如果我们能做到O(nm)的话，那就能皆大欢喜了。

泛化物品的并： 因为两个泛化物品之间存在交集，所以不能同时两者都取，那么我们就需要求泛化物品的并，对同一体积，我们需要选取两者中价值较大的一者，效率 O(C)。
G[j] = max{ G1[j] , G2[j] } (C>=j>=0)
现在问题在于，我们该如何将树上的泛化物品的和转化为并？

我们设状态Fi为，以i为根的树（这个树定义为当前已经经过的点集所形成的树）的泛化物品。由于选取规则，则i必选。我们现在考虑去递归到i的一个儿子s。
我们发现，如果我们往i里硬塞一个s，Fi就会变成Fs！

如果我们在当前的 Fi中强制放入物品 s 后作为以 s 为根的子树的初始状态的话，那么处理完以 s 为根的子树以后，Fs就是与 Fi有交集的泛化物品（实际上是 Fs包含Fi） ，同时，Fs必须满足放了物品s，即Fs[j] (Vs>j>=0)已经无意义了，而Fs[j] (C>=j>=Vs)必然包含物品 s。为了方便，经过处理以后，在程序中规定只有Fs[j] (C-Vs>=j>=0)是合法的。
接下来只需要把 Fs与Fi的并赋给 Fi，就完成了对一个儿子的处理。如 此，我们需要的总时间复杂度仅为O(n*C)。
多么巧妙的思想啊！
#include<bits/stdc++.h>
using namespace std;
const int inf=1e7;
int head[1001],nxt[2001],point[2001],W[1001],V[1001];
int f[61][32011];
int tot,n,m,pi,qi;
void addedge(int x,int y){
    tot++;nxt[tot]=head[x];head[x]=tot;point[tot]=y;
}
void dfs(int now,int dad){
    for(int i=m;i>=0;i--) if(i>=W[now]) f[now][i]=f[dad][i-W[now]]+V[now];
    for(int tmp=head[now];tmp;tmp=nxt[tmp]){
        int v=point[tmp];
        dfs(v,now);
        for(int i=0;i<=m;i++) if(i+W[v]<=m)f[v][i]=f[v][i+W[v]]-V[v];else f[v][i]=-inf;
        for(int i=m;i>=0;i--) if(i>=W[v]) f[now][i]=max(f[now][i],f[v][i-W[v]]+V[v]);
    }
}
int main(){
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&W[i],&pi,&qi);
        addedge(qi,i);
        V[i]=W[i]*pi;
    }
    memset(f,-51,sizeof(f));
    f[0][0]=0;
    dfs(0,0);
    int ans=0;
    for(int i=0;i<=m;i++) ans=max(ans,f[0][i]);
    cout<<ans<<endl;
}
*/

/*
//ac 56ms 徐持衡论文中的办法
//个人觉得他的思路并不算好 我的那种(第三种做法)在dfs 后序遍历中模拟01背包更好理解 比他这个做法好
#include<bits/stdc++.h>
using namespace std;

int N,m,w[200],c[200],x,dp[200][40000];//数组大小qwq
int head[200],k=1;//链式前向星加边用
struct edge
{
	int to,next;
}e[200];//树的边

void adde(int u,int v)//链式前向星加边
{
	e[k].to=v;
	e[k].next=head[u];
	head[u]=k++;
}

void dfs(int u,int t,int fa)
//u是当前节点，t是当前容量，fa是父亲节点
{
	if(t<=0)return;//装不下了
	for(int i=head[u];i;i=e[i].next)//访问与该点相连的每一条边
	{
		int v=e[i].to;
		if(v==fa)continue;//如果是父节点则跳过
		for(int k=N-w[v];k>=0;k--)
			dp[v][k]=dp[u][k]+c[v];//要选子树，就必须选该节点
		dfs(v,t-w[v],u);//继续递归
		for(int k=N;k>=w[v];k--)
			dp[u][k]=max(dp[u][k],dp[v][k-w[v]]);//选或不选（这是01背包）
	}
}

int main()
{
	scanf("%d%d",&N,&m);
	for(register int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&w[i],&c[i],&x);
		c[i]*=w[i];//读入
		adde(i,x);adde(x,i);//连双向边
	}
	dfs(0,N,-1);//0为虚拟根节点，深搜跑dp
	int ans=0;
	for(register int i=0;i<=N;i++)//这里一定要写<=，因为可以刚好把钱花完
		ans=max(ans,dp[0][i]);//统计答案
	printf("%d\n",ans);//输出
	return 0;//结束了罪恶的一生
}
*/

