#include<cstdio>
#include<cstring>
#define max(i,j) i>j?i:j
//ac 187ms 01背包 背包尽可能多地装,不要求恰好装满
/*
题意:现有一笔经费可以报销一定额度的发票.允许报销的发票类型包括买图书(A类)、文具(B类)、差旅(C类),
要求每张发票的总额不得超过1000元,每张发票上,单项物品的价值不得超过600元.现请你编写程序,
在给出的一堆发票中找出可以报销的、不超过给定额度的最大报销额.
input
测试输入包含若干测试用例.每个测试用例的第1行包含两个正数Q和N,其中Q是给定的报销额度,
(N<=30)是发票张数.随后是N行输入,每行的格式为:
m Type_1:price_1 Type_2:price_2 ... Type_m:price_m
其中正整数m是这张发票上所开物品的件数,Type_i和price_i是第i项物品的种类和价值.
物品种类用一个大写英文字母表示.当N为0时,全部输入结束,相应的结果不要输出.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1864
思路:排除不可报销的发票和不满足条件的发票(同类不能超过600,每张发票不能超过1000,
除了A,B,C之外的发票不能报销),然后统计可报销发票的张数和总额,置初始化dp[0] = 0,
表示都没有报销,外层循环遍历后续的发票,内层循环遍历当前发票之前的发票,
判定如果报销发票满足输入能报销的最大额,就加上.最后遍历一遍DP数组,取最大值便是最优解.
注意:因为报销额度为小数,但是要作为背包的数组下标,所以要乘100,最后结果输出时除以100即可.
*/
int dp[3000005];//这里dp数组的长度也要乘100,否则dp时会数组越界异常
int main(){
    double Q,tmp;
    int N,m,a,b,c,sum[31],q;
    char str;
    bool flag;
    while(scanf("%lf%d",&Q,&N)&&N){
        memset(dp,0,sizeof(dp));
        memset(sum,0,sizeof(sum));
        q=Q*100;//本身有两位小数,因为dp数组长度下标要为int类型的关系,所以乘100
        for(int i=0;i<N;i++){
            scanf("%d",&m);
            a=b=c=0;
            flag=false;
            while(m--){
                scanf(" %c:%lf",&str,&tmp);
                if(str=='A')
                    a+=tmp*100;
                else if(str=='B')
                    b+=tmp*100;
                else if(str=='C')
                    c+=tmp*100;
                else
                    flag=true;//只对A、B、C类物品报销
            }
            sum[i]=a+b+c;
            if(a>60000||b>60000||c>60000||sum[i]>100000||flag){//不符合题目要求的发票要作废不报销
                sum[i]=-1;
            }
        }
        for(int i=0;i<N;i++){
            if(sum[i]!=-1){
                for(int j=q;j>=sum[i];j--){
                    dp[j]=max(dp[j],dp[j-sum[i]]+sum[i]);
                }
            }
        }
        printf("%.2f\n",(double)dp[q]/100);//最后再除100输出原本的最大报销额度
    }
    return 0;
}
