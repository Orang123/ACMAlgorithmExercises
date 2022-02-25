/*
在 LeetCode 商店中， 有 n 件在售的物品。每件物品都有对应的价格。
然而，也有一些大礼包，每个大礼包以优惠的价格捆绑销售一组物品。
给你一个整数数组 price 表示物品价格，其中 price[i] 是第 i 件物品的价格。
另有一个整数数组 needs 表示购物清单，其中 needs[i] 是需要购买第 i 件物品的数量。
还有一个数组 special 表示大礼包，special[i] 的长度为 n + 1 ，其中 special[i][j]
表示第 i 个大礼包中内含第 j 件物品的数量，且 special[i][n] （也就是数组中的最后一个整数）
为第 i 个大礼包的价格。返回 确切 满足购物清单所需花费的最低价格，你可以充分利用大礼包的优惠活动。
你不能购买超出购物清单指定数量的物品，即使那样会降低整体价格。任意大礼包可无限次购买。
链接：https://leetcode-cn.com/problems/shopping-offers
*/
//状压dp 32ms 1771560 因为每个物品最多需要10个,11进制数表示剩余需要物品的状态
class Solution {
public:
    int dp[1771561];//1771560 因为每个物品最多需要10个,11进制数表示剩余需要物品的状态
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
        for(int i=0;i<price.size();i++)//默认是单个买
            dp[sta]+=price[i]*needs[i];
        for(auto &tp : sp){//礼包数量无限 只要满足条件可以无限制选取
            int n=tp.size(),flag=0;
            for(int i=0;i<n-1;i++){
                if(needs[i]<tp[i])
                    flag=1;
                needs[i]-=tp[i];
            }
            if(!flag)
                dp[sta]=min(dp[sta],dfs(price,needs)+tp[n-1]);
            for(int i=0;i<n-1;i++)//还原需要的needs数组
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
                if(val[i]>needs[i]){//礼包购买的数量比要求的还多 不满足条件
                    flag=1;
                    break;
                }
                cost+=price[i]*val[i];
            }
            if(!flag && cost>val[n-1])//礼包的价格必须比单买的划算才合格
                sp.push_back(val);//sp为满足条件削减数量后的大礼包
        }
        return dfs(price,needs);
    }
};

/*
//记忆化搜索 不同物品 不同数量 6维dp数组标记重复状态 36ms
class Solution {
public:
    int dp[11][11][11][11][11][11];
    vector<vector<int>> sp;
    int dfs(vector<int>& price,vector<int>& needs){
        int &ans=dp[needs[0]][needs[1]][needs[2]][needs[3]][needs[4]][needs[5]];
        if(ans)
            return ans;
        for(int i=0;i<price.size();i++)//默认是单个买
            ans+=price[i]*needs[i];
        for(auto &tp : sp){//礼包数量无限 只要满足条件可以无限制选取
            int n=tp.size(),flag=0;
            for(int i=0;i<n-1;i++){
                if(needs[i]<tp[i])
                    flag=1;
                needs[i]-=tp[i];
            }
            if(!flag)
                ans=min(ans,dfs(price,needs)+tp[n-1]);
            for(int i=0;i<n-1;i++)//还原需要的needs数组
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
                if(val[i]>needs[i]){//礼包购买的数量比要求的还多 不满足条件
                    flag=1;
                    break;
                }
                cost+=price[i]*val[i];
            }
            if(!flag && cost>val[n-1])//礼包的价格必须比单买的划算才合格
                sp.push_back(val);//sp为满足条件削减数量后的大礼包
        }
        while(needs.size()!=6)//不够6个添加到6个
            needs.push_back(0);
        return dfs(price,needs);
    }
};
*/
