这里的最优方案是指物品总价值最大的方案。以01 背包为例。
结合求最大总价值和方案总数两个问题的思路，最优方案的总数可以这样求：
F[i,v]代表该状态的最大价值,G[i,v]表示这个子问题的最优方案的总数，则在求
F[i,v]的同时求G[i,v]的伪代码如下:
G[0,0]  = 1
for i  1 to N
for v  0 to V
F[i,v] =max{F[i-1,v],F[i-1,v-Ci] +Wi}
G[i,v] =  0
if F[i,v] = F[i-1,v]
G[i,v]=G[i,v] + G[i-1][v]
if F[i,v] = F[i-1,v-Ci]+Wi
G[i,v] = G[i,v] + G[i-1][v-Ci]
