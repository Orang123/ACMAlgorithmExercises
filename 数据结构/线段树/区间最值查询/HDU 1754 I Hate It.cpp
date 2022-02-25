/*
题意:
很多学校流行一种比较的习惯。老师们很喜欢询问，从某某到某某当中，
分数最高的是多少。这让很多学生很反感。
不管你喜不喜欢，现在需要你做的是，就是按照老师的要求，写一个程序，
模拟老师的询问。当然，老师有时候需要更新某位同学的成绩。
本题目包含多组测试，请处理到文件结束。
在每个测试的第一行，有两个正整数 N 和 M ( 0<N<=200000,0<M<5000 )，
分别代表学生的数目和操作的数目。
学生ID编号分别从1编到N。
第二行包含N个整数，代表这N个学生的初始成绩，其中第i个数代表ID为i的学生的成绩。
接下来有M行。每一行有一个字符 C (只取'Q'或'U') ，和两个正整数A，B。
当C为'Q'的时候，表示这是一条询问操作，它询问ID从A到B(包括A,B)的学生当中，成绩最高的是多少。
当C为'U'的时候，表示这是一条更新操作，要求把ID为A的学生的成绩更改为B。
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1754
思路:线段树单点更新区间最值查询.
*/
//ac 702ms 线段树单点更新区间最值查询
#include<cstdio>
#include<algorithm>
#define N 200010
using namespace std;

int sum[N<<2],n,m;

void pushup(int rt){
    sum[rt]=max(sum[rt<<1],sum[rt<<1|1]);
}

void build(int rt,int l,int r){
    if(l == r){
        scanf("%d",&sum[rt]);
        return;
    }
    int mid=(l+r)/2;
    build(rt<<1,l,mid);
    build(rt<<1|1,mid+1,r);
    pushup(rt);
}

void update(int pos,int rt,int l,int r,int c){
    if(l == r){
        sum[rt]=c;
        return;
    }
    int mid=(l+r)/2;
    if(pos<=mid)
        update(pos,rt<<1,l,mid,c);
    else
        update(pos,rt<<1|1,mid+1,r,c);
    pushup(rt);
}

int query(int l,int r,int rt,int curl,int curr){
    if(l<=curl && curr<=r)
        return sum[rt];
    int mid=(curl+curr)/2;
    if(r<=mid)
        return query(l,r,rt<<1,curl,mid);
    else if(l>mid)
        return query(l,r,rt<<1|1,mid+1,curr);
    else
        return max(query(l,r,rt<<1,curl,mid),query(l,r,rt<<1|1,mid+1,curr));
}

int main(){
    char p;
    int a,b;
    while(scanf("%d%d",&n,&m)!=EOF){
        build(1,1,n);
        while(m--){
            scanf(" %c%d%d",&p,&a,&b);
            if(p == 'U')
                update(a,1,1,n,b);
            else
                printf("%d\n",query(a,b,1,1,n));
        }
    }
    return 0;
}
