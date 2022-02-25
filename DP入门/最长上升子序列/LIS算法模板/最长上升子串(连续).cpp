//最长上升子串,连续
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[110];

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    int num=0,ans=-1;//因为第一个元素a[1]要与a[0]比较,所以num初始化为0
    for(int i=1;i<=n;i++){
        if(a[i]>a[i-1]) num++;//每次判断相邻的两个元素,若单调上升 则num+1
        else num=1;//否则num从新从1开始
        ans=max(ans,num);
    }
    printf("%d\n",ans);
    return 0;
}

/*
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int a[110];
//最长不下降子串 连续
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    int num=0,ans=-1;//因为第一个元素a[1]要与a[0]比较,所以num初始化为0
    for(int i=1;i<=n;i++){
        if(a[i]>=a[i-1]) num++;//每次判断相邻的两个元素,若单调上升 则num+1
        else num=1;//否则num从新从1开始
        ans=max(ans,num);
    }
    printf("%d\n",ans);
    return 0;
}
*/

/*
leetcode 845 数组中的最长山脉
链接:https://leetcode-cn.com/problems/longest-mountain-in-array/
最长上升下降子串的长度
把符合下列属性的数组 arr 称为 山脉数组 ：
arr.length >= 3
存在下标 i（0 < i < arr.length - 1），满足
arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
给出一个整数数组 arr，返回最长山脉子数组的长度。如果不存在山脉子数组，返回 0 。
1 <= arr.length <= 104
0 <= arr[i] <= 104

// //正反序dp 枚举中位数
// class Solution {
// public:
//     int dp1[10010],dp2[10010];
//     int longestMountain(vector<int>& arr) {
//         int n=arr.size();
//         for(int i=1;i<n;i++){
//             if(arr[i]>arr[i-1])
//                 dp1[i]=dp1[i-1]+1;
//         }
//         for(int i=n-2;i>=0;i--){
//             if(arr[i]>arr[i+1])
//                 dp2[i]=dp2[i+1]+1;
//         }
//         int ans=0;
//         for(int i=1;i<n-1;i++){
//             if(dp1[i] && dp2[i])
//                 ans=max(ans,dp1[i]+1+dp2[i]);
//         }
//         return ans;
//     }
// };

//模拟
class Solution {
public:
    int longestMountain(vector<int>& arr) {
        int n=arr.size(),up=0,down=0,ans=0;
        for(int i=1;i<n;i++){
            if(arr[i]>arr[i-1]){
                if(down){
                    ans=max(ans,up+down+1);
                    up=down=0;
                }
                up++;
            }
            else if(arr[i]<arr[i-1]){
                if(up)
                    down++;
            }
            else{
                if(down)
                    ans=max(ans,up+down+1);
                else
                    up=0;
            }
        }
        if(down)
            ans=max(ans,up+down+1);
        return ans;
    }
};



//枚举中位数 向两边扩展 复杂度最坏O(n^2)
// class Solution {
// public:
//     int longestMountain(vector<int>& arr) {
//         int n=arr.size(),l,r,ans=0;
//         for(int i=1;i<n-1;i++){
//             l=r=i;
//             while(l>=1 && arr[l]>arr[l-1])
//                 l--;
//             while(r<=n-2 && arr[r]>arr[r+1])
//                 r++;
//             if(l!=i && r!=i)
//                 ans=max(ans,r-l+1);
//         }
//         return ans;
//     }
// };
*/
