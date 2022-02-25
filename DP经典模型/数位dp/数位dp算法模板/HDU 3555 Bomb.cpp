/*
题意:给一个数字n,范围在1~2^63-1，求1~n之间含有49的数字有多少个。
注意:"49"必须是连续的子串.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=3555
思路:直接暴力判断每一位数字,n最大10^18,1s肯定会TLE.
考虑数位dp.
这里有2个博客讲的比较详细.
https://blog.csdn.net/qq_34374664/article/details/52917231
https://www.cnblogs.com/liuxueyang/archive/2013/04/14/3020032.html
*/
//ac 15ms 记忆化搜索
//dp[k][pre]表示n的数位从k到末尾(从右至左计算数位下标)这部分能构成的所有不超过原始n的数字串满足出现"49"的数字串的个数
//pre == 0表示上一位不是4
//pre == 1表示上一位是4
//pre == 2表示开头到下标为k的串中出现过连续的"49"子串
//空间复杂度O(20*3)=60
//时间复杂度O(10*20*3)=600
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20//2^63-1 对应10^18 最多有19位数 long long 表示
using namespace std;
typedef long long ll;

int len,a[N];
ll n,dp[N][3];

ll dfs(int k,int pre,int limit){
    if(!k)//所有数位的数字确定,pre == 2才说明出现了 "49"串,返回1 表示一个合法的数字串
        return pre == 2;
    /*
    对于的limit=0的情况,该位的数值是取的最大的9去累加的,而对于limit==1的时候,
    最高位已经取得都是最大的了,后面的位就不能取比n本身位还大的数字,这样就超过n了,
    而记忆化dp[k][pre]保存的是limit=0的时候,就是后面的位的数字有可能超过n,
    该位只能取本身该位的数值,直接记忆化返回之前limit=0的情况 会使结果偏大。
    所以要判断，不然就错了。
    */
    //这里的记忆化只对limit == 0即不是最高位的情况记录,因为这样后面的位都是按最大取9来算的,就算多次dfs也可以套用之前记录的dp值
    if(!limit && dp[k][pre]!=-1)//需保证limit=0 即前面的位本身取得并不是最大 后面的数为才能按照取到最大值9来酸
        return dp[k][pre];
    //limit == 1 当前位就只能取到a[k](原始n当前位的数值),否则会超过n,
    //limit == 0 前面位没有按最大取,那当前位就可以取到最大位9,这样也不会超过n
    int last=limit?a[k]:9;
    ll ans=0;
    for(int i=0;i<=last;i++){//最小从0开始取,可以前导0
        //上一位不是4 或 上一位是4 当前位不取9,这两种情况都是不含"49"连续串的,
        //对于下来pre的取值 如果当前位 i == 4,那么取1,否则取0,
        //limit的值 只有当本身为1,且当前位取最大值last limit才是1,其余都是0(即:前面位并没有取到最大)
        if(pre == 0 || (pre ==1 && i != 9))
            ans+=dfs(k-1,i == 4,limit && i == last);//从高位向低位遍历,这样才能保证搜索的数位不超过n
        //这里有2种情况,表示数位串已经出现"49",可以pre 要为2
        //1.pre == 1 && i ==9 即:第一次出现"49"串
        //2.pre == 2,前面数位已经出现过"49"串
        else
            ans+=dfs(k-1,2,limit && i == last);
    }
    //这里实际对于limit ==1的情况,永远都只会最后搜索一遍,实际不加这个判断也是不会影响结果的.
    //如果有多次dfs,而dp数组只初始化一次,后面的dfs会用到前面的dp数值,这里就一定要加上!limit不然结果会错
    //因为最高位的情况last的值取决于当前a[k],而每次的a[k]可能是不同的
    if(!limit)
        dp[k][pre]=ans;
    return ans;
}

