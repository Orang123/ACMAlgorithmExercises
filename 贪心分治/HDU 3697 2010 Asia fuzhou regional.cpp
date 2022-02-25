#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
/*
贪心+暴力
题意:有n门课程(n<=300),每门课程有个选课的时间段s,e,只能在s之后，在e之前选择该门课程。
每位同学可以选择任意一个开始时间，然后每5分钟有一次选课机会，问每位同学最多可以选多少门课。
因为选择了某个时间点后,只能按照时间点后推5min再选 并且只能选一个,所以不存在那种选哪个不选哪个求解最优的思维,
所以排除暴力回溯.
*/
int n,vis[310];
struct Course{
    int st,ed;
    bool operator <(const Course &x)const{
        if(ed!=x.ed) return ed<x.ed;//若结束时间是否相等排序
        else return st<x.st;
    }
}cors[310];

int main(){
    while(scanf("%d",&n) && n){
        for(int i=1;i<=n;i++)
            scanf("%d%d",&cors[i].st,&cors[i].ed);
        sort(cors+1,cors+1+n);
        int cnt,ans=-1;
        for(int i=0;i<5;i++){//i取值0~4 其实是5个取值区间 0~1、1~2、2~3、3~4、4~5 因为时间是以5为单位前进的以这5个区间开始后面时间点是等效的,因为不知道第一个
            cnt=0;
            memset(vis,0,sizeof(vis));
            for(int k=i;k<cors[n].ed;k+=5){
                for(int j=1;j<=n;j++){
                    if(!vis[j] && k>=cors[j].st && k<cors[j].ed){//k>=cors[j].st代表k在cors[j].st和cors[j].st+1之间
                        vis[j]=1;
                        cnt++;
                        break;//一次时间点只能选择一门课程 时间k+=5 再次判断是否有课程满足情况
                    }
                }
            }
            ans=max(ans,cnt);
        }
        printf("%d\n",ans);
    }
    return 0;
}
