

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
#define PI 3.1415926535897932384626
#define MAX 500

/////////////////// SPARSE TABLE METHOD O(1) ///////////////////

// lookup[i][j] is going to store index of minimum value in
// arr[i..j]. Ideally lookup table size should not be fixed and
// should be determined using n Log n. It is kept constant to
// keep code simple.
int dic[MAX][MAX];

void build(int arr[], int n){
    for (int i = 0; i < n; i++){
        dic[i][0] = arr[i];
    }
    for (int j = 1; (1 << j) <= n; j++){
        for (int i = 0; (i + (1 << j) - 1) < n; i++){
            if (dic[i][j - 1] > dic[i + (1 << (j - 1))][j - 1]){
                dic[i][j] = dic[i][j - 1];
            }else {
                dic[i][j] = dic[i + (1 << (j - 1))][j - 1];
            }
        }
    }
}

int RMQ(int l, int u){
    int j = (int)log2(u - l + 1);
    if (dic[l][j] >= dic[u - (1 << j) + 1][j]){
        return dic[l][j];
    }else {
        return dic[u - (1 << j) + 1][j];
    }
}

int main(){
    int a[] = { 7, 2, 3, 0, 5, 10, 3, 12, 18 };
    int n = sizeof(a)/sizeof(a[0]);
    cout << n << endl;
    build(a, n);
    cout << RMQ(0, 4) << endl;
    cout << RMQ(4, 7) << endl;
    cout << RMQ(7, 8) << endl;
}
