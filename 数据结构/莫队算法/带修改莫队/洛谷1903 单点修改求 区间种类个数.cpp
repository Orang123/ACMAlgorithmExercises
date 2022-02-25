#include<cstdio>
#include<cmath>
#include<algorithm>
#define N 150000
#define maxn 1000100
using namespace std;
//qnumΪѯ�ʵı��,bnumΪ�޸ļ�¼�ı��
int a[N],pos[N],qnum,bnum,cnt[maxn],ans[N],res;
/*
����ֻ��88��(��������TLE),�ĳɿ�������94��(һ������TLE) �о�������ݿ���ûɶ����,������û�����,�����Ƿݶ�ά����Ĵ���100��
����ͨĪ�ӵĻ����� ����һάʱ��ά��,��ɽ��е����޸�,�����޸Ĳ�֧��,�ɲ����߶���.
����6�ֿ��ܵ�ת�����:[l-1,r,t],[l+1,r,t],[l,r-1,t],[l,r+1,t],[l,r,t-1],[l,r,t+1].
*/

struct seq{
    int l,r,id,t;
    bool operator < (const seq &x)const{//��������ż������Ч�ʽϵ�.
        /*
        ����˵����ڿ鲻ͬ,����˵����,
        �������Ҷ˵����ڿ�,������ͬһ��,���Ҷ˵����,������ʱ�����
        ������������.
        */
        if(pos[l] != pos[x.l]) return l<x.l;
        if(pos[r] != pos[x.r]) return r<x.r;
        return t<x.t;
    }
}q[N];
struct Node{
    int x,y;
}b[N];

void add(int x){
    if(!cnt[x])
        res++;
    cnt[x]++;
}

void sub(int x){
    cnt[x]--;
    if(!cnt[x])
        res--;
}

