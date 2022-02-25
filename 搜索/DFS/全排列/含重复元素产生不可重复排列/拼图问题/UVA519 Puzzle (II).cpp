/*
题意:摘自网上
给出n*m个拼图的碎片，要求判断是否能组成一个n*m的矩形，对于碎片，F表示平面，
I表示凹面，O表示凸面，对于矩形，外缘边必须为平F， 矩形内部的边只能是以IO或OI
的形式相连，输入给出的字符串4个字符以顺时针方向分别表示碎片的顶部、右侧、底部、左侧。
现在问这些碎片能否拼出一个满足拼放规则的矩形。
注意:每张拼图碎片尺寸都是相同的,放置时是严格按照顺时针方向的标识的凹凸曹放置的,只有一种放置方式.
0<n,m<=6.
链接:https://www.luogu.com.cn/problem/UVA519
思路:需要枚举n*m的矩形内部每个位置(x,y)可能放置哪些碎片,实际就是枚举矩形内部放置碎片规则
的全排列,只有有一种情况满足拼凑规则就返回.
放置时需要考虑合法配对的情况.
1.在放置时需要考虑的是当前位置(x,y),如果是靠近边缘顶部、底部、左端、右端,则需保证外部边为'F'.
2.如果(x,y)在矩形内部,需要保证其顶部和上一行(x-1,y)的底部满足IO或OI的配对,以及其左端与(x,y-1)的
右端满足IO或OI的配对才行.并且(x,y)底部和右侧不能是'F'平面.

一个剪枝优化是对于当前位置(x,y)如果之前已经放置过相同的碎片,就不再重复放置,因为这样只会求出重复
的排列,因此需要对随便的序列按照字典序进行排序 这样好触发这个剪枝条件.
在枚举全排列之前要保证F平边数目是是周长(n+m)*2,以及IO数目要相等才能配对成功,否则直接输出NO.
*/
//ac 10ms qsort 对二维数组按字典序排序
//不加字典序和对相同位置重复碎片的判重会TLE
//最坏时间复杂度36!,但实际因为有check和重复元素的判定 复杂度并没有那么大
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 40
using namespace std;

int n,m,cnt,Icnt,Ocnt,Fcnt,mp[6][6],vis[N];
char block[N][5];//注意长度至少要定义为5,要保证能放下最后一个'\0'结束符,否则对于相同位置 重复碎片放置 会判断失误导致TLE

int cmp(const void*a, const void*b) {
	return strcmp((char*)a, (char*)b);
}

int check(int x,int y,int i){
    if(!x && block[i][0]!='F')//顶部 必须是平边
        return 0;
    if(x == n-1 && block[i][2]!='F')//底部 必须是平边
        return 0;
    if(x != n-1 && block[i][2] == 'F')//矩形内部 底部不能是平边
        return 0;
    if(!y && block[i][3]!='F')//左端 必须是平边
        return 0;
    if(y == m-1 && block[i][1]!='F')//右端 必须是平边
        return 0;
    if(y != m-1 && block[i][1] == 'F')//矩形内部 右端不能是平边
        return 0;
    if(x>0 && block[i][0]+block[mp[x-1][y]][2]!='I'+'O')//不是顶部 考虑IO或OI配对
        return 0;
    if(y>0 && block[i][3]+block[mp[x][y-1]][1]!='I'+'O')//不是左端 考虑IO或OI配对
        return 0;
    return 1;
}

int dfs(int cur){
    if(cur == cnt)
        return 1;
    int x=cur/m,y=cur%m;
    char tp[5]={0};//这里不初始化 会wa
    for(int i=0;i<cnt;i++){
        if(!vis[i] && strcmp(tp,block[i]) && check(x,y,i)){//strcmp(tp,block[i].str)判断 当前位置(x,y)是否已经重复放置过碎片
            vis[i]=1;
            strcpy(tp,block[i]);
            //memcpy(tp,block[i],sizeof(tp));//ac
            mp[x][y]=i;
            if(dfs(cur+1))
                return 1;
            vis[i]=0;
        }
    }
    return 0;
}

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        memset(vis,0,sizeof(vis));
        cnt=n*m;
        Icnt=Ocnt=Fcnt=0;
        for(int i=0;i<cnt;i++){
            scanf("%s",block[i]);
            for(int j=0;j<4;j++){
                if(block[i][j] == 'I')
                    Icnt++;
                else if(block[i][j] == 'O')
                    Ocnt++;
                else
                    Fcnt++;
            }
        }
        if(Icnt != Ocnt || Fcnt!=(n+m)*2){
            printf("NO\n");
            continue;
        }
        qsort(block, cnt, sizeof(block[0]), cmp);
        if(dfs(0))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

/*
//ac 10ms 用结构体对block字典序排序,注意重载里 必须手写判断函数,不能用strcmp函数否则会re
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 40
using namespace std;

int n,m,cnt,Icnt,Ocnt,Fcnt,mp[6][6],vis[N];
struct Block{
    char str[5];
    bool operator <(const Block & x)const{
        //return strcmp(str,x.str);//这样写会RE
    	for(int i=0;i<4;i++){
    		if(str[i]!=x.str[i])
    			return str[i]<x.str[i];
		}
		return 1;
    }
}block[N];

int check(int x,int y,int i){
    if(!x && block[i].str[0]!='F')//顶部 必须是平边
        return 0;
    if(x == n-1 && block[i].str[2]!='F')//底部 必须是平边
        return 0;
    if(x != n-1 && block[i].str[2] == 'F')//矩形内部 底部不能是平边
        return 0;
    if(!y && block[i].str[3]!='F')//左端 必须是平边
        return 0;
    if(y == m-1 && block[i].str[1]!='F')//右端 必须是平边
        return 0;
    if(y != m-1 && block[i].str[1] == 'F')//矩形内部 右端不能是平边
        return 0;
    if(x>0 && block[i].str[0]+block[mp[x-1][y]].str[2]!='I'+'O')//不是顶部 考虑IO或OI配对
        return 0;
    if(y>0 && block[i].str[3]+block[mp[x][y-1]].str[1]!='I'+'O')//不是左端 考虑IO或OI配对
        return 0;
    return 1;
}

int dfs(int cur){
    if(cur == cnt)
        return 1;
    int x=cur/m,y=cur%m;
    char tp[5]={0};
    for(int i=0;i<cnt;i++){
        if(!vis[i] && strcmp(tp,block[i].str) && check(x,y,i)){//strcmp(tp,block[i].str)判断 当前位置(x,y)是否已经重复放置过碎片
            vis[i]=1;
            //strcpy(tp,block[i].str);//ac
            memcpy(tp,block[i].str,sizeof(tp));//ac
            mp[x][y]=i;
            if(dfs(cur+1))
                return 1;
            vis[i]=0;
        }
    }
    return 0;
}

int main(){
    while(scanf("%d%d",&n,&m) && n+m){
        memset(vis,0,sizeof(vis));
        cnt=n*m;
        Icnt=Ocnt=Fcnt=0;
        for(int i=0;i<cnt;i++){
            scanf("%s",block[i].str);
            for(int j=0;j<4;j++){
                if(block[i].str[j] == 'I')
                    Icnt++;
                else if(block[i].str[j] == 'O')
                    Ocnt++;
                else
                    Fcnt++;
            }
        }
        if(Icnt != Ocnt || Fcnt!=(n+m)*2){
            printf("NO\n");
            continue;
        }
        sort(block,block+cnt);
        if(dfs(0))
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
*/
