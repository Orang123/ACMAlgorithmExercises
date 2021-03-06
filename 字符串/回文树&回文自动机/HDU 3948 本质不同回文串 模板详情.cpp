#include<cstdio>
#include<cstring>
#define N 100100
/* manacher能解决的问题 PAM一定能解决，PAM能解决的 manacher解决起来可能会很繁琐，但有些简单问题manacher解决效率要高些*/
/*对于一个字符串  ，它的本质不同回文子串个数最多只有|s|个。 因此PAM的结点数最多有strlen(s)+2个 时间复杂度就是O(n*26)即O(n) 空间复杂度O(n*26) 官方是n*log(alp) alp为字符集(26个英文字母)大小 不太理解alp实际alp可忽略 时间复杂度 可以当做线性的*/
struct PAM{//PAM Palindrome Auto Machine 回文自动机
    int s[N];//表示第i次添加的字符
    int n;//当前添加的字符的小标
    int p;//当前添加的PAM中节点的下标
    int last;//指向上一次新添加一个字母后所形成的较长回文串表示的结点下标编号
    int next[N][26];//next[i][c]表示编号为i的节点表示的回文串在两边各添加一个字符c以后形成的回文串的结点编号（类似字典树的公共前缀）。
    int fail[N];//后缀指针 指向当前节点 所表示的回文串的最长回文后缀所代表的结点下标
    int len[N];//记录PAM中结点所代表的回文串的长度
    int cnt[N];//记录结点所表示的本质不同回文串出现的次数,构建自动机时cnt并不完整(主要集中在父亲节点),需要后期cnt[fail[i]]+=cnt[i]累加以后才是完整的
    int num[N];//表示以下标i代表的字符作为最右端点结尾的回文串的个数

    int newNode(int l){//新建结点
        for(int i=0;i<26;i++) next[p][i]=0;//将其儿子节点置0,避免构建第2个PAM时 上一次的儿子 已经构建过 导致重复 会出错
        len[p]=l;
        cnt[p]=0;//初始化时 cnt、num都为0
        num[p]=0;
        return p++;
    }

    void init(){
        p=0;
        /* PAM(回文自动机)是由2棵树构成，一条偶回文串根，一条奇回文串根
        */
        newNode(0);//偶根 默认长度为0,其扩展后的回文结点 长度为偶数
        newNode(-1);//奇根 默认长度为-1，这样扩展后的回文结点长度都为奇数
        n=0;
        last=0;
        s[0]=-1;//默认下标为0的位置必须和后续添加的字符不同，设置为-1 这样比较相等时便不会相等
        fail[0]=1;//偶根的后缀指针指向奇根
        fail[1]=0;//奇根实际是没有后缀指针的，但是add时仍旧会用到fail[1]这个概念，其值是为0的
    }

    //这里时间复杂度 最多为O(n/2) 绝大多数时候循环是一个常数 因此时间复杂度可以粗略算为O(1)
    int getFail(int x){
        /* 尝试在上一个节点所构成的回文串的基础上 可否构成长度
        为原先长度+2的更大长度的回文串,第一个x表示的len[x]代表上一个结点
        构成的回文串的长度实际就是判断s串这个len[x]表示的回文串的两端字符是否相等
        即当前添加字符与上个回文串紧挨着的左端的字符是否相等是否能构成更大回文串若不能
        x=fail[x],尝试其较短的回文后缀是否能作为中间回文匹配这个新添加的字符
        即:若原先是yAx不匹配将A缩小考虑其回文后缀即y[...xB]x是否匹配构成新的回文
        fail指针越往上跳，对应的回文后缀长度越短直到这个回文串最右端字符单独成一个回文串 */
        while(s[n-len[x]-1] != s[n]) x=fail[x];//因为减len[x]才刚刚到原先回文串的开头 要比较的是回文串紧邻的左端的字符，即减1
        return x;//发现匹配时，返回这个回文后缀的结点编号,这个结点便是新节点的父亲结点
    }

    void add(int c){
        c-='a';
        s[++n]=c;
        int cur=getFail(last);
        if(!next[cur][c]){//如果这个结点没有出现过,就新生成一个结点代表本质不同的新的回文串
            int now=newNode(len[cur]+2);//新回文串是在cur结点的基础上在两端都加上c字符构成的 即长度+2
            /*新结点的后缀回文指针指向原先cur结点的后缀回文判断能否和当前加入字符匹配构成新的回文后缀，则这里根据对称性
            cur结点表示的回文串A内部c[Bc...cB]c则新结点的回文后缀就为cB]c,因为现在xAx已经是新的回文串了,
            如果A中有回文后缀B与c能构成回文后缀...cB]c，那么根据A的对称性其前缀也一定存在一个回文B想对应即c[Bc...
            实际fail[now]所指向的是...cB]c与之对称的回文前缀c[Bc...即next[getFail(fail[cur])][c] 是next扩展的c结点刚好是c[Bc
            这里需要注意若A中的回文后缀没有一个可与c构成新的回文后缀则会考虑直接将c与A的最后一个字符比较是否构成长度为2的回文如若也不匹配
            则这个c字符单独成为一个回文串,fail[now]回文后缀指向字符c本身但这里实际指向的是奇根下第一次出现的c字符*/
            fail[now]=next[getFail(fail[cur])][c];
            next[cur][c]=now;//cur当前的结点扩展的回文串指向now即cAc
            num[now]=num[fail[now]]+1;//当前回文串的回文后缀个数为上一个回文后缀的个数加1num[fail[now]]+1
        }
        last=next[cur][c];//last记录这次新添加的回文串结点或之前添加过重复的结点
        cnt[last]++;//这个本质不同回文串结点出现次数+1
        /* 这里需要注意cnt[last]++有时会因为构成了更大长度的新的回文串导致这个新添加的字符可能与较小长度的回文后缀构成的回文串重复出现没被统计列如
        构成了回文串bbaabb但是 bb重复的出现缺没被统计,这个可以在cnt后续的累加cnt[fail[i]]+=cnt[i]完成对其bb出现次数的更新即cnt[bb]+=cnt[bbaabb]*/
    }

    void countAllNum(){
        /*后缀回文子串累加其本身回文串 即若bbaabb出现了1次那么回文后缀bb也必然出现了一次，那么回文后缀b也必然出现了一次* 总共b出现了3次*/
        for(int i=p-1;i>=2;i--) cnt[fail[i]]+=cnt[i];
    }

}pam;

int main(){
    int T,index=1;
    char a[N];
    scanf("%d",&T);
    while(T--){
        scanf("%s",a);
        int len=strlen(a);
        pam.init();//每次构建PAM需要初始化
        for(int i=0;i<len;i++)//O(n)
            pam.add(a[i]);
        printf("Case #%d: %d\n",index,pam.p-2);//所有本质不同的回文子串即PAM中除偶数根节点和奇数根节点之外的结点个数
        index++;
    }
    return 0;
}
