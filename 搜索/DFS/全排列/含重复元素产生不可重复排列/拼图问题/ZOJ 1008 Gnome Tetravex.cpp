/*
题意:将n*n个正方形进行排列，需要判断相邻的正方形的相邻三角形上边的数字是不是都相等。
0<=n<=5.
链接:https://zoj.pintia.cn/problem-sets/91827364500/problems/91827364507
思路:枚举每个正方形放置在n*n图形中的位置,是个排列问题.
只是最多有25个正方形,要注意不能枚举重复排列,因此要判重.
*/
//ac 1624ms 预处理时,将重复正方形放置在同一类别,vis[i]统计第i种正方形的个数
//高效做法,对于特殊位置特判,不需要判断的方位不判断,需要判断的地方才判断
#include<cstdio>
#include<cstring>
int n,num,vis[30],record[30],cnt;
struct Node{
    int top,right,bottom,left;
}node[30],tmp;

int dfs(int k){
    if(k == n*n) return 1;
    int x=k/n,y=k%n;//x-行的下标 y-列的下标
    for(int i=0;i<num;i++){
        if(!vis[i]) continue;
        //如果不是在第一行 那就需要比较当前位置的上侧和上一行该位置处的下侧是否相等
        if(x>0 && node[i].top!=node[record[k-n]].bottom) continue;
        //如果不是在第一列 那就需要比较当前位置的左侧和上一个位置处的右侧是否相等
        if(y>0 && node[i].left!=node[record[k-1]].right) continue;
        vis[i]--;
        record[k]=i;
        if(dfs(k+1)) return 1;
        vis[i]++;
    }
    return 0;
}
int main(){
    while(scanf("%d",&n) && n){
        cnt++;
        memset(vis,0,sizeof(vis));
        num=0;
        for(int i=0,j;i<n*n;i++){
            scanf("%d%d%d%d",&tmp.top,&tmp.right,&tmp.bottom,&tmp.left);
            for(j=0;j<num;j++){
                //和前面的相同,直接将第j中类别的数量+1
                if(node[j].top==tmp.top && node[j].right==tmp.right && node[j].bottom==tmp.bottom && node[j].left==tmp.left){
                    vis[j]++;
                    break;
                }
            }
            if(j == num){//和前面的没有相同的,就把当前的 作为一个新的类别
                node[num]=tmp;
                vis[num++]++;
            }
        }
        if(cnt!=1) printf("\n");
        if(dfs(0)) printf("Game %d: Possible\n",cnt);
        else printf("Game %d: Impossible\n",cnt);
    }
	return 0;
}

/*
//ac 6730ms dfs枚举排列+枚举过程中判重
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 6
using namespace std;

int n,num,vis[N*N],mp[N][N],cnt;

struct Node{
    int str[5];
    bool operator <(const Node &x)const{
        for(int i=0;i<4;i++){
            if(str[i] != x.str[i])
                return str[i]<x.str[i];
        }
        return 1;
    }
}node[N*N];

int check(int x,int y,int i){
    //如果不是在第一列 那就需要比较当前位置的左侧和上一个位置处的右侧是否相等
    if(y>0 && node[i].str[3]!=node[mp[x][y-1]].str[1])
        return 0;
    //如果不是在第一行 那就需要比较当前位置的上侧和上一行该位置处的下侧是否相等
    if(x>0 && node[i].str[0]!=node[mp[x-1][y]].str[2])
        return 0;
    return 1;
}

int cmp(int *tp,int k){
    for(int i=0;i<4;i++){
        if(tp[i] != node[k].str[i])
            return 0;
    }
    return 1;
}

int dfs(int k){
    if(k == num)
        return 1;
    int x=k/n,y=k%n;//x-行的下标 y-列的下标
    int tp[5]={-1,-1,-1,-1};//初始值-1 保证第一次不会重复
    for(int i=0;i<num;i++){
        if(vis[i] || !check(x,y,i) || cmp(tp,i)) continue;
        vis[i]=1;
        mp[x][y]=i;
        memcpy(tp,node[i].str,sizeof(tp));
        if(dfs(k+1)) return 1;
        vis[i]=0;;
    }
    return 0;
}

int main(){
    while(scanf("%d",&n) && n){
        cnt++;
        memset(vis,0,sizeof(vis));
        num=n*n;
        for(int i=0;i<num;i++)
            scanf("%d%d%d%d",&node[i].str[0],&node[i].str[1],&node[i].str[2],&node[i].str[3]);
        sort(node,node+num);
        if(cnt!=1) printf("\n");
        if(dfs(0)) printf("Game %d: Possible\n",cnt);
        else printf("Game %d: Impossible\n",cnt);
    }
	return 0;
}
*/

/*
//ac 2086ms
#include<cstdio>
#include<cstring>

int n,num,vis[30],record[30],cnt;
struct Node{
    int top,right,bottom,left;//top代表小正方形上侧的数字
}node[30],tmp;

int dfs(int k){
    if(k == n*n+1) return 1;
    for(int i=1;i<=num;i++){
        if(!vis[i]) continue;
        if(k==1){//放置第一行第一个小正方形 不需要特判直接放入
            vis[i]--;
            record[k]=i;//记录这个位置放入的小正方形的种类编号,方便后续放置时和前面的进行比较
            if(dfs(k+1)) return 1;//若不满足,则这一位置选择放入别的小正方形
            vis[i]++;
        }
        else if(k<=n){//对于第一行内的小正方形 除过第一个外其余均需要当前的位置的左侧与上一个位置的右侧相等
            if(node[i].left == node[record[k-1]].right){
                vis[i]--;
                record[k]=i;
                if(dfs(k+1)) return 1;
                vis[i]++;
            }
        }
        else if(k%n==1){//对于除第一行外的第一列,需判断当前位置的上侧和上一行该位置处的下侧是否相等
            if(node[i].top == node[record[k-n]].bottom){
                vis[i]--;
                record[k]=i;
                if(dfs(k+1)) return 1;
                vis[i]++;
            }
        }
        else{//对于在中间位置需要判断当前位置的左侧和上一位置的右侧以及当前位置的上侧和上一行当前位置的下侧是否相等
            if(node[i].left == node[record[k-1]].right && node[i].top == node[record[k-n]].bottom){
                vis[i]--;
                record[k]=i;
                if(dfs(k+1)) return 1;
                vis[i]++;
            }
        }
    }
    return 0;
}
int main(){
    while(scanf("%d",&n) && n){
        cnt++;
        memset(vis,0,sizeof(vis));
        num=0;
        for(int i=1,j;i<=n*n;i++){
            scanf("%d%d%d%d",&tmp.top,&tmp.right,&tmp.bottom,&tmp.left);
            for(j=1;j<=num;j++){
                //剪枝 对于相同类型的小正方形(即:上、左、下、右数字均相同)记录为同一类型,可以减少dfs时循环的次数
                if(node[j].top==tmp.top && node[j].right==tmp.right && node[j].bottom==tmp.bottom && node[j].left==tmp.left){
                    vis[j]++;
                    break;
                }
            }
            if(j == num+1){
                node[++num]=tmp;
                vis[num]++;
            }
        }
        if(cnt!=1) printf("\n");
        if(dfs(1)) printf("Game %d: Possible\n",cnt);
        else printf("Game %d: Impossible\n",cnt);
    }
	return 0;
}
*/
