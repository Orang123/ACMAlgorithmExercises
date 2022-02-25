/*
ͬUVA 1449 Dominating Patterns
����:��N����Сд��ĸ��ɵ�ģʽ���Լ�һ���ı���T��
ÿ��ģʽ�����ܻ����ı����г��ֶ�Ρ�����Ҫ�ҳ���Щ
ģʽ�����ı���T�г��ֵĴ�����ࡣ
��֤������������ͬ��ģʽ����
N<=150,ÿ��ģʽ������<=70.�ı���T����<=10^6.
˵��:һ��ͳ�Ƴ��ִ������ǿ����ص���.
����:https://www.luogu.com.cn/problem/P3796
˼·:��ΪҪͳ��ģʽ�����ֵĴ���,��ô�ڱ����ı�����ǰǰ׺��
��׺�Ӵ�ʱ,��������,ÿ�ζ����Ӻ�׺�Ӵ���ģʽ�����ִ���.
��Ҫ����ֵ����е��ʶ�Ӧģʽ���е�id.��wordId[root]=index;
root���ֵ���һά���,index��ģʽ����������,���Ƚ��������
��������ģʽ������.
*/
//ac 2.74s
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 11000//150*70=10500 �ֵ�����洢�ռ�һά���
#define max_len 1000010
using namespace std;

int trie[N][26];
//wordId��¼�ֵ������ʶ�Ӧģʽ����������
int fail[N],wordId[N],cntWord[N],tot,cnt[160],res;
char s[160][80],str[max_len];

void init(){
    memset(trie,0,sizeof(trie));
    memset(wordId,0,sizeof(wordId));
    memset(cntWord,0,sizeof(cntWord));
    res=tot=0;
}

void insertWords(char *s0,int index){
    int root = 0,next;
    int len = strlen(s0);
    for(int i=0; i<len ;i++){
        next=s0[i]-'a';
        if(!trie[root][next])
            trie[root][next]=++tot;
        root=trie[root][next];
    }
    //��֤������������ͬ��ģʽ����
    wordId[root]=index;//����trie��ʱֻ���ģʽ����Ӧ�Ķ�ά����һά���
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

int solve(){
    int now=0;
    int len=strlen(str);
    for(int i=0;i<len;i++){
        now=trie[now][str[i]-'a'];
        for(int j=now;j;j=fail[j])//������Ϊ�������ñ����ظ�����Ϊ�������Ҫͳ���ظ����ִ�����
            if(wordId[j])//�����ǰ�ڵ����һ��ģʽ�� �����ģʽ�����ִ���+1
                cntWord[j]++;
    }
    for(int i=1;i<=tot;i++){
        if(wordId[i]){
            res=max(cntWord[i],res);//��¼�ı������ִ������Ĵ���
            cnt[wordId[i]]=cntWord[i];//����ӳ�� cnt[ģʽ�����]=ģʽ�����ı������ִ���
        }
    }
    return res;
}

int main(){
    int n;
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++){
            scanf("%s",s[i]);
            insertWords(s[i],i);
        }
        scanf("%s",str);
        build();
        solve();
        printf("%d\n",res);
        for(int i=1;i<=n;i++){
            if(cnt[i] == res)
                printf("%s\n",s[i]);
        }
    }
    return 0;
}

/*
//ac 1.83s ���P3796
//trie��ʼ�� ���½ڵ��26�����ӽڵ���Ϊ��
//ac 70ms UVA 1449 Dominating Patterns
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define N 11000//150*70=10500 �ֵ�����洢�ռ�һά���
#define max_len 1000010
using namespace std;

int trie[N][26];
//wordId��¼�ֵ������ʶ�Ӧģʽ����������
int fail[N],wordId[N],cntWord[N],tot,cnt[160],res;
char s[160][80],str[max_len];

//���½ڵ��26�����ӽڵ���Ϊ��
int newNode(){
    ++tot;
    for(int i=0;i<26;i++)
        trie[tot][i]=0;
    wordId[tot]=0;
    return tot;
}

void init(){
    tot=-1;
    newNode();
    memset(cntWord,0,sizeof(cntWord));
    res=tot=0;
}


void insertWords(char *s0,int index){
    int root = 0,next;
    int len = strlen(s0);
    for(int i=0; i<len ;i++){
        next=s0[i]-'a';
        if(!trie[root][next])
            trie[root][next]=newNode();
        root=trie[root][next];
    }
    //��֤������������ͬ��ģʽ����
    wordId[root]=index;//����trie��ʱֻ���ģʽ����Ӧ�Ķ�ά����һά���
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

int solve(){
    int now=0;
    int len=strlen(str);
    for(int i=0;i<len;i++){
        now=trie[now][str[i]-'a'];
        for(int j=now;j;j=fail[j])//������Ϊ�������ñ����ظ�����Ϊ�������Ҫͳ���ظ����ִ�����
            if(wordId[j])//�����ǰ�ڵ����һ��ģʽ�� �����ģʽ�����ִ���+1
                cntWord[j]++;
    }
    for(int i=1;i<=tot;i++){
        if(wordId[i]){
            res=max(cntWord[i],res);//��¼�ı������ִ������Ĵ���
            cnt[wordId[i]]=cntWord[i];//����ӳ�� cnt[ģʽ�����]=ģʽ�����ı������ִ���
        }
    }
    return res;
}

int main(){
    int n;
    while(scanf("%d",&n) && n){
        init();
        for(int i=1;i<=n;i++){
            scanf("%s",s[i]);
            insertWords(s[i],i);
        }
        scanf("%s",str);
        build();
        solve();
        printf("%d\n",res);
        for(int i=1;i<=n;i++){
            if(cnt[i] == res)
                printf("%s\n",s[i]);
        }
    }
    return 0;
}
*/

