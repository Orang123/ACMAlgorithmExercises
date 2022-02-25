#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 550
#define INF 0x3f3f3f3f
using namespace std;
//ac 374ms 最优匹配 非slack优化 O(V^4)
//2008 Asia Hangzhou Regional Contest Online
//https://blog.csdn.net/qq_21057881/article/details/50682525 这个将不存在边和负权边也加入图的做法初始化mp只能用-INF,用-1就错不知为何
/*
KM算法将顶标之和与边权最小差值d若放在dfs匈牙利匹配中计算,会增加复杂度,耗时较多 876ms
而放在KM() while(1)每次dfs完后的循环里两层for循环计算效率,复杂度就会降低,耗时较少 374ms.
但是直观来看,不应该是差值d放在dfs匈牙利里直接计算一次更快吗,这可能是因为递归
的dfs里 因为需要判断差值d不为0时,计算d=min(d,tp),而递归if else d=min(d,tp)编译
后的指令集 变得更复杂一些,所以机器耗时就多了些,事实上也就慢了500ms,表现地也并不是很差.
//好像单单只是这道题 最小差值d若放在dfs匈牙利匹配中计算耗时较多,其它题目效率时间和slack优化差不多
现在暂时就用将差值d放在KM while(1)计算这种做法
*/

/*
题意:n个学生m个房间,每个学生对一些(不是全部)房间进行
评分,评分为正说明这个房间较优,评分为0标明房间质量较中,
评分为负代表房间质量较差,学生不喜欢住在质量较差的房间里,
现在要将每个学生分配到一个他已评分房间,一个房间只能住一个学生,
不能将学生分配到它未评分的房间,因为学生因为其它原因不能住在这个房间里.
要求各个学生对居住房间的评分之和最大,输出这个最大评分之和.
如果并不是所有学生都能分配到自己评分的房间,输出-1.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2426
思路:此题学生人数和房间人数可能不对等,即n<m n=m n>m都有可能,
对于学生评分为负和未评分的房间都不应建边,只建立权值w>=0的边,
在KM算法里应判断有效边.对于存在学生不能分配到房间的情况,
应根据每次匈牙利算法求解完后,待加入相等子图的边的差值
d=lx+ly-mp[x][y]来判断,每次初始化d=INF,如果跑完匈牙利d仍然等于INF,
说明本次匹配的过程,存在某个点u没有有效边可匹配(u可能是本身就无边连接,
也可能是连接边都被别的点匹配,没有剩余有效边),则必然u这个学生不能分配到房间.
输出-1.
*/
int cas,n,m,e,mp[N][N],link[N],visx[N],visy[N],lx[N],ly[N],d;

int dfs(int u){
    visx[u]=1;
    for(int v=0;v<m;v++){
        if(mp[u][v] == -1 || visy[v]) continue;
        int tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(link[v] == -1 || dfs(link[v])){
                link[v]=u;
                return 1;
            }
        }
    }
    return 0;
}
//O(V^4) 因为记录最小差值d在while(1)里又用了两层循环
int KM(){
    for(int i=0;i<n;i++){//初始化x顶标
        for(int j=0;j<m;j++){
            if(mp[i][j] == -1) continue;//不存在的边不需要比较最大边权
            lx[i]=max(lx[i],mp[i][j]);
        }
    }
    for(int i=0;i<m;i++)//初始化y顶标
        ly[i]=0;
    for(int i=0;i<n;i++){//O(V)
        while(1){//O(V)
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;//O(E)
            for(int j=0;j<n;j++){//不要放在dfs匈牙利里记录最小差值 O(V^2)
                if(!visx[j]) continue;
                for(int k=0;k<m;k++){
                    //不身不存在的边对应的visy[k]也为0,所以要排除,否则真的没有有效边匹配时,
                    //对应的Y集合未匹配的点visy[k]也是0,这就会导致d被更新不能结束死循环
                    if(mp[j][k] == -1) continue;
                    if(!visy[k])
                        d=min(d,lx[j]+ly[k]-mp[j][k]);
                }
            }
            if(d == INF) return -1;//X集合存在点没有有效边可配对 退出返回-1 针对n>m的情况
            //增广失败,将访问过的点(包括增广失败的点)形成的树称为交错树.
            //更新匈牙利遍历的相等子图中访问到的交错树中点顶标值,lx降低,ly减少.
            for(int j=0;j<n;j++){
                if(visx[j]) lx[j]-=d;
            }
            for(int j=0;j<m;j++){
                if(visy[j]) ly[j]+=d;
            }
        }
    }
    int sum=0;
    for(int i=0;i<m;i++){
        if(link[i] == -1) continue;//只累加Y集合匹配点对应边权
        sum+=mp[link[i]][i];
    }
    return sum;
}

