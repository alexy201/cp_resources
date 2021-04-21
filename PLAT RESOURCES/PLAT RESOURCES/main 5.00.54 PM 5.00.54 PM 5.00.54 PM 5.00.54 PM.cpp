

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
#include <bitset>

using namespace std;

typedef long long int ll;
typedef vector <int> vi;
typedef pair <int, int> p;
typedef vector <p> vip;
typedef priority_queue<int, vector<int>, greater<int> > pri;
typedef priority_queue<int> bpri;

#define pb push_back
#define mp make_pair
#define popb pop_back
#define fi first
#define se second
#define MOD 1000000007
#define INF 2000000000


//BIT
int N;
int BIT[100001];

int pref(int ind){
    ind++;
    int sum = 0;
    while (ind > 0){
        sum += BIT[ind];
        ind -= ind & (-ind);
    }
    return sum;
}

void update(int ind, int val){
    ind++;
    while (ind <= N){
        BIT[ind] += val;
        ind += ind & (-ind);
    }
}

//tarjans scc

int F, R;
vi adj[10001];
int sc[10001];
int num = 0;
int ind[10001], lowlink[10001];
int t = 0;
stack <int> s;
bool ins[10001];

void dfs(int curr){
    t++;
    lowlink[curr] = t;
    ind[curr] = t;
    s.push(curr);
    ins[curr] = true;
    for (auto u : adj[curr]){
        if (ind[u] == INF){
            dfs(u);
            lowlink[curr] = min(lowlink[curr], lowlink[u]);
        }else if (ins[u]){
            lowlink[curr] = min(lowlink[curr], ind[u]);
        }
    }
    if (lowlink[curr] == ind[curr]){
        do {
            int u = s.top();
            s.pop();
            ins[u] = false;
            sc[u] = num;
            if (u == curr){
                break;
            }
        }while (true);
        num++;
    }
}

int main(){
    cin >> F >> R;
    for (int i = 0; i < R; i++){
        int x, y; cin >> x >> y;
        adj[x].pb(y);
    }
    for (int i = 1; i <= F; i++){
        sc[i] = INF;
        ind[i] = INF;
    }
    for (int i = 1; i <= F; i++){
        if (sc[i] == INF) {
            dfs(i);
        }
    }
    map <int, vi> con;
    for (int j = 1; j <= F; j++){
        con[sc[j]].pb(j);
    }
    for (auto u : con){
        cout << u.fi << ": ";
        for (auto i : u.se){
            cout << i << " ";
        }
        cout << endl;
    }
}

//kmp

int F[15]; //size
string T;
vi places;

void gen(string a){
    F[0] = -1;
    for (int i = 0; i < a.size(); i++){
        F[i + 1] = F[i];
        while (F[i + 1] > -1 && a[i] != a[F[i + 1]]){
            F[i + 1] = F[F[i + 1]];
        }
        F[i + 1]++;
    }
}

void search(string a){
    int j = 0, k = 0;
    int nP = 0;
    while (j < T.size()){
        if (a[k] == T[j]){
            j++; k++;
            if (k == a.size()){
                places.pb(j - k);
                nP++;
                k = F[k];
            }
        }else {
            k = F[k];
            if (k < 0){
                j++; k++;
            }
        }
    }
}

//segtree

int N, Q;

int seg[140000];
//size 2^log2(N) + 1

void up(int i, int val, int l, int r, int n) {
    if (l > i || r < i){
        return;
    }
    if (l == r){
        seg[n] += val; //seg[n] = x in case of min/max, seg[n] += x if sum
        return;
    }
    int m = (l + r)/2;
    up(i, val, l, m, (2 * n) + 1);
    up(i, val, m + 1, r, (2 * n) + 2);
    seg[n] = seg[(2 * n) + 1] + seg[(2 * n) + 2];
}

int qu(int x, int y, int l, int r, int n) {
    if (r < x || l > y){
        return 0; //IF MAX/MIN return INF, if sum, return 0
    }
    if (r <= y && l >= x){
        return seg[n];
    }
    int m = (l + r)/2;
    return qu(x, y, l, m, (2 * n) + 1) + qu(x, y, m + 1, r, (2 * n) + 2);
}

void update(int i, int val){
    up(i, val, 0, N - 1, 0);
}

