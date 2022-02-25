/*
����:����n��ģʽ��si,��һ���ı���t��
���ж��ٸ���ͬ��ģʽ�����ı�������ֹ���
����ģʽ����ͬ���ҽ������Ǳ�Ų�ͬ��
n<=10^6,|t|<=10^6,��|si|<=10^6.
����:https://www.luogu.com.cn/problem/P3808
˼·:��ģʽ��ƥ������,AC�Զ���,�ѱ������ĺ�׺�Ӵ�Ҫ���,
�����ظ�����.
*/

/*
Aho-Corasick automaton AC�Զ��� ��Alfred Aho ��Margaret Corasick��1975���ڱ���ʵ���ҷ����Ķ�ģʽƥ���㷨
ʵ����AC�Զ�����ͨ��Ԥ������failָ�����չ�������ı����켣��������ʹ��
ƥģʽ��ʱ��ͨ����ǰ���׺��ƥ����ַ���ֱ����ת��ĳ��ģʽ����֧��ǰ׺������ı����ַ����Ǹ����ȥƥ��
   ����ʡ�������´Ӹ��ڵ㿼��ǰ׺�����м�ĳ���Ӵ�ƥ��Ĺ��̣���ʡ��Ҫ�ߵ�·��������Ȼ�����ʱ��硣
failָ����������������ǽ�����trie����ĳ����֧��һ���Ǵ�������һ��ģʽ����,������ת��ĳ���ַ�������·���Ƿ�
�ܳ���ģʽ���������ּ��ı����������ģʽ����

AC�Զ�����kmp�㷨�ıȽ�:
���ڶ�ģʽ����ƥ�����������kmp�㷨,��ôÿ��ģʽ������Ҫ��������next����,n��ģʽ��
����Ҫ���ı���ִ��һ��ƥ��,������ӶȺ�����n*(slen+plen),nΪģʽ���ĸ���
����ֻ��һ��ģʽ�����ı���ƥ��,AC�Զ������ҵ�ʱ�����Ȼ������ʱ���,��kmp�㷨���,
����kmp�ܾ�׼����ģʽ�����ı�����ƥ���λ���±�,��AC�Զ���������trie��Ҫ�ķѾ޴�Ŀռ临�Ӷ�,
��kmp�ռ临�Ӷ������Ե�,trie����C*L,C=26,L������ģʽ�����Ⱥ�.Ҫʵ�ַ���ģʽ�����ı���ƥ���±껹��Ҫ
��¼ģʽ�����ֵ���ǰ׺�ĵ�ǰ����,���Ҫ���ķѿռ�

���AC�Զ����ο�����:
https://oi-wiki.org/string/ac-automaton/
https://www.cnblogs.com/hyfhaha/p/10802604.html
https://blog.csdn.net/bestsort/article/details/82947639

https://blog.csdn.net/mobius_strip/article/details/22549517 (���������ϸ˵�����Ż��Ľ�)
(ʵ��������д�İ汾���ֵ�ͼ�Ż��汾,failָ�뻹������ԭ�ֵ����в����ڵı�,
�������������еĺ�׺�Ӵ���һ����ĸ��û�е�ǰǰ׺����һ����ĸʱ ��ֱ��O(1)����0�Ÿ��ڵ�)
δ�Ż� �ֵ���
setfail()
{
	Q[0] = root;
	root->fail = NULL;
	for ( int move = 0,save = 1 ; move < save ; ++ move ) {//����bfs���
		tnode* now = Q[move];
		for ( int i = 0 ; i < dictsize ; ++ i )
			if ( now->next[i] ) {
			tnode* p = now->fail;//�Ӹ��ڵ��fail�ڵ㿪ʼ
			while ( p && !p->next[i] ) p = p->fail;//Ѱ�ұ��ڵ��fail�ڵ�
			now->next[i]->fail = p?p->next[i]:root;//������fail��ֵΪroot
			Q[save ++] = now->next[i];
		}
	}
}

�Ż��Ľ��ֵ�ͼ
setfail()
{
	Q[0] = root;
	root->fail = NULL;
	for ( int move = 0,save = 1 ; move < save ; ++ move ) {
		tnode* now = Q[move];
		for ( int i = 0 ; i < dictsize ; ++ i )
		if ( now->next[i] ) {
			tnode* p = now->fail;
			while ( p && !p->next[i] ) p = p->fail;
			now->next[i]->fail = p?p->next[i]:root;
			Q[save ++] = now->next[i];
		}else now->next[i] = now!=root?now->fail->next[i]:root;//��ʵֻ������һ��
	}
}
*/
//ac 332ms
#include<cstdio>
#include<cstring>
#include<queue>
#define N 1000000
using namespace std;

