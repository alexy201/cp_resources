

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <utility>
#include <queue>
#include <cmath>
#include <tuple>
#include <set>
#include <cmath>
#include <iomanip>

using namespace std;

typedef long long int ll;
typedef vector <int> vi;
typedef pair <int, int> p;
typedef vector <pair <int, int> > vip;
typedef priority_queue<int, vector<int>, greater<int> > pri;
typedef priority_queue<int> bpri;

#define pb push_back
#define mp make_pair
#define popb pop_back
#define fir first
#define sec second
#define INF 2000000000
#define MOD 1000000007
#define PI 3.1415926535897932384626
#define MAX 2000000

ll a[MAX];
class SegTree {
public:
    int S;
    ll sum[MAX];
    ll lazy[MAX];
    void init(int id, int l, int r) {
        if(r-l>1) {
            int m = l + ((r-l)>>1);
            init(id<<1, l, m);
            init(id<<1|1, m, r);
            //[l..r)
            sum[id] = sum[id<<1] + sum[id<<1|1];
            lazy[id] = -1;
        } else
            sum[id] = (ll) a[l], lazy[id] = -1;
    }
    void setz(int id, int l, int r, int x) {
        sum[id] = ((ll)x)*(r-l);
        lazy[id] = x;
    }
    void propogate(int id, int l, int r) {
        if(lazy[id] != -1) {
            if(r-l>1) {
                int m = l + ((r-l)>>1);
                setz(id<<1, l, m, lazy[id]);
                setz(id<<1|1, m, r, lazy[id]);
            }
            lazy[id] = -1;
        }
    }
    void upd(int id, int l, int r, int ql, int qr, int x) {
        if(ql <= l&&r <= qr) {
            setz(id, l, r, x);
            propogate(id, l, r);
        } else {
            propogate(id, l, r);
            int m = l + ((r-l)>>1);
            if(ql < m)
                upd(id<<1, l, m, ql, qr, x);
            if(m < qr)
                upd(id<<1|1, m, r, ql, qr, x);
            sum[id] = sum[id<<1] + sum[id<<1|1];
        }
    }
    ll qry(int id, int l, int r, int ql, int qr) {
        if(ql <= l&&r <= qr) {
            return sum[id];
        } else {
            propogate(id, l, r);
            int m = l + ((r-l)>>1);
            ll ans = 0LL;
            if(ql < m)
                ans += qry(id<<1, l, m, ql, qr);
            if(m < qr)
                ans += qry(id<<1|1, m, r, ql, qr);
            return ans;
        }
    }
};

int main(){
    SegTree now;
    ll siz = 1000001;
    ll N; cin >> N;
    for (ll i = 0; i < N; i++){
        char a; ll x, y; cin >> a >> x >> y;
        if (a == 'P'){
            now.upd(0, 0, siz, x, y, 1);
        }else {
            now.upd(0, 0, siz, x, y, -1);
        }
        cout << now.qry(0, 0, siz, x, y) << endl;
    }
    /*cin >> N;
    cout << endl;
    for (int i = 0; i < N; i++){
        int x, y; cin >> x >> y;
        cout << sum(size, x, y) << endl;
    }*/
}







