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

int T;

int main(){
    cin >> T;
    for (int i = 1; i <= T; i++){
        int N; cin >> N;
        if (N == -1){
            return 0;
        }
        double div = N;
        int c[N];
        double num[N];
        bool used[N];
        for (int a = 0; a < N; a++){
            c[a] = 1; used[a] = false;
        }
        for (int a = 0; a < N; a++){
            int x; cin >> x;
            if (x == -1){
                return 0;
            }
            int fla = -1; double mi = INF;
            for (int b = 0; b < x; b++){
                int y; cin >> y;
                if (num[y]/div < mi && !used[y]){
                    fla = y;
                    mi = num[y]/div;
                }
            }
            if (fla != -1){
                used[fla] = true;
                num[fla]++;
            }
            cout << fla << endl;
        }
    }
    return 0;
}
