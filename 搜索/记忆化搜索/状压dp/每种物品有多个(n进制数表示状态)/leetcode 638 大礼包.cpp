/*
�� LeetCode �̵��У� �� n �����۵���Ʒ��ÿ����Ʒ���ж�Ӧ�ļ۸�
Ȼ����Ҳ��һЩ�������ÿ����������Żݵļ۸���������һ����Ʒ��
����һ���������� price ��ʾ��Ʒ�۸����� price[i] �ǵ� i ����Ʒ�ļ۸�
����һ���������� needs ��ʾ�����嵥������ needs[i] ����Ҫ����� i ����Ʒ��������
����һ������ special ��ʾ�������special[i] �ĳ���Ϊ n + 1 ������ special[i][j]
��ʾ�� i ����������ں��� j ����Ʒ���������� special[i][n] ��Ҳ���������е����һ��������
Ϊ�� i ��������ļ۸񡣷��� ȷ�� ���㹺���嵥���軨�ѵ���ͼ۸�����Գ�����ô�������Żݻ��
�㲻�ܹ��򳬳������嵥ָ����������Ʒ����ʹ�����ή������۸��������������޴ι���
���ӣ�https://leetcode-cn.com/problems/shopping-offers
*/
//״ѹdp 32ms 1771560 ��Ϊÿ����Ʒ�����Ҫ10��,11��������ʾʣ����Ҫ��Ʒ��״̬
class Solution {
public:
    int dp[1771561];//1771560 ��Ϊÿ����Ʒ�����Ҫ10��,11��������ʾʣ����Ҫ��Ʒ��״̬
    vector<vector<int>> sp;

    int cal(vector<int>& needs){
        int sta=0;
        for(int i=0;i<needs.size();i++)
            sta=sta*11+needs[i];
        return sta;
    }

    int dfs(vector<int>& price,vector<int>& needs){
        int sta=cal(needs);
        if(dp[sta])
            return dp[sta];
        for(int i=0;i<price.size();i++)//Ĭ���ǵ�����
            dp[sta]+=price[i]*needs[i];
        for(auto &tp : sp){//����������� ֻҪ������������������ѡȡ
            int n=tp.size(),flag=0;
            for(int i=0;i<n-1;i++){
                if(needs[i]<tp[i])
                    flag=1;
                needs[i]-=tp[i];
            }
            if(!flag)
                dp[sta]=min(dp[sta],dfs(price,needs)+tp[n-1]);
            for(int i=0;i<n-1;i++)//��ԭ��Ҫ��needs����
                needs[i]+=tp[i];
        }
        return dp[sta];
    }

    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        int cost,flag,n;
        for(auto &val : special){
            flag=cost=0;
            n=val.size();
            for(int i=0;i<n-1;i++){
                if(val[i]>needs[i]){//��������������Ҫ��Ļ��� ����������
                    flag=1;
                    break;
                }
                cost+=price[i]*val[i];
            }
            if(!flag && cost>val[n-1])//����ļ۸����ȵ���Ļ���źϸ�
                sp.push_back(val);//spΪ������������������Ĵ����
        }
        return dfs(price,needs);
    }
};

/*
//���仯���� ��ͬ��Ʒ ��ͬ���� 6άdp�������ظ�״̬ 36ms
class Solution {
public:
    int dp[11][11][11][11][11][11];
    vector<vector<int>> sp;
    int dfs(vector<int>& price,vector<int>& needs){
        int &ans=dp[needs[0]][needs[1]][needs[2]][needs[3]][needs[4]][needs[5]];
        if(ans)
            return ans;
        for(int i=0;i<price.size();i++)//Ĭ���ǵ�����
            ans+=price[i]*needs[i];
        for(auto &tp : sp){//����������� ֻҪ������������������ѡȡ
            int n=tp.size(),flag=0;
            for(int i=0;i<n-1;i++){
                if(needs[i]<tp[i])
                    flag=1;
                needs[i]-=tp[i];
            }
            if(!flag)
                ans=min(ans,dfs(price,needs)+tp[n-1]);
            for(int i=0;i<n-1;i++)//��ԭ��Ҫ��needs����
                needs[i]+=tp[i];
        }
        return ans;
    }

    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        int cost,flag,n;
        for(auto &val : special){
            flag=cost=0;
            n=val.size();
            for(int i=0;i<n-1;i++){
                if(val[i]>needs[i]){//��������������Ҫ��Ļ��� ����������
                    flag=1;
                    break;
                }
                cost+=price[i]*val[i];
            }
            if(!flag && cost>val[n-1])//����ļ۸����ȵ���Ļ���źϸ�
                sp.push_back(val);//spΪ������������������Ĵ����
        }
        while(needs.size()!=6)//����6����ӵ�6��
            needs.push_back(0);
        return dfs(price,needs);
    }
};
*/
