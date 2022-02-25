离散化数组
将一个数组离散化，并进行查询是比较常用的应用场景：
// a[i] 为初始数组,下标范围为 [1, n]
// len 为离散化后数组的有效长度
std::sort(a + 1, a + 1 + n);

len = std::unique(a + 1, a + n + 1) - a - 1;
// 离散化整个数组的同时求出离散化后本质不同数的个数。

在完成上述离散化之后可以使用 std::lower_bound 函数查找离散化之后的排名（即新编号）：
std::lower_bound(a + 1, a + len + 1, x) - a;  // 查询 x 离散化后对应的编号
同样地，我们也可以对 vector 进行离散化：
// std::vector<int> a, b; // b 是 a 的一个副本
std::sort(a.begin(), a.end());
a.erase(std::unique(a.begin(), a.end()), a.end());
for (int i = 0; i < n; ++i)
  b[i] = std::lower_bound(a.begin(), a.end(), b[i]) - a.begin();


/*
//摘自博客:https://blog.csdn.net/QiHang_QiHang/article/details/80739063
typedef long long ll;
const int N = 1e5+10;

int main()
{
    int a[N],sub[N];
    int n;
    scanf("%d",&n);
    for(int i = 0; i < n; i++) {
        scanf("%d",&sub[i]);
        a[i] = sub[i];
    }
    sort(sub, sub + n);
    int size = unique(sub, sub + n) - sub;

    printf("size  %d\n",size);
    for(int i = 0; i < n; i++)
        a[i] = lower_bound(sub, sub + size, a[i]) - sub;
    for(int i =0 ;i < n; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}
*/

/*
//摘自博客:https://blog.csdn.net/tb_youth/article/details/104334081
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int a[8] = {1,5,3,2,3,2,7,90};
    sort(a,a+8);
    vector<int>vec(a,a+8);

    cout<<"使用unique前:"<<endl;
    for(int i = 0; i < vec.size(); i++)
    {
        cout<<vec[i]<<" ";
    }
    cout<<endl;

    //使用unique前需要保证数据是有序的，
    //unique返回的是不重复序列最后的地址（迭代器形式），
    //unique只是将重复的元素的位置用后面与它不同的元素来覆盖
    int cnt = unique(vec.begin(),vec.end())-vec.begin();

    cout<<"目标序列长度："<<cnt<<endl;
    cout<<"使用unique后:"<<endl;
    for(int i = 0; i < vec.size(); i++)
    {
        cout<<vec[i]<<" ";
    }
    cout<<endl;
    cout<<"使用erase后:"<<endl;
    vec.erase(vec.begin()+cnt,vec.end());
    for(int i = 0; i < vec.size(); i++)
    {
        cout<<vec[i]<<" ";
    }
    cout<<endl;
    return 0;
}

*/
