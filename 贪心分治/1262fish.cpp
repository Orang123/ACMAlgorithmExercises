#include<cstdio>
#include<queue>
using namespace std;
struct pool{
    int a,b;
    friend bool operator< (const pool &x,const pool &y){
        return x.a < y.a;
    }
};
int main(){
    int T,n,m,sum;
    pool tmp;
    scanf("%d",&T);
    priority_queue<pool> Q;//这里有时其实可以写在for循环里面,编译器可以优化如果还有剩余会新开一个,如果没有剩余应该会继续用这个
    while(T--){
        sum=0;
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++){
            scanf("%d%d",&tmp.a,&tmp.b);
            Q.push(tmp);
        }
        for(int i=0;i<m&&!Q.empty();i++){//这里有可能钓不到m次鱼已经没有能钓的鱼塘了
            tmp=Q.top();
            if(!tmp.b){
                sum+=(m-i)*tmp.a;
                break;
            }
            Q.pop();
            sum+=tmp.a;
            tmp.a-=tmp.b;
            if(tmp.a>0) Q.push(tmp);//因为有可能tmp.a第一次钓完鱼tmp.b比tmp.a还大就为负数了
        }
        while(!Q.empty()) Q.pop();
         printf("%d\n",sum);
    }
    return 0;
}
