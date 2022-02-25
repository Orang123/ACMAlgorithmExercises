/*
input
5
2 3 1 5 4

output
3

input
7
1 4 2 3 6 5 7

output
3
*/
//暴力找逆序数需要每个数线性考虑前面所有比它小的数,时间复杂度为O(n^2)
//ac 树状数组 reflect[i]离散化 时间复杂度O(nlog(n))
//构建树状数组顺序a数组从1到n
#include<cstdio>
#include<algorithm>
#define N 10000
using namespace std;

//reflect[i]=val 表示原先a数组i位置的数值为val,这里val是离散过后数值范围在1~n之间
int n,c[N],reflect[N],ans;
struct Ele{
    int val,pos;
    bool operator <(const Ele &x)const{
        return val<x.val;
    }
}a[N];

int lowbit(int x){
    return x & -x;
}

void update(int x){
    while(x<=n){
        c[x]+=1;//因为是计数,所以祖先节点累加的数值都是1
        x+=lowbit(x);
    }
}

int getsum(int x){
    int sum=0;
    while(x){
        sum+=c[x];
        x-=lowbit(x);
    }
    return sum;
}

int main(){
    //a[0].val=-1//如果原始值含有0,a[0].val设置为-1避免离散化出错
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i].val);
        a[i].pos=i;//记录当前val在原数组中的位置
    }
    sort(a+1,a+1+n);//C++ stl中的sort并非稳定排序,因此离散化对于相同的数值 仍旧要处理成相等的
    for(int i=1;i<=n;i++){
        //这里离散化要将 相等的值 离散后的值也相等,如果不这样,
        //原先序列排在前面相等的值,排序后放在后面,离散后的值就大,
        //这样树状数组查找时,离散后大于的值,但本身数值是相等 并不构成逆序就不包括结果就会出错
        if(a[i].val == a[i-1].val)
            reflect[a[i].pos]=reflect[a[i-1].pos];
        else
            reflect[a[i].pos]=i;
    }
    for(int i=1;i<=n;i++){//O(nlog(n))
        update(reflect[i]);//将第i位置上的数值reflect[i] 加入树状数组中
        //getsum(reflect[i])求出第i位置之前有几个数小于等于第i位置上的数值,这里将i位置本身的数值也算了进去
        ans+=i-getsum(reflect[i]);//统计第i位置之前有几个数大于第i位置上的数值,这便是第i个数产生的逆序数
    }
    printf("%d",ans);
    return 0;
}

/*
//ac 树状数组 reflect[i]离散化 时间复杂度O(nlog(n))
//构建树状数组顺序a数组从n到1
#include<cstdio>
#include<algorithm>
#define N 10000
using namespace std;

//reflect[i]=val 表示原先a数组i位置的数值为val,这里val是离散过后数值范围在1~n之间
int n,c[N],reflect[N],ans;
struct Ele{
    int val,pos;
    bool operator <(const Ele &x)const{
        return val<x.val;
    }
}a[N];

int lowbit(int x){
    return x & -x;
}

void update(int x){
    while(x<=n){
        c[x]+=1;//因为是计数,所以祖先节点累加的数值都是1
        x+=lowbit(x);
    }
}

int getsum(int x){
    int sum=0;
    while(x){
        sum+=c[x];
        x-=lowbit(x);
    }
    return sum;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i].val);
        a[i].pos=i;//记录当前val在原数组中的位置
    }
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i++){
        //离散化,将原先的数值大小关系不变,将其变成1~n之间的数值
        //将原数组中pos位置的数 val设置为其位次rnk i
        if(a[i].val == a[i-1].val)//离散化相等的值一定要保证离散的值相等,因为现在是c[x]表示的是小于等于,从n末尾开始添加的
        	reflect[a[i].pos]=reflect[a[i-1].pos];
        else
        	reflect[a[i].pos]=i;
	}
    for(int i=n;i>=1;i--){//O(nlog(n))
        //因为是按从后往前的顺序统计的,需要统计i+1~n的位置上有几个数比reflect[i]小,因此查询时要减1 因为是严格小于,等于的不计入逆序对
        ans+=getsum(reflect[i]-1);
        //更新放在getsum前后都可以
        update(reflect[i]);//将第i位置上的数值reflect[i] 加入树状数组中
    }
    printf("%d",ans);
    return 0;
}
*/

/*
//归并排序求解逆序数 O(nlog(n))
//因为将原数组分治为了很多子段,而这些子段相互之间不会重叠,
//每次判断逆序对是判断a[low..mid]是否比a[mid+1..high]大,而当子问题解决后,
//问题规模扩大后,再次判断逆序对会将a[low..high]作为左边的字段和右边的子段a[high..],这样就不会重复计算逆序数.
//这正是利用了归并排序分治字段不会重叠的特性,巧妙地在O(nlog(n))时间不重复地求出逆序对
#include<cstdio>
#define N 10000

int n,a[N],tp[N],ans;

void mergeArr(int low,int mid,int high){
    int i=low,j=mid+1,k=low;
    while(i<=mid && j<=high){
        if(a[i]<=a[j])//这里是<=,因为只有严格大于才构成逆序对
            tp[k++]=a[i++];
        else{
            tp[k++]=a[j++];
            ans+=mid-i+1;
        }
    }
    while(i<=mid)
        tp[k++]=a[i++];
    while(j<=high)
        tp[k++]=a[j++];
    for(int i=low;i<=high;i++)
        a[i]=tp[i];
}

//o(nlog(n))
void mergeSort(int low,int high){
    if(low<high){
        int mid=(low+high)/2;
        mergeSort(low,mid);
        mergeSort(mid+1,high);
        mergeArr(low,mid,high);
    }
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    mergeSort(1,n);
    printf("%d",ans);
    return 0;
}
*/
