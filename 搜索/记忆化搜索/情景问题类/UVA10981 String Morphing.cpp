/*
����:ժ������
������ʼ���ַ���str��Ҫ����ݱ��仯��һ���ַ�ed�����Ƴ����衣
str�����Ϊ100,����Ҫ����������,ֻҪ�ҵ�һ���Ƴ������������.
����:https://www.luogu.com.cn/problem/UVA10981
˼·:���ڵ�ǰ״̬���ַ���sta,ö��[0,len-1]�е�sta[i],sta[i+1]���,
���ڲ����Ƴ�ed��״̬Ҫ���Ϊ0,���Ƴ��µ�sta�ַ���ʱ,״̬�����ظ�,
��˼��仯����.
dp[sta]=0��ʾ��ǰ�ַ���sta֮ǰ������ �����Ƴ�ed,�����ظ�����.
record[sta]=s,��ǰ״̬sta ��ϱ��ε���һ���ַ���Ϊs.
*/
//ac 0ms ���仯���� map<string,int> ��¼״̬�Ŀ�����,string replace�滻
//dp[sta]=0��ʾ��ǰ�ַ���sta֮ǰ������ �����Ƴ�ed,�����ظ�����.
//record[sta]=s,��ǰ״̬sta ��ϱ��ε���һ���ַ���Ϊs.
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

void init(){//��Ŀ������a,b,c֮��Ľ��ӳ���
    a['a']['a']='b';a['a']['b']='b';a['a']['c']='a';
    a['b']['a']='c';a['b']['b']='b';a['b']['c']='a';
    a['c']['a']='a';a['c']['b']='c';a['c']['c']='c';
}

int dfs(string sta){
    if(dp.count(sta))//��ǰ����״̬�Ѿ��Ƴ��� ���Ҳ��ɴ�״̬ed,ֱ�ӷ���0
        return dp[sta];
    dp[sta]=0;//��ʼֵΪ0
    if(sta.size() == 1){
        if(sta == ed)
            return dp[sta]=1;
        else
            return dp[sta]=0;
    }
    for(int i=0;i<sta.size()-1;i++){//ö���Ƚ��i,i+1 Ϊa[sta[i]][sta[i+1]]
        string tp="";
        tp+=a[sta[i]][sta[i+1]];
        string s=sta;
        //ֻҪ�ҵ�һ�� �Ƴ���ʽ �����
        if(dfs(s.replace(i,2,tp))){//��s�еĴ�i��ʼ��2���ַ��滻Ϊa[sta[i]][sta[i+1]]
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
//ac 0ms map<string,string>��¼ ��֮ǰ�޷��Ƴ���� �����ظ�����
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
        if(record.count(s))//count�жϵ���<key,val>�е�key,��˼�¼·���Ƿ��ż�¼  record[s]=sta
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
