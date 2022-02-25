//ac 61ms ö��k����������ѭ������
/*
����:����n����ͬ��������,����k(k<=n)�Լ�һ��Ŀ������target.��
����n���������ҳ�k����,ʹ����k�����ĺ͵���Ŀ������,�����ж����ַ���?
����:https://www.lintcode.com/problem/k-sum/description
˼·:������ⱳ������k����Ʒ��ֵ�͸պ�Ϊtarget�ķ�������,��������Ҫ
ǡ��װ������,���Գ�ʼ��ֻ��dp[0][0]=1.

�ܽ�:�������ѭ��dp,ע��ڶ���ѭ���ȿ�����ö�ٱ���ʣ������Ҳ������
ö�ٵ�ǰ�����·�����Ʒ����k,������Ҫ������ö��,��Ϊֻ���������ܱ�֤
dp[j-val[i]][k-1]��ǰi-1����Ʒʱ��dpֵ,�������ö�ٻᵼ�µ�i����Ʒ�ظ�
���뱳��,����dp[j-val[i]][k-1]�Ƿ����i����Ʒʱ��ǰi����Ʒʱ��״̬������ǰi-1
����Ʒ��״̬.���������ѭ�������Ǳ����ݻ����Ƿ��뱳����Ʒ����,�ȿ�����Ҳ�ɽ���.
*/

/*
���û��Ҫ��k����,ֻ���ҳ������������֮��ǡ�õ���Ŀ������target,����һ���򵥵�01��������.��Ӧ�������P1164 СA���
ע��:���ֻ�����ǡ�õ���Ŀ�����ֵķ�������,������⾡���ܶ��װ�������ķ�����(������Ҳװ���µķ�����)
������Ҳװ���µķ����� ��ӦPOJ 3093 Margaritas on the River Walk������
��Ŀ����:https://nanti.jisuanke.com/t/T1218
    int kSum(vector<int> &A, int k, int target) {
        int n = A.size();
        int dp[1000];
        memset(dp,0,sizeof(dp));
        dp[0] = 1;
        for (int i = 0; i < n; i ++) {
            for (int t = target; t >= A[i]; t --) {
                dp[t]+=dp[t-A[i]];
            }
        }
        return dp[target];
    }
*/
class Solution {
public:
    /**
     * @param A: An integer array
     * @param k: A positive integer (k <= length(A))
     * @param target: An integer
     * @return: An integera
     * dp[k][j]��������Ϊj�ı���ǡ��װ��k����Ʒ���ܷ�����,��������jû��ʣ��
     */
    int kSum(vector<int> &A, int k, int target) {
        // write your code here
        int n = A.size();
        int dp[1000][1000];
        memset(dp,0,sizeof(dp));
        dp[0][0] = 1;//ǡ��װ�� ֻ�б�������Ϊ0,װ��0����Ʒ �ǳ�ʼ״̬,��ʼ��Ϊ1
        for (int i = 0; i < n; i ++) {
            for (int t = target; t >= A[i]; t --) {
                 for (int j = 1; j <= k; j ++) {//�������� ������Ҳ��ȷ
                    dp[j][t] += dp[j-1][t-A[i]];
                 }
            }
        }
        return dp[k][target];
    }
};
/*
//ac 61ms ö��k����������ѭ������
class Solution {
public:
    int kSum(vector<int> &A, int k, int target) {
        // write your code here
        int n = A.size();
        int dp[1000][1000];
        memset(dp,0,sizeof(dp));
        dp[0][0] = 1;
        for (int i = 0; i < n; i ++) {
            for (int t = target; t >= A[i]; t --) {
                 for (int j = k; j >= 1; j --) {//����������Ҳ��ȷ
                    dp[j][t] += dp[j-1][t-A[i]];
                 }
            }
        }
        return dp[k][target];
    }
};
*/
/*
//ac 102ms ö��k�����ڶ���ѭ������
class Solution {
public:
    int kSum(vector<int> &A, int k, int target) {
        // write your code here
        int n = A.size();
        int dp[1000][1000];
        memset(dp,0,sizeof(dp));
        dp[0][0] = 1;
        for (int i = 0; i < n; i ++) {
            for (int j = k; j >= 1; j --) {//����������������ȷ
                for (int t = target; t >= A[i]; t --) {
                    dp[j][t] += dp[j-1][t-A[i]];
                }
            }
        }
        return dp[k][target];
    }
};
*/

/*
//ac 102ms ����ά[A[i],target] ����
class Solution {
public:
    int kSum(vector<int> &A, int k, int target) {
        // write your code here
        int n = A.size();
        int dp[1000][1000];
        memset(dp,0,sizeof(dp));
        dp[0][0] = 1;
        for (int i = 0; i < n; i ++) {
            for (int j = k; j >= 1; j --) {//����������������ȷ
                for (int t = A[i]; t <= target; t ++) {
                    dp[j][t] += dp[j-1][t-A[i]];
                }
            }
        }
        return dp[k][target];
    }
};
*/
