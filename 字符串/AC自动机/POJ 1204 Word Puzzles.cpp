/*
����:ժ������
����һ���ַ�������n�����ʣ�Ҫ��n������ȥƥ���������
���ʿ��Գ��־�������λ�ã�����б�ţ����ţ����š�
���ÿ�����ʵ�����ĸ�ھ����е�λ�ã��Լ�����
ģʽ������<=1000
����:http://poj.org/problem?id=1204
˼·:AC�Զ���,ֻ�Ƕ����ı�����Ҫö�ٸ�������8��������Ӵ�,
���԰������л���,�������е���,�ֳ������ʼ����ұ���ʼ��,�ֱ�
��Ӧ3������{��������������} ,{��������������}.
�������е���,�ֳɶ�����ʼ��͵ײ���ʼ��,�ֱ�
��Ӧ3������{���ϡ��ϡ�����} ,{��������������}.
*/
//ac 750ms �Ա������ĺ�׺�Ӵ����
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1000010
#define M 1100
using namespace std;

int dir[8][2]={{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
int l,c,w,tr[N][26],fail[N],wordId[N],cnt,len[M],ans[M][3];
char p[M],mp[M][M];

int newNode(){
    cnt++;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    wordId[cnt]=0;
    return cnt;
}

void insertWord(int id){
    int rt=0,son;
    len[id]=strlen(p);
    for(int i=0;i<len[id];i++){
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

int check(int x,int y){
    if(x>=0 && x<l && y>=0 && y<c)
        return 1;
    return 0;
}

void query(int x,int y,int d){
    int rt=0;
    while(check(x,y)){
        rt=tr[rt][mp[x][y]-'A'];
        for(int i=rt;i && wordId[i]!=-1;i=fail[i]){
            if(wordId[i]){
                ans[wordId[i]][0]=x-dir[d][0]*(len[wordId[i]]-1);//����-1Ҫ����������,��������+1,�п��� x,y�����ǲ����
                ans[wordId[i]][1]=y-dir[d][1]*(len[wordId[i]]-1);
                ans[wordId[i]][2]='A'+d;
            }
            wordId[i]=-1;//�����������ĺ�׺�Ӵ���� ʱ��Ϊ1204ms
        }
        x+=dir[d][0];
        y+=dir[d][1];
    }
}

int main(){
    scanf("%d%d%d",&l,&c,&w);
    for(int i=0;i<l;i++)
        scanf("%s",mp[i]);
    cnt=-1;
    newNode();
    for(int i=1;i<=w;i++){
        scanf("%s",p);
        insertWord(i);
    }
    build();
    for(int i=0;i<l;i++){
        //������ʼ�� ��������������
        query(i,0,1);
        query(i,0,2);
        query(i,0,3);
        //������ʼ�� ��������������
        query(i,c-1,5);
        query(i,c-1,6);
        query(i,c-1,7);
    }
    for(int i=0;i<c;i++){
        //�ж���ʼ�� ���ϡ��ϡ�����
        query(0,i,3);
        query(0,i,4);
        query(0,i,5);
        //�е���ʼ�� ��������������
        query(l-1,i,7);
        query(l-1,i,0);
        query(l-1,i,1);
    }
    for(int i=1;i<=w;i++)
        printf("%d %d %c\n",ans[i][0],ans[i][1],ans[i][2]);
    return 0;
}

/*
//ac 2907ms ֱ���ֵ���dfs����
//ժ�Բ���:https://blog.csdn.net/huyifan1/article/details/84812629
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
char c[1005][1005];
int n,m,w,sx,sy;
int out[1005][3];
char str[1005];
int dx[8]={-1,-1,0,1,1,1,0,-1};
int dy[8]={0,1,1,1,0,-1,-1,-1};
typedef struct Trie
{
    Trie *next[26];
    int v;
    int id;

};
Trie *root;
void createTrie(int num)
{
    Trie *p=root,*q;
    for(int i=0;i<strlen(str);i++)
    {
        int id=str[i]-'A';
        if(p->next[id]==NULL)
        {
           p->next[id]=new Trie();
           p=p->next[id];
        }
        else
        {
            p->next[id]->v++;
            p=p->next[id];
        }
    }
    p->id=num;
}
void dfs(Trie *p,int x,int y,int dir)
{
    if(p==NULL)
    {
        return;
    }
    if(p->id>0)                 //�����ﲻ�ܷ��أ���Ȼ��ֻ������ǰ׺�Ӵ��ͷ����ˣ��޷��ﵽ����ʱ�临�Ӷȵ�Ŀ��
    {
        out[p->id][0]=sx;
        out[p->id][1]=sy;
        out[p->id][2]=dir;
    }
    if(x<0||x>=n||y<0||y>=m)
        return;
   dfs(p->next[c[x][y]-'A'],x+dx[dir],y+dy[dir],dir);   //������ǰ׺�Ӵ������±���

}
int main()
{
    scanf("%d%d%d",&n,&m,&w);
    for(int i=0; i<n; i++)
    {
        getchar();
        for(int j=0; j<m; j++)
        {
            scanf("%c",&c[i][j]);
        }
    }
    root=new Trie();
  for(int i=1;i<=w;i++)
   {
        scanf("%s",str);
        createTrie(i);  //������Ҫ��ѯ���ַ�������һ���ֵ���
   }
    Trie *p=root;
   for(int i=0;i<n;i++)
   {
        for(int j=0;j<m;j++)
        {
            for(int k=0;k<8;k++)
            {
                sx=i;
                sy=j;
                dfs(p,i,j,k);
            }
        }

   }

    for(int i=1;i<=w;i++)
    {
        printf("%d %d %c\n",out[i][0],out[i][1],out[i][2]+'A');
    }
    return 0;
}
*/