//�ֵ�����һά��С �ǰ���ģʽ�������Ӵ��ĳ��Ⱥͼ����,
//��������,ʵ�ʲ����ܳ����������,����ÿ���ַ�
//������ռ��һ�����,ʵ��26��Ӣ����ĸһ������ǰ׺�ظ��Ĳ���.
int trie[N][26];
//faikl[x]=k:�ֵ����б��Ϊx�Ľڵ���ַ���βָ�������׺�Ľڵ�ı��Ϊk(ʵ�ʱ��ģʽ����ǰ׺)
int fail[N];
//cntWord[x]��ʾ���ֵ����б��Ϊx�Ľڵ���ַ���β�ĵ��ʳ��ֵĴ���
//cntΪ�ֵ����ڵ���
int cntWord[N],cnt;
char s[N];

//���뵥�� �����ֵ��� ������ģʽ�ĳ��Ⱥ�ΪL���ı�����Ϊm��ʱ�临�Ӷȵ��ܺ�ΪO(L+m) �ռ临�Ӷ�ΪO(C*L)��
//����CΪʹ�õ��ַ���(26����ĸ)�Ĵ�С�����ڽ���ǰ׺����
void insertWords(){
    int root = 0,next;
    int len = strlen(s);
    for(int i=0; i<len ;i++){
        next=s[i]-'a';
        if(!trie[root][next])
            trie[root][next]=++cnt;
        root=trie[root][next];
    }
    cntWord[root]++;
}

//����failָ��,ͬʱ�����ڵ��ַ���չΪ�ֵ��������ӱ߹����ֵ�ͼ
//����bfsʱ�临�Ӷȡ��ռ临�Ӷ�O(��|s[i]|),|s[i]|ģʽ���ĳ���,�Ǹ����Ը��Ӷ�,
//��Ϊÿ�����ֻ��Դ��ڵ�ģʽ���ַ����,�����ڵı�ֻ����չ���ֵ�ͼ,�������,ʵ����Ϊģʽ�����ڹ���ǰ׺ ���Ӷ�Ҫ�������С
void build(){
    int node;
    queue<int> Q;
    for(int i=0;i<26;i++){
        node=trie[0][i];
        if(node){
            //�ڶ������failָ�붼ָ����ڵ㣬��Ϊ������ĸ���������׺Ϊnull
            fail[node]=0;
            Q.push(node);
        }
    }
    /*
    ��ȡ������ȱ�����ȥ��չfail���ӣ�֮����bfs������Ϊ����չ��һ������fail
    ָ��ʱ����Ҫ��֤ǰ��ĸ��ڵ��failָ���Ѿ������,��ΪҪ�����丸�ڵ��fail
    ȥ���õ�ǰ�ڵ��fail
    */
    while(!Q.empty()){
        node=Q.front();
        Q.pop();
        //��չ26����ĸ�Ķ��ӽ���failָ�������
        for(int i=0;i<26;i++){
            //����ж��Ӿ͹���fail ��ǰ�Ե�i����ĸ��β��ǰ׺�����׺(���ģʽ����ǰ׺)
            if(trie[node][i]){
                //��ǰ����failΪ�丸�׽ڵ��fail����ָ������i��ĸ���Ǹ����ӽ��
                //�����׵����׺��Ϊ����i�ַ�����չΪ��ǰ�������׺��
                fail[trie[node][i]]=trie[fail[node]][i];
                Q.push(trie[node][i]);//��ǰ��չfail��Ľ�������Ϊ��һ�γ���ʱ�ĸ��׽��ȥ��չ����Ķ��ӽ��
            }
            //�����ǽ��ֵ�������Ϊ�ֵ�ͼ,��Щ����û�е�������Ϊ�˷����ı��������ַ���ƥ��,
            //û�к������ַ��Ϳ��ǵ�ǰǰ׺�����׺����һ���ַ��Ƿ��ܼ���ƥ��.
            //����ֱ���������ģʽ��,���ܱ��ģʽ��������ַ�ǡ�õ��ڵ�ǰ�ı������ַ�,Ҳ��
            //���ܱ��ģʽ��ĩβ��û���ı�����ǰ�ַ�,�������ָ���ص�0�Ÿ��ڵ�.
            else
                trie[node][i]=trie[fail[node]][i];
        }
    }
}

