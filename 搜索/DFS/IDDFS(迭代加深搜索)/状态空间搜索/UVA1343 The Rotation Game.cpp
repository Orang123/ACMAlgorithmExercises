/*
����:ժ������
ÿ��������1��2��3��һ��8��1��8��2��8��3.��A~Hһ��8�ֺϷ�������
����A�����A��һ�������ƶ�һ����������ĸ�Ჹ�������档
��ʹ����8����������һ�µ����ٲ��裬Ҫ�������Ĳ������輰
����������������֡�����ж���⣬����ֵ�����С�Ĳ������衣
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4089
˼·:һ��24������,�����ƶ��ķ�ʽ��A~H����,����dfsÿ��ö����8������,
����8������ÿ���ƶ��Ĵ��������޵�,��������dfs�������ö�ٵ�,�����
ĳ��������һֱ�޽��,�����ѭ��,���dfsö����Ҫ����һ�����������
����,����ǰ�������������������ʱ�ͼ�ʱ�˳�,����������Ӳ�������,
������������.
һ����֦��:����ǰ����+�����������ٲ�ͬ�����ָ���(ʵ��������Ҫ�ƶ�����)>��ǰָ��
�Ĳ�������ʱ,����.
*/
//ac 250ms IDA*(iterative deepening A*)  (IDDFS iterative deepening depth-first search)
//ʱ�临�Ӷ�O(8^n)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 24
using namespace std;
/*
24�������ϵ���,������,���.
        A     B
        00    01
        02    03
H 04 05 06 07 08 09 10 C
        11    12
G 13 14 15 16 17 18 19 D
        20    21
        22    23
        F     E
*/
//oper�����ֵ��� ����ö�� ������ߴ�������Ϊ100
char oper[10]="ABCDEFGH",ans[100];
int mp[8][7]={{0,2,6,11,15,20,22},//A 0
              {1,3,8,12,17,21,23},//B 1
              {10,9,8,7,6,5,4},//C 2 ����move������a[mp[k][i]]=a[mp[k][i+1]],��������Ҫ����
              {19,18,17,16,15,14,13},//D 3 ͬ��
              {23,21,17,12,8,3,1},//E 4
              {22,20,15,11,6,2,0},//F 5
              {13,14,15,16,17,18,19},//G 6
              {4,5,6,7,8,9,10}};//H 7
int a[N];
//center�����������±���
int center[8]={6,7,8,11,12,15,16,17};
//rec��8���������� ���������ָ��ķ�����.
int rec[8]={5,4,7,6,1,0,3,2};

void move(int k){
    int tp=a[mp[k][0]];
    for(int i=0;i<6;i++)
        a[mp[k][i]]=a[mp[k][i+1]];
    a[mp[k][6]]=tp;
}

int check(){
    for(int i=0;i<7;i++){
        if(a[center[i]]!=a[center[i+1]])
            return 0;
    }
    return 1;
}

int diff(int val){
    int cnt=0;
    for(int i=0;i<8;i++){
        if(a[center[i]] != val)
            cnt++;
    }
    return cnt;
}

int surplusStep(){//�ж��������� �����������ֶ���1��2��3ʱ�м������ǲ�ͬ��,ȡ��Сֵ ����ʵ�� �������ٲ����Ĵ���
    return min(diff(1),min(diff(2),diff(3)));
}

int dfs(int k,int maxs){
    if(k == maxs){
        if(check())
            return 1;
        else
            return 0;
    }
    //����ǰ����+�����������ٲ�ͬ�����ָ���(ʵ��������Ҫ�ƶ�����)>��ǰָ��
    //�Ĳ�������ʱ,����.
    if(k+surplusStep() > maxs)
        return 0;
    for(int i=0;i<8;i++){
        move(i);
        ans[k]=oper[i];
        if(dfs(k+1,maxs))
            return 1;
        move(rec[i]);//���� �ָ�a�����״̬ i�ķ�������rec[i]
    }
    return 0;
}

int main(){
    while(scanf("%d",&a[0]) && a[0]){
        for(int i=1;i<24;i++)
            scanf("%d",&a[i]);
        if(check()){
            printf("No moves needed\n");
            printf("%d\n",a[6]);
            continue;
        }
        for(int i=1;;i++){
            if(dfs(0,i)){
                for(int j=0;j<i;j++)
                    printf("%c",ans[j]);
                printf("\n%d\n",a[6]);
                break;
            }
        }
    }
    return 0;
}

/*
dfs+���ѿ϶��ᳬʱ,��Ϊ���ת̬�ռ�����,���һֱ����i=0�ķ�����λ,
��һ����ص���ʼ״̬��,�����������в���ʹ���м�8���������,
��������ظ���������ɱ���,��ΪҪ�����������,�ᵼ�����޵ݹ�,���
������IDA������������,��ͨ��dfs��û�н���������,����ѭ��.
*/

