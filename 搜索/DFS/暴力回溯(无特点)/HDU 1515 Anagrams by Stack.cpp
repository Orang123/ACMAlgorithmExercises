/*
题意:
两个字符串str1,str2,尝试将str1压入栈中,可以在用栈顶的字符去
匹配str2,str1可以不完全压入栈中再去匹配,是边压边匹配的,
每次str1和str2匹配后,退栈pop,将压栈操作记作'i',将退栈操作记作'o',
按照字典序输出str1和str2匹配的所有io操作序列.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=1515
思路:dfs回溯,因为按照字典序'i'<'o',因此先尽可能地将
str1压栈,回溯时,判断栈顶元素是否和str2当前位置匹配.
当str1和str2完全匹配时 即:i == len1 j == len2.
*/
//ac 109ms dfs回溯
#include<cstdio>
#include<cstring>
#include<stack>
#include<algorithm>
#define N 110
using namespace std;

int len1,len2;
char str1[N],str2[N];
stack<char> s;
vector<char> ans;

void dfs(int i,int j){
    if(i == len1 && j == len2){
        for(char &x : ans)
            printf("%c ",x);
        printf("\n");
        return;
    }
    if(i<len1){//尽可能先将str1 入栈 i操作 字典序较小
        s.push(str1[i]);
        ans.push_back('i');
        dfs(i+1,j);
        s.pop();
        ans.pop_back();
    }
    if(j<len2 && !s.empty() && s.top() == str2[j]){//判断当前栈顶元素是否和str2[j]匹配
        s.pop();
        ans.push_back('o');
        dfs(i,j+1);
        s.push(str2[j]);
        ans.pop_back();
    }
}

int main(){
    while(scanf("%s",str1)!=EOF){
        scanf("%s",str2);
        len1=strlen(str1);
        len2=strlen(str2);
        printf("[\n");
        if(len1 == len2)//两字符串长度相同 才能匹配
            dfs(0,0);
        printf("]\n");
    }
    return 0;
}
