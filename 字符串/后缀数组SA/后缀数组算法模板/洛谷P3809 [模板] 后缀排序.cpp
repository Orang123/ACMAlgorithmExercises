/*
题意:读入一个长度为 nn 的由大小写英文字母或数字组成的字符串，
请把这个字符串的所有非空后缀按字典序（用 ASCII 数值比较）从小到大排序，
然后按顺序输出后缀的第一个字符在原串中的位置。位置编号为 11 到 nn。
链接:https://www.luogu.com.cn/problem/P3809
思路:后缀数组模板题.
*/
/*
后缀数组sa[i]就表示排名为i的后缀的起始位置的下标,
而它的映射数组rk[i]就表示起始位置的下标为i的后缀的排名 即:rk[sa[i]=i sa[rk[i]]=i.
映射数组rk在倍增时,有可能会出现并列的情况,即不同下标对应的排名是一致的,因为此时计算的
是后缀子串(后缀的前缀子串)的排名,有可能是相同的.

cnt[i]是计数排序用到的,第一次计算字符串每个字符的排名和倍增w=1时,表示的是当字符的ASCII码
值为i,不大于i值的其余字母有cnt[i]个.
后续倍增计算时,当w=2时,cnt[i]表示某个后缀前缀的排名为i,并且其余后缀前缀子串排名不大于i的个数为cnt[i]

id临时的sa
oldRk是rk数组的拷贝,根据新计算得到的长度为2*w的后缀子串的sa数组,来生成新的长度为2*w的后缀子串的排名.

参考博客:
https://www.cnblogs.com/zwfymqz/p/8413523.html
https://www.cnblogs.com/victorique/p/8480093.html

辅助理解动画:https://visualgo.net/zh/suffixarray eg:$aabaaaab
教学视频:https://www.bilibili.com/video/BV1VE411J7u8?spm_id_from=333.999.0.0
*/
//ac 825ms
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 1000100
char s[N];
//rk 、oldRk数组 因为会判断i+w,所以要开成原数组的2倍,避免数组越界异常
int sa[N],rk[N<<1],oldRk[N<<1],cnt[N],id[N];

//时间复杂度O(nlog(n) n为字符串长度,暴力做法 时间复杂度O(n^2*log(n)) 因为每个字符串间比较O(n),而排序算法O(nlogn)
//基数排序+计数排序 采用了基数排序的分伦次的想法,具体排序的方法 采用计数排序(因为字符的ASCII本身就不是很大,后面的rk值也比较小)
void SA(int n){//倍增法 DA-doble array 倍增数组
    //rk数组中的值可能取到的最大结果,第一次计算单个字符的时候,
    //最大为小写字母z-122 ASCII值,后面为字符串的长度,但n可能也比ASCII值要大
    int m=max(n,300);
    //int m=max(n,126);//300 好像最大是255
    //第一次计算每个后缀前一个字符的序列,即每个字符序列 事实上如果采用未优化的倍增算法,
    //每次都对第二关键词排序,这里是不必第一次再计算每个字符的排名的,因为后面又对第二关键字从新排了,在这里只对rk初始化即可
    //for(int i=1;i<=n;i++) rk[i]=s[i];
    //将字符串中的每个字符的ASCII记录在rk数组中,并且记录该字符出现的次数,相同的字符可累加多次
    for(int i=1;i<=n;i++) ++cnt[rk[i]=s[i]];
    //对cnt进行前缀和累加,用来记录这个字符前面包括这个字符有几个字符,
    //实际就是当前这个字符的排序结果从哪个值开始,相同字符排名依次++
    for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
    /*
    这里其实从哪个下标开始计算其sa值都无所谓,我是从下标为1依次开始计算的,也可以反过来从n开始计算,
    先算的对于相同字符的cnt而言可能其排名会计算较大但不影响结果,每计算一次这个cnt对应的值都减一下
    一次,再计算这个字符的时候排名就越靠前,但是总体的排名都是在上个值cnt[i-1]之后的
    */
    //升序降序都可
    //for(int i=n;i>=1;i--) sa[cnt[rk[i]]--]=i;
    for(int i=1;i<=n;i++) sa[cnt[rk[i]]--]=i;
    /*
    倍增法进行基数排序,这里在排序大体的思维上借鉴了基数排序对数字分轮次进行个位排序,十位排序,百位排序那样,
    这里倍增法分2轮排序,先对第二关键字排序,再对第一关键字排序,也就是相对数字来讲只有2位数 上面计算出了每个
    后缀前1个字符构成的子串的字典序,下面就得计算每个后缀前2个字符构成的子串的字典序,那么我们可以把前面计算的
    字典序长度为1的后缀(suf(i),suf(i+1))结果分别作为第一关键字和第二关键字合并起来分两轮基数排序进行字典序排序
    这样就计算出了长度为2的每个字典序的排序,然后我们接下来不计算长度为3的后缀的字典序可以直接计算长度为4的后缀的
    字典序方法还是把之前计算出来的2个长度为2的连续后缀(suf(i),suf(i+2))合并进行2轮基数排序 接下来在进行长度为8的
    后缀计算 即合并suf(i)和suf(i+4)... 直到w=2/n时即suf(i),suf(i+w)刚好占满全部的字符时 即计算每个后缀的全部字符的字典序
    */
    for(int w=1;w<n;w<<=1){//每次计算每个后缀长度为2*w的子串的字典序
        memset(cnt,0,sizeof(cnt));//初始化cnt计数排序的数组
        //基数排序 先对第二关键字 suf(i+w)排序 这里为了模拟流程又重复地计算了一次长度为w的后缀序号
        for(int i=1;i<=n;i++) id[i]=sa[i];
        //计数排序 有可能i+w会超出字符的下标n,这时代表不存在第二关键字,第一关键字代表的后缀子串的长度<=w.
        //而这个rk的值为0即cnt[0]++
        for(int i=1;i<=n;i++) ++cnt[rk[i+w]];
        //计算每个第二关键字的前缀和,即这个第二关键字前面包括自己本身又几个字符,
        //实际这个第二关键字字符的排名也是从cnt[i-1]开始的
        for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
        /*
        这里记录的是长度为2*w的后缀的首字符的下标id[i],而不是第二关键字的下标,
        得先根据上一次合并后的长度为w的后缀的id[i],第i名的下标再加上w,根据第二
        关键字去排,单记录的是第一关键字的下标id[i],次序i升序降序都可以.
        */
        //升序、降序都可以,因为只是单独对第二关键字排序,只是记录的是第一关键字开始的下标
        for(int i=1;i<=n;i++) sa[cnt[rk[id[i]+w]]--]=id[i];
        //for(int i=n;i>=1;i--) sa[cnt[rk[id[i]+w]]--]=id[i];
        memset(cnt,0,sizeof(cnt));//清空cnt
        for(int i=1;i<=n;i++) id[i]=sa[i];
        for(int i=1;i<=n;i++) ++cnt[rk[i]];
        for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
        /*
        这里因为是基数排序 需要建立在第二关键字已排序好的结果上去排第一关键字,所以
        先取第二关键字排名靠后的后缀的起始下标去取值也就是从n开始,这样对于第一关键字
        相同的cnt所取得值是相对较大的,因为其第二关键字较大 字典序就靠后,对于第一关键字
        不同则较小的cnt也较小 不影响其结果
        */
        //只能降序,因为是建立在第二关键字的基础上对第一关键字排序,对于第1关键字cnt相同的值,第二关键字较小的就会排在后面
        for(int i=n;i>=1;i--) sa[cnt[rk[id[i]]]--]=id[i];
        memcpy(oldRk,rk,sizeof(rk));//从新更新rk的值域,因此将其赋值给oldRk方便判断
        int k=0;
        for(int i=1;i<=n;i++){
            //如果排名i-1和i的后缀的 第一关键字和第二关键字 rk值(字符大小值)相同,
            //则说明其长度为2*w的后缀字典序是相同的,第i-1名和第i名后缀子串是并列的
            //随着后缀子串长度w不断增大,这个并列的子串个数会更多地被细分出来,知道每个子串都不再并列.
            if(oldRk[sa[i-1]]==oldRk[sa[i]] && oldRk[sa[i-1]+w]==oldRk[sa[i]+w])
                rk[sa[i]]=k;
            else
                rk[sa[i]]=++k;//否则 rk的排名+1
        }
        if(k == n)
            break;
        m=k;//更新cnt的值域
    }
}

