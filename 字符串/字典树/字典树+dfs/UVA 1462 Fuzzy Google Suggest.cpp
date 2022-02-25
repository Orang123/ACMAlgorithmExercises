/*
题意:摘自网上
要模拟谷歌的模糊搜索，先有n个模式串，然后输入m个文本串单词查询，
这个单词可以进行最多x次操作，每次操作可以删除一个字符，修改一个字符，
或增添一个字符，问这样这个单词最多可以匹配多少个模式串前缀.
n<=300000,m<=300.0<=x<=2.每个单词的长度<=10.
链接:
思路:先将n个模式串构建到字典树中,对于每个文本串单词的查询,dfs按照字典树
去查询,对于删除操作,实际是直接将文本串当前下标右移一位,但字典树的根节点
编号不变.对于插入操作实际是将字典树向下再搜索一层,但文本串下标不变,对于
修改操作字典树会向下搜索一层,文本串也会下标也会右移一位.当然也可以直接
按照文本串对应的当前下标的字符让字典树向下搜索,不使用操作次数x.注意对于
每个文本串的查询,每次都需要清空vis数组,但因为vis数组大小有3000010,因此不能
直接使用memset,会TLE,需要在dfs搜索时标记走过的字典树节点,清空时按照走过的标记复原.

对于找到的前缀要用vis标记,计数时单独计数,计数只考虑较前的前缀,只要字典树的某个前缀
计数过,就不再往下搜索计数,不然会重复计数.
*/

//ac 610ms
#include<cstdio>
#include<cstring>
#define N 3000010

int n,m,tr[N][26],wordCnt[N],vis[N],cnt,ans;
char s[20];

int newNode(){
    cnt++;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    wordCnt[cnt]=0;
    return cnt;
}

void insertWord(){
    int rt=0,son,len=strlen(s);
    for(int i=0;i<len;i++){
        son=s[i]-'a';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
        wordCnt[rt]++;//记录每个模式串前缀出现次数
    }
}

void dfs(int rt,int k,int x,int len){
	if(x<0)
		return;
    if(!vis[rt])
        vis[rt]=1;//标记搜索过的字典树的节点
    if(k == len){//文本串匹配完成
        vis[rt]=2;//标记匹配到的字典树前缀编号为2
        return;
    }
    int son=s[k]-'a';
    dfs(rt,k+1,x-1,len);//删除文本串下标为k的字符,字典树的当前根节点并没有去比较,因此不变
    for(int i=0;i<26;i++){
        if(tr[rt][i]){
        	if(i == son)//字典树中恰好存在s[k]的儿子 可以匹配,直接向下搜索,无需使用操作次数x
				dfs(tr[rt][son],k+1,x,len);
            if(i!=son)//剩余操作次数不为0时 将当前s[k]修改为 a+i的字符向下匹配
                dfs(tr[rt][i],k+1,x-1,len);
			//在下标为k的字符前面插入一个 a+i的字符,字典树向第i个儿子往下搜索,文本串下标k不变
            dfs(tr[rt][i],k,x-1,len);
        }
    }
}

void solve(int rt){
    if(vis[rt] == 2){
        ans+=wordCnt[rt];//累加匹配到的前缀的个数
        return;//只计数较短的前缀,因为可以删除、添加、修改,有可能某一个单词可以匹配多个前缀
    }
    for(int i=0;i<26;i++){
    	if(!tr[rt][i]) continue;
        if(vis[tr[rt][i]])
            solve(tr[rt][i]);
    }
}

void clr(int rt){//清空之前标记的字典树节点
    vis[rt]=0;
    for(int i=0;i<26;i++){
    	if(!tr[rt][i]) continue;
        if(vis[tr[rt][i]])
            clr(tr[rt][i]);
    }
}

int main(){
    int x,len;
    cnt=-1;
    newNode();
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",s);
        insertWord();
    }
    scanf("%d",&m);
    while(m--){
        scanf("%s %d",s,&x);
        len=strlen(s);
        //对于len=1 x=1的情况,实际应该输出n,但这个程序因为删除操作 只会输出0,但是这样特判UVA 会wa
        dfs(0,0,x,len);
        ans=0;
        solve(0);
        clr(0);
        printf("%d\n",ans);
    }
    return 0;
}
