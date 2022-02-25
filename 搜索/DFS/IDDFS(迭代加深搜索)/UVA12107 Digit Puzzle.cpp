/*
题意:摘自网上
给一个不完整表达式，要求修改尽量少的数，使修改后的数字谜只有唯一解。
数字可以修改为通配符,通配符也可以修改为数字，数字也可以改变为另一数字，
但不能增删，表达式中所有涉及的数必须是没有前导零的正数。输入数字谜一定
形如a*b=c，其中a、b、c分别最多有2、2、4位。用下划线表示未知数字。输入
保证会有解，即有经过变换后肯定能有一个表达式有唯一解。如果有多个解，
输出字典序最小的解.
链接:https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3259
思路:可以先dfs枚举修改后的表达式,再用另一个dfs去填补通配符 验证当前表达式
的结果是否有唯一解.因为复杂度很大,因此要用迭代加深搜索枚举修改次数依次增大.
*/
//ac 110ms IDDFS
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5
#define INF 0x3f3f3f3f
using namespace std;

int len[3];
char str[3][N],op[12]="*0123456789";//按照字典序顺序'*'号最小

//前两个乘数 通配符填补完,cal()验证 两数之积的数字部分是否和str[3]一致
int cal(){
    int a=0,b=0;
    for(int i=0;i<len[0];i++)
        a=a*10+str[0][i]-'0';
    for(int i=0;i<len[1];i++)
        b=b*10+str[1][i]-'0';
    int c=a*b;
    char s[4];
    int i=1;
    while(c){
        s[len[2]-i]=c%10+'0';
        c/=10;
        i++;
    }
    if(i!=len[2]+1)//长度不一致 则无解
        return 0;
    for(int j=0;j<len[2];j++){
        //str[2]不是通配符的地方 数字必须保持一致
        if(str[2][j]!='*' && str[2][j]!=s[j])
            return 0;
    }
    return 1;//有解
}

//在修改了dep次的原串上验证 解是否唯一,填补前两个乘数的通配符
int check(int k,int pos){
    if(pos == len[k]){
        k++;
        pos=0;
    }
    if(k == 2)//前两个乘数 通配符填补完,cal()验证 两数之积的数字部分是否和str[2]一致
        return cal();
    char old=str[k][pos];
    int cnt=0;//记录当前方案数
    if(str[k][pos]!='*')//本身是数字 就不能填补了
        cnt+=check(k,pos+1);
    else{//通配符可以填补
        for(int i=1;i<11;i++){//只能填补数字 因此是下标是1,10
            if(i == 1 && !pos)//去掉前导零
                continue;
            str[k][pos]=op[i];
            cnt+=check(k,pos+1);
            if(cnt>1)//大于1 就说明已经不唯一了,就不必再验证 不加这个剪枝 230ms
                break;
        }
    }
    str[k][pos]=old;//因为要输出原先修改后含有通配符的原串,所以要还原
    return cnt;
}

//修改dep次原串
int dfs(int d,int dep,int k,int pos){
    if(d == dep)
        return check(0,0) == 1;//判断当前修改次数为dep的表达式 解是否唯一 0代表无解,>1代表解不唯一
    if(pos == len[k]){
        k++;
        pos=0;
    }
    if(k == 3)//修改次数未达到dep次,由于修改次数为0,dep-1的结果在前面已经全部验证 解不唯一或无解了.
        return 0;
    char old=str[k][pos];
    //不能先按照本身的old不修改去搜索,这样搜索到的不一定是字典序最小的.
    for(int i=0;i<11;i++){//枚举str[k][pos]位置 可以修改的数字
        if(i == 1 && !pos)//0 不能放在第一个
            continue;
        str[k][pos]=op[i];
        if(op[i] == old){//本身就是old数字,修改次数不变,这里是按照字典序枚举,在dep次修改下 是否唯一解
            if(dfs(d,dep,k,pos+1))
                return 1;
        }
        else{//将原先的old修改为op[i]
            if(dfs(d+1,dep,k,pos+1))
                return 1;
        }
    }
    str[k][pos]=old;//回溯时恢复 原先的old
    return 0;
}

int main(){
    int cas=0;
    while(scanf("%s",str[0]) && str[0][0]!='0'){
        scanf("%s",str[1]);
        scanf("%s",str[2]);
        len[0]=strlen(str[0]);
        len[1]=strlen(str[1]);
        len[2]=strlen(str[2]);
        cas++;
        for(int i=0;;i++){
            if(dfs(0,i,0,0)){
                printf("Case %d: %s %s %s\n",cas,str[0],str[1],str[2]);
                break;
            }
        }
    }
    return 0;
}

/*
//ac 2.98s dfs
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 5
#define INF 0x3f3f3f3f
using namespace std;

int len[3],ans;
char str[3][N],op[12]="*0123456789",res[3][N];

int cal(){
    int a=0,b=0;
    for(int i=0;i<len[0];i++)
        a=a*10+str[0][i]-'0';
    for(int i=0;i<len[1];i++)
        b=b*10+str[1][i]-'0';
    int c=a*b;
    char s[4];
    int i=1;
    while(c){
        s[len[2]-i]=c%10+'0';
        c/=10;
        i++;
    }
    if(i!=len[2]+1)
        return 0;
    for(int j=0;j<len[2];j++){
        if(str[2][j]!='*' && str[2][j]!=s[j])
            return 0;
    }
    return 1;
}

int check(int k,int pos){
    if(pos == len[k]){
        k++;
        pos=0;
    }
    if(k == 2)
        return cal();
    char old=str[k][pos];
    int cnt=0;
    if(str[k][pos]!='*')
        cnt+=check(k,pos+1);
    else{
        for(int i=1;i<11;i++){
            if(i == 1 && !pos)
                continue;
            str[k][pos]=op[i];
            cnt+=check(k,pos+1);
            if(cnt>1)
                break;
        }
    }
    str[k][pos]=old;
    return cnt;
}

void dfs(int d,int k,int pos){
    if(check(0,0) == 1){
        if(d<ans){
        	ans=d;
        	for(int i=0;i<3;i++)
        		strcpy(res[i],str[i]);
		}
        return;
	}
	if(d>=ans)
		return;
    if(pos == len[k]){
        k++;
        pos=0;
    }
    if(k == 3)
        return;
    char old=str[k][pos];
    for(int i=0;i<11;i++){
        if(i == 1 && !pos)
            continue;
        str[k][pos]=op[i];
        if(op[i] == old)
            dfs(d,k,pos+1);
        else
            dfs(d+1,k,pos+1);
    }
    str[k][pos]=old;
}

int main(){
    int cas=0;
    while(scanf("%s",str[0]) && str[0][0]!='0'){
        scanf("%s",str[1]);
        scanf("%s",str[2]);
        len[0]=strlen(str[0]);
        len[1]=strlen(str[1]);
        len[2]=strlen(str[2]);
        cas++;
        ans=INF;
        dfs(0,0,0);
        printf("Case %d: %s %s %s\n",cas,res[0],res[1],res[2]);
    }
    return 0;
}
*/

/*
bfs 不好模拟,状态不好表示,无法判重,必定会MLE.
*/
