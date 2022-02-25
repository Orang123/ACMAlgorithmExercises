//������Ӵ�,����
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
    int num=0,ans=-1;//��Ϊ��һ��Ԫ��a[1]Ҫ��a[0]�Ƚ�,����num��ʼ��Ϊ0
    for(int i=1;i<=n;i++){
        if(a[i]>a[i-1]) num++;//ÿ���ж����ڵ�����Ԫ��,���������� ��num+1
        else num=1;//����num���´�1��ʼ
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
//����½��Ӵ� ����
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    int num=0,ans=-1;//��Ϊ��һ��Ԫ��a[1]Ҫ��a[0]�Ƚ�,����num��ʼ��Ϊ0
    for(int i=1;i<=n;i++){
        if(a[i]>=a[i-1]) num++;//ÿ���ж����ڵ�����Ԫ��,���������� ��num+1
        else num=1;//����num���´�1��ʼ
        ans=max(ans,num);
    }
    printf("%d\n",ans);
    return 0;
}
*/

/*
leetcode 845 �����е��ɽ��
����:https://leetcode-cn.com/problems/longest-mountain-in-array/
������½��Ӵ��ĳ���
�ѷ����������Ե����� arr ��Ϊ ɽ������ ��
arr.length >= 3
�����±� i��0 < i < arr.length - 1��������
arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
����һ���������� arr�������ɽ��������ĳ��ȡ����������ɽ�������飬���� 0 ��
1 <= arr.length <= 104
0 <= arr[i] <= 104

// //������dp ö����λ��
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

//ģ��
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



//ö����λ�� ��������չ ���Ӷ��O(n^2)
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
