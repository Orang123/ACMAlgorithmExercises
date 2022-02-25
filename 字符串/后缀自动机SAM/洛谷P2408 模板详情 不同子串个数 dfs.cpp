#include<cstdio>
#include<cstring>
#define N 100100
struct node{
    int ch[26],fa,len;//ch 字符集大小 len表示该等价类的最长的字符串长度
    node(){
        memset(ch,0,sizeof(ch));
        len=0;
    }
}t[N<<1];
char s[N];
int last=1,tot=1;
long long dp[N<<1];
/*
后缀自动机(SAM-suffix automation machine) 所建立的边所构成的子串恰好是去重后的,所以可能看似不完整但实际是 所有不重复的子串,
即:对于任意两个 endposendpos 等价类，它们不会同时包含同一个子串，因此到达任意两个不同节点可能形成的字符串均不会重复。
每条从起点到终点的路径都代表一条后缀
对于长度为n的字符串 时间复杂度 O(n) 空间复杂度O(n),实际上空间这里我觉得应该大于n的 但要小于2n,因此我们预设的node的数组长度为N<<1
*/
void SAM(int c){
    int p=last,np=last=++tot;// last是未加入此字符前最长的前缀（整个串）所属的节点的编号， tot 则是当前后缀自动机节点的总数。
    t[np].len=t[p].len+1;
    /* 这里将新的字符加入先前每个后缀的尾部,
    因为由一个节点往外连一条边就等于允许到达此节点的所有字符串往尾部添加一个新的字符。
    所以我们把每一个节点想象成所有到达它的字符串的集合。那么，这个跳 fa(i)fa(i) 的操作可以理解为
    压缩地遍历一个串的所有后缀。在这里， p=fa(p)p=fa(p) 即从长到短遍历旧串的所有后缀。*/
    for(;p&&!t[p].ch[c];p=t[p].fa) t[p].ch[c]=np;// !p 只是防止其跳出根节点），即 p 没有一条 c 的出边。而 p 每一次循环后会跳到 t[p].fa，即 fa(p)。
    /* 如果已经遍历完了旧串的后缀且它们加 c 一个都不是旧串的子串，就说明 c 实际上是一个在旧串中没有出现过的字符，
    因此不可能存在除节点 1 以外的祖先，直接令 fa(np)=1。*/
    if(!p) t[np].fa=1;
    else{//p 在第一个有c边的祖先停下了
        int q=t[p].ch[c];//将q设为p的c出边到达的节点
        if(t[q].len==t[p].len+1) t[np].fa=q;//q是我们找到的第一个与np不同的且有后缀关系的节点，我们把fa(np)设为q
        else{//新建一个节点 nqnq ，让 endposendpos 多出了 nn 的字符串转移到此节点。
            int nq=++tot;
            t[nq]=t[q];
            t[nq].len=t[p].len+1;
            t[q].fa=t[np].fa=nq;
            for(;p&&t[p].ch[c]==q;p=t[p].fa) t[p].ch[c]=nq;
        }
    }
}

long long dfs(int p){//记忆化搜索
    if(dp[p]) return dp[p];//如果这个结点后的路径数统计过,就不再遍历
    for(int i=0;i<26;i++){
        if(t[p].ch[i])
            dp[p]+=dfs(t[p].ch[i])+1;//这里计算子串的方法 是从每个不同后缀 去枚举它的前缀开始的,因此深度遍历算路径数，一个节点下每有一个点，就多一条路径,就多一条不重复子串
    }
    return dp[p];
}

int main(){
    int n;
    long long sum=0;
    scanf("%d",&n);
    scanf("%s",s);
    for(int i=0;i<n;i++)
        SAM(s[i]-'a');
    printf("%lld\n", dfs(1));
    return 0;
}
