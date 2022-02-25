#include<bits/stdc++.h>
#define N 100100
#define M 1000
typedef long long ll;
using namespace std;
/*
回滚莫队时间复杂度n*根号n
L[i]、R[i] 块号为i的对应的区间左端点、右端点 cnt1为暴力统计次数最大重要度 cnt2为左右端点移动扩展统计次数最大重要度
*/
int a[N],val[N],tmp[N],pos[N],cnt1[N],cnt2[N],L[M],R[M];
ll max0,tmp0,ans[N];
struct Node{
    int l,r,id;
    bool operator < (const Node &x)const{
        //以左端点所在的块升序为第一关键字,以右端点升序为第二关键字.
        if(pos[l]^pos[x.l]) return pos[l]<pos[x.l];//这里实际按照 左端点return l<x.l也没有错.
        else return r<x.r;
    }
}Q[N];

//a[i]<=10^9 离散化 存入val[i]
void discret(int n){
    int len;
    sort(tmp+1,tmp+1+n);
    len=unique(tmp+1,tmp+1+n)-tmp-1;
    for(int i=1;i<=n;i++)
        val[i]=lower_bound(tmp+1,tmp+1+len,val[i])-tmp;
}
//分块
void setBlock(int n){
    int siz,num;
    siz=sqrt(n);//n不一定能 完全平方,siz*siz可能<n
    num=n/siz;//块的大小为siz,块的个数为num.
    for(int i=1;i<=num;i++){
        L[i]=(i-1)*siz+1;
        R[i]=i*siz;
        for(int j=L[i];j<=R[i];j++) pos[j]=i;//记录区间小标所在的块,区间下标L[i]~R[i]所属的块的编号为i

    }
    if(R[num]<n){//siz*siz<n时,剩下的数的个数小于一个siz块
        num++;//从新设置一个新块
        L[num]=R[num-1]+1;//新块的左端点为上一个块右端点+1
        R[num]=n;//新块的右端点为区间最末尾下标n
        for(int j=L[num];j<=R[num];j++)
            pos[j]=num;
    }
    /*for(int i=1;i<=num;i++)
        for(int j=L[i];j<=R[i];j++)
            pos[j]=i;*/
}
//每增加一个数 就更新区间里重要度(出现次数*a[i])最大的值
void add(int k,ll &max1){
    cnt1[val[k]]++;
    max1=max(1ll*cnt1[val[k]]*a[k],max1);
}
//这里是回滚 撤销之前增加的次数,并不对最大值进行计算.
void rollback(int k){
    cnt1[val[k]]--;
}

int main(){
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        tmp[i]=val[i]=a[i];
    }
    for(int i=1;i<=q;i++){
        scanf("%d%d",&Q[i].l,&Q[i].r);
        Q[i].id=i;
    }
    discret(n);
    setBlock(n);
    sort(Q+1,Q+1+q);
    //lastblock 用来判断这次的询问和上一个询问的左端点是否在同一块,若在同一块方便继续尾随让一个询问的r指针扩展更新最大的重要度
    int l=1,r=0,_l,lastblock=0;
    for(int i=1;i<=q;i++){
        /*
        对于询问左右端点在同一块中的询问,暴力累加Q{i].l到Q[i].r出现的次数 再记录最大重要度,之后再还原出现次数
        之所以要单独暴力处理,是因为本次询问右端点并不会从R[pos[Q[i].l]]开始向右扩展,所以就单独采用cnt2数组记录次数与
        左、右端点分别想左、右移动扩展的cnt1区分开.
        */
        if(pos[Q[i].l] == pos[Q[i].r]){
            tmp0=0;
            for(int j=Q[i].l;j<=Q[i].r;j++) cnt2[val[j]]++;//这里用的是cnt2,下面右端点移动用的是cnt1
            for(int j=Q[i].l;j<=Q[i].r;j++)
                tmp0=max(1ll*cnt2[val[j]]*a[j],tmp0);
            ans[Q[i].id]=tmp0;
            for(int j=Q[i].l;j<=Q[i].r;j++) cnt2[val[j]]--;
            continue;
        }
        //如果新的询问左端点和之前左端点所在块不在同一块 并且新询问左右端点也不在同一块
        if(lastblock ^ pos[Q[i].l]){
            //初始化 左、右端点 右端点为R[pos[Q[i].l]],左端点为R[pos[Q[i].l]]+1
            /*
            有可能上一次r右端点本身就比较小,即:r<R[pos[Q[i].l]],这种情况下面while(l<R[pos[Q[i].l]]+1) rollback(r--);
            会将上次询问的l~r这一段还原,并且本次使得r~R[pos[Q[i].l]]-1这一段多余减少了次数,这一段多余减少的次数等到了后面
            while(r<Q[i].r) add(++r,max0);会得到还原,并且同时对从新询问R[pos[Q[i].l]]~Q[i].r这段区间进行累加次数并更新最大重要度.
            若上一次询问的右端点较大即:r>R[pos[Q[i].l]]则需要对r端点进行初始化为R[pos[Q[i].l]].上一次询问的左端点l类同
            */
            while(r>R[pos[Q[i].l]]) rollback(r--);
            while(l<R[pos[Q[i].l]]+1) rollback(l++);
            //max0最大重要度要设置为0,因为是从新的块开始计数了,同时上一块号更新为当前的pos[Q[i].l]
            max0=0,lastblock=pos[Q[i].l];
        }
        /*
        当这次询问左端点所属块和上一次左端点所属块相同时,根据sort排序原则,本次询问的右端点一定大于等于上一次询问右端点,
        所以右指针的移动继续尾随上一次的位置继续向右边扩展移动增加次数更新最大重要度.但是本次询问的左端点与上一次询问的左端点大小关系是不确定的,
        可以说是随机的有可能大,也有可能小,但这不影响左端点向左扩展 增加次数,因为每次都是从这个询问左端点所在块的右边界开始扩展的,
        因为它的左端点一定是在左端点所在块右边界的左侧的.
        */
        //移动右端点 进行计数更新最大重要度  这个做法实际就是对于左端点在同一块内的做莫队的增加转移,就是左端点所在块块内莫队,不同块 暴力求解
        while(r<Q[i].r) add(++r,max0);
        //这里记录左端点的初始值,用_l进行移动累加,之后方便还原cnt次数
        _l=l;
        tmp0=max0;//同时对于左端点的重要度计算 用一个临时值,因为最后左端点还要还原,重要度自然只能计算右端点移动增加的,这样对于下一次询问 左端点才能继续扩展
        //移动左端点,可以发现 左右端点都是在向外扩,都是增加次数.
        while(_l>Q[i].l) add(--_l,tmp0);
        ans[Q[i].id]=tmp0;//记录当前询问区间最大重要度
        while(_l<l) rollback(_l++);//还原左端点移动增加次数 到原先的R[pos[Q[i].l]]+1
    }
    for(int i=1;i<=q;i++)
        printf("%lld\n",ans[i]);
    return 0;
}
