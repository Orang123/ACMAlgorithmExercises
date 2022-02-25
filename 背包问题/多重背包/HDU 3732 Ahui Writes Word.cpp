/*
题意:有n个单词,每个单词有价值val[i]、复杂度w[i],
问在总复杂度v的限制下能够获得的最大价值.
n<=10^5,v<=10^4.
0<=val[i],w[i]<=10.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=3732
思路:题目是个01背包问题,但是复杂度O(nv)=10^9,显然1s
时限会TLE,但是每个单词的价值和复杂度在[0,10]之间,而
在这个范围下根据乘法原理最多会有10*10=100种不相同的单词,
而现在题目给出的最多有10^5个单词,也就是说会有很多单词
都是相同种类的单词,将相同类型的单词当成同一种单词对待
记录这种单词的数目,问题就转化成了多重背包.最多会有100
种单词,但单词的数目仍然是10^5个,考虑极端情形,10^5个单词
都是同一种单词,则复杂度为=log(10^5)*10^4=1.7*10^5,这样
复杂度就能降低,1s时限就可行.可以根据单词的价值和复杂度
区分是否为同一种单词.
*/
//ac 249ms 01背包转换为 多重背包+完全背包
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 11
#define M 10010
using namespace std;

//kds[i][j]代表单词复杂度为i,价值为j的这种类型单词的数目
int n,v,kds[N][N],dp[M];

int main(){
    int w,val;
    char str[12];
    while(scanf("%d%d",&n,&v)!=EOF){
        memset(kds,0,sizeof(kds));
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++){
            scanf("%s%d%d",str,&val,&w);
            kds[w][val]++;//第i个单词对应的单词种类中单词数目+1
        }
        int tw,tv;
        for(w=0;w<N;w++){
            for(val=0;val<N;val++){
                if(!kds[w][val]) continue;
                if(v-kds[w][val]*w<w){//更宽泛的完全背包判定条件
                    for(int j=w;j<=v;j++)
                        dp[j]=max(dp[j],dp[j-w]+val);
                }
                else{
                    for(int k=1;kds[w][val]>0;k<<=1){
                        kds[w][val]-=k;
                        if(kds[w][val]<0)
                            k+=kds[w][val];
                        tw=k*w;
                        tv=k*val;
                        for(int j=v;j>=tw;j--)
                            dp[j]=max(dp[j],dp[j-tw]+tv);
                    }
                }
            }
        }
        printf("%d\n",dp[v]);
    }
    return 0;
}
