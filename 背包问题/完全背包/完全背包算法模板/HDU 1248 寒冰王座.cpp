/*
题意:不死族的巫妖王发工资拉,死亡骑士拿到一张N元的钞票(记住,只有一张钞票),
为了防止自己在战斗中频繁的死掉,他决定给自己买一些道具,于是他来到了地精商店前.
死亡骑士:"我要买道具!"
地精商人:"我们这里有三种道具,血瓶150块一个,魔法药200块一个,无敌药水350块一个.
"死亡骑士:"好的,给我一个血瓶."说完他掏出那张N元的大钞递给地精商人.
地精商人:"我忘了提醒你了,我们这里没有找客人钱的习惯的,多的钱我们都当小费收了的,嘿嘿."
死亡骑士:"......"
死亡骑士想,与其把钱当小费送个他还不如自己多买一点道具,反正以后都要买的,早点买了放在家里也好,
但是要尽量少让他赚小费.现在死亡骑士希望你能帮他计算一下,最少他要给地精商人多少小费.
链接:http://acm.hdu.edu.cn/showproblem.php?pid=1248
思路:完全背包裸题.物品价值和体积分别为150、200、350.背包尽可能多地装,总钱数可能有剩余.
*/
//ac 0ms 完全背包裸题 一维数组 提前dp
#include<bits/stdc++.h>
#define M 10100
using namespace std;
int n,dp[M],val[4]={0,150,200,350};
int main(){
    int T;
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=3;i++)
        for(int j=val[i];j<M;j++)
            dp[j]=max(dp[j],dp[j-val[i]]+val[i]);
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        printf("%d\n",n-dp[n]);//最少要找的钱,即买的东西要尽可能多花钱
    }
    return 0;
}

/*
//ac 0ms 完全背包裸题 一维数组
#include<bits/stdc++.h>
#define M 10100
using namespace std;
int n,dp[M],val[4]={0,150,200,350};
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=3;i++)
            for(int j=val[i];j<=n;j++)
                dp[j]=max(dp[j],dp[j-val[i]]+val[i]);
        printf("%d\n",n-dp[n]);//最少要找的钱,即买的东西要尽可能多花钱
    }
    return 0;
}
*/

/*
//ac 15ms 二维数组
#include<bits/stdc++.h>
#define N 4
#define M 10100
using namespace std;
int n,dp[N][M],val[N]={0,150,200,350};
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=3;i++){
            for(int j=0;j<=n;j++){
                if(j>=val[i])
                    dp[i][j]=max(dp[i-1][j],dp[i][j-val[i]]+val[i]);
                else
                    dp[i][j]=dp[i-1][j];
            }
        }
        printf("%d\n",n-dp[3][n]);//最少要找的钱,即买的东西要尽可能多花钱
    }
    return 0;
}
*/

/*
//ac 15ms 暴力枚举搜索dfs 时间复杂度O(n^(n/min(w[i])))
//不加vis记忆化搜索判重 会tle
#include<bits/stdc++.h>
#define N 4
#define M 10100
using namespace std;

int n,ans,vis[M];

//O(n^(总价钱/min(w[i]))) 这里n为物品种类数,实际当总价钱大于3000时,这个做法复杂度已经很高了.
void dfs(int sum){
    if(sum>n)
        return;
    if(vis[sum])
        return;
    vis[sum]=1;
    if(sum>ans)
        ans=sum;
    //因为每种物品不限制数量,每一件物品都有3种取法 分别是150、200、350
    //O(3^(总价钱/150))
    dfs(sum+150);
    dfs(sum+200);
    dfs(sum+350);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=0;
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        dfs(0);
        printf("%d\n",n-ans);
    }
    return 0;
}
*/

/*
//ac 15ms 暴力枚举3个物品可以买个个数 记录最多能花费的钱
//一个优化无敌药水的价钱(350)正好等于血瓶(150)+魔法药品(200)的价钱
//因此可以只枚举血瓶和魔法药品的价钱,复杂度变成了2重循环,即O((n/w[1])*(n/w[2]))
//这种做法只适用物品种类比较少,如果n较大,实际复杂度是O(num1*num2*..*numn),显然不是个多项式时间
#include<bits/stdc++.h>
#define N 4
using namespace std;

int n,ans,w[4]={0,150,200,350};

int main(){
    int T,num1,num2,num3;
    scanf("%d",&T);
    while(T--){
        ans=0;
        scanf("%d",&n);
        num1=n/w[1];
        num2=n/w[2];
        //num3=n/w[3];
        //for(int i=0;i<=num1;i++){//O(num1*num2*num3)
            //for(int j=0;j<=num2;j++){
                //for(int k=0;k<=num3;k++){
                    //int tp=i*w[1]+j*w[2]+k*w[3];
                    //if(tp<=n && tp>ans)
                        //ans=tp;
                //}
            //}
        //}
        for(int i=0;i<=num1;i++){//O(num1*num2)
            for(int j=0;j<=num2;j++){
                //for(int k=0;k<=num3;k++){
                int tp=i*w[1]+j*w[2];
                if(tp<=n && tp>ans)
                    ans=tp;
                //}
            }
        }
        printf("%d\n",n-ans);
    }
    return 0;
}
*/

/*
//ac 0ms 广度搜索bfs枚举可能的状态点 更新剩下钱的最小金额
//不加vis判重会MLE,自然也会TLE
//每个状态都有n种可能的转移,最坏情况下,每个物品体积为1,最坏时间复杂度 感觉也不是个多项式时间
//这里n=2,比较小 所以可以bfs暴力求解
#include<bits/stdc++.h>
#define N 4
#define M 10100
#define INF 0x3f3f3f3f
using namespace std;

int n,ans,vis[M];

//复杂度是 队列最多能入队的元素个数,按照每种物品价格1元,那么总价钱n元,那么队列中最多有n个元素
//因此时间复杂度是线性时间O(n)
void bfs(){
    queue<int> Q;
    Q.push(n);
    int tp;
    while(!Q.empty()){
        tp=Q.front();
        if(ans>tp)
            ans=tp;
        Q.pop();
        //如果之前枚举过tp-150这种状态 即:vis[tp-150]=1,就不再枚举
        if(tp-150>=0 && !vis[tp-150]){
            Q.push(tp-150);
            vis[tp-150]=1;
        }
        if(tp-200>=0 && !vis[tp-200]){
            Q.push(tp-200);
            vis[tp-200]=1;
        }
        //因为无敌药水350可以由 血瓶150和魔法药200组合而成,因此不必枚举这个状态点
    }
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        memset(vis,0,sizeof(vis));
        scanf("%d",&n);
        ans=n;
        bfs();
        printf("%d\n",ans);
    }
    return 0;
}
*/

/*
//ac 15ms 数学方法 复杂度是常数时间
//两种药品价钱150,200,对于小于150的数直接就是那个数,大于300的都不会超过50,
//所以大于三百直接%50.在这之间的如果判断%200和%150哪个小,哪个小取哪个.
#include<bits/stdc++.h>
using namespace std;

int n,ans;

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        if(n>=150){
            if(n>=300)
                n%=50;
            else{
                if(n%150<n%200)
                    n%=150;
                else
                    n%=200;
            }
        }
        printf("%d\n",n);
    }
    return 0;
}
*/
