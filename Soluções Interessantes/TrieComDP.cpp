#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 30;
using ll = long long ;
//template
ll n, m, k;
ll x[N];
string s;
#pragma region 
// const int MOD = 998244353;
const int MOD = 1e9 + 7;

#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace __gnu_pbds;

template<class T> using ordset = tree<
T,
null_type,
less<T>,
rb_tree_tag,
tree_order_statistics_node_update>;


struct mi {
    int v;
    explicit operator int() const { return v; }
    mi() { v = 0; }
    mi(long long _v) : v(_v % MOD) { v += (v < 0) * MOD; }
};
mi &operator+=(mi &a, mi b) {
    if ((a.v += b.v) >= MOD) a.v -= MOD;
    return a;
}
mi &operator-=(mi &a, mi b) {
    if ((a.v -= b.v) < 0) a.v += MOD;
    return a;
}
mi operator+(mi a, mi b) { return a += b; }
mi operator-(mi a, mi b) { return a -= b; }
mi operator*(mi a, mi b) { return mi((long long)a.v * b.v); }
mi &operator*=(mi &a, mi b) { return a = a * b; }
mi mypow(mi a, long long p) {
    assert(p >= 0);
    return p == 0 ? 1 : mypow(a * a, p / 2) * (p & 1 ? a : 1);
}
mi inv(mi a) {
    assert(a.v != 0);
    return mypow(a, MOD - 2);
}
mi operator/(mi a, mi b) { return a * inv(b); }

#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define get_bit(x,i) ((x)&(1ll<<(i)))
#define ft first
#define sd second
#define mt make_tuple
#define mp make_pair
#define eb emplace_back
#define pb push_back
#define dbg(x) cout << #x << " = " << x << '\n';
#define rep(i, begin, end) for (__typeof(begin) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))

// typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef pair<int, int> pii;
typedef pair<ld, ld> pdb;
typedef __int128_t lll;

template<typename T, typename T1>
ostream & operator<<(ostream &os, pair<T, T1> p){
    os << "(" << p.ft << "," << p.sd << ")";
    return os;
}

template<typename T, typename T1>
istream & operator>>(istream &is, pair<T, T1>& p){
    is >> p.ft >> p.sd;
    return is;
}


ll g(ll a, ll b){
    return a + b;
}

ll bit[N];

void update(ll x, ll v){
    while(x < N){
        bit[x] = g(bit[x], v);
        x += x&-x;
    }
}

ll query(ll x){
    ll v = 0;
    while(x){
        v = g(bit[x], v);
        x -= x&-x;
    }
    return v;
}


lll f(lll mid){
    // cout << mid << ' ' << mid* (m/(mid +1)) + m % (mid + 1) << ' ' << k/n << '\n';
    return  (lll)n * (mid * (lll)(m/(mid + 1)) + m % (mid + 1)) >= k;
}

ll bb(ll l, ll r ){
    ll ans = -1;
    while(l<=r){
        ll mid = (l+r);
        mid>>=1;
        if(f(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    return ans;
}


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#pragma endregion

const int MAXN = 5e4 * 52;

struct node{
    bool end;
    map<char,int> prox;
    node(){
        end = false;
    }
};

int idx = 1;

struct node nodes[MAXN];
char dp[int(1e6 + 10)];

void insert_trie(string &s)
{
    int curr = 0;
    for(char c: s)
    {
        if(nodes[curr].prox[c] == 0) nodes[curr].prox[c] = idx++;
        curr = nodes[curr].prox[c];
    }
    nodes[curr].end = true;
}

// void query(string &s, int i, vector<int> & g)
// {
//     int at = 0;
//     for(int j = i; j < s.size(); j++){
//         char c = s[j];
//         if(nodes[at].prox[c] == 0) return;
//         at = nodes[at].prox[c];
//         if(nodes[at].end) g.pb(j);
//     }
// }
char solve(int i){
    if(i == s.size()) return 1;
    char &ans = dp[i];
    if(ans == -1)
    {
        ans = 0;
        int at = 0;
        for(int j = i; j < s.size(); j++){
            char c = s[j];
            if(nodes[at].prox[c] == 0) break;
            at = nodes[at].prox[c];
            if(nodes[at].end) ans |= solve(j + 1);
        }
    }
    return ans;
}
 
map<string,string> mapa;
void walk(int i){
    if(i == s.size()) return ;
    vector<int> g;
    int gre = 0;
    int at = 0;
    for(int j = i; j < s.size(); j++){
        char c = s[j];
        if(nodes[at].prox.find(c) == nodes[at].prox.end()) break;
        at = nodes[at].prox[c];
        if(nodes[at].end && dp[j + 1]) gre = max(gre, j);
    }
    cout << mapa[s.substr(i, gre - i + 1)] << " ";
    walk(gre + 1);
}
 
void test(){
    /*
        Basicamente, o problema é dado uma string S = |10^6|. E N = |5*10^4| Strings menores
        ai = |50|. Eu quero saber se é possivel formar a string S usando as ais. Nesse problema tinha umas coisas a mais
        que é que as string tem um correspondente e tenho que formar a string com as maiores palavras possiveis no prefixo.
        mas o principal que quero salvar desse código é a Hash pra usar no futuro.
    */
    cin >> n;
 
    vector<string>v;
    string at;
    for(int i = 0; i < n; i++){
        cin >> at;
        v.push_back(at);
        cin.ignore();
        insert_trie(at);
        getline(cin, at);
        mapa[v[i]] = at;    
    }
    
    cin >> s;
    int p = s.size();
    dp[p] = 1;
    for(int i = p - 1; i >= 0; i--){
        int at = 0;
        for(int j = i; j < s.size(); j++){
            char c = s[j];
            if(nodes[at].prox.find(c) == nodes[at].prox.end()) break;
            at = nodes[at].prox[c];
            if(nodes[at].end) dp[i] |= dp[j + 1];
        }
    }
    walk(0);
    cout << '\n';
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int te = 1;
    // cin >> te;
    while(te--) test();
    return 0;
}
