#include<cstdio>
#include<ctype.h>
#include<cmath>
#include<algorithm>
#define N 100100
#define M 2000100
using namespace std;
int st[N][20];//st[i][j]表示从第i个数起向后连续2^j个数中的最大值(包括i这个数)

/*
ST表算法全称Sparse-Table(稀疏表)算法，是由Tarjan提出的一种解决RMQ(Range Minimum/Maximum Query)问题（区间最值）的强力算法。
离线预处理时间复杂度 θ（nlogn），在线查询时间θ（1）
不支持修改操作.它只能处理静态区间最值,不能维护动态的,
也就是说不支持在预处理后对值进行修改.一旦修改,整张表便要重新计算,时间复杂度极高.
*/

//这题需要用到getchar()快速输入 不然m(M<=2000100)条查询数条数 scanf读取太慢
inline int read(){
	int x=0,f=1;char ch=getchar();//f判断正数或负数
	//isdigit() 如果参数是0到9之间的数字字符，函数返回非零值，否则返回零值.
	while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}//这里用来读取正负号 或其它非数字字符
	while (isdigit(ch)){x=x*10+ch-48;ch=getchar();}//累加x的值,getchar用来读取下一个数字或非数字字符(空格或回车),若是数字则正常累加,否则退出循环
	return x*f;
}
//可以理解为区间dp 预处理O(nlog(n))
void init(int n){
    for(int i=1;(1<<i)<=n;i++)//枚举区间的长度 依次以2的倍率倍增 区间的长度永远是偶数 O(log(n))
        for(int j=1;j+(1<<i)-1<=n;j++)//枚举区间的左起始点 不能超过右边界 +-*/优先级高于 移位>><<运算符 O(n)
            /*
            这里依据前面的结果递推以j为起始点在内的2^i次方个数中的最大值,可以将其拆分为2个子区间(已递推)去比较它们之间的最大值去比较,
            分别是[j~j+(1<<i-1)-1]、[j+(1<<i-1)~j+(1<<i)-1]而以各个点为起始点长度为2^(i-1)方长度的区间已经在上一次循环中计算出来
            */
            st[j][i]=max(st[j][i-1],st[j+(1<<i-1)][i-1]);//+-*/优先级高于 移位>><<运算符 O(n)
}

//O(1) 回答每个询问 lg数组优化才是理想化的O(1)  log2函数和while(1<<(k+1)<len) 都是有一定时间界的
int query(int l,int r){
    /*
    这里所取的k 2^k都>=len/2,对于区间长度为偶数的情况,2^k=len,
    st[l][k],st[r-(1<<k)+1][k] 刚好为st[l][log2(len)] 2个子区间都是[l,r]
    */
    //int k=log2(r-l+1);
    int len=r-l+1;//计算区间长度
    int k=0;
    /*
    判断要覆盖整个区间,所需要的最小的2的倍率长度,
    1.这里若区间长度时偶数,则2^k次刚好是区间长度一半,
    这样st[l][k],st[r-(1<<k)+1][k]刚好各覆盖区间的一半,没有重复相交的区域.
    2.若区间长度为奇数,则2^k次方大于区间的一半,重复的区域大小取决于区间长度距离较大的2的倍率之间的距离，
    如9、10 距离16,它重复的相交的区域就较大,但14 、15就较小,2个子区间接近于占满整个区间的一半.
    这里对于两个子区间会重复相交并不响应求取整个区间的最值.
    相比较于log2(len) 2^k>=len/2的做法,最终结果都是一致的
    */
    while(1<<(k+1)<len) k++;//O(log(len))
    return max(st[l][k],st[r-(1<<k)+1][k]);
}

int main(){
    int n,m,l,r;
    n=read();m=read();
    for(int i=1;i<=n;i++) st[i][0]=read();//输入i这个数本身,2^0=1只有这个数本身
    init(n);
    while(m--){
        l=read(),r=read();
        printf("%d\n",query(l,r));
    }
    return 0;
}
