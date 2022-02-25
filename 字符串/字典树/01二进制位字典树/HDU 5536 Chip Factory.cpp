/*
题意:摘自网上
有一个数组a[], 包含n个数，从n个数中找到三个数使得
(a[i]+a[j])^a[k]最大，i,j,k不同;
n<=1000,a[i]<=10^9.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=5536
思路:01字典树,将所有a[i]的二进制位插入字典树.
只是要保证a[i]、a[j]、a[k]三个数都不同,那么在考虑
a[i]+a[j]的最大异或值时,就需要将字典树中的a[i]和a[j]
删掉.在插入时需要累加每个前缀出现次数,删除实际是对
每个字符串的前缀num[rt]进行减一,在查找时的判断条件
就变为tr[rt][son^1] && num[tr[rt][son^1]],num的次数不能为0.
*/
//ac 2667ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 31000
using namespace std;

int n,tr[N][2],cnt,num[N],a[1100],ans;

int newNode(){
    cnt++;
    tr[cnt][0]=tr[cnt][1]=0;
    num[cnt]=0;
    return cnt;
}

void insertWord(int val){
    int rt=0,son;
    for(int i=30;i>=0;i--){
        son=val>>i & 1;
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
        num[rt]++;//前缀出现次数+1
    }
}

void deletWord(int val){
    int rt=0,son;
    for(int i=30;i>=0;i--){
        son=val>>i & 1;
        rt=tr[rt][son];
        num[rt]--;//val单词出现的次数-1,因为别的数可能也共用这个前缀,不能直接将tr数组置为0
    }
}

int findWord(int val){
    int rt=0,son,res=0;
    for(int i=30;i>=0;i--){
        son=val>>i &1;
        //trie树中存在 异或位,并且当前位并没有被删完
        if(tr[rt][son^1] && num[tr[rt][son^1]]){
            res|=1<<i;
            rt=tr[rt][son^1];
        }
        else
            rt=tr[rt][son];
    }
    return res;
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        ans=0;
        cnt=-1;
        newNode();
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            insertWord(a[i]);
        }
        for(int i=1;i<=n;i++){
            deletWord(a[i]);//删除a[i]
            for(int j=i+1;j<=n;j++){
                deletWord(a[j]);//删除a[j]
                ans=max(ans,findWord(a[i]+a[j]));
                insertWord(a[j]);//恢复a[j]
            }
            insertWord(a[i]);//恢复a[i]
        }
        printf("%d\n",ans);
    }
    return 0;
}
