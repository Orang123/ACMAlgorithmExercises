/*
题意:给n个模式串,有m个文本串,对于每个文本串中出现了
哪些模式串,输出对应模式串的编号,再输出有几个文本串中
出现了模式串.
n<=500,模式串长度<=200,m<=1000,文本串长度<=10000.
注意:以上模式串、文本串中的字符都是ASCII码可加字符,因此
字典树分支数为128,题目保证每个模式串都是不同的.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=2896
思路:多模式串多文本串的匹配问题,AC自动机模板题.只是字典树的分支数为
128,并不是26.
*/
//ac 202ms
#include<cstdio>
#include<cstring>
#include<queue>
#define N 10010
#define M 100010
using namespace std;

int n,m,tr[M][128],fail[M],wordId[M],cnt,vis[510];
char p[210],s[N];

int newNode(){
    ++cnt;
    for(int i=0;i<128;i++)
        tr[cnt][i]=0;
    wordId[cnt]=0;
    return cnt;
}

void insertWord(int id){
    int len=strlen(p),rt=0;
    for(int i=0;i<len;i++){
        if(!tr[rt][p[i]])
            tr[rt][p[i]]=newNode();
        rt=tr[rt][p[i]];
    }
    wordId[rt]=id;
}

void build(){
    queue<int> Q;
    int fa,son;
    for(int i=0;i<128;i++){
        son=tr[0][i];
        if(son){
            fail[son]=0;
            Q.push(son);
        }
    }
    while(!Q.empty()){
        fa=Q.front();
        Q.pop();
        for(int i=0;i<128;i++){
            son=tr[fa][i];
            if(son){
                fail[son]=tr[fail[fa]][i];
                Q.push(son);
            }
            else
                tr[fa][i]=tr[fail[fa]][i];
        }
    }
}

int query(){
    int now=0,len=strlen(s),sum=0;
    for(int i=0;i<len;i++){
        now=tr[now][s[i]];
        for(int j=now;j;j=fail[j]){
            if(wordId[j]){//当前后缀子串是模式串
                if(!vis[wordId[j]]){
                    sum++;//出现的模式串种类数+1
                    vis[wordId[j]]=1;//标记这个模式串出现过
                }
            }
        }
        if(sum == 3)//每个网站最多含有3个病毒
            break;
    }
    return sum;
}

int main(){
    int ans;
    ans=0;
    cnt=-1;
    newNode();
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",p);
        insertWord(i);
    }
    build();
    scanf("%d",&m);
    //时间复杂度O(1000*(10000+100000)),实际因为病毒数最多3个,所以复杂度会比较低
    for(int i=1;i<=m;i++){
        scanf("%s",s);
        memset(vis,0,sizeof(vis));
        if(query()){
            ans++;
            printf("web %d:",i);
            for(int j=1;j<=n;j++){
                if(vis[j])
                    printf(" %d",j);
            }
            printf("\n");
        }
    }
    printf("total: %d\n",ans);
    return 0;
}
