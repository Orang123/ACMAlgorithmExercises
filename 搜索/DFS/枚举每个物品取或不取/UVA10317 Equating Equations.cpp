/*
����:ժ������
����һ��ʽ�ӣ������ʽ�Ӳ�һ���ǵ�ʽ���ڡ�+������-������=������λ�ò��������£�
�����������ֵ�λ�ã�ʹ���Ϊ��ʽ��������ԵĻ����������һ�����з�ʽ��
���ָ������16��.
����:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1258
˼·:��Ϊ�����16������,ֱ��ö��ȫ���еĻ�,���Ӷȿɴ�16!=20922789888000.
����a+b-c=d-e,���Խ��Ⱥ��ұߵ�ʽ���Ƶ����,ԭʽ��ת��Ϊa+b+e-(c+d)=0.
Ҫʹ�õȺų���,��ôa+b+e�������c+dmҲ����˵��������֮�ͱ�����ż����
�п���ʹ�õȺų���.��ô����Ҫ����������ȫ��'+'�����ӻ������ȫ��'-'
�����ӵ����ֵĸ���num,��������ת��Ϊ������������ѡȡ��num������,ʹ��
��͵����ܺ͵�һ��.��������ÿ��������ѡ�벻ѡ���ֿ���,�ܸ��Ӷ�2^16=65536,
���Խ���.
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
            sscanf(input+i+1,"%d",&a[++cnt]);//a�����¼ ����
            sum+=a[cnt];//�������������ܺ�
        }
    }
    num=1;
    for(int i=1;i<=l;i++){//ͳ�ƵȺ����ȫ����'+'�����������ֵĸ���
        if(i<=sep && oper[i] == '+')
            num++;
        else if(i>sep && oper[i] == '-')//�Ⱥ��ұ߱����Ǽ��ŵ��Ƶ�����ǼӺ�
            num++;
    }
    suffixsum[cnt+1]=0;//��׺��
    for(int i=cnt;i>=1;i--)
        suffixsum[i]=suffixsum[i+1]+a[i];
}

int dfs(int cur,int k,int val){
    if(k == num)
        return val == sum;
    if(cur == cnt+1)
        return 0;
    if(k+cnt-cur+1<num)//��֦1:��ǰѡ����Ŀ���Ϻ������е��� ����numС ����
        return 0;
    if(val+suffixsum[cur]<sum)//��֦2:��ǰ�ۼӺͼ��Ϻ������е�����ֵ ����sumС ����
        return 0;
    if(val+a[cur]<=sum){
        vis[cur]=1;//��¼��ѡ����
        if(dfs(cur+1,k+1,val+a[cur]))
            return 1;
        vis[cur]=0;
    }
    if(dfs(cur+1,k,val))
        return 1;
    return 0;
}

void output(){//�������
    int cnt1=0,cnt2=0;
    for(int i=1;i<=cnt;i++){
        if(vis[i])
            left[++cnt1]=a[i];//�ڵȺ����left��right�ֱ��¼ �Ӻ����������ֺͼ�������������
        else
            right[++cnt2]=a[i];
    }
    cnt1=cnt2=0;
    printf("%d",left[++cnt1]);//��ߵ�һ����û�в�����
    for(int i=1;i<=sep;i++){//�Ⱥ����
        printf(" %c ",oper[i]);
        if(oper[i] == '+')//�Ⱥ����'+'
            printf("%d",left[++cnt1]);
        else//�Ⱥ���߼��Ŷ�Ӧ�ľ���û��ѡ���
            printf("%d",right[++cnt2]);
    }
    printf(" = ");
    printf("%d",right[++cnt2]);//�ұߵ�һ����û�в�����
    for(int i=sep+1;i<=l;i++){
        printf(" %c ",oper[i]);
        if(oper[i] == '+')//�ұ߼ӺŶ�Ӧ����߾��Ǽ���
            printf("%d",right[++cnt2]);
        else//�ұ߼��Ŷ�Ӧ����߾��ǼӺ�
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
//ac 610ms ������״ѹ
//ժ�Բ���:https://blog.csdn.net/HelloWorld10086/article/details/43954729
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
vector<int> rec; //��������
vector<char> op; //���������
int pos , neg; //��¼�������ĸ���
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
    vector<int> postive, negative; //�½������������ڱ��������͸���

    for(int i = 0; i < rec.size(); i++) {
        if(st & (1 << i)) //��������
            postive.push_back(rec[i]);
        else //���渺��
            negative.push_back(rec[i]);
    }

    int np = 0, nn = 0; //���������ĸ��������渺���ĸ���
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
    if(sum & 1) { //���sumΪ��������������
        puts("no solution");
        return;
    }

    sum = sum / 2;

    int end = 1 << rec.size();
    for(int i = 0; i < end; i++) { //������� 2^16�����
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