/*
//ac 1.33s ����ÿ�ζ��������е�fail��׺�Ӵ�
#include <bits/stdc++.h>
using namespace std;
#define io_speed_up ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define rep(i,a,b) for (int i=a;i<=b;i++)
#define per(i,a,b) for (int i=a;i>=b;i--)
#define ms(a,b)  memset(a,b,sizeof a)
#define sz(x) (int)x.size()
using ll = long long;
const int inf = 0x3f3f3f3f;
const int maxn = 1e5+5;
const int mod = 1e9+7;
int n;
string str[maxn];

struct Trie {
    int nxt[maxn][26];
    int fail[maxn];
    int end[maxn];
    int num[maxn];
    int tot,root;

    int a[maxn],N;
    int newnode() {
        memset(nxt[tot],-1,sizeof nxt[tot]);
        end[tot] = num[tot] = 0;
        return tot++;
    }
    void init() {
        tot = N = 0;
        root = newnode();
    }
    void insert(string &s,int k) {
        int p = root;
        for(int i=0;i<s.size();i++) {
            int x = s[i] - 'a';
            if(nxt[p][x]==-1) nxt[p][x] = newnode();
            p = nxt[p][x];
        }
        end[p] = k;//��¼p�ڵ��Ӧ��ģʽ�����
    }
    void build() {
        queue<int> q;
        fail[root] = root;
        for(int i=0;i<26;i++)
            if(nxt[root][i]==-1) nxt[root][i] = root;
            else fail[nxt[root][i]] = root,q.push(nxt[root][i]);

        while(!q.empty()) {
            int p = q.front(); q.pop();
            a[++N] = p;
            for(int i=0;i<26;i++)
                if(nxt[p][i]==-1)
                    nxt[p][i] = nxt[fail[p]][i];
                else
                    fail[nxt[p][i]] = nxt[fail[p]][i], q.push(nxt[p][i]);
        }
    }
    void solve(string &t) {
        int p = root;
        for(int i=0;i<t.size();i++) {
            p = nxt[p][t[i]-'a'];//p=0 ʵ�ʱ�ʾ�ֵ����� û�е�ǰ�ַ���Ϊ��׺�ĵ���,û�ҵ�ģʽ��ƥ��
            num[p]++;//ֻ��¼�ı�����ǰǰ׺���һ���ڵ���ִ���
        }
        //�����Ƿ��ջ������Ǹ����õ�ǰ���ĳ��ִ����ۼӸ������׺���Ĵ����ĸ���
        //�����Ǵ�ĩβ������Ľϳ���ȥ����ǰ��Ľϳ���׺��
        //ԭ��ǰ׺�����˼���,��Ӧ�����׺Ҳ����ּ���
        for(int i=N;i>=1;i--)//num[0] 0�Ÿ��ڵ���û�����,��ʾû��ģʽ��ƥ��
            num[fail[a[i]]] += num[a[i]];

        int mx = 0;
        //ʵ���ֵ��� 0�Ÿ��ڵ�
        for(int i=1;i<tot;i++) {//1�Žڵ㿪ʼ �ű�ʾ�Ϸ�ģʽ�� ��ƥ�䵽��
            if(end[i] && num[i]>mx) mx = num[i];//ͳ��ģʽ�����ִ���
        }
        vector<int> ans;
        for(int i=1;i<tot;i++) {
            if(end[i] && num[i]==mx) ans.push_back(end[i]);
        }
        sort(ans.begin(),ans.end());//������˳�� ���
        cout<<mx<<"\n";
        for(auto x:ans)
            cout<<str[x]<<"\n";
    }

}ac;
string t;
int main()
{
    io_speed_up;
    while(cin>>n && n) {
        ac.init();
        rep(i,1,n) {
            cin>>str[i];
            ac.insert(str[i],i);
        }
        ac.build();
        cin>>t;
        ac.solve(t);
    }
    return 0;
}
*/
