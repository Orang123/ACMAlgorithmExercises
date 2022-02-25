/*
题意:给n个模式串,1个文本串,对于在文本串中出现的模式串,
输出其出现的次数.题目保证n个模式串都是不同的.
n<=1000,模式串长度<=50,文本串长度<=2000000.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=3065
思路:多模式串的匹配问题,AC自动机.
*/
//ac 202ms
#include<cstdio>
#include<cstring>
#include<queue>
#define N 50010
#define M 2000010
using namespace std;

int n,tr[N][128],fail[N],wordId[N],cnt,num[1100];
char p[1100][55],str[M];

int newNode(){
    cnt++;
    for(int i=0;i<128;i++)
        tr[cnt][i]=0;
    wordId[cnt]=0;
    return cnt;
}

void insertWord(int id){
    int rt=0,len=strlen(p[id]);
    for(int i=0;i<len;i++){
        if(!tr[rt][p[id][i]])
            tr[rt][p[id][i]]=newNode();
        rt=tr[rt][p[id][i]];
    }
    wordId[rt]=id;
}

void build(){
    queue<int> Q;
    int node,son;
    for(int i=0;i<128;i++){
        son=tr[0][i];
        if(son){
            fail[son]=0;
            Q.push(son);
        }
    }
    while(!Q.empty()){
        node=Q.front();
        Q.pop();
        for(int i=0;i<128;i++){
            son=tr[node][i];
            if(son){
                fail[son]=tr[fail[node]][i];
                Q.push(son);
            }
            else
                tr[node][i]=tr[fail[node]][i];
        }
    }
}

void query(){
    int rt=0,len=strlen(str);
    for(int i=0;i<len;i++){
        rt=tr[rt][str[i]];
        for(int j=rt;j;j=fail[j]){
            if(wordId[j])//若当前后缀子串是模式串
                num[wordId[j]]++;//则对应模式串数目+1
        }
    }
}

int main(){
    while(scanf("%d",&n)!=EOF){//输入是多样例,单样例会wa
        cnt=-1;
        newNode();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%s",p[i]);
            insertWord(i);
            num[i]=0;
        }
        scanf("%s",str);
        build();
        query();
        for(int i=1;i<=n;i++){
            if(num[i])
                printf("%s: %d\n",p[i],num[i]);
        }
    }
    return 0;
}
