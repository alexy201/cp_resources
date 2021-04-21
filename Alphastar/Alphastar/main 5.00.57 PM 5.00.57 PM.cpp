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
typedef vector <ll> vi;
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

long double dis(p a, p b) {
    return sqrt((abs(a.fi - b.fi) * abs(a.fi - b.fi)) + (abs(a.se - b.se) * abs(a.se - b.se)));
}

long long ccw(p a, p b, p c) {
    return (ll)((b.fi - a.fi) * (c.se - a.se)) - (ll)((b.se - a.se) * (c.fi - a.fi));
}

vip scan(vip points) {
    int n = (int)points.size();
    sort(points.begin(), points.end());
    vip hull(points.size());
    int idx = 0;
    for (int i = 0; i < n; i++) {
        while (idx >= 2 && ccw(hull[idx - 2], hull[idx - 1], points[i]) >= 0){
            idx--;
        }
        hull[idx++] = points[i];
    }
    int half = idx;
    for (int i = n; i >= 0; i--) {
        while (idx > half && ccw(hull[idx - 2], hull[idx - 1], points[i]) >= 0){
            idx--;
        }
        hull[idx++] = points[i];
    }
    idx--;
    hull.resize(idx);
    return hull;
}

int main(){
    int N; cin >> N;
    vip arr;
    for (int i = 0; i < N; i++){
        int x, y; cin >> x >> y;
        arr.pb({x, y});
    }
    vip ans = scan(arr);
    long double sum = 0;
    for (int i = 0; i < ans.size(); i++){
        sum += dis(ans[i], ans[(i + 1) % ans.size()]);
    }
    cout << setprecision(2) << fixed << sum << endl;
}








