/*
题意:给一个长为n的字符串，问字符串的前缀是不是周期串，
也就还是说，它是否为某一字符串重复连接而成（必须至少重复2次）
（即循环节）。如果是周期串，输出前缀的最后一个字母的位置和最短周期.
n<=10^6.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4074
思路:
next数组下标从0开始 i-next[i]表示长度为i的前缀最小循环节的长度 i%(i-next[i]) == 0 表示存在完整循环节
next数组下标从1开始 i+1-next[i+1]表示长度为i的前缀最小循环节的长度 i%(i+1-next[i+1]) == 0 表示存在完整循环节
题目要求输出重复次数不小于2的循环节,
因此对于下标从0开始 长度为i的前缀 next[i]=0的不计算,只有一个循环节.
下标从0开始 长度为i的前缀 next[i+1]=1的不计算,只有一个循环节.
*/
//ac 40ms 下标从1开始
#include<cstdio>
#include<cstring>
#define N 1000010

int n,next[N];
char str[N];

void getNext(){
    int i=0,j=1;
    next[1]=0;
    while(j<=n){
        if(!i || str[i] == str[j])
            next[++j]=++i;
        else
            i=next[i];
    }
}

int main(){
    for(int cas=1;scanf("%d",&n) && n;cas++){
        scanf("%s",str+1);
        getNext();
        printf("Test case #%d\n",cas);
        for(int i=2;i<=n;i++){
            //等于1 表示1~i最长相同前后缀长度为0,这样循环节只有1个,
            //就是1~i作为一个整体,但是题目要输出循环节至少为2,等于1 是因为下标从1开始计算next数组,并且初始不合法值为0
            if(next[i+1] == 1) continue;
            if(i%(i+1-next[i+1]) == 0)//i-next[i+1]会导致 分母为0 出现异常
                printf("%d %d\n",i,i/(i+1-next[i+1]));
        }
        printf("\n");
    }
    return 0;
}

/*
//ac 40ms 下标从0开始
#include<cstdio>
#include<cstring>
#define N 1000010

int n,next[N];
char str[N];

void getNext(){
    int i=-1,j=0;
    next[0]=-1;
    while(j<n){
        if(i == -1 || str[i] == str[j])
            next[++j]=++i;
        else
            i=next[i];
    }
}

int main(){
    for(int cas=1;scanf("%d",&n) && n;cas++){
        scanf("%s",str);
        getNext();
        printf("Test case #%d\n",cas);
        for(int i=2;i<=n;i++){
            if(!next[i]) continue;
            if(i%(i-next[i]) == 0)
                printf("%d %d\n",i,i/(i-next[i]));
        }
        printf("\n");
    }
    return 0;
}
*/

/*
//wa 不能用优化的next数组,那个只能单纯用于字符串匹配,
//而这里关于循环节的问题,需要用的是最长公共前后缀,优化的next数组 概念上已经不等于最长公共前后缀了
#include<cstdio>
#include<cstring>
#define N 1000010

int n,next[N];
char str[N];

void getNext(){
    int i=-1,j=0;
    next[0]=-1;
    while(j<n){
        if(i == -1 || str[i] == str[j]){
        	i++;
			j++;
			if(str[i] != str[j])
				next[j]=i;
			else
				next[j]=next[i];
		}
        else
            i=next[i];
    }
}

int main(){
    for(int cas=1;scanf("%d",&n) && n;cas++){
        scanf("%s",str);
        getNext();
        printf("Test case #%d\n",cas);
        for(int i=2;i<=n;i++){
            if(!next[i]) continue;
            if(i%(i-next[i]) == 0)
                printf("%d %d\n",i,i/(i-next[i]));
        }
        printf("\n");
    }
    return 0;
}
*/
