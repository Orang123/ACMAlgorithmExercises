/*
����:
����һ�����֣����м�����������+��-��* ��ʹ������һ��ʽ�ӣ��˺��ȼ��㣩��
Ҫ�����ʽ�Ӽ�����Ϊ2000����������������ֵ��������
ע�����Ҫ����������2000=�ǲ����Եġ�
���9λ����.
ע��:��Ҫ������������ȼ�.
����:https://www.luogu.com.cn/problem/UVA817
˼·:ע��������������,���ǰ������ҵ�˳���������,
����'*'����������ȼ����,�ȼ���˺�.���Ҫ����ȫ����ö��
ÿ�������ּ���ܷ��õķ�����4��' ','*','+','-',����' '����
�����������,Ϊ�˷����жϲ��Ϸ��Ĳ�������,��:���ܽ�������
���0��Ϊһ��0����,��dfsʱ����ֱ�ӽ��ָ��õ����ּ����,
ֻ����Ԥ�ȴ�����,����������������ִ����뿪���м���,�ֳ�num,
��sym�ֱ����ָ��İ��ճ˷����Ƚ�ϵ����ִ��ͷ��Ŵ�.

������Ϊֻ��+-*���������,û��/��()�����,����û��Ҫʹ�û���ջ��
�沨�����ʽ,��׺ת��׺.
*/
//ac 430ms dfs����,���������ȼ�,����˷� ����Ӽ���
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define N 15
using namespace std;

int len;
char oper[4]={'*','+','-',' '},str[N],s[N],flag;//�����ֵ��� '*'<'+'<'-'<'����'(������,�ո�)
vector<int> num;
vector<char> sym;

int calRes(){
    //�����������Ϊ���ִ����ȼ�1
    for(int i=0;i<num.size()-1;i++){//���Ƚ�ϳ˷�����
        if(sym[i] == '*'){
            num[i+1]=num[i]*num[i+1];
            num[i]=-1;
            sym[i]=' ';
        }
    }
    vector<int> numtp;//���Ϻϲ����µ� ���ִ����������
    vector<char> symtp;
    for(int i=0;i<num.size();i++){
        if(num[i]!=-1)//���ִ����˵� �˷���Ϻ��-1
            numtp.push_back(num[i]);
        if(i && sym[i-1]!=' ')//������Ÿ���Ϊ num.size()-1,�����ж�i-1
            symtp.push_back(sym[i-1]);
    }
    int res=numtp[0];//��Ϊ���������������֮��,���� res��ʼֵΪnumtp[0]
    for(int i=1;i<numtp.size();i++){//���ִ��ӵڶ�����ʼ��� �±�1��ʼ
        if(symtp[i-1] == '+')//symtp �±��0��ʼ,���i-1
            res+=numtp[i];
        else if(symtp[i-1] == '-')
            res-=numtp[i];
    }
    return res == 2000;
}

int check(){//�ж����ִ��Ƿ�Ϸ��Լ��������Ƿ�Ϊ2000
    num.clear();
    sym.clear();
    int res=0;
    for(int i=0;i<len;i++){
        res=res*10+str[i]-'0';
        if(s[i] != ' '){//ֻҪ����' ' �ʹ���ǰһ�������ִ����Է��������
            num.push_back(res);
            sym.push_back(s[i]);
            res=0;
        }
    }
    int cnt=0;
    //��ΪҪ�ж� �����ǽ�������0��Ϊһ������0���ָ�,�����dfsֻ��Ԥ�����������,����ֱ�Ӽ���
    //�жϷָ��� ���ִ��Ƿ�Ϸ�,�м�0�ĸ��� ֻ���ǵ���һ��0,������2��0��3��0...��Ϊһ������,���ǲ��Ϸ��Ļ���
    for(int val : num){//���ﲻ�ܼ� & ����,num�е�Ԫ�ض�����ѭ���б���0
        if(!val){//���м��0,����ֻ��һλ ����ж����ָ����Ƿ��ԭ����ͬ
            cnt++;
            continue;
        }
        while(val){
            cnt++;
            val/=10;
        }
    }
    if(cnt != len)//���ָ���������ԭ�����ָ��� �Ͳ��Ϸ�
        return 0;
    return calRes();//�ж��Ƿ����2000
}

void print(){
    printf("  ");
    for(int i=0;i<len;i++){
        printf("%c",str[i]);
        if(s[i]!=' ' && i!=len-1)//s[len-1]�ķ�����'\0',Ҫ�ų�
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
        if(!strcmp(str,"2000=")){//ֱ��2000 û������� �ǲ��Ϸ���
            printf("  IMPOSSIBLE\n");
            continue;
        }
        dfs(0);
        if(!flag)
            printf("  IMPOSSIBLE\n");
    }
    return 0;
}