void init(){
    cas++;
    memset(link,-1,sizeof(link));//因为点的编号是从0开始编,因此link初始化-1
    memset(mp,-1,sizeof(mp));//允许存在权值为0和权值大于0的边,因此初始化-1
    memset(lx,-1,sizeof(lx));//因为实际建立的二分图中边权都>=0,因此lx初始化为-1
}

int main(){
    int u,v,w;
    while(scanf("%d%d%d",&n,&m,&e)!=EOF){
        init();
        while(e--){
            scanf("%d%d%d",&u,&v,&w);
            if(w>=0)//只建立边权大于等于0的边
                mp[u][v]=w;
        }
        printf("Case %d: %d\n",cas,KM());
    }
    return 0;
}

/*
//ac 873m 最优匹配 差值d(全局变量)放在dfs里更新,每次dfs都需初始化d=INF 耗时较多 但省去了slack数组,
//针对这道题而言耗时较多 HDU 2255这题最小差值d放在dfs里求解,耗时比放在KM() while里要快,跟测试数据有关
//这里KM复杂度按道理只有O(V^2*E) 但是相比用slack数组记录Y集合每个点最小差值,这个做法反而慢了许多.
//一个博客中说到的原因:https://www.cnblogs.com/fzl194/p/8848061.html
//和全局变量不同的是,全局变量在每次while循环中都需要赋值成INF,
//每次求出的是所有点的最小值,而slack数组在每个while外面就初始化好,
//每次while循环slack数组的每个值都在用到,一次增广路中求出的slack值会更准确,
//循环次数比全局变量更少,why"循环次数比全局变量更少"???
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 550
#define INF 0x3f3f3f3f
using namespace std;

int cas,n,m,e,mp[N][N],link[N],visx[N],visy[N],lx[N],ly[N],d;

int dfs(int u){
    visx[u]=1;
    for(int v=0;v<m;v++){
        if(mp[u][v] == -1 || visy[v]) continue;
        int tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(link[v] == -1 || dfs(link[v])){
                link[v]=u;
                return 1;
            }
        }
        else
            d=min(d,tp);
    }
    return 0;
}
//O(V^2*E)
int KM(){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(mp[i][j] == -1) continue;
            lx[i]=max(lx[i],mp[i][j]);
        }
    }
    for(int i=0;i<m;i++)
        ly[i]=0;
    for(int i=0;i<n;i++){
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            if(d == INF) return -1;
            for(int j=0;j<n;j++){
                if(visx[j]) lx[j]-=d;
            }
            for(int j=0;j<m;j++){
                if(visy[j]) ly[j]+=d;
            }
        }
    }
    int sum=0;
    for(int i=0;i<m;i++){
        if(link[i] == -1) continue;
        sum+=mp[link[i]][i];
    }
    return sum;
}

void init(){
    cas++;
    memset(link,-1,sizeof(link));
    memset(mp,-1,sizeof(mp));
    memset(lx,-1,sizeof(lx));
}

int main(){
    int u,v,w;
    while(scanf("%d%d%d",&n,&m,&e)!=EOF){
        init();
        while(e--){
            scanf("%d%d%d",&u,&v,&w);
            if(w>=0)
                mp[u][v]=w;
        }
        printf("Case %d: %d\n",cas,KM());
    }
    return 0;
}
*/

