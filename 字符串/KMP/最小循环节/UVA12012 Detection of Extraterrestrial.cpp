/*
题意:给定一个字符串，问说子串中，循环次数为k个最大长度为多少。
字符串长度<=1000.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3163
思路:枚举各个子串的起点,求next数组,再枚举每个子串的前缀长度,然后循环判定是否
构成循环节,如果长度j能整除(j-nxt[tp]),说明构成循环节,循环次数为x=j/(j-nxt[tp]),
则更新ans[x]=max(ans[x],j/(j-nxt[tp]));
ans[1]出现次数为1 整个原始整个串作为一个循环节永远是最大长度,无需更新.
ans[x]=j,循环次数为x的循环节对应的最大子串长度为j.

注意j-nxt[j]求得是最短循环节的长度,j/(j-nxt[j])是最多的循环次数.
而j-nxt[tp],nxt[tp]<nxt[j],j-nxt[tp]求得的不是最短循环节,循环节较大,循环次数较少.
*/
//ac 60ms
//ans[x]=j,循环次数为x的循环节对应的最大子串长度为j.
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 1100
using namespace std;

int nxt[N],pplen,ans[N];
char p[N];

void getNext(char *p,int plen){
    int i=-1,j=0;
    nxt[0]=-1;
    while(j<plen){
        if(i == -1 || p[i] == p[j])
            nxt[++j]=++i;
        else
            i=nxt[i];
    }
}

int main(){
    int T,len,tp,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        memset(ans,0,sizeof(ans));
        scanf("%s",p);
        pplen=strlen(p);
        ans[1]=pplen;//循环次数为1,原始串长度是最大的
        //O(10^6)
        for(int i=0;i<pplen;i++){//枚举起点 子串
            len=strlen(p+i);
            getNext(p+i,len);//求p+i开始到末尾的子串nxt数组值
            for(int j=2;j<=len;j++){//枚举子串长度,不同子串
                tp=j;
                while(nxt[tp]){//nxt[tp]不为0,为0时 只有一个循环节 不用更新
                    if(j%(j-nxt[tp]) == 0){//能整除作为循环节
                        int x=j/(j-nxt[tp]);
                        ans[x]=max(ans[x],j);
                    }
                    tp=nxt[tp];
                }
            }
        }
        printf("Case #%d:",cas);
        for(int i=1;i<=pplen;i++)
            printf(" %d",ans[i]);
        printf("\n");
    }
    return 0;
}