void change(int t,int i){
    //��Ҫ�޸ĵĵ�����ѯ�ʵ�������,�������res���ܵ�Ӱ��,��Ҫ�޸�
    if(b[t].x>=q[i].l && b[t].x<=q[i].r){
        //�����޸ĵ�λ�û��ʳ��ֵĴ�����1��Ϊ0,�����������1
        if(!--cnt[a[b[t].x]])
            res--;
        //�����޸ĵĻ������޸ĳɵ���ɫ���ֵĴ���������0,���޸ĺ����������1
        if(!cnt[b[t].y]++)
            res++;
    }
    /*
    �����޸ĵ�λ�õĻ�����ɫ��Ҫ�޸ĳɵ���ɫ����,�����´ε�ʱ������ڵ�ǰѯ�ʵ�ʱ���ʱ,
    ���޸Ļ�ԭ,����֮ǰ�޸ĺ����ɫ�ٻ�ԭ��δ�޸�֮ǰ����ɫ,Ҳ��������ѯ������ ���޸ĺ���ɫ����ļ���.
    */
    swap(a[b[t].x],b[t].y);
}
int main(){
    int n,m,siz;
    char c;
    scanf("%d%d",&n,&m);
    siz=pow(n,2.0/3.0);//��Ĵ�СΪn^(2/3),��ĸ���Ϊn^(1/3)
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        pos[i]=(i-1)/siz+1;
    }

    while(m--){
        scanf(" %c",&c);
        if(c == 'Q'){
            qnum++;
            scanf("%d%d",&q[qnum].l,&q[qnum].r);
            q[qnum].id=qnum;
            q[qnum].t=bnum;//���ø�ѯ�ʵ�ʱ���Ϊbnum,bnumΪ0ʱ��û���޸�
        }
        else{
            bnum++;
            scanf("%d%d",&b[bnum].x,&b[bnum].y);
        }
    }
    sort(q+1,q+1+qnum);
    int l=1,r=0,t=0;//t=0 Ĭ�Ͽ�ʼ��û���޸ĵ�
    //����ת��ʱ�临�Ӷ� O(n^(5/3)) =n*n^(2/3)
    for(int i=1;i<=qnum;i++){
        /*
        �������һ��Ҫ�ȼ��������,��ȥ�޸�,������޸�,�ᵼ���޸ĺ����ɫ,�������������ɫ����ʱ,
        ���ֵĴ����ظ�����cnt�����,���Ҵ��޸ĵ���ɫ��֮ǰû����ѯ��������,�����ٳ�-1.
        */
        while(l<q[i].l) sub(a[l++]);
        while(l>q[i].l) add(a[--l]);
        while(r<q[i].r) add(a[++r]);
        while(r>q[i].r) sub(a[r--]);
        //����ǰ��ʱ���С������ѯ������Ӧ��ʱ���,��t+1~q[i].t��Ӧ���޸ļ���
        while(t<q[i].t) change(++t,i);//��t+1��ʼ �޸�
        //���±���q[i]+1~t�ڵ��޸Ļ�ԭ t����Ҳ������ѯ�ʵ�ʱ���,���Ҳ��ԭ
        while(t>q[i].t) change(t--,i);//��t��ʼ�ݼ� �޸�
        ans[q[i].id]=res;
    }
    for(int i=1;i<=qnum;i++)
        printf("%d\n",ans[i]);
    return 0;
}
/*
��� Qiuly�û�
����������ά���������100��
Q[i][0] ��ʾ��i�β�������ĵ�λ��
Q[i][1] ��ʾ��i�β�������λ�õ�������ɫ
Q[i][2] ��ʾ��i�β���Ҫ�ĳɵ���ɫ
ע��,Q[i][1]��֮ǰ�ĸ��Ĳ����п����Ѿ����Ĺ�����������Ҫ��¼��������ڵ�ֵ��
������ά����һ��C��������ʱ��¼ÿ�β����ı仯��ԭ��������Ϊval���飬
��Ȼ�ǲ�����ԭ������������¼��(��Ȼ��Ī��ʱ������).
#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f
#define A printf("A")
#define P(x) printf("V %d V",x);
#define S 1000003
using namespace std;
const int N=15e4+5;
template<typename _Tp>inline void read(_Tp&dig){
    char c;dig=0;
    while(c=getchar(),!isdigit(c));
    while(isdigit(c))dig=dig*10+c-'0',c=getchar();
}
int n,m,Be,c1,c2,ans,C[N],val[N],Ans[N],sum[S],Q[N][3];
struct Node{
	int l,r,c,id;
	bool operator < (const Node a)const {
	    if(l/Be==a.l/Be){
            if(r/Be==a.r/Be)return id<a.id;
            return r<a.r;
        }return l<a.l;
	}
}q[N];char opt[10];
inline void Add(int x){if(!sum[x])ans++;sum[x]++;}
inline void Del(int x){sum[x]--;if(!sum[x])ans--;}
int main(){
    read(n);read(m);Be=pow(n,(double)2/(double)3);
    for(register int i=1;i<=n;++i)read(val[i]),C[i]=val[i];
    for(int i=1,a,b;i<=m;i++)
       if(scanf("%s",opt),read(a),read(b),opt[0]=='Q')
          q[c1].l=a,q[c1].r=b,q[c1].id=c1,q[c1].c=c2,c1++;
       else Q[c2][0]=a,Q[c2][1]=C[a],Q[c2][2]=C[a]=b,c2++;
    sort(q,q+c1),Add(val[1]);int l=1,r=1,lst=0;
    for(register int i=0;i<c1;++i){
    	 for(;lst<q[i].c;lst++){
    		 if(l<=Q[lst][0]&&Q[lst][0]<=r)
    			Del(Q[lst][1]),Add(Q[lst][2]);
    		 val[Q[lst][0]]=Q[lst][2];
    	 }
    	 for(;lst>q[i].c;lst--){
    		 if(l<=Q[lst-1][0]&&Q[lst-1][0]<=r)
    			Del(Q[lst-1][2]),Add(Q[lst-1][1]);
    		 val[Q[lst-1][0]]=Q[lst-1][1];
    	 }
    	 for(++r;r<=q[i].r;r++)Add(val[r]);
         for(--r;r>q[i].r;r--)Del(val[r]);
         for(--l;l>=q[i].l;l--)Add(val[l]);
         for(++l;l<q[i].l;l++)Del(val[l]);
    	 Ans[q[i].id]=ans;
    }for(register int i=0;i<c1;++i)printf("%d\n",Ans[i]);
	return 0;
}
*/
