/*
题意:
给出一个文本串s和n个模式串p，求有多少个模式串在正文本串和
反文本串出现过.
n<=250,模式串长度<=1000,文本串长度<=5000000.
说明:实际模式串的长度比1000要大,试过8000才行,这题的数据范围真的有毒.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=3695
思路:AC自动机,只是对于访问过的后缀子串要标记,避免重复遍历,
否则会超时.
*/
//ac 1248ms 对遍历过的后缀子串 进行标记,不会重复遍历
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 250010
#define M 5000010
using namespace std;

int n,tr[N][26],fail[N],wordId[N],cnt,k,ans;
char p[8000],s[M];//这个模式串的长度比1000要大,试过要8000才行.

int newNode(){
    cnt++;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    wordId[cnt]=0;
    return cnt;
}

void insertWord(int id){
    int rt=0,son,len=strlen(p);
    for(int i=0;i<len;i++){
        son=p[i]-'A';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
    wordId[rt]=id;
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

void query(int len){
    int rt=0;
    for(int i=0;i<len;i++){
        rt=tr[rt][s[i]-'A'];
        for(int j=rt;j && wordId[j]!=-1;j=fail[j]){
            if(wordId[j])
            	ans++;
            wordId[j]=-1;//访问过的后缀子串要标记,避免重复遍历
        }
    }
}

int main(){
    int T,num;
    char x;
    scanf("%d",&T);
    while(T--){
        ans=k=0;
        cnt=-1;
        newNode();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%s",p);
            insertWord(i);
        }
        getchar();
        while((x=getchar())!='\n'){
            if(x!='[')
                s[k++]=x;
            else{
                scanf("%d%c",&num,&x);
                //x=getchar();
                while(num--)
                    s[k++]=x;
                getchar();//读']'
            }
        }
        s[k]='\0';
        build();
        query(k);
        reverse(s,s+k);//文本串反转,在反转文本串中查找模式串
        query(k);
        printf("%d\n",ans);
    }
    return 0;
}

/*
//TLE 没有对遍历过的后缀子串进行标记
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 250010
#define M 5000010
using namespace std;

int n,tr[N][26],fail[N],wordId[N],cnt,k,vis[300];
char p[8000],s[M];

int newNode(){
    cnt++;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    wordId[cnt]=0;
    return cnt;
}

void insertWord(int id){
    int rt=0,son,len=strlen(p);
    for(int i=0;i<len;i++){
        son=p[i]-'A';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
    wordId[rt]=id;
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

void query(int len){
    int rt=0;
    for(int i=0;i<len;i++){
        rt=tr[rt][s[i]-'A'];
        for(int j=rt;j;j=fail[j]){
            if(wordId[j]){
                if(!vis[wordId[j]])
                    vis[wordId[j]]=1;
            }
        }
    }
}

int main(){
    int T,num,ans;
    char x;
    scanf("%d",&T);
    while(T--){
        ans=k=0;
        cnt=-1;
        memset(vis,0,sizeof(vis));
        newNode();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%s",p);
            insertWord(i);
        }
        getchar();
        while((x=getchar())!='\n'){
            if(x!='[')
                s[k++]=x;
            else{
                scanf("%d%c",&num,&x);
                //x=getchar();
                while(num--)
                    s[k++]=x;
                getchar();//读']'
            }
        }
        s[k]='\0';
        build();
        query(k);
        reverse(s,s+k);
        query(k);
        for(int i=1;i<=n;i++){
            if(vis[i])
                ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
*/