int main(){
    int n;
    scanf("%s",s+1);
    n=strlen(s+1);
    SA(n);
    printf("%d",sa[1]);
    for(int i=2;i<=n;i++)
        printf(" %d",sa[i]);
    printf("\n");
    return 0;
}

/*
//ac 591ms 不对第二关键字进行排序,优化
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 1000100
char s[N];
//这里因为并不对第二关键字排序,因此rk,oldRk数组长度为N.
int sa[N],rk[N],oldRk[N],cnt[N],id[N];

//时间复杂度 O(5nlog(n))=O(nlog(n))
void SA(int n){
    int p,k=max(n,126);
    for(int i=1;i<=n;i++) ++cnt[rk[i]=s[i]];
    for(int i=1;i<=k;i++) cnt[i]+=cnt[i-1];
    for(int i=1;i<=n;i++) sa[cnt[rk[i]]--]=i;

    for(int w=1;w<n;w<<=1){//O(log(n))
        p=1;
        //第n-k+1到第n位是没有第二关键字的,后缀长度达不到2*w,因此其第二关键字的排序结果靠前,并且后缀起始字符越靠后的 排名越靠前
        //eg:对于后缀aa和a而言 字典序a<aa 如果第一关键字字典序比这个小 在统计时自然排在其前面,当和这个长度不够的第二关键字相同时,
        //也是这个第二关键字靠前,因为ab<abad
        for(int i=n;i>n-w;i--) id[p++]=i;
        //按照先前统计的sa的排名从低到高依次统计其构成的长度2*w的后缀的第一关键字的下标(1~n-w)进入id里 升序,
        //这里因为第二关键字的排序已经在上一轮的倍增合并过程里统计出来了,所以不再采用cnt计数排序进行累加统计
        //这里必须升序
        for(int i=1;i<=n;i++)
            if(sa[i]>w) id[p++]=sa[i]-w;
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++) ++cnt[rk[i]];//O(n)
        for(int i=1;i<=k;i++) cnt[i]+=cnt[i-1];
        for(int i=n;i>=1;i--) sa[cnt[rk[id[i]]]--]=id[i];
        memcpy(oldRk,rk,sizeof(rk));
        k=0;
        for(int i=1;i<=n;i++)
            rk[sa[i]]=(oldRk[sa[i-1]]==oldRk[sa[i]] && oldRk[sa[i-1]+w]==oldRk[sa[i]+w])?k:++k;
        if(k==n) return;//已经排好n个后缀的次序了 结束 不加这个结束条件 2.34s
    }
}

int main(){
    int n;
    scanf("%s",s+1);
    n=strlen(s+1);
    SA(n);
    printf("%d",sa[1]);
    for(int i=2;i<=n;i++)
        printf(" %d",sa[i]);
    printf("\n");
    return 0;
}
*/
