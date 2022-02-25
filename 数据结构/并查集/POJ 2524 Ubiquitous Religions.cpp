#include<cstdio>
int student[50010];
void init(int n){
    for(int i=1;i<=n;i++){
        student[i]=i;
    }
}

int find(int x){
    if(student[x]!=x)
        return student[x]=find(student[x]);
    else
        return x;
}

void union0(int x,int y){
    int v=find(x);
    int w=find(y);
    if(v!=w)
        student[v]=w;
}
int main(){
    int n,m,x,y,ans,index=1;
    while(scanf("%d%d",&n,&m)&&n+m){
        init(n);
        ans=0;
        while(m--){
            scanf("%d%d",&x,&y);
            union0(x,y);
        }
        for(int i=1;i<=n;i++){
            if(student[i]==i)
                ans++;
        }
        printf("Case %d: %d\n",index++,ans);
    }
    return 0;
}
