/*
题意:摘自网上
文章段落长度限制长度为n，然后在给出一篇文章，有若干个单词，以空行结束，
现在要将文章排序使得文章的badness越小。badness的计算方法，如果一行只有
一个单词的话，若单词的长度小于n，则badness 增加500，否则为0。
若一行有多个单词，每两个单词之间的badness = （c - 1) ^ 2 (c为两个单词的空格数），
要求，每行控制长度在n，并且前一个单词顶头，后一个单词顶尾（一个单次的情况除外）。
n<=80,输入文章一段长度上限为10000.
链接:https://www.luogu.com.cn/problem/UVA709
思路:因为文章的规范是如果一行有多个单词,那么一个段落头尾必须都有单词衔接才行.
也就是说现在需要调整单词之间的间距 使得所添加的最后一个单词能刚好填满该行,但是
调整的间隙情况是不确定的,并不是说单词之间的间隙越小越好,有可能前面单词长度都较短,
如果间隙比较小,最后一个单词长度较长,想要将最后一个单词恰好贴紧行尾部,之间的间隙差
距就会比较大,这个badness就会较大,但是可以考虑将前面长度较小的单词间隙调整的大一点,
使得较大长度单词能恰好放置在下一行,并且和后面单词的间隙都能调整得较小,这样整体的
badness会更优,总之最好的情况是不好确定的,需要枚举所有间隙调整的可能性,但在这个过程中,
对于第i个单词放置在某一行第j个位置这个状态 在很多调整间隙情况下会重复出现,属于重叠子
问题.需要将结果记录下来.终止状态就是将所有单词都放置完毕时.

因此记忆化搜索.dp[i][j]表示第i个单词放置在某一行,且之前已经放置了j个位置时,第i个单词
包括其后所有单词放置时所能产生的最小badness.
path[i][j]=p记录第i个单词在第j+1个位置后面产生的空格所占得最后一个位置为p.
path[i][j]=0,代表第i个单词后没有单词尾随了,可以输出换行符了.

//较好的博客讲解:https://www.cnblogs.com/scau20110726/archive/2012/10/01/2709458.html
*/
//ac 10ms 记忆化搜索
//dp[i][j]表示第i个单词放置在某一行,且之前已经放置了j个位置时,第i个单词包括其后
//所有单词放置时所能产生的最小badness.
//path[i][j]=p记录第i个单词在第j+1个位置后面产生的空格所占得最后一个位置为p.
//path[i][j]=0,代表第i个单词后没有单词尾随了,可以输出换行符了.
//时间复杂度O(cnt*80*80)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10005
#define INF 0x3f3f3f3f
using namespace std;

int n,len[N],cnt,dp[N][85],path[N][85];
char str[N],word[N][85];

int dfs(int i,int j){
    if(dp[i][j]!=-1)//dp初始状态要设置为-1,因为INF可能也是 不符合规范的状态,也是一个合法的数值,有可能某种调整方案无法使得 最后一个单词恰好贴近尾部
        return dp[i][j];
    dp[i][j]=INF;//初始值无穷大
    if(i == cnt+1){//所有cnt个单词已经放置完毕
        if(!j)//最后一个单词恰好贴紧最后一行尾部,合法状态 返回0,不产生badness.
            return dp[i][j]=0;
        else//不合法状态,最后一个单词未能紧贴 最后一行尾部,返回INF 作为不合法数值标记
            return dp[i][j];
    }
    int res;
    //第i个单词单独占一行,badness为500
    if(!j){
        dp[i][j]=dfs(i+1,0)+500;
        path[i][j]=0;
    }
    //第i个单词 在当前行j个位置后尾随刚好占满当前行,b不产生额外的badness,badness已经在之前的间隙计算过了
    if(j+len[i] == n){//所有合法状态,最后一个单词一定是紧贴最后一行的尾部的
        dp[i][j]=dfs(i+1,0);
        path[i][j]=0;
    }
    else{//第i个单词当前行第j个位置后面,并不能占满当前行
        int k=j+len[i]+1;//第i个单词所占的位置+至少一个空格
        for(int p=k;p<n;p++){//枚举i+1个单词和第i个单词之间的间隙
            if(p+len[i+1]>n)//当前行不能被第i个单词占满,也放置不下第i+1个单词时结束,已经属于不合法状态 不必再枚举更多间隙
                break;
            int c=p-k;//两单词之间的badness为(空格数-1)的平方
            res=dfs(i+1,p);
            if(dp[i][j]>res+c*c){
                dp[i][j]=res+c*c;
                path[i][j]=p;//记录第i个单词在第j+1个位置后面产生的空格所占得最后一个位置为p
            }
        }
    }
    return dp[i][j];
}