//��ģʽ��ƥ����ҵ�ʱ�临�Ӷ�O(��|s[i]|+|S|)
//��|s[i]|������ģʽ�����ַ��ܺ�,|S|���ı������ַ��ܺ�
int query(){
    int now=0,res=0;
    int len=strlen(s);
    for(int i=0;i<len;i++){
        //now�ڵ��ſ��ܻ��ظ�������,�ı����е��Ӵ�����Ϳ������ظ�,ĳ���ڵ�ʧ����ص�0�Ÿ��ڵ�
        now=trie[now][s[i]-'a'];
        /*
        ����now����������ǰ׺�ַ������ܲ���ĳ��ģʽ����,���ǵ�ǰǰ׺�ַ�����
        ��׺�Ӵ�������ģʽ������,����ָ��ĺ����Ķ��fail�������������׺
        (��ʵ�ǵ�ǰǰ׺�Ķ����׺�Ӵ�),���׺�᲻��������Ծ,���ϳ��Ա�Ľ϶�
        ��ģʽ��ǰ׺�Ƿ��п�����ĳ��ģʽ������,������׺��������ģʽ��,
        ����j=fail[j]����Ծ��0�Ÿ��ڵ�.
        */
        //������ǰǰ׺�����к�׺�Ӵ�,ʵ�ʾ���ö���ı������Ӵ���ǰ�ַ�֮ǰ�������Ӵ�,���Ƿ����ҵ�ģʽ������,
        //���������Ǳ�����0�Ÿ��ڵ��ǰ��׺�Ӵ�j֮ǰ�Ѿ�������
        for(int j=now;j && cntWord[j]!=-1;j=fail[j]){//���ÿ�����ϱ���failʱ������failָ������ƶ������Ϊ�����֧�ĳ��� �����ܹ��ۼӲ�ΪO(n)��˵�����һ��ѭ������ΪO(1)����
            //�ۼ�j��β��ģʽ�����ʵ�����
            res+=cntWord[j];
            //��Ҫ���жϹ��ĺ�׺�Ӵ������,��������׺�Ӵ���ģʽ���������ۼӹ��ò����ۼ�,
            //��������׺�Ӵ�����ģʽ������,�Ѿ��жϹ����ǵ�Ҳ�����ظ��ж�.
            cntWord[j]=-1;
        }
    }
    return res;//�����ı����а������ٸ�ģʽ��
}

int main(){
    int n;
    scanf("%d",&n);
    while(n--){
        scanf("%s",s);
        insertWords();
    }
    scanf("%s",s);
    build();
    printf("%d\n",query());
    return 0;
}

