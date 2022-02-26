/*
设计一个 map ，满足以下几点:

字符串表示键，整数表示值
返回具有前缀等于给定字符串的键的值的总和
实现一个 MapSum 类：

MapSum() 初始化 MapSum 对象
void insert(String key, int val) 插入 key-val 键值对，字符串表示键 key ，整数表示值 val 。如果键 key 已经存在，那么原来的键值对 key-value 将被替代成新的键值对。
int sum(string prefix) 返回所有以该前缀 prefix 开头的键 key 的值的总和。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/map-sum-pairs
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
//trie 暴力dfs求和
// class MapSum {
// public:
//     int tr[100010][26],vis[100010],id;
//     MapSum() {
//         id=0;
//         memset(tr,0,sizeof(tr));
//         memset(vis,0,sizeof(vis));
//     }

//     void insert(string key, int val) {
//         int rt=0;
//         for(int i=0;i<key.size();i++){
//             int son=key[i]-'a';
//             if(!tr[rt][son])
//                 tr[rt][son]=++id;
//             rt=tr[rt][son];
//         }
//         vis[rt]=val;
//     }

//     int dfs(string &s,int rt){
//         int res=vis[rt];
//         for(int i=0;i<26;i++){
//             if(tr[rt][i])
//                 res+=dfs(s,tr[rt][i]);
//         }
//         return res;
//     }

//     int sum(string prefix) {
//         int rt=0;
//         for(int i=0;i<prefix.size();i++){
//             int son=prefix[i]-'a';
//             if(!tr[rt][son])
//                 return 0;
//             rt=tr[rt][son];
//         }
//         return dfs(prefix,rt);
//     }
// };

//trie+map记录已经插入的单词
class MapSum {
public:
    unordered_map<string,int> mp;
    int tr[100010][26],vis[100010],id;
    MapSum() {
        id=0;
        memset(tr,0,sizeof(tr));
        memset(vis,0,sizeof(vis));
    }

    void insert(string key, int val) {
        int delta=val;
        if(mp.count(key))//如果已经插入过该单词,则求出当前单词和之前单词 数值的差值,对差值进行累加
            delta-=mp[key];
        int rt=0;
        for(int i=0;i<key.size();i++){
            int son=key[i]-'a';
            if(!tr[rt][son])
                tr[rt][son]=++id;
            rt=tr[rt][son];
            vis[rt]+=delta;
        }
        mp[key]=val;
    }

    int sum(string prefix) {
        int rt=0;
        for(int i=0;i<prefix.size();i++){
            int son=prefix[i]-'a';
            if(!tr[rt][son])
                return 0;
            rt=tr[rt][son];
        }
        return vis[rt];
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */
//map
// class MapSum {
// public:
//     map<string,int> mp;
//     /** Initialize your data structure here. */
//     MapSum() {

//     }

//     void insert(string key, int val) {
//         mp[key] = val;
//     }

//     int sum(string prefix) {
//         int ans = 0;
//         string s;
//         for(auto it=mp.begin();it!=mp.end();it++)
//         {
//             s = it->first;
//             if(s.find(prefix)==0)
//             {
//                 ans += (it->second);
//             }
//         }
//         return ans;
//     }
// };
