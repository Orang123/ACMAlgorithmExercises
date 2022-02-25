/*注:
这里为什么,x+n,x+2n能表示吃与被吃的关系?
因为题目上说明这n种动物编号为 1-n 使用x+n 以及x+2*n 就 可以保证对应的编号不会在1--n的范围内，也就保证不会影响到无关的动物了。
当然 也可以用 x+3n 以及 x+4n来表示吃与被吃。。不过这样数组就得开的更大了。。*/
#include<cstdio>
int vertex[150010],N;

void init(){
    for(int i=1;i<=150009;i++)
        vertex[i]=i;
}

int find(int x){
    if(vertex[x]!=x)
        return vertex[x]=find(vertex[x]);
    else
        return x;
}

void union0(int x,int y){
    int u=find(x);
    int v=find(y);
    vertex[u]=v;
}

bool judge1(int x,int y){//判断　　ｘ与ｙ是同类　　是否是真话
    if (x>N || y>N || x<=0 ||y<=0) return false;
    if(find(x+N)==find(y)||find(x+2*N)==find(y))//如果　ｘ所吃的东西与ｙ是同类　或　吃ｘ的东西与ｙ是同类，返回０（假话）
        return false;
    return true;
}

bool judge2(int x,int y){//判断　　ｘ吃ｙ　　是否是真话
    if (x>N || y>N || x<=0 ||y<=0 || x==y) return false;//这里 只有样例里有 x==y 但我感觉 不加,下面的判断照样是return false的 而且0 N这样的边界本身也不会有啊
    if(find(x)==find(y)||find(x+2*N)==find(y))//ｘ与ｙ是同类，或，ｙ与吃ｘ的东西是同类，则返回０（是假话）
        return false;
    return true;
}

int main(){
    int K,D,x,y,ans=0;
    init();
    scanf("%d%d",&N,&K);
    while(K--){
        scanf("%d%d%d",&D,&x,&y);
        //这个题目 我们是假定前面说的都是真的 再去否对后面的话，其实也可以假定后面说的是真的 去否定前面说的话，但假话的数目是不会变的
        if(D==1){
            if(judge1(x,y)){
                //要注意同时将三个集合全部重合
                union0(x,y);//将他们所吃的和他们被吃的的都连到一个连通集内,这些x+n x+2n就是 构造出的关系链 根据这个才能判断后面的真假
                union0(x+N,y+N);
                union0(x+2*N,y+2*N);
            }
            else
                ans++;
        }
        else{
            if(judge2(x,y)){
                union0(x+N,y);//ｙ与ｘ吃的东西连接
                union0(x+2*N,y+N);//ｙ吃的东西与吃ｘ的东西连接
                union0(x,y+2*N);//ｘ与吃ｙ的东西连接
            }
            else
                ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
