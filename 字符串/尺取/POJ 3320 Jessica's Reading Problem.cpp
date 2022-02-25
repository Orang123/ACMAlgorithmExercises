/*
题意:摘自网上
一本书有P页，每页都有个知识点a[i]，知识点可能重复，
求包含所有知识点的最少的页数。
1<=p<=10^6.
链接:http://poj.org/problem?id=3320
思路:尺取.
*/
//ac 500ms
#include<cstdio>
#include<map>
#include<set>
#define INF 0x3f3f3f3f
using namespace std;
int a[1000010];
set<int> b;//利用set 将不同页码涉及的相同知识点过滤掉
map<int,int> mp;//记录某一个知识点选中的次数
int main(){
    int p,num;
    b.clear();
    mp.clear();
    scanf("%d",&p);
        for(int i=0;i<p;i++){
            scanf("%d",&a[i]);
            b.insert(a[i]);
        }
        num=b.size();//总的知识点的个数
        int left=0,right=0,sum=0,res=INF;
        while(left<p&&right<p){
            if(!mp[a[right]]){//如果此知识点之前还没涉及 总个数+1
                sum++;
            }
            mp[a[right]]++;//这个知识点对应的个数加1
            while(mp[a[left]]>1){
                mp[a[left]]--;//将多余的知识点剔除 直到至少涉及一个该知识点
                left++;
            }
            if(sum==num){//若所有的知识点都涉及到了
                if(right-left+1<res)
                    res=right-left+1;
                if(mp[a[left]]==1)
                    sum--;//若最左端点个数为1则知识点总数减1
                mp[a[left]]--;//开始将区间右移
                left++;
            }
            right++;//区间右移
        }
        printf("%d\n",res);
    return 0;
}
