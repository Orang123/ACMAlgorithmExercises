/*
题意:摘自网上
给定开始的字符串str，要求根据表格变化成一个字符ed，问推出步骤。
str长度最长为100,并不要求步骤数最少,只要找到一种推出步骤输出即可.
链接:https://www.luogu.com.cn/problem/UVA10981
思路:对于当前状态的字符串sta,枚举[0,len-1]中的sta[i],sta[i+1]结合,
对于不可推出ed的状态要标记为0,在推出新的sta字符串时,状态可能重复,
因此记忆化搜索.
dp[sta]=0表示当前字符串sta之前搜索过 不可推出ed,无需重复搜索.
record[sta]=s,当前状态sta 结合变形的下一个字符串为s.
*/
//ac 0ms 记忆化搜索 map<string,int> 记录状态的可行性,string replace替换
//dp[sta]=0表示当前字符串sta之前搜索过 不可推出ed,无需重复搜索.
//record[sta]=s,当前状态sta 结合变形的下一个字符串为s.
#include<cstdio>
#include<iostream>
#include<cstring>
#include<map>
#include<algorithm>
#define N 150
#define INF 0x3f3f3f3f
using namespace std;

char a[N][N];
string str,ed;
map<string,string> record;
map<string,int> dp;

void init(){//题目给出的a,b,c之间的结合映射表
    a['a']['a']='b';a['a']['b']='b';a['a']['c']='a';
    a['b']['a']='c';a['b']['b']='b';a['b']['c']='a';
    a['c']['a']='a';a['c']['b']='c';a['c']['c']='c';
}

int dfs(string sta){
    if(dp.count(sta))//当前这种状态已经推出过 并且不可达状态ed,直接返回0
        return dp[sta];
    dp[sta]=0;//初始值为0
    if(sta.size() == 1){
        if(sta == ed)
            return dp[sta]=1;
        else
            return dp[sta]=0;
    }
    for(int i=0;i<sta.size()-1;i++){//枚举先结合i,i+1 为a[sta[i]][sta[i+1]]
        string tp="";
        tp+=a[sta[i]][sta[i+1]];
        string s=sta;
        //只要找到一种 推出方式 就输出
        if(dfs(s.replace(i,2,tp))){//将s中的从i开始的2个字符替换为a[sta[i]][sta[i+1]]
            record[sta]=s;
            return dp[sta]=1;
        }
    }
    return dp[sta];
}

void print(string st){
    cout << st <<endl;
    while(st!=ed){
        st=record[st];
        cout << st <<endl;
    }
}

int main(){
    int T;
    init();
    scanf("%d",&T);
    while(T--){
        dp.clear();
        record.clear();
        cin >> str;
        cin >> ed;
        if(dfs(str))
            print(str);
        else
            printf("None exist!\n");
        if(T)
            printf("\n");
    }
    return 0;
}


/*
//ac 0ms map<string,string>记录 对之前无法推出结果 不再重复搜索
#include<cstdio>
#include<iostream>
#include<cstring>
#include<map>
#include<algorithm>
#define N 150
#define INF 0x3f3f3f3f
using namespace std;

char a[N][N];
string str,ed;
map<string,string> record;

void init(){
    a['a']['a']='b';a['a']['b']='b';a['a']['c']='a';
    a['b']['a']='c';a['b']['b']='b';a['b']['c']='a';
    a['c']['a']='a';a['c']['b']='c';a['c']['c']='c';
}

int dfs(string sta){
    if(sta.size() == 1)
    	return sta == ed;
    for(int i=0;i<sta.size()-1;i++){
        string tp="";
        tp+=a[sta[i]][sta[i+1]];
        string s=sta;
        s.replace(i,2,tp);
        if(record.count(s))//count判断的是<key,val>中的key,因此记录路径是反着记录  record[s]=sta
        	continue;
        record[s]=sta;
        if(dfs(s))
            return 1;
    }
    return 0;
}

void print(string st){
	if(st == str){
		cout << st <<endl;
		return;
	}
	print(record[st]);
	cout << st <<endl;
}

int main(){
    int T;
    init();
    scanf("%d",&T);
    while(T--){
        record.clear();
        cin >> str;
        cin >> ed;
        if(dfs(str))
            print(ed);
        else
            printf("None exist!\n");
        if(T)
            printf("\n");
    }
    return 0;
}
*/