/*
//ac 374ms HDU 2222 Keywords Search
//memset��ʼ��trie�� Ϊ0
#include<cstdio>
#include<cstring>
#include<queue>
#define N 1000000
#define M 500010
using namespace std;

int trie[M][26];
int fail[M];
int cntWord[M],cnt;
char s[N];

void insertWords(){
    int root = 0,next;
    int len = strlen(s);
    for(int i=0; i<len ;i++){
        next=s[i]-'a';
        if(!trie[root][next])
            trie[root][next]=++cnt;
        root=trie[root][next];
    }
    cntWord[root]++;
}

void build(){
    int node;
    queue<int> Q;
    for(int i=0;i<26;i++){
        node=trie[0][i];
        if(node){
            fail[node]=0;
            Q.push(node);
        }
    }
    while(!Q.empty()){
        node=Q.front();
        Q.pop();
        for(int i=0;i<26;i++){
            if(trie[node][i]){
                fail[trie[node][i]]=trie[fail[node]][i];
                Q.push(trie[node][i]);
            }
            else
                trie[node][i]=trie[fail[node]][i];
        }
    }
}

int query(){
    int now=0,res=0;
    int len=strlen(s);
    for(int i=0;i<len;i++){
        now=trie[now][s[i]-'a'];
        for(int j=now;j && cntWord[j]!=-1;j=fail[j]){
            res+=cntWord[j];
            cntWord[j]=-1;
        }
    }
    return res;
}

int main(){
    int T,n;
    scanf("%d",&T);
    while(T--){
        memset(trie,0,sizeof(trie));
        memset(cntWord,0,sizeof(cntWord));
        cnt=0;
        scanf("%d",&n);
        while(n--){
            scanf("%s",s);
            insertWords();
        }
        scanf("%s",s);
        build();
        printf("%d\n",query());
    }
    return 0;
}
*/

/*
//ac 234ms HDU 2222 Keywords Search
//trie��ʼ�� ���½ڵ��26�����ӽڵ���Ϊ��
#include<cstdio>
#include<cstring>
#include<queue>
#define N 1000000
#define M 500010
using namespace std;

int trie[M][26];
int fail[M];
int cntWord[M],cnt;
char s[N];

//���½ڵ��26�����ӽڵ���Ϊ��
int newNode(){
    ++cnt;
    for(int i=0;i<26;i++)
        trie[cnt][i]=0;
    cntWord[cnt]=0;
    return cnt;
}

void insertWords(){
    int root = 0,next;
    int len = strlen(s);
    for(int i=0; i<len ;i++){
        next=s[i]-'a';
        if(!trie[root][next])
            trie[root][next]=newNode();
        root=trie[root][next];
    }
    cntWord[root]++;
}

void build(){
    int node;
    queue<int> Q;
    for(int i=0;i<26;i++){
        node=trie[0][i];
        if(node){
            fail[node]=0;
            Q.push(node);
        }
    }
    while(!Q.empty()){
        node=Q.front();
        Q.pop();
        for(int i=0;i<26;i++){
            if(trie[node][i]){
                fail[trie[node][i]]=trie[fail[node]][i];
                Q.push(trie[node][i]);
            }
            else
                trie[node][i]=trie[fail[node]][i];
        }
    }
}

int query(){
    int now=0,res=0;
    int len=strlen(s);
    for(int i=0;i<len;i++){
        now=trie[now][s[i]-'a'];
        for(int j=now;j && cntWord[j]!=-1;j=fail[j]){
            res+=cntWord[j];
            cntWord[j]=-1;
        }
    }
    return res;
}

int main(){
    int T,n;
    scanf("%d",&T);
    while(T--){
        cnt=-1;
        newNode();//0�Ÿ��ڵ� 26����ĸ�Ķ�����Ϊ��
        scanf("%d",&n);
        while(n--){
            scanf("%s",s);
            insertWords();
        }
        scanf("%s",s);
        build();
        printf("%d\n",query());
    }
    return 0;
}
*/