int query(int x, int y){
    return qu(x, y, 0, N - 1, 0);
}

//segtree with lazy

int N, Q;

int seg[250000];
int lazy[250000];

void push(int l, int r, int n) {
    if (lazy[n] == 0){
        return;
    }
    seg[n] += (r - l + 1) * lazy[n];
    if (l != r){
        lazy[(2 * n) + 1] += lazy[n];
        lazy[(2 * n) + 2] += lazy[n];
    }
    lazy[n] = 0;
} 

void upran(int x, int y, int val, int l, int r, int n) {
    push(l, r, n);
    if (l > y || r < x){
        return;
    }
    if (l >= x && r <= y){
        lazy[n] = val;
        push(l, r, n);
        return;
    }
    int m = (l + r)/2;
    upran(x, y, val, l, m, (2 * n) + 1);
    upran(x, y, val, m + 1, r, (2 * n) + 2);
    seg[n] = seg[(2 * n) + 1] + seg[(2 * n) + 2];
}

int qu(int x, int y, int l, int r, int n) {
    push(l, r, n);
    if (r < x || l > y){
        return 0;
    }
    if (r <= y && l >= x){
        return seg[n];
    }
    int m = (l + r)/2;
    return (qu(x, y, l, m, (2 * n) + 1)) + (qu(x, y, m + 1, r, (2 * n) + 2));
}

void update(int i, int j, int val){
    upran(i, j, val, 0, N - 1, 0);
}

int query(int x, int y){
    return qu(x, y, 0, N - 1, 0);
}

//segtree min lazy
int N, M;
vip range;
int stall[100001];

bool cmp(p a, p b){
    if (b.se == a.se){
        return b.fi > a.fi;
    }
    return b.se > a.se;
}

int seg[250000];
int lazy[250000];

void push(int l, int r, int n) {
    if (lazy[n] == 0){
        return;
    }
    seg[n] += lazy[n];
    if (l != r){
        lazy[(2 * n) + 1] += lazy[n];
        lazy[(2 * n) + 2] += lazy[n];
    }
    lazy[n] = 0;
}

void upran(int x, int y, int val, int l, int r, int n) {
    push(l, r, n);
    if (l > y || r < x){
        return;
    }
    if (l >= x && r <= y){
        lazy[n] += val;
        push(l, r, n);
        return;
    }
    int m = (l + r)/2;
    upran(x, y, val, l, m, (2 * n) + 1);
    upran(x, y, val, m + 1, r, (2 * n) + 2);
    seg[n] = min(seg[(2 * n) + 1], seg[(2 * n) + 2]);
}

int qu(int x, int y, int l, int r, int n) {
    push(l, r, n);
    if (r < x || l > y){
        return INF;
    }
    if (r <= y && l >= x){
        return seg[n];
    }
    int m = (l + r)/2;
    return min((qu(x, y, l, m, (2 * n) + 1)), (qu(x, y, m + 1, r, (2 * n) + 2)));
}

void update(int i, int j, int val){
    upran(i, j, val, 0, N - 1, 0);
}

int query(int x, int y){
    return qu(x, y, 0, N - 1, 0);
}

//hamiltonian path
int N, M;
int d[20][20];
int dp[(1 << 20)][20];

int main(){
    cin >> N >> M;
    for (int i = 0; i < M; i++){
        int x, y, z; cin >> x >> y >> z;
        x--; y--;
        d[x][y] = z;
        d[y][x] = z;
    }
    for (int i = 0; i <= (1 << N) - 1; i++){
        for (int j = 0; j < N; j++){
            if (i == (1 << j)){
                dp[i][j] = 0;
            }else {
                dp[i][j] = INF;
            }
        }
    }
    for (int m = 1; m <= (1 << N) - 1; m++){
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                if ((m & 1 << i) && (m & 1 << j) && d[j][i]){
                    dp[m][i] = min(dp[m][i], dp[m^(1 << i)][j] + d[j][i]);
                }
            }
        }
    }
    int mi = INF;
    for (int i = 0; i < N; i++){
        mi = min(mi, dp[(1 << N) - 1][i]);
    }
    cout << mi << endl;
}




//euler tour
int M;
int num[501][501];
stack <int> path;
int degree[501];

