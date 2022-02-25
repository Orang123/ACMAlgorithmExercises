/*
����:
����n���ı���s��m��ģʽ��p����ÿ���ı����г��ֵ�ģʽ�������ܺ�.
ע��:����������ģʽ�����ִ����ܺ�,�����ǳ����˼���ģʽ��,ͬһ��
ģʽ���ظ�����ҲҪ����.
n,m<=10^5.|s|,|p|<=10^4.����ģʽ�����Ⱥ�<=10^5.
����:https://acm.hdu.edu.cn/showproblem.php?pid=5384
˼·:AC�Զ���,n���ı���ÿ������ѯһ��.
*/
//ac 140ms s[N][M]�����ı���,Ԥ���ռ�̫��,����ܿ�������û����,Ҳ�ǳ���������
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 100010
#define M 10010
using namespace std;

int n,m,tr[N][26],fail[N],wordCnt[N],cnt;
char p[M],s[N][M];//����n*m��10*9,��Ϊ����������ı���,����������ͨ��,������string������ÿ���ı���

int newNode(){
    cnt++;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    wordCnt[cnt]=0;
    return cnt;
}

void insertWord(){
    int rt=0,son,len=strlen(p);
    for(int i=0;i<len;i++){
        son=p[i]-'a';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
    wordCnt[rt]++;
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

int query(int id){
    int rt=0,sum=0,len=strlen(s[id]);
    for(int i=0;i<len;i++){
        rt=tr[rt][s[id][i]-'a'];
        for(int j=rt;j;j=fail[j])
            sum+=wordCnt[j];
    }
    return sum;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cnt=-1;
        newNode();
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%s",s[i]);
        scanf("%d",&m);
        for(int i=1;i<=m;i++){
            scanf("%s",p);
            insertWord();
        }
        build();
        for(int i=1;i<=n;i++)
            printf("%d\n",query(i));
    }
    return 0;
}

/*
//ac 249ms ��string�洢n���ı���,��Ϊstring[100000],����Ԥ����ÿ���ı����ĳ���
//�������ı����ĳ��ȺͲ�����10^5
#include<cstdio>
#include<iostream>
#include<cstring>
#include<queue>
#include<string>
#include<algorithm>
#define N 100010
#define M 10010
using namespace std;

int n,m,tr[N][26],fail[N],wordCnt[N],cnt;
char p[M];
string s[N];

int newNode(){
    cnt++;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    wordCnt[cnt]=0;
    return cnt;
}

void insertWord(){
    int rt=0,son,len=strlen(p);
    for(int i=0;i<len;i++){
        son=p[i]-'a';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
    wordCnt[rt]++;
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

int query(int id){
    int rt=0,sum=0,len=s[id].length();
    for(int i=0;i<len;i++){
        rt=tr[rt][s[id][i]-'a'];
        for(int j=rt;j;j=fail[j])
            sum+=wordCnt[j];
    }
    return sum;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        cnt=-1;
        newNode();
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            cin >> s[i];
        scanf("%d",&m);
        for(int i=1;i<=m;i++){
            scanf("%s",p);
            insertWord();
        }
        build();
        for(int i=1;i<=n;i++)
            printf("%d\n",query(i));
    }
    return 0;
}
*/