/*
//ac 249ms slack数组松弛优化 O(V^2*E)
//这个松弛优化主要是在每次更新顶标,确定最小差值时,因为用slack[i]数组记录了Y集合中每个点i作为待加入可行边的端点i需要的最小差值
//这样最终在比较所有Y集合中作为待加入可行边端点的差值时,可以一层for循环就比较出Y集合中最小的差值.
//否则不用slack数组就会导致,这里需要两层for循环先考虑x集合中vis[x]=1的点,再考虑x连边的Y集合visy[y]=0的点.
//但是这里和不用slack数组直接在dfs里记录这个最小差值d 感觉没啥区别啊,为啥不用这个slack数组就慢.

//摘自博客:https://blog.csdn.net/c20182030/article/details/73330556?locationNum=3&fps=1
//貌似加入slack数组后 边权值大小还会影响其性能
//对于随机数据来说,时间复杂度约为O(V^2*E),但是
//如果我们考虑极限数据,把每条边的边权mp[i][j]=i*j,试试看吧,会怎样？   "会很耗时吗,我的理解"
//只针对随即数据O(n^3),对于极限数据（w[i][j]很大）slack优化作用不显著

//摘自博客:https://www.cnblogs.com/Iking123/p/11300885.html
//这个优化似乎是很有用,但并不能把KM优化到O(n^3).这其实和原算法差不多,
//还是要为左部n个点匹配,每次匹配还是最多要增广n次,每次增广还是O(n+m).
//如果是完全图,并且出题人稍微构造一下数据,依然是O(n^4).
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 550
#define INF 0x3f3f3f3f
using namespace std;

int cas,n,m,e,mp[N][N],link[N],visx[N],visy[N],lx[N],ly[N],slack[N],d;

int dfs(int u){
    visx[u]=1;
    for(int v=0;v<m;v++){
        if(mp[u][v] == -1 || visy[v]) continue;
        int tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(link[v] == -1 || dfs(link[v])){
                link[v]=u;
                return 1;
            }
        }
        else
            slack[v]=min(slack[v],tp);
    }
    return 0;
}
//O(V^2*E)
int KM(){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(mp[i][j] == -1) continue;
            lx[i]=max(lx[i],mp[i][j]);
        }
    }
    for(int i=0;i<m;i++)
        ly[i]=0;
    for(int i=0;i<n;i++){
        //放在while(1)之外的原因是每次搜索增广路时lx+ly!=w(x,y)对应的Y集合中的点应该都是不同的,
        //所以只需初始化一次放在考虑i点配对的while(1)循环外
        memset(slack,0x3f,sizeof(slack));
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=0;j<m;j++){//直接考虑Y集合中的点,因为slack数组已经记录最小值各个点的最小差值,一层for循环即可
                if(!visy[j])//对于实际不存在的有效边slack[j]是INF,因此如果本身j点因为未连边未配对,这里d仍旧还是INF
                    d=min(d,slack[j]);
            }
            if(d == INF) return -1;
            for(int j=0;j<n;j++){
                if(visx[j]) lx[j]-=d;
            }
            for(int j=0;j<m;j++){
                if(visy[j]) ly[j]+=d;
                //else slack[j]-=d;// 不明白为啥 slack[j]要减d 事实上不对slack操作也没问题
            }
        }
    }
    int sum=0;
    for(int i=0;i<m;i++){
        if(link[i] == -1) continue;
        sum+=mp[link[i]][i];
    }
    return sum;
}

void init(){
    cas++;
    memset(link,-1,sizeof(link));
    memset(mp,-1,sizeof(mp));
    memset(lx,-1,sizeof(lx));
}

int main(){
    int u,v,w;
    while(scanf("%d%d%d",&n,&m,&e)!=EOF){
        init();
        while(e--){
            scanf("%d%d%d",&u,&v,&w);
            if(w>=0)
                mp[u][v]=w;
        }
        printf("Case %d: %d\n",cas,KM());
    }
    return 0;
}
*/