int main(){
    int T;
    memset(dp,-1,sizeof(dp));//dp数组多组样例只用初始化一次,后面的dfs对前面的dp值同样重复使用
    scanf("%d",&T);
    while(T--){
        len=0;
        scanf("%lld",&n);
        while(n){
            a[++len]=n%10;
            n/=10;
        }
        //从高位向低位遍历,这样才能保证搜索的数位不超过n
        printf("%lld\n",dfs(len,0,1));
    }
    return 0;
}

/*
//ac 15ms 记忆化搜索 dp三维数组,加上limit
//dp[k][pre][limit]表示n的数位从k到末尾(从右至左计算数位下标)这部分能构成的所有不超过原始n的数字串且高位状态为limit时满足出现"49"的数字串的个数
//limit == 0 表示高位并不是最大,后面位都可以最大取到9
//limit == 1 表示高位是最大,当前位最大只能取a[k].
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20//2^63-1 对应10^18 最多有19位数 long long 表示
using namespace std;
typedef long long ll;

int len,a[N];
ll n,dp[N][3][2];

ll dfs(int k,int pre,int limit){
    if(!k)
        return pre == 2;
    if(!limit && dp[k][pre][limit]!=-1)//多样例记忆化只对limit ==0判断,否则不加limit 每次都要初始化dp值
        return dp[k][pre][limit];
    int last=limit?a[k]:9;
    ll ans=0;
    for(int i=0;i<=last;i++){
        if(pre == 0 || (pre ==1 && i != 9))
            ans+=dfs(k-1,i == 4,limit && i == last);
        else
            ans+=dfs(k-1,2,limit && i == last);
    }
    dp[k][pre][limit]=ans;
    return ans;
}

int main(){
    int T;
    memset(dp,-1,sizeof(dp));
    scanf("%d",&T);
    while(T--){
        len=0;
        scanf("%lld",&n);
        while(n){
            a[++len]=n%10;
            n/=10;
        }
        //从高位向低位遍历,这样才能保证搜索的数位不超过n
        printf("%lld\n",dfs(len,0,1));
    }
    return 0;
}
*/

/*
//ac 15ms 记忆化搜索
//dp[k][pre]表示n的数位从k到末尾这部分能构成的所有不超过原始n的数字串满足不出现"49"的数字串的个数
//pre == 0表示上一位不是4
//pre == 1表示上一位是4
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20
using namespace std;
typedef long long ll;

int len,a[N];
ll n,dp[N][2];

ll dfs(int k,int pre,int limit){
    if(!k)//所有数位都取值完了,就是一个不含"49"的数,返回1
        return 1;
    if(!limit && dp[k][pre]!=-1)
        return dp[k][pre];
    int last=limit?a[k]:9;
    ll ans=0;
    for(int i=0;i<=last;i++){
    	if(pre == 1 && i == 9)//上一位是4,当前位是9 不能搜索
    		continue;
    	ans+=dfs(k-1,i == 4,limit && i == last);
    }
    if(!limit)
        dp[k][pre]=ans;
    return ans;
}

int main(){
    int T;
    ll tp;
    memset(dp,-1,sizeof(dp));
    scanf("%d",&T);
    while(T--){
        len=0;
        scanf("%lld",&n);
        tp=n;
        while(tp){
            a[++len]=tp%10;
            tp/=10;
        }
        //因为dfs会搜索出len位全0的情况,这个数值为0,但实际要统计的数值是1~n之间,所以多减了一个"0",要再加上1
        printf("%lld\n",n-dfs(len,0,1)+1);
    }
    return 0;
}
*/