/*
//ժ�Բ���:https://www.cnblogs.com/asdfsag/p/10357259.html
//���״̬�ı�ʾ λ����û̫������
//�����Ԥ�ȼٶ�һ��������ȷ�𰸣���ôʣ�µ���������û�������ˣ�����״̬������0��1����ʾ��
//������״̬������С����C(24,8)=735471���ڿɽ��ܷ�Χ���ˡ���ԭ״̬�ֽ��������״̬��һ��
//bfs���ɵõ���ȷ��������������ÿ�����붼��һ��bfs�Ļ���Ȼ��TLE�������Ƿ��ֶ���ÿ�����룬
//���е�״̬��ʾ�ĺ��嶼��һ���ģ���˿���Ԥ�ȶ�ĩ״̬��һ��bfs����¼������״̬��ĩ״̬����̾��룬
//����ÿ����һ�����붼����ֱ��ͨ��bfs���õ�·����
//���״̬��ʾ�ļ��ɲ�̫�����

//ac 310ms bfs+hash����
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N=24+2,inf=0x3f3f3f3f;
const int b[][10]= {
    {0,2,6,11,15,20,22},
    {1,3,8,12,17,21,23},
    {10,9,8,7,6,5,4},
    {19,18,17,16,15,14,13},
    {23,21,17,12,8,3,1},
    {22,20,15,11,6,2,0},
    {13,14,15,16,17,18,19},
    {4,5,6,7,8,9,10},
};
int t[]= {0,0,0,0,0,0,1,1,1,0,0,1,1,0,0,1,1,1,0,0,0,0,0};
void rot(int* c,int x) {
    const int* bb=b[x];
    for(int i=0; i<6; ++i)swap(c[bb[i]],c[bb[i+1]]);
}
void enc(int* c,int& x) {
    x=0;
    for(int i=23; i>=0; --i)x=x<<1|c[i];
}
void dec(int* c,int x) {
    for(int i=0; i<24; ++i)c[i]=0;
    for(int i=0; i<24; ++i)c[i]=x&1,x>>=1;
}
struct Hashmap {
    static const int N=1e6+10;
    static const int mod=1e6+3;
    int hd[mod],nxt[N],tot,key[N],val[N];
    int H(int x) {return (x+233)%mod;}
    void clear() {tot=0; memset(hd,-1,sizeof hd);}
    int count(int x) {
        for(int u=hd[H(x)]; ~u; u=nxt[u])if(key[u]==x)return 1;
        return 0;
    }
    int& operator[](int x) {
        int h=H(x);
        for(int u=hd[h]; ~u; u=nxt[u])if(key[u]==x)return val[u];
        nxt[tot]=hd[h],key[tot]=x,val[tot]=0,hd[h]=tot;
        return val[tot++];
    }
} d;

int c[N],cc[N],s[N],ss,tt,mi,ans;
string str1,str2;

void bfs() {
    d.clear();
    queue<int> q;
    q.push(tt),d[tt]=0;
    while(!q.empty()) {
        int u=q.front();
        q.pop();
        dec(c,u);
        for(int i=0; i<8; ++i) {
            memcpy(cc,c,sizeof c);
            rot(cc,i);
            int v;
            enc(cc,v);
            if(!d.count(v)) {
                d[v]=d[u]+1;
                q.push(v);
            }
        }
    }
}

int input() {
    for(int i=0; i<24; ++i)if(scanf("%d",&s[i])!=1)return 0;
    return 1;
}

int main() {
    enc(t,tt);
    bfs();
    while(input()) {
        mi=inf;
        for(int i=1; i<=3; ++i) {
            for(int j=0; j<24; ++j)c[j]=s[j]==i?1:0;
            int u;
            enc(c,u);
            mi=min(mi,d[u]);
        }
        str1="Z";
        for(int i=1; i<=3; ++i) {
            for(int j=0; j<24; ++j)c[j]=s[j]==i?1:0;
            int u;
            enc(c,u);
            if(d[u]==mi) {
                str2.clear();
                while(u!=tt) {
                    dec(c,u);
                    for(int j=0; j<8; ++j) {
                        memcpy(cc,c,sizeof c);
                        rot(cc,j);
                        int v;
                        enc(cc,v);
                        if(d.count(v)&&d[v]==d[u]-1) {
                            str2.push_back(j+'A');
                            u=v;
                            break;
                        }
                    }
                }
                if(str2<str1)str1=str2,ans=i;
            }
        }
        if(mi==0)printf("No moves needed\n");
        else printf("%s\n",str1.c_str());
        printf("%d\n",ans);
    }
    return 0;
}
*/
