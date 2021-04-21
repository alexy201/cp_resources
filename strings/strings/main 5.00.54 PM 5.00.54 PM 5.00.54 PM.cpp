

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
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
typedef pair <ll, ll> p;
typedef pair <long double, long double> p1;
typedef vector <pair <int, int> > vip;
typedef vector <p> vip1;
typedef priority_queue<int, vector<int>, greater<int> > pri;
typedef priority_queue<int> bpri;

#define pb push_back
#define mp make_pair
#define popb pop_back
#define fi first
#define se second
#define INF 2000000000
#define MOD 1000000007
#define BASE 7817

p operator + (const p& a, const p& b){
    return { (a.first + b.first) % MOD, (a.second + b.second) % MOD };
}
p operator + (const p& a, const ll& b){
    return { (a.first + b) % MOD, (a.second + b) % MOD };
}
p operator - (const p& a, const p& b){
    return { (MOD + a.first - b.first) % MOD, (MOD + a.second - b.second) % MOD };
}
p operator * (const p& a, const p& b){
    return { (a.first * b.first) % MOD, (a.second * b.second) % MOD };
}
p operator * (const p& a, const ll& b){
    return { (a.first * b) % MOD, (a.second * b) % MOD };
}



class TrieNode {
public:
    TrieNode *next[26]{};
    bool is_leaf = false;
    TrieNode *get(char c) { return next[c - 'a']; }
    void add(char c) { next[c - 'a'] = new TrieNode; }
};


class Trie {
    struct TrieNode {
        bool word;
        unordered_map<char, TrieNode*> children;
        TrieNode() : word(false) {}
    };
    TrieNode* root;
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        auto node = root;
        for (char c : word){
            auto it = node -> children.find(c);
            if (it != node -> children.end()) node = it -> second;
            else node = (node -> children.emplace(c, new TrieNode())).first -> second;
        }
        node->word = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        auto node = root;
        for (char c : word){
            auto it = node -> children.find(c);
            if (it != node -> children.end()) node = it -> second;
            else return false;
        }
        return node->word;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        auto node = root;
        for (char c : prefix){
            auto it = node -> children.find(c);
            if (it != node -> children.end()) node = it -> second;
            else return false;
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */




int N, K;

vi arr;

map <ll, p> seen;

p hash_function(vi s){
    p h = {0, 0};
    for (int i = 0; i < s.size(); i++){
        h = {((4441* h.fi) % MOD) + s[i], ((7817 * h.se) % MOD) + s[i]};
    }
    return h;
}

ll hash_ll(vi s){
    p h = {0, 0};
    for (int i = 0; i < s.size(); i++){
        h = {((4441 * h.fi) % MOD) + s[i], ((7817 * h.se) % MOD) + s[i]};
    }
    return h.fi + h.se;
}

//SUFFIX ARR
vi suff;
string mag;

bool comp(int i, int j){
    return mag[i] < mag[j];
}

void construct() {
    vi classes;
    for (int i = 0; i < N; i++) {
        suff.pb(N - 1 - i);
        classes.pb(mag[i]);
    }
    sort(suff.begin(), suff.end(), comp);
    for (int len = 1; len < N; len *= 2) {
        vi c(classes);
        for (int i = 0; i < N; i++) {
            bool same = i && (suff[i - 1] + len < N) && (c[suff[i]] == c[suff[i - 1]]) && (c[suff[i] + len/2] == c[suff[i - 1] + len/2]);
            classes[suff[i]] = same ? classes[suff[i - 1]] : i;
        }
        vi cnt, s(suff);
        for (int i = 0; i < N; i++){
            cnt.pb(i);
        }
        for (int i = 0; i < N; i++){
            int s1 = s[i] - len;
            if (s1 >= 0){
                suff[cnt[classes[s1]]++] = s1;
            }
        }
    }
}

/*
 POLYNOMIAL HASH
 - find hashes of all sunbstrings
 - base: B and modulo: M
 - (B^(N-1)*a[0] + B^(N-2)*a[1]  .....  + B^(N-3)*a[N - 1]) % M
 - know h[0], h[1], h[N - 1]: find hash of substring from i to j
                              - (h[j]-(B^(j - i + 1)*h[i-1])) % M
 */

struct hsh{
    ll N; vi S, pre, power;
    void init(vi S){
        N = (ll)S.size();
        power.resize(N);
        pre.resize(N + 1);
        power[0] = 1;
        for (int i = 0; i < N; i++){
            pre[i + 1] = pre[i] * BASE + S[i];
            if (i){power[i] = power[i - 1] * BASE;}
        }
    }
    ll get(int s, int e){
        return pre[e] - pre[s] * power[e - s];
    }
};

int main(){
    cin >> N >> K;
    for (int i = 0; i < N; i++){
        int x; cin >> x;
        arr.pb(x);
    }
    vi now;
    for (int i = 0; i < arr.size(); i++){
        for (int j = i; j < min((int)arr.size(), i + 200); j++){
            now.pb(arr[j]);
            ll n = hash_ll(now);
            seen[n].se = j - i + 1; seen[n].fi++;
        }
        now.clear();
    }
    ll ma = 0;
    for (auto u : seen){
        if (u.se.fi >= K){
            ma = max(ma, u.se.se);
        }
    }
    cout << ma << endl;
}


///




