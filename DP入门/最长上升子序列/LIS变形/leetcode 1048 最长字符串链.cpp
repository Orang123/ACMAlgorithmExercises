/*
给出一个单词数组 words ，其中每个单词都由小写英文字母组成。
如果我们可以 不改变其他字符的顺序 ，在 wordA 的任何地方添加 恰好一个 字母使其变成 wordB ，
那么我们认为 wordA 是 wordB 的 前身 。
例如，"abc" 是 "abac" 的 前身 ，而 "cba" 不是 "bcad" 的 前身
词链是单词 [word_1, word_2, ..., word_k] 组成的序列，k >= 1，其中 word1 是 word2 的前身，
word2 是 word3 的前身，依此类推。一个单词通常是 k == 1 的 单词链 。
从给定单词列表 words 中选择单词组成词链，返回 词链的 最长可能长度 。
链接：https://leetcode-cn.com/problems/longest-string-chain
思路:
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
dp+哈希的老套路了。先对单词数组按照单词长度进行排序，使用map记录每个单词在排序后的数组中的位置。
设dp[i]为以单词i作为结尾的最长链长度，则dp[i] = max(dp[i] , dp[j] + 1)，
其中j是与单词i只相差一个字符的单词在数组中的位置，该位置直接通过map可查。
*/
class Solution {
public:
    int dp[1100];
    int longestStrChain(vector<string>& words) {
        int n=words.size();
        for(int i=0;i<n;i++)
            dp[i]=1;
        sort(words.begin(),words.end(),[](string &a,string &b){
            return a.size()<b.size();
        });
        unordered_map<string,int> mp;
        int ans=1;
        for(int i=0;i<n;i++){
            mp[words[i]]=i+1;//记录i+1,是为了避免 判断mp[s]是否存在时 和0区分开
            if(words[i].size()<2)
                continue;
            for(int j=0;j<words[i].size();j++){
                string s=words[i].substr(0,j)+words[i].substr(j+1,words[i].size()-j-1);
                if(mp[s])//实际下标记录时都加了1,
                    dp[i]=max(dp[i],dp[mp[s]-1]+1);//这里上一状态下标要减1,因为dp[i]的i并没有加1
            }
            ans=max(ans,dp[i]);
        }
        return ans;
    }
};