void dfs(int s){
    if (degree[s] == 0){
        path.push(s);
        return;
    }
    while (degree[s]){
        for (int nex = 1; nex <= 500; nex++){
            if (num[s][nex]){
                num[s][nex]--;
                num[nex][s]--;
                degree[s]--;
                degree[nex]--;
                dfs(nex);
            }
        }
    }
    path.push(s);
}

int main(){
    cin >> M;
    for (int i = 0; i < M; i++){
        int x, y; cin >> x >> y;
        num[x][y]++;
        num[y][x]++;
        degree[x]++;
        degree[y]++;
    }
    int s = INF;
    for (int i = 1; i <= 500; i++){
        if (degree[i]){
            s = i;
            break;
        }
    }
    for (int i = 1; i <= 500; i++){
        if (degree[i] & 1){
            s = i;
            break;
        }
    }
    dfs(s);
    while (path.size() > 0){
        cout << path.top() << endl;
        path.pop();
    }
}

///LCA

int V, E;
vi adj[100505];
vi r;
vip hei;
int ins[100505];
bool visited[100005];

void construct(int n, int h){
    visited[n] = true;
    r.pb(n);
    hei.pb({h, n});
    for (auto u : adj[n]){
        if (!visited[u]){
            construct(u, h + 1);
            r.pb(n);
            hei.pb({h, n});
        }
    }
}

p seg[140000];

void up(int i, p val, int l, int r, int n) {
    if (l > i || r < i){
        return;
    }
    if (l == r){
        seg[n] = {val.fi, val.se};
        return;
    }
    int m = (l + r)/2;
    up(i, val, l, m, (2 * n) + 1);
    up(i, val, m + 1, r, (2 * n) + 2);
    seg[n] = min(seg[(2 * n) + 1], seg[(2 * n) + 2]);
}

p qu(int x, int y, int l, int r, int n) {
    if (r < x || l > y){
        return {INF, INF};
    }
    if (r <= y && l >= x){
        return {seg[n].fi, seg[n].se};
    }
    int m = (l + r)/2;
    return min(qu(x, y, l, m, (2 * n) + 1), qu(x, y, m + 1, r, (2 * n) + 2));
}

void update(int i, p val){
    up(i, val, 0, (int)r.size() - 1, 0);
}

p query(int x, int y){
    return qu(min(x, y), max(x, y), 0, (int)r.size() - 1, 0);
}

int main(){
    cin >> V >> E;
    for (int i = 1; i < V; i++){
        int x; cin >> x;
        adj[i + 1].pb(x);
        adj[x].pb(i + 1);
    }
    construct(1, 1);
    for (int i = 1; i <= V; i++){
        ins[i] = -1;
    }
    for (int i = 0; i < r.size(); i++){
        if (ins[r[i]] == -1){
            ins[r[i]] = i;
        }
    }
    for (int i = 0; i < hei.size(); i++){
        update(i, hei[i]);
    }
    for (int i = 0; i < E; i++){
        int x, y; cin >> x >> y;
        cout << query(ins[x], ins[y]).se << endl;
    }
}

// HLD

int N;
vi adj[MAXN];

