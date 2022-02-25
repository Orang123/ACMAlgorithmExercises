/*
����:
����һ���ı���s��n��ģʽ��p�����ж��ٸ�ģʽ�������ı�����
���ı������ֹ�.
n<=250,ģʽ������<=1000,�ı�������<=5000000.
˵��:ʵ��ģʽ���ĳ��ȱ�1000Ҫ��,�Թ�8000����,��������ݷ�Χ����ж�.
����:https://acm.hdu.edu.cn/showproblem.php?pid=3695
˼·:AC�Զ���,ֻ�Ƕ��ڷ��ʹ��ĺ�׺�Ӵ�Ҫ���,�����ظ�����,
����ᳬʱ.
*/
//ac 1248ms �Ա������ĺ�׺�Ӵ� ���б��,�����ظ�����
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 250010
#define M 5000010
using namespace std;

int n,tr[N][26],fail[N],wordId[N],cnt,k,ans;
char p[8000],s[M];//���ģʽ���ĳ��ȱ�1000Ҫ��,�Թ�Ҫ8000����.

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
            wordId[j]=-1;//���ʹ��ĺ�׺�Ӵ�Ҫ���,�����ظ�����
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
                getchar();//��']'
            }
        }
        s[k]='\0';
        build();
        query(k);
        reverse(s,s+k);//�ı�����ת,�ڷ�ת�ı����в���ģʽ��
        query(k);
        printf("%d\n",ans);
    }
    return 0;
}

/*
//TLE û�жԱ������ĺ�׺�Ӵ����б��
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
                getchar();//��']'
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
