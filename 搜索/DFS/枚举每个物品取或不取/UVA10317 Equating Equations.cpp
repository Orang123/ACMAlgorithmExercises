/*
题意:摘自网上
给出一个式子，但这个式子不一定是等式，在‘+’，‘-’，‘=’符号位置不变的情况下，
重新排列数字的位置，使其成为等式，如果可以的话，输出其中一种排列方式。
数字个数最多16个.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1258
思路:因为最多有16个数字,直接枚举全排列的话,复杂度可达16!=20922789888000.
对于a+b-c=d-e,可以将等号右边的式子移到左边,原式子转化为a+b+e-(c+d)=0.
要使得等号成立,那么a+b+e必须等于c+dm也就是说所有数字之和必须是偶数才
有可能使得等号成立.那么就需要计算出运算符全是'+'号连接或运算符全是'-'
号连接的数字的个数num,这个问题就转化为在所有数字中选取出num个数字,使得
其和等于总和的一半.这样对于每个数都有选与不选两种可能,总复杂度2^16=65536,
可以接受.
*/
//ac 20ms dfs
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 50
#define INF 0x3f3f3f3f
using namespace std;

int a[N],vis[N],sum,l,sep,cnt,num,left[N],right[N],suffixsum[N];
char input[N],oper[N];

void init(){
    int len=strlen(input);
    sscanf(input,"%d",&a[1]);
    cnt=0;
    l=0;
    sum=a[++cnt];
    for(int i=1;i<len;i++){
        if(input[i] == '+' || input[i] == '-' || input[i] == '='){
            if(input[i] == '=')
                sep=l;
            if(input[i] != '=')
                oper[++l]=input[i];
            sscanf(input+i+1,"%d",&a[++cnt]);//a数组记录 数字
            sum+=a[cnt];//计算所有数字总和
        }
    }
    num=1;
    for(int i=1;i<=l;i++){//统计等号左边全都是'+'号相连的数字的个数
        if(i<=sep && oper[i] == '+')
            num++;
        else if(i>sep && oper[i] == '-')//等号右边本身是减号的移到左边是加号
            num++;
    }
    suffixsum[cnt+1]=0;//后缀和
    for(int i=cnt;i>=1;i--)
        suffixsum[i]=suffixsum[i+1]+a[i];
}

int dfs(int cur,int k,int val){
    if(k == num)
        return val == sum;
    if(cur == cnt+1)
        return 0;
    if(k+cnt-cur+1<num)//剪枝1:当前选的数目加上后面所有的数 都比num小 结束
        return 0;
    if(val+suffixsum[cur]<sum)//剪枝2:当前累加和加上后面所有的数的值 都比sum小 结束
        return 0;
    if(val+a[cur]<=sum){
        vis[cur]=1;//记录所选的数
        if(dfs(cur+1,k+1,val+a[cur]))
            return 1;
        vis[cur]=0;
    }
    if(dfs(cur+1,k,val))
        return 1;
    return 0;
}

void output(){//输出方案
    int cnt1=0,cnt2=0;
    for(int i=1;i<=cnt;i++){
        if(vis[i])
            left[++cnt1]=a[i];//在等号左边left、right分别记录 加号相连的数字和减号相连的数字
        else
            right[++cnt2]=a[i];
    }
    cnt1=cnt2=0;
    printf("%d",left[++cnt1]);//左边第一个数没有操作符
    for(int i=1;i<=sep;i++){//等号左边
        printf(" %c ",oper[i]);
        if(oper[i] == '+')//等号左边'+'
            printf("%d",left[++cnt1]);
        else//等号左边减号对应的就是没有选入的
            printf("%d",right[++cnt2]);
    }
    printf(" = ");
    printf("%d",right[++cnt2]);//右边第一个数没有操作符
    for(int i=sep+1;i<=l;i++){
        printf(" %c ",oper[i]);
        if(oper[i] == '+')//右边加号对应到左边就是减号
            printf("%d",right[++cnt2]);
        else//右边减号对应到左边就是加号
            printf("%d",left[++cnt1]);
    }
    printf("\n");
}

int main(){
    while(gets(input)!=NULL){
        memset(vis,0,sizeof(vis));
        init();
        if(sum%2)
            printf("no solution\n");
        else{
            sum/=2;
            if(dfs(1,0,0))
                output();
            else
                printf("no solution\n");
        }
    }
    return 0;
}

/*
//ac 610ms 二进制状压
//摘自博客:https://blog.csdn.net/HelloWorld10086/article/details/43954729
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
vector<int> rec; //保存数字
vector<char> op; //保存操作符
int pos , neg; //记录正负数的个数
void init() {
    rec.clear();
    op.clear();
}
void preProc(string str) {
    string buf;
    stringstream ss(str);
    int x;
    bool equal = false;
    pos = 1, neg = 0;
    while(ss >> buf) {
        if(isdigit(buf[0])) {
            x = atoi(buf.c_str());
            rec.push_back(x);
        }else {
            op.push_back(buf[0]);
            if(buf[0] == '=')
                equal = true, neg++;
            else if(equal ^ (buf[0] == '+'))
                pos++;
            else
                neg++;
        }
    }
}
int getSum() {
    int sum = 0;
    for(int i = 0; i < rec.size(); i++) {
        sum += rec[i];
    }
    return sum;
}
void print_state(int st, int cnt) {
    vector<int> postive, negative; //新建两个向量用于保存正数和负数

    for(int i = 0; i < rec.size(); i++) {
        if(st & (1 << i)) //保存正数
            postive.push_back(rec[i]);
        else //保存负数
            negative.push_back(rec[i]);
    }

    int np = 0, nn = 0; //保存正数的个数，保存负数的个数
    bool equal = false;
    if(cnt == pos) {
        printf("%d", postive[np++]);
        for(int i = 0; i < op.size(); i++) {
            if(op[i] == '=') {
                equal = true; printf(" = %d", negative[nn++]);
            }else if(op[i] == '+') {
                equal ? printf(" + %d",negative[nn++]) : printf(" + %d",postive[np++]);
            }else {
                equal ? printf(" - %d",postive[np++]) : printf(" - %d",negative[nn++]);
            }
        }
    }else {
        printf("%d", negative[nn++]);
        for(int i = 0; i < op.size(); i++) {
            if(op[i] == '=') {
                equal = true; printf(" = %d", postive[np++]);
            }else if(op[i] == '+') {
                equal ? printf(" + %d",postive[np++]) : printf(" + %d",negative[nn++]);
            }else {
                equal ? printf(" - %d",negative[nn++]) : printf(" - %d",postive[np++]);
            }
        }
    }
    puts("");
}
void solve() {
    int posSum, negSum, cnt;
    int sum = getSum();
    if(sum & 1) { //如果sum为奇数不符合条件
        puts("no solution");
        return;
    }

    sum = sum / 2;

    int end = 1 << rec.size();
    for(int i = 0; i < end; i++) { //遍历最多 2^16种情况
        posSum = negSum = cnt = 0;
        for(int j = 0; j < rec.size(); j++) {
            if(posSum > sum || neg > sum) break;
            if(i & (1 << j))
                posSum += rec[j] , cnt++;
            else
                negSum += rec[j];
        }
        if(posSum == negSum && (cnt == pos || cnt == neg)) {
            print_state(i, cnt);
            return ;
        }
    }
    puts("no solution");
}
int main() {
    string str;
    while(getline(cin, str)) {
        init();
        preProc(str);
        solve();
    }
    return 0;
}
*/
