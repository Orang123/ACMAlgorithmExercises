/*
题意:
呃......变形课上Harry碰到了一点小麻烦,因为他并不像Hermione
那样能够记住所有的咒语而随意的将一个棒球变成刺猬什么的,但是
他发现了变形咒语的一个统一规律:如果咒语是以a开头b结尾的一个
单词,那么它的作用就恰好是使A物体变成B物体.Harry已经将他所会
的所有咒语都列成了一个表,他想让你帮忙计算一下他是否能完成老
师的作业,将一个B(ball)变成一个M(Mouse),你知道,如果他自己不
能完成的话,他就只好向Hermione请教,并且被迫听一大堆好好学习的道理.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1181
思路:dfs枚举和之前尾字母拼接的单词,一个剪枝是 对于首尾相同的单词可以去掉.
*/
//ac 15ms dfs
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100
#define INF 0x3f3f3f3f
using namespace std;

int len[N],vis[N],cnt;
char str[N][N];

int dfs(char x){
    if(x == 'm')
        return 1;
    for(int i=0;i<cnt;i++){
        if(!vis[i] && str[i][0] == x){
            vis[i]=1;
            if(dfs(str[i][len[i]-1]))
                return 1;
            vis[i]=0;
        }
    }
    return 0;
}

int main(){
    while(scanf("%s",str[cnt])!=EOF){
        len[cnt]=strlen(str[cnt]);
        if(str[cnt][0] != str[cnt][len[cnt]-1])
            cnt++;
        while(scanf("%s",str[cnt]) && str[cnt][0] !='0'){
            len[cnt]=strlen(str[cnt]);
            if(str[cnt][0] != str[cnt][len[cnt]-1])
                cnt++;
        }
        int flag=0;
        for(int i=0;i<cnt;i++){
            if(str[i][0] == 'b'){
                vis[i]=1;
                if(dfs(str[i][len[i]-1])){
                    printf("Yes.\n");
                    flag=1;
                    break;
                }
                vis[i]=0;
            }
        }
        if(!flag)
            printf("No.\n");
        cnt=0;
        memset(vis,0,sizeof(vis));
    }
    return 0;
}
