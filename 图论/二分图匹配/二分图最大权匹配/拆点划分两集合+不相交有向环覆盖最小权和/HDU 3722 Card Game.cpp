#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
#define M 1100
#define INF 0x3f3f3f3f
using namespace std;
//ac 78ms 最优匹配 slack数组优化
//此题同HDU 3435
//2010 Asia Tianjin Regional Contest
/*
题意:n张卡片,每个卡片i包含一个字符串str[i],现在要将
所有的卡片粘贴在一起,卡片i粘贴到卡片j前面的
得分为卡片i的字符串str[i]反转和卡片j的字符串str[j]最长
公共前缀的字符数,注意如果卡片自己贴到自己上,定义其得分为0,
即使该卡片包含的字符串是回文串.现在要求解粘贴n张卡片的最大
得分.
eg:卡片i"abcd" 卡片j"dcab",若i粘在j后面,得分为2,最长公共前缀为2.
若j粘在i后面,得分为0,因为最长公共前缀(LCP)为0.
注意:一个卡片只能贴在一张卡片后面,同时也可作为被贴卡片贴在一张卡片
前面,自己粘贴自己得分固定为0.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3722
思路:因为一个卡片只能贴在一张卡片后面,同时也可作为被贴卡片只贴在一张卡片
前面,可以拆点成2个状态,分为2个集合,构成二分图,因此最终所有的卡片贴在一起
可能刚好构成1个圈,也可能多个圈,也可能一个圈也没有(首尾卡片都是自己粘自己),
这取决于首尾的卡片是否相粘贴.那么显然两张卡片粘在一起构成了一个匹配,2张卡
片贴在一起的得分为匹配边权.那么每张卡片可以作为粘的卡片和被粘的卡片分成2个
状态,也就是主动粘只能粘一次,被粘也只能被粘一次,而这两个状态构成2个集合,因此
求解得分最大的问题就转化为了匹配边权和最大的问题,显然KM算法可解决.
*/
int n,mp[N][N],match[N],visx[N],visy[N],lx[N],ly[N],d,slack[N];
char str[N][M];

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=n;v++){
        if(visy[v]) continue;//每个卡片都可和所有卡片粘贴(包括自己),只不过有些得分为0
        int tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(!match[v] || dfs(match[v])){
                match[v]=u;
                return 1;
            }
        }
        else
            slack[v]=min(slack[v],tp);
    }
    return 0;
}

int KM(){
    for(int i=1;i<=n;i++){
        lx[i]=ly[i]=0;
        for(int j=1;j<=n;j++)
            lx[i]=max(lx[i],mp[i][j]);
    }
    for(int i=1;i<=n;i++){
        memset(slack,0x3f,sizeof(slack));
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=1;j<=n;j++){
                if(!visy[j])
                    d=min(d,slack[j]);
            }
            for(int j=1;j<=n;j++){
                if(visx[j]) lx[j]-=d;
                if(visy[j]) ly[j]+=d;
                else slack[j]-=d;//实际没有slack[j]-=d这个操作也能78ms ac
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(!match[i]) continue;
        ans+=mp[match[i]][i];
    }
    return ans;
}

int cal(int i,int j){
    int len1=strlen(str[i]+1);
    int len2=strlen(str[j]+1);
    int s=len1,t=1;
    for(;s>=1 && t<=len2 && str[i][s] == str[j][t];s--,t++);//结束条件是两个字符串当前位不相等或i串、j串遍历完
    return t-1;//实际LCP为t-1
}

void init(){
    memset(match,0,sizeof(match));
}

int main(){
    while(scanf("%d",&n)!=EOF){
        init();
        for(int i=1;i<=n;i++)
            scanf("%s",str[i]+1);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                //注意对于卡片粘在自己上面形成环,题目定义得分为0,即使本身是回文,其逆序串和原串相等,也定义得分为0,不然会wa
                if(i == j)
                    mp[i][j]=0;
                else
                    mp[i][j]=cal(i,j);
            }
        }
        printf("%d\n",KM());
    }
    return 0;
}

