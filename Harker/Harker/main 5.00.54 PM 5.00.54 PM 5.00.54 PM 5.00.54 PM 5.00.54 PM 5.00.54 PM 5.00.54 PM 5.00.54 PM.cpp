

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
#define INF 20000000

int V, E;
vi adj[100505];
vi r;
int arr[100005];
int ins[100005];
int dic[200005][24];
bool visited[100005];

void construct(int n, int h){
    visited[n] = true;
    r.pb(n);
    arr[n] = h;
    for (auto u : adj[n]){
        if (!visited[u]){
            construct(u, h + 1);
            r.pb(n);
        }
    }
}

void build(){
    for (int i = 0; i < r.size(); i++){
        dic[i][0] = i;
    }
    for (int j = 1; (1 << j) <= r.size(); j++){
        for (int i = 0; (i + (1 << j) - 1) < r.size(); i++){
            if (dic[i][j - 1] < dic[i + (1 << (j - 1))][j - 1]){
                dic[i][j] = dic[i][j - 1];
            }else {
                dic[i][j] = dic[i + (1 << (j - 1))][j - 1];
            }
        }
    }
}

int RMQ(int l, int u){
    if (l > u){
        swap(l, u);
    }
    int j = log2(u - l + 1);
    if (dic[l][j] <= dic[u - (1 << j) + 1][j]){
        return dic[l][j];
    }else {
        return dic[u - (1 << j) + 1][j];
    }
}

int main(){
    cin >> V >> E;
    for (int i = 0; i < V - 1; i++){
        int x, y; cin >> x >> y;
        adj[y].pb(x);
        adj[x].pb(y);
    }
    construct(1, 1);
    for (int i = 0; i < r.size(); i++){
        if (ins[r[i]]){
            ins[r[i]] = i;
        }
    }
    build();
    //return 0;
    for (int i = 0; i < E; i++){
        int x, y; cin >> x >> y;
        int ind = RMQ(ins[x], ins[y]);
        int n = r[ind];
        int l = arr[x], r = arr[y];
        cout << l + r - 2 * arr[n] << endl;
    }
}