/*
//ac 124ms slack数组优化+链式前向星 存图 O(V^2*E)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 550
#define INF 0x3f3f3f3f
using namespace std;

int cnt,head[N];
int cas,n,m,e,link[N],visx[N],visy[N],lx[N],ly[N],slack[N],d;
struct Edge{
    int from,to,next,w;
}edge[N*N];

void addEdge(int from,int to,int w){
    edge[cnt]=(Edge){from,to,head[from],w};
    head[from]=cnt++;
}

int dfs(int u){
    visx[u]=1;
    for(int i=head[u];i!=-1;i=edge[i].next){
        int v=edge[i].to;
        if(visy[v]) continue;
        int tp=lx[u]+ly[v]-edge[i].w;
        if(!tp){
            visy[v]=1;
            if(link[v] == -1 || dfs(link[v])){
                link[v]=u;
                return 1;
            }
        }
        else
            slack[v]=min(slack[v],tp);
    }
    return 0;
}
//O(V^2*E)
int KM(){
    int u,v;
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        lx[u]=max(lx[u],edge[i].w);
        ly[v]=0;
    }
    for(int i=0;i<n;i++){
        memset(slack,0x3f,sizeof(slack));
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=0;j<m;j++){
                if(!visy[j])
                    d=min(d,slack[j]);
            }
            if(d == INF) return -1;
            for(int j=0;j<n;j++){
                if(visx[j]) lx[j]-=d;
            }
            for(int j=0;j<m;j++){
                if(visy[j]) ly[j]+=d;
                else slack[j]-=d;
            }
        }
    }
    int sum=0;
    for(int i=0;i<cnt;i++){
        u=edge[i].from;
        v=edge[i].to;
        if(link[v] == u)
            sum+=edge[i].w;
    }
    return sum;
}

void init(){
    cas++;
    cnt=0;
    memset(link,-1,sizeof(link));
    memset(head,-1,sizeof(head));
    memset(lx,-1,sizeof(lx));
}

int main(){
    int u,v,w;
    while(scanf("%d%d%d",&n,&m,&e)!=EOF){
        init();
        while(e--){
            scanf("%d%d%d",&u,&v,&w);
            if(w>=0)
                addEdge(u,v,w);
        }
        printf("Case %d: ",cas);
        if(n>m) printf("-1\n");
        else printf("%d\n",KM());
    }
    return 0;
}
*/

/*
//ac 327ms mp初始化-1,-2就wa,初始化-3或更小的负数就对了,不知啥原因,有点玄学.也许和判题服务器linux环境编译有关?
//另外此题的测试数据实际 就不存在会选不存在边或评分为负数的边的样例,全是正边
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 550
#define INF 0x3f3f3f3f
using namespace std;

int cas,n,m,e,mp[N][N],link[N],visx[N],visy[N],lx[N],ly[N],d,slack[N];

int dfs(int u){
    visx[u]=1;
    for(int v=0;v<m;v++){
        if(visy[v]) continue;
        int tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(link[v] == -1 || dfs(link[v])){
                link[v]=u;
                return 1;
            }
        }
        else
            slack[v]=min(slack[v],tp);
    }
    return 0;
}

int KM(){
    for(int i=0;i<n;i++){
    	lx[i]=-3;
        for(int j=0;j<m;j++){
            lx[i]=max(lx[i],mp[i][j]);
        }
    }
    for(int i=0;i<m;i++)
        ly[i]=0;
    for(int i=0;i<n;i++){
    	memset(slack,0x3f,sizeof(slack));
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=0;j<m;j++)
            if(!visy[j])
            d=min(d,slack[j]);
            for(int j=0;j<n;j++){
                if(visx[j]) lx[j]-=d;
            }
            for(int j=0;j<m;j++){
                if(visy[j]) ly[j]+=d;
            }
        }
    }
    int sum=0;
    for(int i=0;i<m;i++){
        if(link[i] == -1) continue;
        //if(mp[link[i]][i] == -1) return -1;//测试数据实际 就不存在会选不存在边或评分为负数的边的样例,全是正边
        sum+=mp[link[i]][i];
    }
    return sum;
}

void init(){
    cas++;
    memset(link,-1,sizeof(link));
    memset(mp,-1,sizeof(mp));
}

int main(){
    int u,v,w;
    while(scanf("%d%d%d",&n,&m,&e)!=EOF){
        init();
        for(int i=0;i<n;i++){
        	for(int j=0;j<m;j++)
        		mp[i][j]=-3;
		}
        int num=e;
        while(e--){
            scanf("%d%d%d",&u,&v,&w);
            if(w>=0)
                mp[u][v]=w;
        }
        printf("Case %d: ",cas);
        if(!num)//边数为0时,需要特判输出0,否则KM会一直while(1)里死循环.
        	printf("-1\n");
        else
        	printf("%d\n",KM());
    }
    return 0;
}
*/