/*
//ac 327ms HDU 2222 Keywords Search
//ָ����ʽ�ṹ fail�ֵ���δ�Ż��汾,�������ֵ�ͼ,ֻ���ֵ������ڵ�ģʽ���ı�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node
{
	int cnt;//�Ƿ�Ϊ�õ��ʵ����һ�����
	Node *fail;//ʧ��ָ��
	Node *next[26];//Trie��ÿ�����ĸ����ڵ�
}*queue[500005];//���У�������BFS����ʧ��ָ��
char s[1000005];//���ַ���
char keyword[55];//��Ҫ���ҵĵ���
Node *root;//ͷ���
void Init(Node *root)//ÿ�����ĳ�ʼ��
{
	root->cnt=0;
	root->fail=NULL;
	for(int i=0;i<26;i++)
		root->next[i]=NULL;
}
void Build_trie(char *keyword)//����Trie��
{
	Node *p,*q;
	int i,v;
	int len=strlen(keyword);
	for(i=0,p=root;i<len;i++)
	{
		v=keyword[i]-'a';
		if(p->next[v]==NULL)
		{
			q=(struct Node *)malloc(sizeof(Node));
			Init(q);
			p->next[v]=q;//�������
		}
		p=p->next[v];//ָ���ƶ�����һ�����
	}
	p->cnt++;//�������һ�����cnt++������һ������
}
void Build_AC_automation(Node *root)
{
	int head=0,tail=0;//����ͷ��βָ��
	queue[head++]=root;//�Ƚ�root���
	while(head!=tail)
	{
		Node *p=NULL;
		Node *temp=queue[tail++];//������ͷ���
		for(int i=0;i<26;i++)
		{
			if(temp->next[i]!=NULL)//�ҵ�ʵ�ʴ��ڵ��ַ����
			{ //temp->next[i] Ϊ�ý�㣬tempΪ�丸���
				if(temp==root)//���ǵ�һ���е��ַ���㣬��Ѹý���ʧ��ָ��ָ��root
					temp->next[i]->fail=root;
				else
				{
					//���λ��ݸýڵ�ĸ��ڵ��ʧ��ָ��ֱ��ĳ�ڵ��next[i]��ýڵ���ͬ��
                	//��Ѹýڵ��ʧ��ָ��ָ���next[i]�ڵ㣻
                	//�����ݵ� root ��û���ҵ�����ýڵ��ʧ��ָ��ָ�� root
					p=temp->fail;//���ý��ĸ�����ʧ��ָ���p
					while(p!=NULL)
					{
						if(p->next[i]!=NULL)
						{
							temp->next[i]->fail=p->next[i];
							break;
						}
						p=p->fail;
					}
					//�øý���ʧ��ָ��Ҳָ��root
					if(p==NULL)
						temp->next[i]->fail=root;
				}
				queue[head++]=temp->next[i];//ÿ����һ����㣬���øý������к����������
			}
		}
	}
}
int query(Node *root)
{ //iΪ����ָ�룬pΪģʽ��ָ��
	int i,v,count=0;
	Node *p=root;
	int len=strlen(s);
	for(i=0;i<len;i++)
	{
		v=s[i]-'a';
		//��ʧ��ָ����ݲ��ң��ж�s[i]�Ƿ������Trie����
		while(p->next[v]==NULL && p!=root)
			p=p->fail;
		p=p->next[v];//�ҵ���pָ��ָ��ý��
		if(p==NULL)//��ָ�뷵��Ϊ�գ���û���ҵ���֮ƥ����ַ�
			p=root;
		Node *temp=p;//ƥ��ý�������ʧ��ָ����ݣ��ж���������Ƿ�ƥ��
		while(temp!=root)//ƥ���������
		{
			if(temp->cnt>=0)//�жϸý���Ƿ񱻷���
			{
				count+=temp->cnt;//����cnt��ʼ��Ϊ 0������ֻ��cnt>0ʱ��ͳ���˵��ʵĸ���
				temp->cnt=-1;//����ѷ��ʹ�
			}
			else//����ѷ��ʣ��˳�ѭ��
				break;
			temp=temp->fail;//���� ʧ��ָ�� ����Ѱ����һ�����������Ľ��
		}
	}
	return count;
}
int main()
{
	int T,n;
	scanf("%d",&T);
	while(T--)
	{
		root=(struct Node *)malloc(sizeof(Node));
		Init(root);
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			scanf("\n%s",keyword);
			Build_trie(keyword);
		}
		Build_AC_automation(root);
		scanf("\n%s",s);
		printf("%d\n",query(root));
	}
	return 0;
}
*/

