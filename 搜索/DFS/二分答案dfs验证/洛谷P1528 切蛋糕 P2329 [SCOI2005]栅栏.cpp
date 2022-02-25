/*
题意:
洛谷P1528 切蛋糕
Facer今天买了n块蛋糕，不料被信息组中球球等好吃懒做的家伙发现了，没办法，
只好浪费一点来填他们的嘴巴。他答应给每个人留一口，然后量了量每个人口的大小。
Facer有把刀，可以切蛋糕，但他不能把两块蛋糕拼起来，但是他又不会给任何人两块蛋糕。
现在问你，facer怎样切蛋糕，才能满足最多的人。（facer的刀很强，切的时候不会浪费蛋糕）。
n<=50,m<=1024.

洛谷P2329 [SCOI2005]栅栏
农夫约翰打算建立一个栅栏将他的牧场给围起来，因此他需要一些特定规格的木材。
于是农夫约翰到木材店购买木材。可是木材店老板说他这里只剩下少部分大规格的木板了。
不过约翰可以购买这些木板，然后切割成他所需要的规格。而且约翰有一把神奇的锯子，
用它来锯木板，不会产生任何损失，也就是说长度为10的木板可以切成长度为8和2的两个木板。
你的任务：给你约翰所需要的木板的规格，还有木材店老板能够给出的木材的规格，求约翰最多
能够得到多少他所需要的木板。

洛谷P1528 切蛋糕和洛谷P2329 [SCOI2005]栅栏是同一道题 只是问题背景不同,含义是一样的.
链接:
https://www.luogu.com.cn/problem/P1528
https://www.luogu.com.cn/problem/P2329
思路:题解摘自 洛谷题解 "凌幽"网友
贪心思想:如果一块蛋糕能满足口较大的人，那么口较小的人一定能满足，
并且能满足的人可能会更多，所以先满足口较小的人.
二分可以满足的最多的人有多少
dfs判断是否前mid人是否可行

剪枝:
1.把人按口的大小排序，并记录前缀和与蛋糕总数，显然，前缀和是递增的，
那么这样，我们可以通过缩小二分范围来达到加速的目的。若所有的蛋糕都
不能满足某一个人的口，那么可以将其删去。

2.waste浪费，对于一块蛋糕，将其分出去一部分满足一些人后，倘若剩余部分
连口最小的人都无法满足，那么剩余部分一定不能满足任何人，就属于浪费的部分。
若蛋糕有用的部分（总数-浪费）不能满足前mid个人，那么当前二分的答案不可行。

3.由于口是递增的，在dfs过程中，可能会遇到这么一种情况，第i个人与第i-1个人
的口相同，那么考虑，若不能满足第i-1个人，那么一定不能满足第i个人，进行剪枝。
*/
//ac 44ms dfs+二分验证+前缀和剪枝
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
//还有随机化贪心的解法
int n,m,a[60],tmp[60],b[1100],c[1100],cnt,waste,sum,mid;
//dfs两个剪枝点缺一不可否则都会导致TLE
int dfs(int num,int st){
    if(!num) return 1;//前mid个人都能满足则 结束
    //如果当前蛋糕总量减去浪费不能用的蛋糕比所需要的所有人的口量和小,则无法满足mid个人 可以直接返回 从新枚举
    if(sum-waste<c[mid]) return 0;//剪枝
    for(int i=st;i<=n;i++){
        if(tmp[i]>=b[num]){
            tmp[i]-=b[num];
            if(tmp[i]<b[1]) waste+=tmp[i];//如果当前蛋糕剩余量连最小口量都满足不了,则丢弃
            /*
            若前一个人num-1的口量和当前的人num相同,则num-1 st开始试探的位置可以从当前num第一次满足的位置i开始,
            减少循环次数,对于num这个点如果回溯时,在读选择i+1进入dfs(num-1,i)时,那么num-1看起来好像不会再考虑之前的i-1,
            看起来这样num-1会少枚举一个蛋糕,事实上,当第一次num进入num-1的dfs时,如果num-1验证失败的时候,这时num-1已经考虑
            i+1了,而num和num-1口量是一样的,所以num回溯再考虑i+1时,num-2还是从i+1开始,若从i-1开始会重复枚举遍历.
            */
            //剪枝
            if(b[num] == b[num-1]){//若前一个人num-1的口量和当前的人num相同,则num-1st开始试探的位置可以从当前num第一次满足的位置i开始
                if(dfs(num-1,i)) return 1;
            }
            //否则st从第一个蛋糕开始枚举考虑 因为b[num-1]<b[num]
            else if(dfs(num-1,1)) return 1;
            if(tmp[i]<b[1]) waste-=tmp[i];//回溯还原浪费蛋糕和 蛋糕的原始份量.
            tmp[i]+=b[num];
        }
    }
    return 0;
}

