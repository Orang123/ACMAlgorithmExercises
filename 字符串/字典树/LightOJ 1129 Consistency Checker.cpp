/*
题意:摘自网上
给出n条串判断是否存在一个串为另一个串的前缀。
n<=10000,|s|<=10.
链接:http://lightoj.com/volume_showproblem.php?problem=1129
思路:字典树.插入时判断,有可能先插较短的,也有可能先插较长的,
对于先插较短的,后插较长的,在插较长的要判断当前rt前缀是否有可能
已经构成一个单词.对于先插较长的,后插较短的,在插较短的时,要判断
较短单词的后面是否还有字符.
*/
//ac 36ms
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
using namespace std;

int n,tr[N][10],cnt,word[N],flag;
char s[15];

int newNode(){
    cnt++;
    for(int i=0;i<10;i++)
        tr[cnt][i]=0;
    word[cnt]=0;
    return cnt;
}

void insertWord(){
    int rt=0,son,len=strlen(s);
    for(int i=0;i<len;i++){
        son=s[i]-'0';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
        if(word[rt]){
            flag=1;
            return;
        }
    }
    word[rt]=1;
    for(int i=0;i<10;i++){
        if(tr[rt][i]){
            flag=1;
            return;
        }
    }
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        flag=0;
        cas++;
        cnt=-1;
        newNode();
        scanf("%d",&n);
        while(n--){
            scanf("%s",s);
            if(!flag)
                insertWord();
        }
        printf("Case %d: %s\n",cas,flag?"NO":"YES");
    }
    return 0;
}