void print(int i,int j){
    while(i<=cnt){
        printf("%s",word[i]);
        if(path[i][j] == 0)//path[i][j]为0代表,第i个单词是本行最后一个单词,没有单词尾随,输出换行符
            printf("\n");
        else{
            //输出第i个单词后的空格数,数量为path[i][j]-j-len[i],int k=j+len[i]+1;
            for(int k=1;k<=path[i][j]-j-len[i];k++)
                printf(" ");
        }
        j=path[i][j];//这里要先记录更新j,再更新i,先更新i后,path[i][j]已经不是之前的path[i][j]了
        i++;
    }
    printf("\n");//每个样例后产生一个空行.
}

int main(){
    while(scanf("%d",&n) && n){
        cnt=0;
        memset(dp,-1,sizeof(dp));
        getchar();
        while(gets(str) && str[0]!='\0'){
            for(int i=0;str[i]!='\0';){
                sscanf(str+i,"%s",word[++cnt]);
                len[cnt]=strlen(word[cnt]);
                i+=len[cnt];
                while(str[i] == ' ') i++;
            }
        }
        dfs(1,0);
        print(1,0);
    }
    return 0;
}

/*
//正向dp
//正向动态规划需要的技巧性太高,不太好写,不好确定初始状态
//除过经典的动态规划模型(区间dp,背包,数位dp,状压dp)建议都用dfs递归的方式记忆化搜索来解决,代码写起来比较好写,简洁,大的思路上都是差不多的.
//摘自博客:https://blog.csdn.net/u012997373/article/details/38844073
#include <cstdio>
#include <cstring>

const int N = 10005;
const int M = 85;
const int INF = 0x3f3f3f3f;

int L, n;
int dp[N][M];
int p[N][M];//路径
char str[N];
char word[N][M];
int l[N];//单词长度

int Min (const int a, const int b) { return a < b ? a: b; }

void handle () {处理输入

	int j = 0;
	bool flag = 0;
	for (int i = 0; i <= strlen (str); i++) {

		if (str[i] != ' ' && str[i] != '\0') {
			word[n][j++] = str[i];
			flag = 1;
		} else {
			if (flag) {
				word[n][j] = '\0';
				l[n++] = j;
				j = 0;
				flag = 0;
			}
		}
	}
}

void printf_ans (int x, int y) {//输出路径

	if (x == n + 1)
		return;
	if (!p[x][y] && !y) {//单独一行不要输出空格直接回车
		printf ("%s", word[x - 1]);
	} else {

		printf ("%s", word[x - 1]);
		if (x != n) {
			for (int i = y + l[x - 1]; i < p[x][y]; i++)
				printf (" ");
		}
	}

	if (!p[x][y] || x == n)
		printf ("\n");
	printf_ans(x + 1, p[x][y]);
}

int main () {

	int tmp;
	while (scanf ("%d%*c", &L), L) {

		n = 0;
		while (gets(str) && str[0] != '\0') {

			handle();
		}
		//init
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= L; j++) {
				dp[i][j] = INF;
				p[i][j] = L + 1;
			}
		dp[n][0] = 500;
		p[n][0] = 0;
		dp[n][L - l[n - 1]] = 0;

		for (int i = n - 1; i >= 1; i--) {
			for (int j = 0; j <= L - l[i]; j++) {

				if (dp[i + 1][j] == INF)
					continue;
				if (!j) {

					if (dp[i + 1][j] <= dp[i][L - l[i - 1]]) {//两个单词在两行的情况
						dp[i][L - l[i - 1]] = dp[i + 1][j];
						p[i][L - l[i - 1]] = j;
					}
					tmp = (l[i - 1] == L) ? 0: 500;
					if (dp[i + 1][j] + tmp <= dp[i][0]) {//单独一行
						dp[i][0] = dp[i + 1][j] + tmp;
						p[i][0] = j;
					}

				} else {

					for (int k = 0; k < j - l[i - 1]; k++) {//中间有空格的情况

						tmp = j - l[i - 1] - k - 1;
						if (dp[i + 1][j] + tmp * tmp < dp[i][k]) {

							dp[i][k] = dp[i + 1][j] + tmp * tmp;
							p[i][k] = j;
						} else if (dp[i + 1][j] + tmp * tmp == dp[i][k]) {

							if (p[i][k] > k)//如果后面可以接单词的话，那么就不要单独一行
								p[i][k] = Min (p[i][k], j);//使得前面的空格尽量少
							else
								p[i][k] = j;
						}
					}
				}
			}
		}

		printf_ans(1, 0);
		printf ("\n");
	}
	return 0;
}
*/

