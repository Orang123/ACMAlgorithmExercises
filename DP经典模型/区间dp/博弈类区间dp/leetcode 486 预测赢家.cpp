/*
����һ���������� nums ����� 1 ����� 2 ����������������һ����Ϸ��
��� 1 ����� 2 ���������Լ��Ļغϣ���� 1 ���֡���ʼʱ��������ҵĳ�ʼ��ֵ���� 0 ��
ÿһ�غϣ���Ҵ����������һ��ȡһ�����֣�����nums[0] �� nums[nums.length - 1]����
ȡ�������ֽ�����������Ƴ������鳤�ȼ� 1 �������ѡ�е����ֽ���ӵ����ĵ÷��ϡ�
��������û��ʣ�����ֿ�ȡʱ����Ϸ������
������ 1 �ܳ�ΪӮ�ң����� true �����������ҵ÷���ȣ�ͬ����Ϊ��� 1 ����Ϸ��Ӯ�ң�
Ҳ���� true ������Լ���ÿ����ҵ��淨����ʹ���ķ�����󻯡�
1 <= nums.length <= 20
0 <= nums[i] <= 107
���ӣ�https://leetcode-cn.com/problems/predict-the-winner
*/
//����dp ���Ӷ�O(n^2) 0ms
//dp[i][j]��ʾ�����±��i��j�����1�����֣����������2�����֣�������ֵ��
class Solution {
public:
    int dp[510][510];
    bool PredictTheWinner(vector<int>& nums) {
        int n=nums.size();
        //��ʼ״̬dp[i][i]=nums[i-1],��������С�������������1���һ����,�����ż���������2���һ����
        //������dp[1][n]��ʼ�������1������
        //��dp[1][n]>=0 ��˵�����1Ӯ
        for(int l=0;l<n;l++){
            for(int i=1;i+l<=n;i++){
                int j=i+l;
                dp[i][j]=max(nums[i-1]-dp[i+1][j],nums[j-1]-dp[i][j-1]);
            }
        }
        return dp[1][n]>=0;
    }
};

/*
//���� �ݹ� O(2^n) 168ms
class Solution {
public:
    int dfs(vector<int>& nums,int l,int r,int flag){
        if(l == r)
            return nums[l]*flag;
        int res1=nums[l]*flag+dfs(nums,l+1,r,-flag);
        int res2=nums[r]*flag+dfs(nums,l,r-1,-flag);
         //֮����max��߳�flag,��Ϊ��Ҫ��ȡ��ֵ�ϵ����ֵ,��Ϊ���1��2���Ǿ����ܷ�����󻯵�ȡ��,Ҫ�ָ��ɱ��������,������ٻָ������ٳ�flag
        return max(res1*flag,res2*flag)*flag;
    }
    bool PredictTheWinner(vector<int>& nums) {
        return dfs(nums,0,nums.size()-1,1)>=0;
    }
};
*/
