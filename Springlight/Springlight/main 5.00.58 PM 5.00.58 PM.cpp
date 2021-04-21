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
#define INF 2000000000
#define MOD 1000000007

const int N = 100001;

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

void seg_update(int node, int left, int right, int x, int y, int value) {
    propagate(node, left, right);
    if (x <= left && right <= y){
        segm_tree[node].lazy += value;
    }else {
        int middle = (left + right)/2;
        if (x <= middle){
            seg_update(2 * node + 1, left, middle, x, y, value);
        }
        if (y >= middle + 1){
            seg_update(2 * node + 2, middle + 1, right, x, y, value);
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

void update(int l, int r, int v){
    seg_update(1, 0, N - 1, l, r, v);
}

int qry(int l, int r){
    return seg_query(1, 0, N - 1, l, r);
}

int main(){
    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++){
        int x; cin >> x;
        update(i, i, x);
    }
    for (int i = 0; i < q; i++){
        char a; int x, y; cin >> a >> x >> y;
        if (a == 'q'){
            cout << qry(x - 1, y - 1) << endl;
        }else {
            update(x - 1, x - 1, y);
        }
    }
}