/*
//ac 280ms �ֵ��� û����չ�ֵ�ͼ,���ǲ�����last����,last[i]��¼���� ���׺��Զ��һ��ģʽ��,������failʧ��ָ����Ծ����
//ժ�Բ���:https://blog.csdn.net/u013480600/article/details/23345221
#include <iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
const int maxnode=500000+100;
const int sigma_size=26;
int ans;
struct AC_Automata
{
    int ch[maxnode][sigma_size];
    int val[maxnode];//���ڱ��浱ǰ���������˼���,����findɨ���ı���ʱ��,ֻҪ�����õ��ʾ�+val[i]����vis[i]=false,ʹ���´�������ģ�岻���ظ�����
    int f[maxnode];
    int last[maxnode];
    bool vis[maxnode];//�ǵ��ʽڵ�vis=0,���ʽڵ�vis=1.�����find�ҵ��˵���i�ڵ�,��ôvis=0.
    int sz;
    void init()
    {
        sz=1;
        memset(ch[0],0,sizeof(ch[0]));
        vis[0]=false;
        last[0]=f[0]=val[0]=0;
    }
    void insert(char *s)
    {
        int n=strlen(s),u=0;
        for(int i=0;i<n;i++)
        {
            int id=s[i]-'a';
            if(ch[u][id]==0)
            {
                vis[sz]=false;
                ch[u][id]=sz;
                memset(ch[sz],0,sizeof(ch[sz]));
                val[sz++]=0;
            }
            u=ch[u][id];
        }
        vis[u]=true;
        val[u]++;
    }
    void print(int i)
    {
        if(val[i])
        {
            if(vis[i])
            {
                ans+=val[i];
                vis[i]=false;
            }
            print(last[i]);
        }
    }
    void find(char *s)
    {
        int n=strlen(s),j=0;
        for(int i=0;i<n;i++)
        {
            int id=s[i]-'a';
            while(j && ch[j][id]==0) j=f[j];
            j=ch[j][id];
            if(val[j]) print(j);
            else if(last[j]) print(last[j]);
        }
    }
    void getFail()
    {
        queue<int> q;
        f[0]=0;
        for(int i=0;i<sigma_size;i++)
        {
            int u=ch[0][i];
            if(u)
            {
                last[u]=f[u]=0;
                q.push(u);
            }
        }
        while(!q.empty())
        {
            int r=q.front();q.pop();
            for(int i=0;i<sigma_size;i++)
            {
                int u=ch[r][i];
                if(!u) continue;
                q.push(u);
                int v=f[r];
                while(v && ch[v][i]==0) v=f[v];
                f[u]=ch[v][i];
                last[u] = val[f[u]]?f[u]:last[f[u]];
            }
        }
    }
};
AC_Automata ac;
const int MAXN=1000000+100;
char text[MAXN],word[100];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        ans=0;
        ac.init();
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%s",word);
            ac.insert(word);
        }
        ac.getFail();
        scanf("%s",text);
        ac.find(text);
        printf("%d\n",ans);
    }
    return 0;
}
*/
