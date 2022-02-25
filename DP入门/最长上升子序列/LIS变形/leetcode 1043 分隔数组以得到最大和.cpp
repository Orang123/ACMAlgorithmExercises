/*
����һ���������� arr�����㽫������ָ�Ϊ�������Ϊ k ��һЩ�������������顣
�ָ���ɺ�ÿ����������е�����ֵ�����Ϊ���������е����ֵ��
���ؽ�����ָ��任���ܹ��õ���Ԫ�����͡�
ע�⣬ԭ����ͷָ���������Ӧ˳��Ӧ��һ�£�Ҳ����˵����ֻ��ѡ��ָ������λ�ö����ܵ��������е�˳��
���ӣ�https://leetcode-cn.com/problems/partition-array-for-maximum-sum
*/
//dp[i]��ʾ��arr[i-1]��β�ķָ��Ϊk�� ���������ֵ֮��
class Solution {
public:
    int dp[510];
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int maxn,n=arr.size();
        for(int i=1;i<=n;i++){//�±겻�ܴ�i=0��ʼ
            maxn=-1;
            for(int j=i-1;j>=max(i-k,0);j--){
                maxn=max(maxn,arr[j]);
                dp[i]=max(dp[i],dp[j]+maxn*(i-j));
            }
        }
        return dp[n];
    }
};
