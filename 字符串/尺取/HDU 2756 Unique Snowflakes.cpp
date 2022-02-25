/*
题意:摘自网上
给定若干个数，计算最长的不同数据的长度 。
链接:http://acm.hdu.edu.cn/showproblem.php?pid=2756
思路:尺取.右指针移动条件是当当前[l,r-1]子串中不含有a[r]的数据,
当a[r]已经出现在[l,r-1]中时停止,记录当前子串的长度,之后左指针
删掉最左边出现的,直到删掉当前a[r]的元素后,右指针才重新开始右移
加入新的a[r]元素,再判断最长的不同数据的子串长度.
*/
//ac 592ms
//结束条件 if(!s.count(a[r])) break;
#include<cstdio>
#include<cstring>
#include<set>
#define N 1000010
using namespace std;

int n,a[N],ans;
set<int> s;

int main(){
    int T,l,r;
    while(scanf("%d",&T)!=EOF){
        while(T--){
            s.clear();
            scanf("%d",&n);
            for(int i=1;i<=n;i++)
                scanf("%d",&a[i]);
            ans=l=r=1;
            while(1){
                while(r<=n && !s.count(a[r]))
                    s.insert(a[r++]);
                if(!s.count(a[r]))
                    break;
                //实际当r不变时,l左移 长度只会越来越小,l不断左移是为了删掉子串中已有的a[r],方便右指针右移
                ans=max(ans,r-l);
                s.erase(a[l++]);
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}

/*
//ac 577ms
//结束条件 最外层循环r<=n
#include<cstdio>
#include<cstring>
#include<set>
#define N 1000010
using namespace std;

int n,a[N],ans;
set<int> s;

int main(){
    int T,l,r;
    while(scanf("%d",&T)!=EOF){
        while(T--){
            s.clear();
            scanf("%d",&n);
            for(int i=1;i<=n;i++)
                scanf("%d",&a[i]);
            ans=l=r=1;
            while(r<=n){
                while(r<=n && !s.count(a[r]))
                    s.insert(a[r++]);
                ans=max(ans,r-l);
                s.erase(a[l++]);
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
*/