namespace hld{
    int link[MAXN], dep[MAXN], sz[MAXN], in[MAXN], rin[MAXN], nxt[MAXN], out[MAXN], t = 0;
    vi ch[MAXN];
    void dfs_sz(int n = 0, int p = -1, int d = 0){
        link[n] = p; sz[n] = 1;
        dep[n] = d;
        for (auto u : adj[n]){
            if (u != p){
                dfs_sz(u, n, d + 1);
                sz[n] += sz[u];
                ch[n].push_back(u);
                if (sz[u] > sz[ch[n][0]]){
                    swap(ch[n][0], ch[n].back());
                }
            }
        }
    }
    void dfs_hld(int n = 0){
        in[n] = t++;
        rin[in[n]] = n;
        for (auto v : ch[n]) {
            nxt[v] = (v == ch[n][0] ? nxt[n] : v);
            dfs_hld(v);
        }
        out[n] = t;
    }
    void init(){
        dfs_sz();
        dfs_hld();
    }
    int lca(int u, int v) {
        while (nxt[u] != nxt[v]) {
            if (dep[nxt[u]] < dep[nxt[v]]){
                swap(u, v);
            }
            u = link[nxt[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }
    
    ll st[MAXSEG];
    ll lazy[MAXSEG];
    
    void push(int node, int lo, int hi) {
        if (lazy[node] == 0){
            return;
        }
        st[node] += lazy[node]; //change this if you don't want to append value
        if (lo != hi){
            lazy[2 * node + 1] += lazy[node];
            lazy[2 * node + 2] += lazy[node];
        }
        lazy[node] = 0;
    }
    
    void update_range(int s, int e, int x, int lo = 0, int hi = -1, int node = 0) {
        if (hi == -1){
            hi = N - 1;
        }
        push(node, lo, hi);
        if (hi < s || lo > e){
            return;
        }
        if (lo >= s && hi <= e){
            lazy[node] = x;
            push(node, lo, hi);
            return;
        }
        int mid = (lo + hi) / 2;
        update_range(s, e, x, lo, mid, 2 * node + 1);
        update_range(s, e, x, mid + 1, hi, 2 * node + 2);
        st[node] = max(st[2 * node + 1], st[2 * node + 2]); // max
    }
    
    ll query(int s, int e, int lo = 0, int hi = -1, int node = 0) {
        if (hi == -1){
            hi = N - 1;
        }
        push(node, lo, hi);
        if (hi < s || lo > e){
            return 0;
        }
        if (lo >= s && hi <= e){
            return st[node];
        }
        int mid = (lo + hi)/2;
        return max(query(s, e, lo, mid, 2 * node + 1), query(s, e, mid + 1, hi, 2 * node + 2)); // max
    }
    
    void update_subtree(int n, int x){
        update_range(in[n], out[n] - 1, x);
    }
    
    ll query_subtree(int n){
        return query(in[n], out[n] - 1);
    }
    
    void update_path(int u, int v, int x, bool ig = false) {
        while (nxt[u] != nxt[v]){
            if (dep[nxt[u]] < dep[nxt[v]]){
                swap(u, v);
            }
            update_range(in[nxt[u]], in[u], x);
            u = link[nxt[u]];
        }
        if (dep[u] < dep[v]){
            swap(u, v);
        }
        update_range(in[v] + ig, in[u], x);
    }
    
    ll query_path(int u, int v, bool ig = false) {
        ll ret = 0;
        while (nxt[u] != nxt[v]){
            if (dep[nxt[u]] < dep[nxt[v]]){
                swap(u, v);
            }
            ret = max(ret, query(in[nxt[u]], in[u])); // max
            u = link[nxt[u]];
        }
        if (dep[u] < dep[v]){
            swap(u, v);
        }
        return ret = max(ret, query(in[v] + ig, in[u])); // max
    }
}

//topo sort

int N;
vi adj[100001];

vi topo(int m){
    vi deg(N + 1);
    for (int u = 0; u < N; u++){
        for (auto v : adj[u]){
            deg[v]++; //indegree
        }
    }
    pri stack; //can change if you want lexigraphical
    for (int u = 1; u <= N; u++){
        if (deg[u] == 0) {
            stack.push(u);
        }
    }
    vi order;
    while (!stack.empty()) {
        int u = stack.top(); stack.pop();
        order.push_back(u);
        for (auto v : adj[u]){
            if (--deg[v] == 0){
                stack.push(v);
            }
        }
    }
    return order.size() == N ? order : vector<int>();
}

//binary lifting
class TreeAncestor {
public:
    int dp[50001][16];
    TreeAncestor(int n, vector<int>& parent) {
        for (int i = 0; i < n; i++){
            for (int j = 0; j < 16; j++){
                dp[i][j] = -1;
            }
        }
        for (int i = 0; i < n; i++){
            dp[i][0] = parent[i];
        }
        for (int i = 0; i < n; i++){
            for (int j = 1; j < 16; j++){
                if (dp[i][j - 1] != -1){
                    dp[i][j] = dp[dp[i][j - 1]][j - 1];
                }
            }
        }
    }
    
    int getKthAncestor(int node, int k) {
        for (int i = 15; i >= 0; i--){
            if (node == -1){
                return node;
            }
            if ((1 << i) <= k){
                node = dp[node][i];
                k -= (1 << i);
            }
        }
        return node;
    }
};
