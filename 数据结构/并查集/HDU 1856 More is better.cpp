#include<cstdio>
#include<algorithm>
using namespace std;
pair<int,int> student[10000005];

void init(){
    for(int i=1;i<=10000004;i++){
        student[i].first=i;
        student[i].second=1;
    }
}

int find(int x){
    if(student[x].first!=x)
        return student[x].first=find(student[x].first);
    else
        return x;
}

void union0(int x,int y){
    int v=find(x);
    int w=find(y);
    if(v!=w){
        student[v].first=w;
        student[w].second+=student[v].second;//父节点的数目要加上子节点的数目
    }
}
int main(){
    int n,m,x,y,ans,num;
    while(scanf("%d",&n)!=EOF){
        if(n==0){
            printf("1\n");
            continue;
        }
        init();
        m=ans=-1;
        while(n--){
            scanf("%d%d",&x,&y);
            union0(x,y);
            if(x>m)
                m=x;
            if(y>m)
                m=y;
        }
        for(int i=1;i<=m;i++){
            if(student[i].second>ans)
                ans=student[i].second;
        }
        printf("%d\n",ans);
    }
    return 0;
}
