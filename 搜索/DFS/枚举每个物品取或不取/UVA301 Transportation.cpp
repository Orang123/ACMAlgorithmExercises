/*
题意:从A到B有若干个车站，编号从0到m，列车的最大载客量是n。
每次列车开车之前，会从各个车站收集订票信息。一共有t条订票信息，
一条订票信息包括：起点站，终点站，人数。票价在数值上等于起点站
与终点之间的车站数（包括终点站，不包括起点站）。由于列车的最大
载客量是一定的，所以不一定能接受所有的订票。对于一条订票order，
只能全部接受，或者是全部拒绝。现在选择接受订票使之利润最大，
输出这个最大利润.

含多个例子，每个例子第一行为三个整数n,m,t,分别代表最大载客量、
除A外的车站数量、订票信息总量。接下去t行为订票信息，每一行代表
一条订票信息，一条订票信息包括三个整数，分别是起点站编号、终点站编号、
人数。以0 0 0结束输入.m<=8,t<=22。
链接:https://www.luogu.com.cn/problem/UVA301
思路:每个订单有两种选择全部接受和全部不接受,复杂度O(2^22)=4194304,可行.
对于接受一个订单后,订单起点到终点站台 车上人数要加上当前订单人数.
对于这个题 其实订单是否按照时间线排序与否并不会影响结果的正确性.因为本身就、
枚举了t个订单选取与否的情况.
*/
//ac 160ms 订单按时间排序
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
    //一个剪枝:如果当前获得利润加上后面所有订单的利润都不能比之前获得的利润大,则结束
    int flag=0;
    for(int i=order[k].st;i<order[k].ed;i++){
        s[i]+=order[k].num;
        if(s[i]>n)
            flag=1;
    }
    if(!flag)//确保车上人数在最大人数载量内
        dfs(k+1,sum+order[k].num*(order[k].ed-order[k].st));//接受订单
    for(int i=order[k].st;i<order[k].ed;i++)
        s[i]-=order[k].num;
    dfs(k+1,sum);//不接受订单
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
//ac 200ms 订单不按时间排序
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
//ac 0ms dfs for循环线性枚举车票的选取
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
//station用来模拟 公交车行驶路上车上的实时人数
int station[9],capacity,ticket_num,max_money;

void DFS(int n,int money){
    //printf("%d\n",money);
    if(money>max_money)
        max_money=money;
    for(int i=n;i<=ticket_num;i++){
        if(max_money>money+ticket0[i].val)//剪枝 如果当前的利润+上后面所有订单的利润都没有之前获得的多，就不进行深度遍历
            return;
        if(station[ticket0[i].start]+ticket0[i].per_num<=capacity){
            for(int j=ticket0[i].start;j<ticket0[i].end0;j++)
                station[j]+=ticket0[i].per_num;
            //printf("n=%d i=%d %d %d\n",n,i,money,ticket0[i].per_num*(ticket0[i].end0-ticket0[i].start));
            DFS(i+1,money+ticket0[i].per_num*(ticket0[i].end0-ticket0[i].start));//注意这里是i+1,因为模拟时公交车永远都在通向终点站
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
        for(int i=ticket_num;i>=1;i--){//这里是为了剪枝
            sum+=ticket0[i].per_num*(ticket0[i].end0-ticket0[i].start);
            ticket0[i].val=sum;
        }
        DFS(1,0);
        printf("%d\n",max_money);
    }
    return 0;
}
*/
