/*
题意:摘自网上
给出一个文本串s和n个模式串p，0代表能重叠，1代表不能重叠，
求每个模版串在文本串中出现的次数。
n<=100000,模式串长度<=6,文本串长度<=100000.
链接:https://zoj.pintia.cn/problem-sets/91827364500/problems/91827367940
思路:AC自动机.对于可以重叠的,正常统计就好,对于不能重叠的,需要
记录上次模式串匹配时文本串的位置,如果上次串的位置加上当前匹配模式串的长度
小于等于当前位置,则说明不重叠.
题目输入的模式串有可能有重复模式串,因此统计时,对于同一模式串,
其重叠和不重叠匹配次数都统计就好.
*/
//ac 533ms
#include<cstdio>
#include<cstring>
#include<queue>
#define N 600010
#define M 100010
#define L 100010
using namespace std;

int n,tr[N][26],fail[N],wordId[N],plen[L],cnt,num[L][2],type[L],record[L],pos[N];
char p[100010][7],s[M];

int newNode(){
    cnt++;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    wordId[cnt]=0;
    pos[cnt]=-1;
    return cnt;
}

int insertWord(int id){
    int rt=0,son,len=strlen(p[id]);
    for(int i=0;i<len;i++){
        son=p[id][i]-'a';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
    if(!wordId[rt])//可能有重复模式串,编号只记录一次
        wordId[rt]=id;
    return wordId[rt];
}

void build(){
    queue<int> Q;
    int node,son;
    for(int i=0;i<26;i++){
        son=tr[0][i];
        if(son){
            fail[son]=0;
            Q.push(son);
        }
    }
    while(!Q.empty()){
        node=Q.front();
        Q.pop();
        for(int i=0;i<26;i++){
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
    int rt=0,len=strlen(s);
    for(int i=0;i<len;i++){
        rt=tr[rt][s[i]-'a'];
        for(int j=rt;j;j=fail[j]){
            if(wordId[j]){
                num[wordId[j]][0]++;//重叠计数
                //上次串的位置加上当前匹配模式串的长度小于等于当前位置,则说明不重叠
                if(i-pos[j]>=plen[wordId[j]]){
                    pos[j]=i;
                    num[wordId[j]][1]++;//不重叠计数
                }
            }
        }
    }
}

int main(){
    for(int cas=1;scanf("%s",s)!=EOF;cas++){
        cnt=-1;
        newNode();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d %s",&type[i],p[i]);
            //可能有重复模式串,因此编号要用record[i]再记录一次,不同record[i]记录的编号可能是相同的
            record[i]=insertWord(i);
            num[i][0]=num[i][1]=0;//num[i][0]记录重叠次数,num[i][1]记录不重叠次数
            plen[record[i]]=strlen(p[i]);//plen记录模式串长度
        }
        build();
        query();
        printf("Case %d\n",cas);
        for(int i=1;i<=n;i++)
            printf("%d\n",num[record[i]][type[i]]);
        printf("\n");
    }
    return 0;
}
