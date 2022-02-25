/*
题意:摘自网上
给出n个模式串，串中除开小写字母外，？代表一个字符，
*代表可空的任意字符串，然后再给出m个字符串，问有多少
个模式串可以与之匹配。
说明:'*'字符可以一个也不匹配.
n<=100000,m<=100,模式串长度<=6,文本串长度<=20.
链接:http://poj.org/problem?id=1816
思路:对于'*'号需要枚举匹配文本串几个字符,这需要dfs回溯
实现,但如果每个模式串都和文本串暴力做一遍dfs匹配,复杂度很大,
肯定会TLE,而且模式串长度不超过6,这些模式串字符串可能构成了某些
模式串的前缀,显然可以将所有的模式串构建到一个字典树里,这样匹配时
对于相同的前缀实际只计算了一次,对于有重叠的模式串也会沿着子节点
一直计算下去,并且只计算一次.因此直接对构建好的字典树和文本串做匹配,
只用一次dfs即可统计出所有满足匹配条件的模式串编号.

需要注意:
1.模式串可能有重复,因此在字典树里标记模式串编号,要用一个vector将重复的前缀
的编号全加进去.
2.dfs对于'*'号枚举,可以不匹配,这样就有可能导致dfs搜索到重复的方案,因此输出时
要对编号判重.
*/

/*
一个dfs枚举出现重复编号的例子
模式串:*j*j
文本串:jj、jjj
对于文本串jj,模式串的两个'*'都不做匹配,这样才能走到字典树的叶子节点第二个'j'.
但是对于文本串jjj,模式串中的两个'*'必然要有一个是不能匹配的,这样才能走到字典树
的叶子节点第二个'j',才能完成匹配,那么实际就有2种方案,要么第一个'*'不匹配,要么
第二个'*'不匹配.
*/

//ac 891ms
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 600010
using namespace std;

int n,m,tr[N][28],cnt,slen;
char s[30];
vector<int> wordId[N],ans;

int newNode(){
    cnt++;
    for(int i=0;i<28;i++)
        tr[cnt][i]=0;
    wordId[cnt].clear();
    return cnt;
}

int check(char x){
    if(x == '?')
        return 26;
    if(x == '*')
        return 27;
    return x-'a';
}

void insertWord(int id){
    int rt=0,son,len=strlen(s);
    for(int i=0;i<len;i++){
        son=check(s[i]);
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
    wordId[rt].push_back(id);//模式串可能重复
}

void dfs(int rt,int i){
    //这个'*'号选取必须放最前面考虑,否则会TLE,不知原因
    if(tr[rt][27]){//27 考虑'*'号配对
        //j=i的情况 就是'*'号一个字符也不匹配,输入样例中文本串"the" 模式串"??e*"的情况,
        //对于最后的'*'号实际就可以不匹配,但"??e*"仍然是可以配对"the"的
        for(int j=i;j<=slen;j++)//枚举'*'号配对从i开始的几个文本串字符
            dfs(tr[rt][27],j);
    }
    //当当前字典树前缀构成模式串,并且文本串s匹配完成 即可记录欧世川编号.
    if(wordId[rt].size() && i == slen){
        for(int i=0;i<wordId[rt].size();i++)
            ans.push_back(wordId[rt][i]);
        return;
    }
    if(i == slen)//文本串已经匹配完,字典树的前缀还没能构成满足条件的模式串就返回
        return;
    //考虑字母 配对
    if(s[i]>='a' && s[i]<='z'){
        if(tr[rt][s[i]-'a'])
            dfs(tr[rt][s[i]-'a'],i+1);
    }
    //26 '?'号配对
    if(tr[rt][26])
        dfs(tr[rt][26],i+1);
}

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        cnt=-1;
        newNode();
        for(int i=0;i<n;i++){
            scanf("%s",s);
            insertWord(i);
        }
        while(m--){
            ans.clear();
            scanf("%s",s);
            slen=strlen(s);
            dfs(0,0);
            if(ans.size()){
                sort(ans.begin(),ans.end());
                printf("%d",ans[0]);
                for(int i=1;i<ans.size();i++){
                    if(ans[i]!=ans[i-1])//重复编号不输出
                        printf(" %d",ans[i]);
                }
                printf("\n");
            }
            else
                printf("Not match\n");
        }
    }
    return 0;
}
