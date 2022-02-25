/*
题意:
给出一串数字，在中间可以任意插入+，-，* ，使得其变成一个式子（乘号先计算），
要求输出式子计算结果为2000的所有情况，按照字典序输出。
注意必须要添加运算符，2000=是不可以的。
最多9位数字.
注意:需要考虑运算符优先级.
链接:https://www.luogu.com.cn/problem/UVA817
思路:注意在添加运算符后,不是按从左到右的顺序结合运算的,
而是'*'的运算符优先级最高,先计算乘号.因此要按照全排列枚举
每两个数字间可能放置的符号有4种' ','*','+','-',其中' '代表
不插入运算符,为了方便判断不合法的插入序列,即:不能将连续的
多个0作为一个0计算,在dfs时不能直接将分隔好的数字计算好,
只能先预先存起来,单独将运算符和数字串分离开进行计算,分成num,
和sym分别代表分割后的按照乘法优先结合的数字串和符号串.

这里因为只有+-*三种运算符,没有/、()运算符,所以没必要使用基于栈的
逆波兰表达式,中缀转后缀.
*/
//ac 430ms dfs回溯,有运算优先级,先算乘法 后算加减法
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 15
using namespace std;

int len;
char oper[4]={'*','+','-',' '},str[N],s[N],flag;//按照字典序 '*'<'+'<'-'<'数字'(不插入,空格)
vector<int> num;
vector<char> sym;

int calRes(){
    //运算符串长度为数字串长度减1
    for(int i=0;i<num.size()-1;i++){//优先结合乘法运算
        if(sym[i] == '*'){
            num[i+1]=num[i]*num[i+1];
            num[i]=-1;
            sym[i]=' ';
        }
    }
    vector<int> numtp;//整合合并后新的 数字串和运算符串
    vector<char> symtp;
    for(int i=0;i<num.size();i++){
        if(num[i]!=-1)//数字串过滤掉 乘法结合后的-1
            numtp.push_back(num[i]);
        if(i && sym[i-1]!=' ')//运算符号个数为 num.size()-1,所以判断i-1
            symtp.push_back(sym[i-1]);
    }
    int res=numtp[0];//因为运算符在两个数字之间,所以 res初始值为numtp[0]
    for(int i=1;i<numtp.size();i++){//数字串从第二个开始结合 下标1开始
        if(symtp[i-1] == '+')//symtp 下标从0开始,因此i-1
            res+=numtp[i];
        else if(symtp[i-1] == '-')
            res-=numtp[i];
    }
    return res == 2000;
}

int check(){//判断数字串是否合法以及运算结果是否为2000
    num.clear();
    sym.clear();
    int res=0;
    for(int i=0;i<len;i++){
        res=res*10+str[i]-'0';
        if(s[i] != ' '){//只要不是' ' 就代表当前一整个数字串可以分离出来了
            num.push_back(res);
            sym.push_back(s[i]);
            res=0;
        }
    }
    int cnt=0;
    //因为要判断 不能是将连续的0作为一个数字0来分隔,因此在dfs只是预存运算符符号,而不直接计算
    //判断分割后的 数字串是否合法,中间0的个数 只能是单独一个0,不能是2个0、3个0...作为一个整体,这是不合法的划分
    for(int val : num){//这里不能加 & 否则,num中的元素都会在循环中被置0
        if(!val){//将中间的0,单独只算一位 最后判断数字个数是否和原串相同
            cnt++;
            continue;
        }
        while(val){
            cnt++;
            val/=10;
        }
    }
    if(cnt != len)//数字个数不等于原串数字个数 就不合法
        return 0;
    return calRes();//判断是否等于2000
}

void print(){
    printf("  ");
    for(int i=0;i<len;i++){
        printf("%c",str[i]);
        if(s[i]!=' ' && i!=len-1)//s[len-1]的符号是'\0',要排除
            printf("%c",s[i]);
    }
    printf("=\n");
}

void dfs(int k){
    if(k == len-1){
        if(check()){
            flag=1;
            print();
        }
        return;
    }
    for(int i=0;i<4;i++){
        s[k]=oper[i];
        dfs(k+1);
    }
}

int main(){
    int cas=0;
    while(scanf("%s",str) && strcmp(str,"=")){
        cas++;
        flag=0;
        len=strlen(str)-1;
        s[len-1]='\0';
        printf("Problem %d\n",cas);
        if(!strcmp(str,"2000=")){//直接2000 没有运算符 是不合法的
            printf("  IMPOSSIBLE\n");
            continue;
        }
        dfs(0);
        if(!flag)
            printf("  IMPOSSIBLE\n");
    }
    return 0;
}
