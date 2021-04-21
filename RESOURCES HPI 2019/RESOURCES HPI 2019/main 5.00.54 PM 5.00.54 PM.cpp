
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
#define fi first
#define se second
#define MOD 1000000007
#define INF 2000000000

///////////////////////////////////   DP   ///////////////////////////////////

//String Edit Distance

void SED(){
    string a, b;
    cin >> a >> b;
    int dp[a.size() + 1][b.size() + 1];
    for (int i = 0; i <= a.size(); i++){
        for (int j = 0; j <= b.size(); j++){
            if (i == 0){
                dp[i][j] = j;
            }
            if (j == 0){
                dp[i][j] = i;
            }
        }
    }
    for (int i = 1; i <= a.size(); i++){
        for (int j = 1; j <= b.size(); j++){
            if (a[i - 1] == b[j - 1]){
                dp[i][j] = dp[i - 1][j - 1];
            }else {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
        }
    }
    cout << dp[a.size()][b.size()] << endl;
}

//knapsack no memory op

void knap(){
    int N, C;
    vip obj;
    cin >> N >> C;
    int dp[N + 1][C + 1];
    for (int i = 0; i < N; i++){
        int x, y; cin >> x >> y;
        obj.pb({x, y});
    }
    for (int i = 0; i <= N; i++){
        for (int j = 0; j <= C; j++){
            if (i == 0 || j == 0){
                dp[i][j] = 0;
                continue;
            }
            if (obj[i - 1].fi <= j){
                dp[i][j] = obj[i - 1].se + dp[i - 1][j - obj[i - 1].fi];
            }
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        }
    }
    cout << dp[N][C] << endl;
}

//knapsack memory op

void goodknap(){
    int N, C;
    vip obj;
    cin >> N >> C;
    int dp[C + 1];
    for (int i = 0; i < N; i++){
        int x, y; cin >> x >> y;
        obj.pb({x, y});
    }
    for (int i = 0; i <= N; i++){
        int ne[C + 1];
        for (int j = 0; j <= C; j++){
            if (i == 0 || j == 0){
                ne[j] = 0;
                continue;
            }
            if (obj[i - 1].fi <= j){
                ne[j] = obj[i - 1].se + dp[j - obj[i - 1].fi];
            }
            ne[j] = max(ne[j], dp[j]);
        }
        for (int j = 0; j <= C; j++){
            dp[j] = ne[j];
        }
    }
    cout << dp[C] << endl;
}

//infinite knapsack memory opt
void infinite(){
    int N, C;
    vip obj;
    cin >> N >> C;
    int dp[C + 1];
    obj.pb({0, 0});
    for (int i = 0; i < N; i++){
        int x, y; cin >> x >> y;
        obj.pb({x, y});
    }
    for (int i = 0; i <= N; i++){
        int ne[C + 1];
        for (int j = 0; j <= C; j++){
            if (i == 0 || j == 0){
                ne[j] = 0;
                continue;
            }
            if (obj[i].fi <= j){
                ne[j] = obj[i].se + ne[j - obj[i].fi];
            }
            ne[j] = max(ne[j], dp[j]);
        }
        for (int j = 0; j <= C; j++){
            dp[j] = ne[j];
        }
    }
    cout << dp[C] << endl;
}

///////////////////////////////////   GRAPHS   ///////////////////////////////////

//kruskal + union find

int V, E;
int link[1001];
int size[1001];

vector <pair <int, p > > edges;

int find(int x){
    if (link[x] == x){
        return x;
    }
    int res = find(link[x]);
    link[x] = res;
    return res;
}

bool same(int x, int y){
    if (find(x) == find(y)){
        return true;
    }
    return false;
}

void unite(int x, int y){
    int a = find(x);
    int b = find(y);
    if (size[a] < size[b]){
        swap(a, b);
    }
    size[a] += size[b];
    link[b] = a;
}

int kruskal(){
    int num = 0;
    for (int i = 0; i < edges.size(); i++){
        if (!same(edges[i].se.fi, edges[i].se.se)){
            unite(edges[i].se.fi, edges[i].se.se);
            num += edges[i].fi;
        }
    }
    return num;
}

void init(){
    cin >> V >> E;
    int x, y, z;
    //-----------------------------
    for (int i = 1; i <= V; i++){
        link[i] = i;
        size[i] = 1;
    }
    //-----------------------------
    for (int i = 0; i < E; i++){
        cin >> x >> y >> z;
        edges.pb({z, {x, y}});
        unite(x, y);
    }
    sort (edges.begin(), edges.end());
    //-----------------------------
    cout << kruskal() << endl;
}


//djikstras

void djikstras(){
    int V, E, S;
    cin >> V >> E >> S;
    vip adj[V + 1];
    int dis[V + 1];
    bool visited[V + 1];
    int x, y, z;
    for (int i = 1; i <= V; i++){
        dis[i] = INF;
        visited[i] = false;
    }
    dis[S] = 0;
    for (int i = 0; i < E; i++){
        cin >> x >> y >> z;
        adj[x].pb({y, z});
        adj[y].pb({x, z});
    }
    priority_queue<p, vector<p>, greater<p> > q;
    q.push({0, S});
    while (!q.empty()){
        p now = q.top();
        q.pop();
        if (visited[now.se]){
            continue;
        }
        visited[now.se] = true;
        for (auto u : adj[now.se]){
            if (dis[now.se] + u.se < dis[u.fi]){
                dis[u.fi] = dis[now.se] + u.se;
                q.push({dis[u.fi], u.fi});
            }
        }
    }
    for (int i = 1; i <= V; i++){
        if (dis[i] == INF){
            cout << "-1" << endl;
        }else {
            cout << dis[i] << endl;
        }
    }
}

//prims

void prim(){
    int V, E;
    cin >> V >> E;
    priority_queue<p, vector<p>, greater<p > > q;
    vip adj[V + 1];
    bool visited[V + 1];
    int key[V + 1];
    for (int i = 1; i <= V; i++){
        visited[i] = false;
        key[i] = INF;
    }
    int sum = 0;
    int x, y, z;
    for (int i = 0; i < E; i++){
        cin >> x >> y >> z;
        adj[x].pb({y, z});
        adj[y].pb({x, z});
    }
    q.push({0, 1});
    while (!q.empty()){
        p now = q.top();
        q.pop();
        visited[now.se] = true;
        for (auto u : adj[now.se]){
            if (!visited[u.fi] && key[u.fi] > u.se){
                key[u.fi] = u.se;
                q.push({u.se, u.fi});
            }
        }
    }
    for (int i = 1; i <= V; i++){
        sum += key[i];
    }
    cout << sum << endl;
}

//floyd warshall

void floyd(){
    int V, E;
    cin >> V >> E;
    int arr[V + 1][V + 1];
    int dis[V + 1][V + 1];
    int x, y, z;
    for (int i = 0; i < E; i++){
        cin >> x >> y >> z;
        arr[x][y] = z;
    }
    for (int i = 1; i <= V; i++){
        for (int j = 1; j <= V; j++){
            if (i == j){
                dis[i][j] = 0;
            }else if (arr[i][j]){
                dis[i][j] = arr[i][j];
            }else {
                dis[i][j] = INF;
            }
        }
    }
    for (int l = 1; l <= V; l++){
        for (int i = 1; i <= V; i++){
            for (int j = 1; j <= V; j++){
                if (dis[i][l] != INF && dis[l][j] != INF){
                    dis[i][j] = min(dis[i][j], dis[i][l] + dis[l][j]);
                }
            }
        }
    }
}


//euleriean path/tour check

int N, M;
set <int> nodes;
vi adj[501];
bool visited[501];
vi start;

void dfs(int v){
    visited[v] = true;
    for (auto i : adj[v]){
        if (!visited[i]){
            dfs(i);
        }
    }
}

bool connected(){
    for (int i = 0; i <= N; i++){
        visited[i] = false;
    }
    int s;
    for (s = 0; s <= N; s++){
        if (adj[s].size() != 0){
            break;
        }
    }
    dfs(s);
    for (int i = 1; i <= N; i++){
        if (visited[i] == false && adj[i].size() > 0){
            return false;
        }
    }
    return true;
}

bool path(){
    if (!connected()){
        return false;
    }
    int odd = 0;
    for (int i = 1; i <= N; i++){
        if ((adj[i].size() % 2) == 1){
            odd++;
            start.pb(i);
            if (odd > 2){
                return false;
            }
        }
    }
    return true;
}


// http://ekzlib.herokuapp.com/view/







// https://ucdavis-bioinformatics-training.github.io/2020-Advanced_Single_Cell_RNA_Seq/data_analysis/shiny_app_install
