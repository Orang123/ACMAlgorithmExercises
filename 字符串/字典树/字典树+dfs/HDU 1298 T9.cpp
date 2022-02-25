/*
题意:摘自网上
给出n个单词的权值，现在使用九键拼音，根据用户的按键弹出权值最大单词，
如果答案有多个，弹出字典序最小的，问当用户按下一个键时，应该弹出哪个单词。
规定每次按键的值一定是1-9的数字，如果为1不用处理。对于一系列按键，如果字典
中没有与之对应的单词，输出“MANUALLY”。如果单词a是单词b的前缀，那么a的权值
为两者的累加和，例如对于hel 2，hello 4，hel的权值为2+4=6。如果一个单词在
字典中，那么它的前缀也可以认为是在字典中，并且对应的权值为该字母的权值。
现在输入m个数字串,输出在输入每个数字时弹出权值最大的单词.
n<=1000,单词长度<=100.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1298
思路:先将n个模式串单词构建到字典树中,对于每个输入的数字串,
dfs按照字典序枚举每个数字上可能出现的字母,记录在按下各个数字时
出现权值最大的单词,结束条件是数字串全部按完.
*/
//ac 0ms 字典树+dfs
#include<cstdio>
#include<cstring>
#define N 100010

char phone[10][5]={"","","ABC","DEF","GHI","JKL","MNO","PQRS","TUV","WXYZ"};
int n,m,tr[N][26],wordVal[N],cnt,p[110],plen;
char s[110],ans[110][110],tp[110];

int newNode(){
    cnt++;
    for(int i=0;i<26;i++)
        tr[cnt][i]=0;
    wordVal[cnt]=0;
    return cnt;
}

void insertWord(int val){
    int rt=0,son,len=strlen(s);
    for(int i=0;i<len;i++){
        son=s[i]-'a';
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
        wordVal[rt]+=val;
    }
}

void dfs(int rt,int k){
    if(wordVal[rt]>p[k]){//记录长度为k的单词的最大权值和
        p[k]=wordVal[rt];
        tp[k]='\0';
        strcpy(ans[k],tp);
    }
    if(k == plen)
        return;
    int id=s[k]-'0';
    int num=strlen(phone[id]);
    int son;
    for(int i=0;i<num;i++){
        son=phone[id][i]-'A';//手机上的单词是大写,这里其实不区分大小写
        if(tr[rt][son]){
            tp[k]='a'+son;//记录当前按下下标为k的数字出现的字母
            dfs(tr[rt][son],k+1);
        }
    }
}

int main(){
    int T,cas=0,val;
    scanf("%d",&T);
    while(T--){
        cnt=-1;
        newNode();
        cas++;
        scanf("%d",&n);
        while(n--){
            scanf("%s %d",s,&val);
            insertWord(val);
        }
        scanf("%d",&m);
        printf("Scenario #%d:\n",cas);
        while(m--){
            scanf("%s",s);
            plen=strlen(s)-1;//最后一个数字为1 不会出现字母
            memset(p,0,sizeof(p));
            dfs(0,0);
            for(int i=1;i<=plen;i++){
                if(p[i])
                    printf("%s\n",ans[i]);
                else
                    printf("MANUALLY\n");
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
