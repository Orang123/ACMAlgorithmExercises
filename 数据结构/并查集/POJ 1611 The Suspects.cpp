#include<cstdio>
int student[30010];
void init(int n){
    for(int i=0;i<=n;i++){
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
    int n,m,x,y,ans,num;
    while(scanf("%d%d",&n,&m)&&n+m){
        init(n);
        ans=0;
        while(m--){
            scanf("%d",&num);
            scanf("%d",&x);
            num--;
            while(num--){
                scanf("%d",&y);
                union0(x,y);
            }
        }
        for(int i=0;i<=n;i++){
            if(find(i)==find(0))//注意这里是拿find(i)判断 因为要找到根节点来判断是否处于同一个连通集内
                ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
