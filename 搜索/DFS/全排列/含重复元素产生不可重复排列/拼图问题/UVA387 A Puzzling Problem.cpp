/*
题意:摘自网上
在二维平面上放不规则木块拼图，问能用所有的拼图
把4×4的平面拼满，注意拼图不能旋转，翻转，而且
所有的拼图都要用到。
木块拼图个数最多16个,因为每个木块最小是1*1的正方形.
链接:https://www.luogu.com.cn/problem/UVA387
思路:相比UVA 798 Tile Puzzle 拼图是标准的矩形,而这题
拼图包含不规则图形.UVA 798矩形拼图的放置只有2种方式,
要么横放要么竖放,因此可以按照dfs(x,y+1)方式枚举在(x,y)
位置上所能放置的所有拼图.但此题因为拼图不规则,就是说在
判断的是否可能(x,y)已经放置过拼图,但是因为当前要放的拼图不规则,
因此实际在判断能放置的合法位置时,当前放置的位本身是'1',虽然已经
放置过别的拼图,但是当前拼图并不占据该位置,但是需要用(x,y)这个
相对位置来确定出拼图如何放置,实际拼图有效位置'1'并不会和当前(x,y)
已放置的拼图冲突.
*/
//ac 30ms dfs枚举每个拼图cur放置的位置,而不是在每个位置枚举可能放置的拼图
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 5
using namespace std;

int n,mp[N][N];
struct A{
    int r,c;
    char a[N][N];
}shape[20];

//判断(x,y)为相对位置能否放置下第k个拼图
int check(int x,int y,int k){
    for(int i=1;i<=shape[k].r;i++){
        for(int j=1;j<=shape[k].c;j++){
            if(shape[k].a[i][j]-'0'){//是1有效位,相对(x,y)位置,实际在mp[x+i-1][y+j-1]位置,减1是因为(x,y)本身占据了一个行列的单元格
                if(x+i-1>4 || y+j-1>4)
                    return 0;
                if(mp[x+i-1][y+j-1])
                    return 0;
            }
        }
    }
    return 1;
}

//将放置过拼图的位置数字 设置为拼图编号或回溯时恢复为0
void update(int x,int y,int k,int val){
    for(int i=1;i<=shape[k].r;i++){
        for(int j=1;j<=shape[k].c;j++){
            if(shape[k].a[i][j]-'0')
                mp[x+i-1][y+j-1]=val;
        }
    }
}

int dfs(int cur){
    if(cur == n+1){//n个拼图放置完毕,判断4*4方格是否全部放满
        for(int i=1;i<=4;i++){
            for(int j=1;j<=4;j++){
                if(!mp[i][j])
                    return 0;
            }
        }
        return 1;
    }
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++){
            //这里无需判断mp[x][y]是否已经放置过拼图,因为当前cur拼图的有效位1 可能并不占据当前(x,y)位置
            if(check(i,j,cur)){
                update(i,j,cur,cur);
                if(dfs(cur+1))
                    return 1;
                update(i,j,cur,0);
            }
        }
    }
    return 0;
}

int main(){
    int flag=0;
    while(scanf("%d",&n) && n){
        memset(mp,0,sizeof(mp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&shape[i].r,&shape[i].c);
            for(int j=1;j<=shape[i].r;j++){
                for(int k=1;k<=shape[i].c;k++)
                    scanf(" %c",&shape[i].a[j][k]);
            }
        }
        if(flag)
            printf("\n");
        if(dfs(1)){
            for(int i=1;i<=4;i++){
                for(int j=1;j<=4;j++)
                    printf("%d",mp[i][j]);
                printf("\n");
            }
        }
        else
            printf("No solution possible\n");
        flag=1;
    }
    return 0;
}

/*
//ac 30ms 下标从0开始
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 4
using namespace std;

int n,mp[N][N];
struct A{
    int r,c;
    char a[N][N];
}shape[20];

int check(int x,int y,int k){
    for(int i=0;i<shape[k].r;i++){
        for(int j=0;j<shape[k].c;j++){
            if(shape[k].a[i][j]-'0'){
                if(x+i>=4 || y+j>=4)
                    return 0;
                if(mp[x+i][y+j])
                    return 0;
            }
        }
    }
    return 1;
}

void update(int x,int y,int k,int val){
    for(int i=0;i<shape[k].r;i++){
        for(int j=0;j<shape[k].c;j++){
            if(shape[k].a[i][j]-'0')
                mp[x+i][y+j]=val;
        }
    }
}

int dfs(int cur){
    if(cur == n+1){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(!mp[i][j])
                    return 0;
            }
        }
        return 1;
    }
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(check(i,j,cur)){
                update(i,j,cur,cur);
                if(dfs(cur+1))
                    return 1;
                update(i,j,cur,0);
            }
        }
    }
    return 0;
}

int main(){
    int flag=0;
    while(scanf("%d",&n) && n){
        memset(mp,0,sizeof(mp));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&shape[i].r,&shape[i].c);
            for(int j=0;j<shape[i].r;j++){
                for(int k=0;k<shape[i].c;k++)
                    scanf(" %c",&shape[i].a[j][k]);
            }
        }
        if(flag)
            printf("\n");
        if(dfs(1)){
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++)
                    printf("%d",mp[i][j]);
                printf("\n");
            }
        }
        else
            printf("No solution possible\n");
        flag=1;
    }
    return 0;
}
*/

/*
//wa 在每个位置枚举所能放置的拼图,这个做法对于(x,y)被占据的情况不会继续往下(x,y+1)判断,会出错
//这个做法样例都能过,但是交上去是wa,不知何原因
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 5//N设置为4 多样例就会错,单样例不会错,不知何原因
using namespace std;

int n,mp[N][N],vis[N];
struct A{
    int r,c;
    char a[N][N];
}shape[20];

int check(int x,int y,int k){
    for(int i=0;i<shape[k].r;i++){
        for(int j=0;j<shape[k].c;j++){
            if(shape[k].a[i][j]-'0'){
                if(x+i>=4 || y+j>=4)
                    return 0;
                if(mp[x+i][y+j])
                    return 0;
            }
        }
    }
    return 1;
}

void update(int x,int y,int k,int val){
    for(int i=0;i<shape[k].r;i++){
        for(int j=0;j<shape[k].c;j++){
            if(shape[k].a[i][j]-'0')
                mp[x+i][y+j]=val;
        }
    }
}

int dfs(int x,int y){
	if(y == 4){
		x++;
		y=0;
	}
	if(x == 4){
		for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if(!mp[i][j])
                    return 0;
            }
        }
        return 1;
	}
    for(int i=1;i<=n;i++){
    	if(!vis[i] && check(x,y,i)){
    		vis[i]=1;
    		update(x,y,i,i);
    		if(dfs(x,y+1))
    			return 1;
    		update(x,y,i,0);
    		vis[i]=0;
		}
	}
	if(dfs(x,y+1))//不考虑(x,y)是否放置过拼图,直接往下接着判断
		return 1;
    return 0;
}

int main(){
    int flag=0;
    while(scanf("%d",&n) && n){
        memset(mp,0,sizeof(mp));
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            scanf("%d%d",&shape[i].r,&shape[i].c);
            for(int j=0;j<shape[i].r;j++){
                for(int k=0;k<shape[i].c;k++)
                    scanf(" %c",&shape[i].a[j][k]);
            }
        }
        if(flag)
            printf("\n");
        if(dfs(0,0)){
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++)
                    printf("%d",mp[i][j]);
                printf("\n");
            }
        }
        else
            printf("No solution possible\n");
        flag=1;
    }
    return 0;
}
*/