/*
//ac 0ms 正向dp
//摘自博客:https://blog.csdn.net/mobius_strip/article/details/22175897
// a+b = c, aa + bb = aa + (c-a)(c-a) = cc + 2aa - 2ac,最值在 2a = c
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

typedef struct dnode
{
	char word[85];
	int  length;
}data;
data D[10005];

int sumL[10005];
int F[10005];
int E[10005];

void output( int i, int width, int max )
{
	if ( i < max ) {
		if ( E[i] > i+1 ) {
			//计算每行中具体的空格分布
			int sblack = width-sumL[E[i]-1]+sumL[i-1];
			int eblack = sblack/(E[i]-1-i);
			int nshort = (eblack+1)*(E[i]-1-i)-sblack;
			int count = 0;
			printf("%s",D[i].word);
			for ( int j = i+1 ; j < E[i] ; ++ j ) {
				for ( int k = 0 ; k < eblack ; ++ k )
					printf(" ");
				if ( ++ count > nshort ) printf(" ");
				printf("%s",D[j].word);
			}printf("\n");
		}else printf("%s\n",D[i].word);//自己独立一行
		output( E[i], width, max );
	}
}

int main()
{
	int width,temp;
	while ( scanf("%d",&width) && width ) {
		getchar();
		int count = 1;
		while ( (temp = getchar()) != '\n' ) {
			do {
				ungetc( temp, stdin );
				scanf("%s",D[count].word);
				D[count].length = strlen(D[count].word);
				count ++;
			}while ( (temp = getchar()) != '\n' );
		}

		sumL[0] = 0;
		for ( int i = 1 ; i < count ; ++ i )
			sumL[i] = sumL[i-1]+D[i].length;

		F[count] = 0;
		for ( int i = count-1 ; i > 0 ; -- i ) {
			F[i] = F[i+1] + 500;
			E[i] = i+1;
			for ( int j = i+1 ; j < count && sumL[j]-sumL[i-1]+j-i <= width ; ++ j ) {
				//计算每行中具体的空格分布
				int sblack = width-sumL[j]+sumL[i-1];
				int eblack = sblack/(j-i);
				int nshort = (eblack+1)*(j-i)-sblack;
				int add = (j-i-nshort)*eblack*eblack+nshort*(eblack-1)*(eblack-1);//本行代价
				if ( F[i] >= F[j+1] + add ) {
					F[i] = F[j+1] + add;
					E[i] = j+1;
				}
			}
		}

		output( 1, width, count );
		printf("\n");
	}
	return 0;
}
*/
