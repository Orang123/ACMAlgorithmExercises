/*
����:��A��B�����ɸ���վ����Ŵ�0��m���г�������ؿ�����n��
ÿ���г�����֮ǰ����Ӹ�����վ�ռ���Ʊ��Ϣ��һ����t����Ʊ��Ϣ��
һ����Ʊ��Ϣ���������վ���յ�վ��������Ʊ������ֵ�ϵ������վ
���յ�֮��ĳ�վ���������յ�վ�����������վ���������г������
�ؿ�����һ���ģ����Բ�һ���ܽ������еĶ�Ʊ������һ����Ʊorder��
ֻ��ȫ�����ܣ�������ȫ���ܾ�������ѡ����ܶ�Ʊʹ֮�������
�������������.

��������ӣ�ÿ�����ӵ�һ��Ϊ��������n,m,t,�ֱ��������ؿ�����
��A��ĳ�վ��������Ʊ��Ϣ����������ȥt��Ϊ��Ʊ��Ϣ��ÿһ�д���
һ����Ʊ��Ϣ��һ����Ʊ��Ϣ���������������ֱ������վ��š��յ�վ��š�
��������0 0 0��������.m<=8,t<=22��
����:https://www.luogu.com.cn/problem/UVA301
˼·:ÿ������������ѡ��ȫ�����ܺ�ȫ��������,���Ӷ�O(2^22)=4194304,����.
���ڽ���һ��������,������㵽�յ�վ̨ ��������Ҫ���ϵ�ǰ��������.
��������� ��ʵ�����Ƿ���ʱ����������񲢲���Ӱ��������ȷ��.��Ϊ����͡�
ö����t������ѡȡ�������.
*/
//ac 160ms ������ʱ������
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 30
using namespace std;

int n,m,t,s[N],ans;
struct Order{
    int st,ed,num;
    bool operator <(const Order &x)const{
        if(st!=ed)
            return st<x.st;
        else
            return ed<x.ed;
    }
}order[N];

void dfs(int k,int sum){
    if(k == t+1){
        if(sum>ans)
            ans=sum;
        return;
    }
    //һ����֦:�����ǰ���������Ϻ������ж��������󶼲��ܱ�֮ǰ��õ������,�����
    int flag=0;
    for(int i=order[k].st;i<order[k].ed;i++){
        s[i]+=order[k].num;
        if(s[i]>n)
            flag=1;
    }
    if(!flag)//ȷ�������������������������
        dfs(k+1,sum+order[k].num*(order[k].ed-order[k].st));//���ܶ���
    for(int i=order[k].st;i<order[k].ed;i++)
        s[i]-=order[k].num;
    dfs(k+1,sum);//�����ܶ���
}

int main(){
    while(scanf("%d%d%d",&n,&m,&t) && n+m+t){
        ans=0;
        for(int i=1;i<=t;i++)
            scanf("%d%d%d",&order[i].st,&order[i].ed,&order[i].num);
        sort(order+1,order+1+t);
        dfs(1,0);
        printf("%d\n",ans);
    }
    return 0;
}

/*
//ac 200ms ��������ʱ������
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 30
using namespace std;

int n,m,t,s[N],ans;
struct Order{
    int st,ed,num;
}order[N];

void dfs(int k,int sum){
    if(k == t+1){
        if(sum>ans)
            ans=sum;
        return;
    }
    int flag=0;
    for(int i=order[k].st;i<order[k].ed;i++){
        s[i]+=order[k].num;
        if(s[i]>n)
            flag=1;
    }
    if(!flag)
        dfs(k+1,sum+order[k].num*(order[k].ed-order[k].st));
    for(int i=order[k].st;i<order[k].ed;i++)
        s[i]-=order[k].num;
    dfs(k+1,sum);

}

int main(){
    while(scanf("%d%d%d",&n,&m,&t) && n+m+t){
        ans=0;
        for(int i=1;i<=t;i++)
            scanf("%d%d%d",&order[i].st,&order[i].ed,&order[i].num);
        dfs(1,0);
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 0ms dfs forѭ������ö�ٳ�Ʊ��ѡȡ
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct ticket{
    int start;
    int end0;
    int per_num;
    int val;
    bool operator < (const ticket &a)const{
        if(start==a.start)
            return end0<a.end0;
        return start<a.start;
    }
}ticket0[25];
//station����ģ�� ��������ʻ·�ϳ��ϵ�ʵʱ����
int station[9],capacity,ticket_num,max_money;

void DFS(int n,int money){
    //printf("%d\n",money);
    if(money>max_money)
        max_money=money;
    for(int i=n;i<=ticket_num;i++){
        if(max_money>money+ticket0[i].val)//��֦ �����ǰ������+�Ϻ������ж���������û��֮ǰ��õĶ࣬�Ͳ�������ȱ���
            return;
        if(station[ticket0[i].start]+ticket0[i].per_num<=capacity){
            for(int j=ticket0[i].start;j<ticket0[i].end0;j++)
                station[j]+=ticket0[i].per_num;
            //printf("n=%d i=%d %d %d\n",n,i,money,ticket0[i].per_num*(ticket0[i].end0-ticket0[i].start));
            DFS(i+1,money+ticket0[i].per_num*(ticket0[i].end0-ticket0[i].start));//ע��������i+1,��Ϊģ��ʱ��������Զ����ͨ���յ�վ
            for(int j=ticket0[i].start;j<ticket0[i].end0;j++)
                station[j]-=ticket0[i].per_num;
        }
    }
}

int main(){
    int city_num;
    while(scanf("%d%d%d",&capacity,&city_num,&ticket_num)&&capacity||city_num||ticket_num){
        memset(station,0,4*(city_num+1));
        max_money=-1;
        for(int i=1;i<=ticket_num;i++){
            scanf("%d%d%d",&ticket0[i].start,&ticket0[i].end0,&ticket0[i].per_num);
        }
        sort(ticket0+1,ticket0+1+ticket_num);
        int sum=0;
        for(int i=ticket_num;i>=1;i--){//������Ϊ�˼�֦
            sum+=ticket0[i].per_num*(ticket0[i].end0-ticket0[i].start);
            ticket0[i].val=sum;
        }
        DFS(1,0);
        printf("%d\n",max_money);
    }
    return 0;
}
*/
