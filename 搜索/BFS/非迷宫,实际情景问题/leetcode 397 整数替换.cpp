/*
题意:给定一个正整数 n ，你可以做如下操作：
如果 n 是偶数，则用 n / 2替换 n 。
如果 n 是奇数，则可以用 n + 1或n - 1替换 n 。
n 变为 1 所需的最小替换次数是多少？
1 <= n <= 2^31 - 1
链接:https://leetcode-cn.com/problems/integer-replacement/
*/

//bfs
typedef long long ll;
class Solution {
public:
    unordered_map<ll,int> mp;//n最大可达2^31-1,开不了O(n)的vis数组,可以用map去重
    struct State{
        ll n;
        int s;
        State(ll n=0,int s=0):n(n),s(s){}
    };

    int bfs(int n){
        queue<State> Q;
        Q.push(State(n,0));
        mp.insert(make_pair(n,0));
        State tp;
        while(!Q.empty()){
            tp=Q.front();
            if(tp.n == 1)
                return tp.s;
            Q.pop();
            if(tp.n%2 == 0 && !mp.count(tp.n/2)){
                mp.insert(make_pair(tp.n/2,tp.s+1));
                Q.push(State(tp.n/2,tp.s+1));
            }
            else if(tp.n%2){
                if(!mp.count(tp.n-1)){
                    mp[tp.n-1]=tp.s+1;
                    Q.push(State(tp.n-1,tp.s+1));
                }
                if(!mp.count(tp.n+1)){
                    mp[tp.n+1]=tp.s+1;
                    Q.push(State(tp.n+1,tp.s+1));
                }
            }
        }
        return -1;
    }

    int integerReplacement(int n) {
        return bfs(n);
    }
};

/*
//IDA*
typedef long long ll;
class Solution {
public:

    int dfs(ll n,int k,int dep){
        if(n == 1)
            return 1;
        if(k == dep)
            return 0;
        if(n%2 == 0)
            return dfs(n/2,k+1,dep);
        else
            return dfs(n+1,k+1,dep) | dfs(n-1,k+1,dep);
    }

    int integerReplacement(int n) {
        for(int i=0;i<n;i++){
            if(dfs(n,0,i))
                return i;
        }
        return -1;
    }
};
*/
