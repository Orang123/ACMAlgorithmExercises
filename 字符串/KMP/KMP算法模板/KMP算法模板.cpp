/*
背景:
KMP算法是一种改进的字符串匹配算法，由D.E.Knuth，J.H.Morris和V.R.Pratt
在1977年发表，因此人们称它为克努特—莫里斯—普拉特操作（简称KMP算法）.
一个长度为slen的文本串s,和一个长度为plen的模式串p,现在要求出文本串s
是否包含模式串p,若包含输出第一次完整匹配的位置,若不包含输出-1.
构造next数组和kmp匹配总时间复杂度为O(slen+plen) 空间复杂度O(slen+plen)

相关定义:
1.前缀:包含首位字符但不包含末位字符的子串.
2.后缀:包含末位字符但不包含首位字符的子串.
3.最长相同前后缀(最长公共前后缀):模式串p中某段连续子串中前缀和后缀相同的最长子串.
下面next数组的定义 是建立在数组下标从0开始,初始值为-1的情况
4.next数组定义:当文本串s与模式串p不匹配时,模式串p要回退的数组位置下标.
5.next[i]:其值 = 第i+1位字符前面i位字符构成的子串的最长相同前后缀的长度,这里的前缀后缀不可能等于整个串,至少要少最后一个或第一个字符.
也是当模式串p[i]失配时,模式串p需要重新回退的位置.
说明:next数组的值就等于模式串子串最长相同前后缀的数值右移一位,其初始第一个值为-1.

理解算法时参考博客:
https://blog.csdn.net/v_july_v/article/details/7041827#t10  v_JULY_v博主写的非常详细,强烈推荐
https://blog.csdn.net/yyzsir/article/details/89462339
https://blog.csdn.net/dark_cy/article/details/88698736
*/
//构造next数组和kmp匹配总时间复杂度为O(slen+plen)
#include<cstdio>
#include<cstring>
#define N 1100
using namespace std;

int next[N],slen,plen;
char s[N],p[N];

//普通next数组
//时间复杂度O(plen)
void getNext(){
    next[0]=-1;
    int i=-1,j=0;
    //模式串p只判断到倒数第二位,因为每次i == -1 或 p[i] == p[j]时,next[++j]=++i j会再加一位
    //模式串的最后一位判断的是前j-1位中最长相同前后缀的长度
    while(j<plen-1){
        /*
        i == -1表示:
        之前计算而得最长相同前后缀已经不可再增大,需要
        重新开始计算新的最长相同前后缀,初始状态标记为-1,
        表示之前计算的最长相同前后缀.
        p[i] == p[j]表示,最长相同前后缀长度可以再加1,
        即:next[j+1]=next[j]+1
        */
        if(i == -1 || p[i] == p[j]){
            i++;//i++ j++ 继续向后判断最长相同前后缀是否还能增大
            j++;
            next[j]=i;//前j个字符构成的子串的最长前后缀的长度为i,因为下标从0开始,现在下标已经到j+1个字符了
        }
        else//p[i]!=p[j]时,考虑将模式串回退,考虑长度较短的最长相同前后缀是否有可能匹配增大.
            i=next[i];
    }
}

//优化版本next数组,next[j]记录的位置的字符都是和当前第j位字符不同
//时间复杂度O(plen)
//优化过后的next数组如果前后缀相同,next数值也相同,
//eg:abcabcabc 对应优化next数值: -1 0 0 -1 0 0 -1 0 0
//abcabcabc 未优化next数值: -1 0 0 0 1 2 3 4 5
//注意:优化的next数组不能用来求解有关循环节的问题,因为next[i]所表示的,
//可能已经不是0~i-1的最长相同前后缀的长度了,而是表示下一个匹配位置
void betterNext(){
    next[0]=-1;
    int i=-1,j=0;
    while(j<plen-1){
        if(i == -1 || p[i] == p[j]){
            i++;
            j++;
            //最长相同前后缀下一位如果不相同,直接记录即可
            if(p[i]!=p[j])
                next[j]=i;
            /*
            如果下一位相同,则next[j]记录 前缀中 前i位对应的最长相同前后缀的位置,即next[i]
            p[next[i]]记录的位置字符一定和p[i]是不同的,因为i一定小于j,已经统计过的next数组
            一定是优化过了的.
            */
            else
                next[j]=next[i];
        }
        else//p[i]!=p[j] 考虑将模式串回退,考虑长度较短的最长相同前后缀是否有可能匹配增大.
            i=next[i];
    }
}