/*
//ac 15ms 记忆化搜索 ten数组加速dfs
//ten[i]表示10^i
//dp[k][pre]表示n的数位从k到末尾这部分能构成的所有不超过原始n的数字串满足出现"49"的数字串的个数
//pre == 0表示上一位不是4
//pre == 1表示上一位是4
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 20
using namespace std;
typedef long long ll;

int len,a[N];
ll n,dp[N][2],ten[N];

ll dfs(int k,int pre,int limit){
    if(!k)//所有位取完,也没有出现"49"的串情况,返回0
        return 0;
    if(!limit && dp[k][pre]!=-1)
        return dp[k][pre];
    int last=limit?a[k]:9;
    ll ans=0;
    for(int i=0;i<=last;i++){
    	if(pre == 1 && i == 9)
    		//已经出现49
			//1.limit == 1 之前的位都取的是最大位,后面的位不能超过n本身的原始数位,
			//因此所有数字串的个数就是n的下标k-1~1位表示的数串,对ten[k-1]取模可得到
			//但是并不包括k-1~i位全部取0的情况,所以要再加1.
			//2.limit == 0 之前的位本身就不是最大,那k-1~1位就最大都可以取9,那就是所有位都是9+ 所有位都是0,个数为ten[k-1] 10^(k-1)
    		ans+=limit?n%ten[k-1]+1:ten[k-1];
    	else
    		ans+=dfs(k-1,i == 4,limit && i == last);
    }
    if(!limit)
        dp[k][pre]=ans;
    return ans;
}

int main(){
    int T;
    ll tp;
    ten[0]=1;
    for(int i=1;i<=18;i++)
    	ten[i]=ten[i-1]*10;
    memset(dp,-1,sizeof(dp));
    scanf("%d",&T);
    while(T--){
        len=0;
        scanf("%lld",&n);
        tp=n;
        while(tp){
            a[++len]=tp%10;
            tp/=10;
        }
        printf("%lld\n",dfs(len,0,1));
    }
    return 0;
}
*/

/*
//ac 15ms 正向递推
#include<cstdio>
#include<algorithm>
#define N 20
using namespace std;
typedef long long ll;

int a[N];
ll n,dp[N][3],ans;

int main(){
    int T;
    scanf("%d",&T);
    //这里dp时第i位是从右至左从1开始定义的
    //dp[i][0]代表长度为 i 并且不含有49的数字的个数；
　　//dp[i][1]代表长度为 i 并且不含有49，但是最高位是9的数字的个数；
　　//dp[i][2]代表长度为 i 并且含有49的数字的个数。
	//注意dp[i][0]是包含dp[i][1]的,dp[i][0]也会有 含有49，但是最高位是9的数字串
    dp[0][0]=1,dp[0][1]=dp[0][2]=0;//初始状态
    for(int i=1;i<21;i++){
    	//根据乘法原理,不含49 dp[i][0]在上一位dp[i-1][0]基础上 第i位可以取0~9,共十位数字,对于放前导0的 实际表示的就是dp[i-1][0]长度为i-1的这部分直接继承
		//但是对于第i-1位为9也就是dp[i-1][1],第i位取4时,构成了49xxxx,要减去这一种情况
        dp[i][0]=10*dp[i-1][0]-dp[i-1][1];
        //dp[i][1]就是在前i-1位不含49的情况,再在第i位放上9
        dp[i][1]=dp[i-1][0];
        //含49的就是在前i-1位含49的基础上,第i位可以放0~9 共10位数字, 还可以再前i-1位不含49但最高位为9,在第i位放置4,也可以构成新的含49的
        dp[i][2]=10*dp[i-1][2]+dp[i-1][1];//dp[1][2]根据dp[0][2] dp[0][1]结果为0
    }
    while(T--){
       scanf("%lld",&n);
       int len=0;
       //就是为什么要在输入 n 后，要把 n 加1。想了一下特例，比如输入49，按照上面的做法，在第3步，并不会把符合条件的数字加上，
	   //因为4不是严格大于4，最后的执行结果就是0，但是如果加上1之后，n就变成了50，这样第3步恰好可以执行，结果就是正确的了。
	   //但是对于一般的情况，还是不知道为什么要把n加1
       n++;
       while(n){
        	a[++len]=n%10;
            n/=10;
       }
       a[len+1]=0;//避免影响 i == len时,a[i+1] == 4 a[i] == 9的判定
       int flag=0;
       ans=0;
       for(int i=len;i>=1;i--){
       		//这里a[i]表示的实际是0、1、2..a[i]-1的数位,
			//对于取0时,实际就是从右至左计数长度为i-1的含49的数字串
			//对于取1、2、..、a[i]-1时,就是乘法原理和dp[i-1][2]拼凑出长度为i的含49的数字串
			//之所以不取a[i]是因为无法保证,dp[i-][2]中的数字串会含有大于原数n的数字串,而实际上一位i+1的a[i+1]就刚好和第i位的 1、2、..a[i]-1拼凑出长度为i+1的含49的数字串
			//这里是比较玄学的,网上几乎没有解释清楚的
            ans+=a[i]*dp[i-1][2];
            //flag == 1表示前面已经出现过49了,直接和dp[i-1][0]不含49的拼接 构成新的含49的数字串 同样a[i]实际表示的是0、1、2..a[i]-1,为了避免数字串可能比n大
            if(flag) ans+=a[i]*dp[i-1][0];//这里前面计算过cnt了 继续计算并不是重复计算  前面计算的只是0-a[i]-1 往后计算都假定的是前面取了a[i]
            else{//flag == 0,前面没出现49
            	if(a[i]>4)//a[i]>4 则这里可以实际可以取到4,就可以和dp[i-1][1]最高位的9拼凑成49
            		ans+=dp[i-1][1];
			}
            if(a[i+1]==4 && a[i] == 9) flag=1;//i+1位和i位构成了49
       }
       printf("%lld\n",ans);
    }
    return 0;
}
*/

