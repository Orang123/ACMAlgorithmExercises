/*
题意:摘自网上
给出n个数和m次询问，每次询问给出一个数x，
问在n个数中哪个数与x异或值最大.
n,m<=100000.每个数大小<=2^32.
链接:https://acm.hdu.edu.cn/showproblem.php?pid=4825
思路:01字典树.可以将每个数对应的二进制位的01串从高位
到低位建一棵字典树.这样对于输入的数x,可以按照字典树从
高位向低位去查找,对于x的第i位,值是son,判断当前儿子中是否
存在son^1的子节点,如果存在第i位的异或值就可以为1,这里是
从高位向低位贪心取的,能取到的1尽可能都取到,如果不存在,则
第i位只能为0了,就继续按照当前son的节点继续向下搜索判断.

注意:输入的x最大2^32次方,实际二进制位有33位,已经超过了int的范围,
因此要用long long,否则位运算的时候会出错.
*/
//ac 265ms 查找时,逐个记录每一位的值
#include<cstdio>
#include<cstring>
#define N 3200010
typedef long long ll;

int n,m,tr[N][2],cnt;
ll val;

int newNode(){
    cnt++;
    tr[cnt][0]=tr[cnt][1]=0;
    return cnt;
}

void insertWord(){
    int son,rt=0;
    //由最高位第32位开始向低位建立字典树,因为比较是
    //贪心选取保留较高位异或值为1的情况,这样才能最大
    for(int i=32;i>=0;i--){
        son=val>>i & 1;//val 第i位为son(0或1)
        if(!tr[rt][son])
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
}

ll findWord(){
    int son,rt=0;
    ll res=0;
    for(int i=32;i>=0;i--){
        son=val>>i & 1;
        if(tr[rt][son^1]){//如果字典树中第i位存在son^1的儿子,则第i位异或值就可以取1
            res|=(son^1)<<i;//记录字典树中选取的第i位的值为son^1
            rt=tr[rt][son^1];
        }
        else{//否则第i位的异或值只能是0
            res|=son<<i;//记录字典树中选取的第i位的值为son
            rt=tr[rt][son];
        }
    }
    return res;
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        cnt=-1;
        newNode();
        scanf("%d%d",&n,&m);
        while(n--){
            scanf("%d",&val);
            insertWord();
        }
        printf("Case #%d:\n",cas);
        while(m--){
            scanf("%d",&val);
            printf("%lld\n",findWord());
        }
    }
    return 0;
}

/*
//ac 390ms 将01字典树插入时对应的10进制数值记录下来
#include<cstdio>
#include<cstring>
#define N 3200010
typedef long long ll;

int n,m,tr[N][2],cnt;
ll word[N],val;

int newNode(){
    cnt++;
    tr[cnt][0]=tr[cnt][1]=-1;
    return cnt;
}

void insertWord(){
    int son,rt=0;
    for(int i=32;i>=0;i--){
        son=val>>i & 1;
        if(tr[rt][son] == -1)
            tr[rt][son]=newNode();
        rt=tr[rt][son];
    }
    word[rt]=val;
}

ll findWord(){
    int son,rt=0;
    for(int i=32;i>=0;i--){
        son=val>>i & 1;
        if(tr[rt][son^1]!=-1)
            rt=tr[rt][son^1];
        else
            rt=tr[rt][son];
    }
    return word[rt];
}

int main(){
    int T,cas=0;
    scanf("%d",&T);
    while(T--){
        cas++;
        cnt=-1;
        newNode();
        scanf("%d%d",&n,&m);
        while(n--){
            scanf("%d",&val);
            insertWord();
        }
        printf("Case #%d:\n",cas);
        while(m--){
            scanf("%d",&val);
            printf("%lld\n",findWord());
        }
    }
    return 0;
}
*/
