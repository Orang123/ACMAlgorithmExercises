/*
题意:7月17日是Mr.W的生日，ACM-THU为此要制作一个体积为Nπ的M层生日蛋糕，每层都是一个圆柱体。
设从下往上数第i(1 <= i <= M)层蛋糕是半径为Ri, 高度为Hi的圆柱。当i < M时，要求Ri > Ri+1且Hi > Hi+1。
由于要在蛋糕上抹奶油，为尽可能节约经费，我们希望蛋糕外表面（最下一层的下底面除外）的面积Q最小。
令Q = Sπ
请编程对给出的N和M，找出蛋糕的制作方案（适当的Ri和Hi的值），使S最小。
（除Q外，以上所有数据皆为正整数）
n<=10000,m<=20.
链接:http://poj.org/problem?id=1190
思路:dfs.每层蛋糕的半径和高的上界比下面一层少1,
初始最后一层半径最大sqrt(n)高最大为h=n.V=π*r^2*h,r、h分别取极限
3个剪枝:2个前缀和剪枝,1个剩余体积下的最小侧面积剪枝
解析如下.
*/
//ac 47ms
#include<cstdio>
#include<cmath>
#include<algorithm>
#define INF 0x3f3f3f3f
using namespace std;
int n,m,mins[30],minv[30],ans=INF;
//eirc的ppt上还有一些说明 状态第m层i=1开始呈递增,代码r、h下界要做减法求得
void init(){
    mins[0]=0,minv[0]=0;
    for(int i=1;i<=20;i++){
        /*
        mins表示从最上面第1层到i层的最小表面积(这里仅仅算了侧面),
        所有蛋糕上面的面积是相邻两个上侧面积之差.
        最终值相互抵消等于最下层蛋糕的上侧面积πr^2.这里半径和高度每层都只增加1,不计算圆周率
        */
        mins[i]=mins[i-1]+2*i*i;
        minv[i]=minv[i-1]+i*i*i;//minv表示从最上面第1层到i层的最小体积
    }
}
/*
这里对于r、h的枚举一定要从m层逐层向上枚举,并且值从大向小枚举.
只有这样才能和mins minv数组配合进行剪枝
若从第1层向m层向下枚举,r、h值从小向大枚举,无法正常结束,程序的设计上面不太好求出最小侧面积,
因为对于r、h的增长没有确切的上界,首先是耗时的问题,另一个是对于<n和>n分别要做哪些处理,程序逻辑上
有很多不通的地方,也不太好剪枝.自己第一次写的时候是这个错误的思路.
*/
void dfs(int dep,int r,int h,int sumv,int sums){//r、h、sumv、sums分别代表dep+1层的蛋糕的r、h和m层到dep+1层的体积和、侧面积和
    if(!dep){
        if(sumv == n && sums<ans)//当体积刚好是n时,更新最小侧面积
            ans=sums;
        return;//这里不管体积是否达到n,小于n，等于n都回溯,继续枚举每一层的r h,更新最小侧面积
    }
    /*
    剪枝1:
    sums+mins[dep]>ans 之前的m层到dep+1层的表面积和sums
    加上从1层到dep层的最小表面积如果都大于了已经得到的ans,结束
    */
    if(sums+mins[dep]>=ans) return;
    /*
    剪枝2:
    对于体积而言,同剪枝1,当加上上层最小体积时仍旧比n大时,结束.
    */
    if(sumv+minv[dep]>n) return;
    /*
    剪枝3:
    2*(h[1]*r[1]*r[1]+...+ h[dep]*r[dep]*r[dep])/r[dep]<=2*r[1]*h[1]+..+2*r[dep]*h[dep]
    左半段代表对从1层到dep层蛋糕的体积和除以dep层的半径乘以2近似模拟表面积和,根据体积V = πr^2h,侧面积A'=2πrh V/r=A'/2=r*h
    因为1到dep-1层的r都小于r[dep],但是这里除的是r[de]所以比实际的表面积和要小,因为分母比实际分母r大.
    如果这个比实际表面积还小的值也比之前的ans大,则结束.
    */
    if(sums+2*(n-sumv)/r>=ans) return;
    //dep层的r的上界应该为dep+1层半径r-1,下界是dep
    for(int i=r-1;i>=dep;i--){//从大到小枚举r
        //求解高度h的上界,根据体积V=r^2*h,n总体积减去m层到dep+1层的体积和以及1层到dep-1层的体积和,剩下的就是dep层体积,v/r^2=h
        int maxh=min(n-sumv-minv[dep-1]/(i*i),h-1);
        if(dep == m) sums=i*i;//第m层要加上所有1到m层的蛋糕上表面积和,数值上等于第m层的上表面积
        for(int j=maxh;j>=dep;j--){//h的下界是dep 从大到小枚举h
            dfs(dep-1,i,j,sumv+i*i*j,sums+2*i*j);//累积体积和sumv和侧面积和sums,再进行第dep-1层蛋糕的r h选取
        }
    }
}

int main(){
    scanf("%d",&n);
    scanf("%d",&m);
    init();
    dfs(m,sqrt(n),n,0,0);//m层r的上界根据n=r^2*h,h=1时,r(max)=根号n h同理r=1时,h(max)=n
    if(ans !=INF)
        printf("%d\n",ans);
    else
        printf("0\n");
	return 0;
}
/*第一次自己写的,思维上不太好,答案是错的,程序逻辑结果有问题
#include<cstdio>
#include<cstring>
int n,m,maxr,maxs;
//从第1层开始向上到m层开始枚举,r、h也是从小向大枚举
//因为对于r、h的增长没有确切的上界,首先是耗时的问题,另一个是对于<n和>n分别要做哪些处理,程序逻辑上
//有很多不通的地方,也不太好剪枝.自己第一次写的时候是这个错误的思路.这算法也存在很大的问题,这样子第一次求得的侧面积感觉不一定是最小的.
int dfs(int num,int r,int h,int v,int s){
    if(v>n) return -1;
    if(num == m+1){
        if(v == n){
            maxr=r-1;
            maxs=s;
            return 1;
        }
        else if(v<n) return 0;
        else return -1;
    }
    int sta;
    //首先对于下一层层都选择比本层r、h均大1的数,v、s只累计本层r、h的侧面积和体积的值
    sta=dfs(num+1,r+1,h+1,v+r*r*h,s+2*r*h);
    if(sta == 1) return 1;//返回1 说明刚好体积达到了n,因为枚举r、h本身就是小到大枚举的,所以该答案一定是最小值
    else if(!sta){//返回0 说明体积和小于n
        sta=dfs(num,r,h+1,v,s);//在原先r h都比上一层大1的情况下,线性优先递增枚举h,因为增加h对整个整体面积体积的影响时最小的,注意num并不加1,v,s也不增加,因为这是对本层h递增枚举
        if(sta == 1) return 1;
        else if(!sta)//若h较小,线性优先递增枚举r,同理
            dfs(num,r+1,h,v,s);
        else return 0;
    }
    else return -1;
}

int main(){
    scanf("%d",&n);
    scanf("%d",&m);
    if(dfs(1,1,1,0,0)==1)
        printf("%d\n",maxs+maxr*maxr);
    else
        printf("-1\n");
	return 0;
}
*/
