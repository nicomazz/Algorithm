#include <bits/stdc++.h>

using namespace std;
#define MAXN 600010

typedef long long ll;
ll tree[MAXN];
ll lazy[MAXN];

int N;
void propaga(int inx, int cnt_num)
{
    if ( lazy[inx])
    {
        tree[inx] += lazy[inx]*cnt_num;
        lazy[inx*2] += lazy[inx];
        lazy[inx*2+1] += lazy[inx];
        lazy[inx] = 0;
    }
}
void update(int tl, int tr, ll val,int l = 0, int r = N, int inx = 1)
{
propaga(inx,r-l);
    // tutto fuori
    if ( tr <= l || tl >= r || r <= l)
        return;
    // att dentro target
    int cnt_num = r-l;

    if (tl <= l && tr >= r){
        lazy[inx] += val;
        propaga(inx,cnt_num);
        return;
    }
    propaga(inx, cnt_num);
    int mid = (l+r)/2;
    update(tl,tr,val,l,mid,inx*2);
    update(tl,tr,val,mid,r,inx*2+1);
    tree[inx] = tree[inx*2]+tree[inx*2+1];
}

ll query(int tl,int tr, int l = 0, int r = N, int inx = 1)
{
    propaga(inx, r-l);

     // tutto fuori
    if ( tr <= l || tl >= r)
        return 0 ;

    // att dentro target
    if (tl <= l && tr >= r)
        return tree[inx];

    int mid = (l+r)/2;
    return query(tl,tr,l,mid,inx*2)+query(tl,tr,mid,r,inx*2+1);
}
int main()
{
ios::sync_with_stdio(0);
   // freopen("input.txt","r",stdin);
    int T;
    cin>>T;
    while (T--)
    {
       int t;
       cin>>N>>t;
       memset(tree,0,sizeof tree);
       memset(lazy,0,sizeof lazy);
       int cmd;
       int da, a, dt;
       for (int i = 0; i < t; i++)
       {
            cin>>cmd;
            if (cmd == 0)
            {
                cin>>da>>a>>dt;
                da--;
                //cerr<<"update\n";
                update(da,a, dt);

               /* cerr<<"after update:\n";
                for (int i = 0; i < N; i++)
                    cerr<<query(i,i+1)<<" ";
                cerr<<"\n";*/
            }
            else
            {
                cin>>da>>a;
                da--;
                //cerr<<"query\n";
                cout<<query(da,a)<<"\n";
            }
       }
    }
    return 0;
}
