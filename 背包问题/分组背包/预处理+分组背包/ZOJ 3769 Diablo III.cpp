/*
题意:有13种装备,每种装备只能选一个,每种装备有一个伤害值和韧性,
其中如果选Two-Handed的话就不能选Shield和Weapon,Finger可以选两个.
求使得在韧性达最小到m的情况下,伤害总值最大是多少.
链接:https://zoj.pintia.cn/problem-sets/91827364500/problems/91827369730
思路:显然每个装包槽位最多只能放一个同类型的装备,那么同种类型的装备可以分到
一个组中,应用分组背包求解即可,对于Two-Handed(双手)因为与Shield(护盾)和Weapon(武器)
是互斥的,因此可以把武器和护盾单独作为一件双手装备以及把两者合起来组合成一个双手装备
放到同一组中.而finger选择单个戒指就相当于只有一只手戴戒指,把戒指两两组合起来也就相当
于双手都带了戒指,将戒指两两组合的装备再放到finger组中.分组背包时注意:至少要有m韧性,
也就是转移时对于大于m的韧性只能取m作为韧性,求j+t和m的最小值作为转移后的韧性,
这样状态转移方程就是int tp=min(j+k.t,m);dp[i][tp]=max(dp[i][tp],dp[i-1][j]+k.d);
需要注意的是不能用滚动数组优化,因为即使背包容量j降序,当j=m时,j+k.t=tp,tp仍旧是最小值m,
这样再考虑同组内别的装备时,dp[j]=dp[m],这个dp[j]已经放入了第i组的装备,现在又在继续累加
第i组的装备了,因此不能用滚动数组一维数组去做.
*/
//ac 359ms 二维数组实现 不能滚动数组优化
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define M 50010
using namespace std;

int n,m,dp[14][M];
char str[15][20]={"","Shield", "Weapon", "Two-Handed", "Finger","Head", "Shoulder", "Neck", "Torso", "Hand", "Wrist", "Waist", "Legs", "Feet"};
struct Node{
    int d,t;
    Node(int d=0,int t=0):d(d),t(t){}
};
vector<Node> G[14];

int check(char *x){
    for(int i=1;i<=13;i++){
        if(!strcmp(x,str[i]))
           return i;
    }
    return 0;
}

int main(){
    char x[20];
    int T,d,t,id;
    scanf("%d",&T);
    while(T--){
        for(int i=1;i<=13;i++)
            G[i].clear();
        memset(dp,-1,sizeof(dp));
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            scanf("%s%d%d",x,&d,&t);
            id=check(x);
            G[id].push_back(Node(d,t));
        }
        //将Weapon武器放到Two-Handed双手一组中
        for(Node &i : G[2])
            G[3].push_back(i);
        for(Node &i : G[1]){
            //将Shield盾牌放到Two-Handed双手一组中
            G[3].push_back(i);
            for(Node &j : G[2])
                //将Shield与Weapon的组合装备放到Two-Handed双手一组中
                G[3].push_back(Node(i.d+j.d,i.t+j.t));
        }
        int len=G[4].size();
        //将Finger中装备两两组合重新作为一种装备再放到finger中
        for(int i=0;i<len;i++){
            for(int j=i+1;j<len;j++)
                G[4].push_back(Node(G[4][i].d+G[4][j].d,G[4][i].t+G[4][j].t));
        }
        dp[2][0]=0;
        //因为Shield与Weapon都与Two-Handed互斥,所以直接从更新后的Two-Handed装备组开始dp
        for(int i=3;i<=13;i++){
            for(int j=0;j<=m;j++)
                dp[i][j]=dp[i-1][j];
            for(int j=0;j<=m;j++){
                //不加会TLE
                if(dp[i-1][j] == -1) continue;//背包必须保证恰好装满才是合法状态
                for(Node &k : G[i]){
                    /*
                    需要注意的是不能用滚动数组优化,因为即使背包容量j降序,当j=m时,j+k.t=tp,tp仍旧是最小值m,
                    这样再考虑同组内别的装备时,dp[j]=dp[m],这个dp[j]已经放入了第i组的装备,现在又在继续累加
                    第i组的装备了,因此不能用滚动数组一维数组去做.
                    */
                    int tp=min(j+k.t,m);//超过韧性m时,只取m
                    dp[i][tp]=max(dp[i][tp],dp[i-1][j]+k.d);
                }
            }
        }
        printf("%d\n",dp[13][m]);
    }
    return 0;
}