/*
//ac 78ms 最小差值d放在dfs里求解
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
#define M 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,m,mp[N][N],match[N],visx[N],visy[N],lx[N],ly[N],d;
char str[N][M];

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=n;v++){
        if(visy[v]) continue;
        int tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(!match[v] || dfs(match[v])){
                match[v]=u;
                return 1;
            }
        }
        else
            d=min(d,tp);
    }
    return 0;
}

int KM(){
    for(int i=1;i<=n;i++){
        lx[i]=ly[i]=0;
        for(int j=1;j<=n;j++)
            lx[i]=max(lx[i],mp[i][j]);
    }
    for(int i=1;i<=n;i++){
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=1;j<=n;j++){
                if(visx[j]) lx[j]-=d;
                if(visy[j]) ly[j]+=d;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(!match[i]) continue;
        ans+=mp[match[i]][i];
    }
    return ans;
}

int cal(int i,int j){
    int len1=strlen(str[i]+1);
    int len2=strlen(str[j]+1);
    int s=len1,t=1;
    for(;s>=1 && t<=len2 && str[i][s] == str[j][t];s--,t++);
    return t-1;
}

void init(){
    memset(match,0,sizeof(match));
}

int main(){
    while(scanf("%d",&n)!=EOF){
        init();
        for(int i=1;i<=n;i++)
            scanf("%s",str[i]+1);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                //注意对于卡片粘在自己上面形成环,题目定义得分为0,即使本身是回文,其逆序串和原串相等,也定义得分为0,不然会wa
                if(i == j)
                    mp[i][j]=0;
                else
                    mp[i][j]=cal(i,j);
            }
        }
        printf("%d\n",KM());
    }
    return 0;
}
*/

/*
//ac 93ms 最小差值d放在KM while(1)循环内,两层for循环求解
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 210
#define M 1100
#define INF 0x3f3f3f3f
using namespace std;

int n,mp[N][N],match[N],visx[N],visy[N],lx[N],ly[N],d;
char str[N][M];

int dfs(int u){
    visx[u]=1;
    for(int v=1;v<=n;v++){
        if(visy[v]) continue;
        int tp=lx[u]+ly[v]-mp[u][v];
        if(!tp){
            visy[v]=1;
            if(!match[v] || dfs(match[v])){
                match[v]=u;
                return 1;
            }
        }
    }
    return 0;
}

int KM(){
    for(int i=1;i<=n;i++){
        lx[i]=ly[i]=0;
        for(int j=1;j<=n;j++)
            lx[i]=max(lx[i],mp[i][j]);
    }
    for(int i=1;i<=n;i++){
        while(1){
            d=INF;
            memset(visx,0,sizeof(visx));
            memset(visy,0,sizeof(visy));
            if(dfs(i)) break;
            for(int j=1;j<=n;j++){
                if(!visx[j]) continue;
                for(int k=1;k<=n;k++){
                    if(!visy[k])
                        d=min(d,lx[j]+ly[k]-mp[j][k]);
                }
            }
            for(int j=1;j<=n;j++){
                if(visx[j]) lx[j]-=d;
                if(visy[j]) ly[j]+=d;
            }
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        if(!match[i]) continue;
        ans+=mp[match[i]][i];
    }
    return ans;
}

int cal(int i,int j){
    int len1=strlen(str[i]+1);
    int len2=strlen(str[j]+1);
    int s=len1,t=1;
    for(;s>=1 && t<=len2 && str[i][s] == str[j][t];s--,t++);
    return t-1;
}

void init(){
    memset(match,0,sizeof(match));
}

int main(){
    while(scanf("%d",&n)!=EOF){
        init();
        for(int i=1;i<=n;i++)
            scanf("%s",str[i]+1);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                //注意对于卡片粘在自己上面形成环,题目定义得分为0,即使本身是回文,其逆序串和原串相等,也定义得分为0,不然会wa
                if(i == j)
                    mp[i][j]=0;
                else
                    mp[i][j]=cal(i,j);
            }
        }
        printf("%d\n",KM());
    }
    return 0;
}
*/
