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
#define MOD 100000000
#define INF 2000000000

const int N = 1000001;

struct Segment{
    int sum, lazy;
}
segm_tree[2 * N];

void propagate(int node, int left, int right) {
    segm_tree[node].sum += (right - left + 1) * segm_tree[node].lazy;
    if (left < right) {
        segm_tree[2 * node + 1].lazy += segm_tree[node].lazy;
        segm_tree[2 * node + 2].lazy += segm_tree[node].lazy;
    }
    segm_tree[node].lazy = 0;
}

void seg_update(int node, int left, int right, int x, int y) {
    propagate(node, left, right);
    if (x <= left && right <= y){
        segm_tree[node].lazy = false;
    }else {
        int middle = (left + right)/2;
        if (x <= middle){
            seg_update(2 * node + 1, left, middle, x, y);
        }
        if (y >= middle + 1){
            seg_update(2 * node + 2, middle + 1, right, x, y);
        }
        propagate(2 * node + 1, left, middle);
        propagate(2 * node + 2, middle + 1, right);
        segm_tree[node].sum = segm_tree[2 * node + 1].sum + segm_tree[2 * node + 2].sum;
    }
}

int seg_query(int node, int left, int right, int x, int y) {
    propagate(node, left, right);
    if (x <= left && right <= y){
        return segm_tree[node].sum;
    }else {
        int sum = 0;
        int middle = (left + right)/2;
        if (x <= middle){
            sum += seg_query(2 * node + 1, left, middle, x, y);
        }
        if (y >= middle + 1){
            sum += seg_query(2 * node + 2, middle + 1, right, x, y);
        }
        return sum;
    }
}

void update(int l, int r){
    seg_update(1, 0, N - 1, l, r);
}

int qry(int l, int r){
    return seg_query(1, 0, N - 1, l, r);
}

int main(){
    int T; cin >> T;
    for (int i = 1; i <= T; i++){
        cout << "Case #" << i << ": ";
        int n, Q; cin >> n >> Q;
        vip que;
        for (int j = 0; j < n; j++){
            int x, y; cin >> x >> y;
            que.pb({y, x});
        }
        sort (que.begin(), que.end());
        int mi = INF;
        for (int j = 0; j < n; j++){
            mi = min(mi, qry(que[j].se - 1, que[j].fi - 1));
            update(que[j].se - 1, que[j].fi - 1);
        }
        cout << mi << endl;
    }
}




