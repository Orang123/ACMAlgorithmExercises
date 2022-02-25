//邻接表Time：234ms；Memory：5284kB
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define LL long long
#define CLR(x) memset(x,0,sizeof(x))
#define mod 9973
#define man 262144
const int maxn = 100005;

struct PAM
{
    vector<pair<int,int> > next[maxn];
    int fail[maxn], num[maxn],len[maxn], cnt[maxn];
    int s[maxn], n, p, last;

    int newnode(int w)
    {
        next[p].clear();
        cnt[p]=num[p]=0;
        len[p]=w;
        return p++;
    }
    void init()
    {
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        s[n] = -1;
        fail[0] = 1;
    }
    int get_fail(int x)
    {
        while(s[n-len[x]-1] != s[n]) x = fail[x];
        return x;
    }
    void add(int c)
    {
        c -= 'a';
        s[++n] = c;
        int cur = get_fail(last);
        int flag = 0;
        for(int i=0; i<next[cur].size(); i++)
            if(next[cur][i].first==c)
            {
                last = next[cur][i].second;
                cnt[last]++;
                return ;
            }
        int now = newnode(len[cur]+2);
        int fi = get_fail(fail[cur]);
        flag = 0;
        for(int i=0; i<next[fi].size(); i++)
            if(next[fi][i].first==c)
            {
                flag = next[fi][i].second;
                break;
            }
        fail[now] = flag;
        next[cur].push_back(make_pair(c,now));
        num[now] = num[flag] + 1;
        last = now;
        cnt[now]++;
    }
    void count()
    {
        for(int i=p-1; i>1; i--)
        {
            cnt[fail[i]] += cnt[i];
        }
    }
} PaTree;

int main()
{
    char str[maxn];
    scanf("%s", str);
    PaTree.init();
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        PaTree.add(str[i]);
        printf("%d", PaTree.p-2);
        if (i != len-1) printf(" ");
    }
    return 0;
}