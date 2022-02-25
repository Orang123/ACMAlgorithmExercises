/*
D Substring http://172.22.112.249/exam/index.php/problem/exam_read/id/1363/exam_id/161

思路：
尝试了一下复杂度O(T*|S|log|S|26)的做法，由于常数太大了，TLE，
想了一下应该可以把26个字符压缩一下，说不定能过。
谢大的做法应该是最优解，复杂度O(T|S|*26)

Eric的想法:
尺取吧
求一个最短的子串，包含所有的英文字母
依次扫描字符串，维护所有字母出现最右的位置，判断这些位置中最左的位置，更新答案
此题和HDU 5672 String是一道题,是此题的弱化版。
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int vis[256];
int main(){
    char s[2005];
    while(scanf("%s",s+1)!=EOF){
        memset(vis,0,sizeof vis);
        int cnt=0;
        int len=strlen(s+1);
        int ans=0x3f3f3f3f;
        for(int i=1;i<=len;i++){
            if(vis[s[i]]==0){
                cnt++;
            } vis[s[i]]=i;
            if(cnt==26){
                int dis=INT_MIN;
                for(int j='a';j<='z';j++){
                    dis=max(dis , i-vis[j]+1);
                }
                ans = min( ans , dis);
            }
        }
        if(cnt<26)ans=0;
        cout<<ans<<endl;
    }
    return 0;
}
/*
上述代码来自 屈京 这个并不是尺取
---------------------
作者：mMingfunnyTree
来源：CSDN
原文：https://blog.csdn.net/mMingfunnyTree/article/details/80696847
版权声明：本文为博主原创文章，转载请附上博文链接！
*/