int main(){
    int maxa=-1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        sum+=a[i];
        maxa=max(a[i],maxa);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
        scanf("%d",&b[i]);
    sort(b+1,b+m+1,less<int>());
    for(int i=m;b[i]>maxa;i--) m--;//若某人的嘴比最大分量的蛋糕还大  则他永远无法被满足,缩小二分范围 剪枝
    for(int i=1;i<=m;i++)//前缀和一定要排完序再累加
        c[i]=c[i-1]+b[i];
    int l=1,r=m;//l=0貌似结果也对
    /*
    二分的两种形式：
    1、范围缩小时，r = mid，l = mid + 1，取中间值时，mid = (l + r) >> 1.
    2、范围缩小时，l = mid，r = mid - 1，取中间值时，mid = (l + r + 1) >> 1;
    */
    /*
    对可能满足的人数进行二分,从而不断靠近最大满足人数,dfs只是对这个答案进行验证,
    相比较于下面直接dfs暴力拿b[i]去试探1~n的a[i]
    它的满足人数是尽可能扩大,也就是满足人数是按线性递增的,
    可m最大有1024,这样递归的深度会加大,最主要的费时就在这里.而二分答案,可以跳跃式地略过中间很多满足条件的答案的验证
    相比暴力线性递增答案就快很多.
    */
    //当能够考虑将数据排序的时候,就可考虑对结果进行二分,而避免暴力线性递增枚举.
    //在这里之所以排序考虑的是 当答案是mid时,那么排序后的前mid个人就一定能满足,其实也是考虑了贪心,先满足较小的口量人数一定是最多的
    while(l<r){
        waste=0;
        for(int i=1;i<=n;i++) tmp[i]=a[i];
        mid=(r+l+1)/2;
        if(dfs(mid,1)) l=mid;//若当前枚举的人数mid通过验证,则将答案区间向右调整,再考虑更大的答案.
        else r=mid-1;//若当前枚举的人数mid不通过验证,则将答案区间向左调整,再考虑相对较小的答案.
    }
    printf("%d\n",r);
    return 0;
}

/*
//TLE 57分 dfs+剪枝,不做二分答案验证
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

int n,m,a[60],b[1100],c[1100],cnt,waste,sum;

int dfs(int num,int st){
    cnt=max(cnt,num-1);
    if(num == m+1) return 1;
    if(sum-waste<c[num]) return 0;
    for(int i=st;i<=n;i++){
        if(a[i]>=b[num]){
            a[i]-=b[num];
            if(a[i]<b[num]) waste+=a[i];
            if(b[num] == b[num+1]){
                if(dfs(num+1,i)) return 1;
            }
            else if(dfs(num+1,1)) return 1;
            if(a[i]<b[num]) waste-=a[i];
            a[i]+=b[num];
        }
    }
    return 0;
}

int main(){
    int maxa=-1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        sum+=a[i];
        maxa=max(a[i],maxa);
    }
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        scanf("%d",&b[i]);
        c[i]=c[i-1]+b[i];
    }
    sort(b+1,b+m+1,less<int>());
    for(int i=m;b[i]>maxa;i--) m--;
    dfs(1,1);
    printf("%d\n",cnt);
    return 0;
}
*/

/*
对蛋糕按照从大到小排好序,人的口量从小到大排序,对于每个人都尽可能先考虑拿蛋糕较大的切分,
这样蛋糕量大的就能尽可能先分给口量小的,这样就能满足更多人口量,这样结果是有问题的
如果只是把最大的蛋糕分给尽可能小的口量,那么有可能本身这个最大蛋糕是可以刚好可以全部分给
最大的口量的,而较小的口量选择次大的蛋糕,这样所能分的个数才是最大的,而现在最大的蛋糕因为
尽可能分给了尽可能小的口量,最大蛋糕剩余口量已经不能满足最大口量,导致整体分到的口量实际并不
是最大的.
//wa 纯贪心
#include<cstdio>
#include<iostream>
using namespace std;

int n,m,a[60],b[1100],cnt;

int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    sort(a,a+n,greater<int>());
    scanf("%d",&m);
    for(int i=0;i<m;i++)
        scanf("%d",&b[i]);
    sort(b,b+m,less<int>());
    for(int i=0;i<m;i++){//枚举每个口量 试探n个蛋糕哪个还能分
        for(int j=0;j<n;j++){
            if(a[j]>=b[i]){
                a[j]-=b[i];
                cnt++;
                break;
            }
        }
    }
    printf("%d\n",cnt);
    return 0;
}
*/

