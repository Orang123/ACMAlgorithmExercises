/*
题意:在一个操场上摆放着一排N堆石子。现要将石子有次序地合并成一堆。
规定每次只能选相邻的2堆石子合并成新的一堆，并将新的一堆石子数记为该次合并的得分。
试设计一个算法，计算出将N堆石子合并成一堆的最小得分。
N<=40000.
链接:https://www.luogu.com.cn/problem/P5569
思路:
GarsiaWachs算法
n最大可达 40000,四边形不等式优化也会TLE,采用GarsiaWachs,
这个算法专门解决石子合并的问题.
*/
#include<bits/stdc++.h>
using namespace std;
long long ans,n;
vector<int> l;
inline int read()
{
    int i=0; char c=getchar();
    while(c>'9'||c<'0')c=getchar();
    while(c>='0'&&c<='9')i=i*10+c-'0',c=getchar();
    return i;
}
int merge()
{
    int k=l.size()-1-1;//如果我们在A[0]到A[n-3]找不到A[k]<=A[k+2]，那么k的值应该为n-2
    for(int i=0;i<l.size()-2;++i)
    {
        if(l[i]<=l[i+2])
        {
            k=i;
            break;
        }
    }
    int tmp=l[k]+l[k+1];
    l.erase(l.begin()+k);
    l.erase(l.begin()+k);//删除
    int in=-1;
    for(int i=k-1;i>=0;--i) //从右往左找第一个
    {
        if(l[i]>tmp)
        {
            in=i;
            break;
        }
    }
    l.insert(l.begin()+in+1,tmp);//因为是在后面插入，所以要+1
  return tmp;
}
int main()
{
    cin>>n;
    for(int i=1; i<=n;++i)
        l.push_back(read());
    for(int i=0;i<n-1;i++)
        ans+=merge();
    cout<<ans;
    return 0;
}