//文本串S和模式串P开始匹配
//时间复杂度O(slen)
int kmp(){
    int i=0,j=0;//S和P下标从0开始
    while(i<slen && j<plen){
        /*
        j == -1,表示之前匹配的子串已经不能再匹配了,模式串P需要从头开始和文本串S的下一位开始配对了

        s[i]==p[j]时 继续比较S和P的下一位判断是否相等
        */
        if(j == -1 || s[i] == p[j]){
            i++;
            j++;
        }
        //s[i]!=p[j]时,模式串p需要回退到next[j]位置继续和S[i]比较是否相等,s[i] 是否等于 p[next[j]]
        //因为s[i]和p[j]不相等,而s[i]和p[j]之前有相同的一段,再次匹配时,选择模式串相同的前缀那一段和s[i]比较
        //相当于模式串右移了j-next[j]位
        else
            j=next[j];
    }
    if(j == plen)//模式串匹配完成
        return i-j+1;//返回模式串p在文本串s中第一次匹配的位置,这里是下标+1
    else//文本串s中未找到模式串p 返回-1
        return -1;
}

//构造next数组和kmp匹配总时间复杂度为O(slen+plen)

int main(){
    scanf("%s",s);//bacbababadababacambabacaddababacasdsd
    scanf("%s",p);//ababaca
    slen=strlen(s);//文本串s长度
    plen=strlen(p);//模式串p长度
    getNext();
    //betterNext();
    printf("%d",kmp());//11
    return 0;
}

/*
input
ababcabcacbab
abcac

bacbababadababacambabacaddababacasdsd
ababaca

output
6
11
*/

/*
//kmp 下标从1开始
#include<cstdio>
#include<cstring>
#define N 1100
using namespace std;

int next[N],slen,plen;
char s[N],p[N];

void getNext(){
    next[1]=0;
    int i=0,j=1;//下标从1开始,因此不合法初始值为0,不再是-1,不合法初始值是第一个初始下标减1.
    while(j<plen){
        if(!i || p[i] == p[j]){//不合法值为i == 0
            i++;
            j++;
            next[j]=i;
        }
        else
            i=next[i];
    }
}

void betterNext(){
    next[1]=0;
    int i=0,j=1;
    while(j<plen){
        if(!i || p[i] == p[j]){
            i++;
            j++;
            if(p[i]!=p[j])
                next[j]=i;
            else
                next[j]=next[i];
        }
        else
            i=next[i];
    }
}

int kmp(){
    int i=1,j=1;
    while(i<=slen && j<=plen){
        if(!j || s[i] == p[j]){
            i++;
            j++;
        }
        else
            j=next[j];
    }
    if(j == plen+1)
        return i-j+1;
    else
        return -1;
}

int main(){
    scanf("%s",s+1);//文本串和模式串下标都从1开始
    scanf("%s",p+1);
    slen=strlen(s+1);
    plen=strlen(p+1);
    //getNext();
    betterNext();
    printf("%d",kmp());
    return 0;
}
*/

/*
//普通的暴力匹配做法
//时间复杂度O(slen*plen)
#include<cstdio>
#include<cstring>
#define N 1100
using namespace std;

int slen,plen;
char s[N],p[N];

int match(){
    slen=strlen(s);
    plen=strlen(p);
    int i=0,j=0;
    while(i<slen && j<plen){
        if(s[i] == p[j]){
            i++;
            j++;
        }
        else{//s[i]和p[j]不相等时,将模式串p回溯到0,重新开始和之前文本串初始配对的第一个位置的下一位置开始进行配对
            i=i-j+1;//注意这里不能写成i-=j+1,这样实际的表达是i=i-(j+1)=i-j-1 会出错 死循环
            j=0;
        }
    }
    if(j == plen)
        return i-j+1;
    else
        return -1;
}

int main(){
    scanf("%s",s);
    scanf("%s",p);
    printf("%d",match());
    return 0;
}
*/