/*
//ac 15ms 正向递推 只需开dp[N][[2] Eric课件上的
#include<cstdio>
#define N 20
typedef long long LL;
LL dp[N][2];

//状态表示
//dp[i][0]表示i位长，含“49”的数的数目
//dp[i][1]表示i位长，不含“49”的数的数目
//状态转移
//dp[i][0] = dp[i-1][0]*10 + dp[i-2][1]
//dp[i][1] = dp[i-1][1]*10 – dp[i-2][1]
//边界条件
//dp[0][1] = 1,dp[1][1] = 10
void init(){
    int i;
    dp[0][1] = 1;
    dp[1][1] = 10;

    for(i=2;i<N;i++){
        dp[i][0] = dp[i-1][0]*10 + dp[i-2][1];
        dp[i][1] = dp[i-1][1]*10 - dp[i-2][1];
    }
}

int main(){
    int i,len,tag,digit[N],cas;
    LL ans,n;

    init();
    scanf("%d",&cas);
    while(cas--){
        scanf("%I64d",&n);
        for(len=0;n;n/=10) digit[len++] = n%10;
        digit[len] = 0;
        ans = 0;
        tag = 0;
        //统计
        //n = 0ak-1…a0
		//第i位可以取1到ai的数码
		//ans += ai * dp[i][0]
		//如果前面已经存在“49”，那么i长的不含49的也需要加入,而第i位可以取1到ai的数码
		//ans += ai *dp[i][1]
		//如果前面没有存在49的数码，且ai > 4,加入dp[i-1][1]
		//ans += dp[i-1][1]
		//判断a[i+1,i]==49,设置出现标志，计算下一个数码
		//如果已经存在49，那么490…0也是解，ans++
        for(i=len-1;i>=0;i--){
            ans += dp[i][0]*digit[i];
            if(tag) ans += dp[i][1]*digit[i];
            else if(digit[i]>4 && i) ans += dp[i-1][1];
            if(digit[i+1]==4 && digit[i]==9) tag = 1;
        }
        //统计举例
        //49
		//4*dp[1][0]+9*dp[0][0]+1 = 1
		//548
		//5*dp[2][0]+dp[1][1]+4*dp[1][0]+8*dp[0][0] = 5*1+10 = 15
		//4910
		//4*dp[3][0]+9*dp[2][0]+dp[1][1]+1*dp[1][0]+dp[1][1]+0*dp[0][0]+1= 4*20+9*1+10+1*0+10+0*0+1 = 110
        printf("%I64d\n",ans+tag);
    }

    return 0;
}
*/
