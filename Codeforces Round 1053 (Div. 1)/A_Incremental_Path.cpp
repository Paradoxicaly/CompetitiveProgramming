/*
Tomato_Cultivator 
*/
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using vi  = vector<int>;

#define pb push_back
#define fi first
#define se second
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0;i<(n);++i)
#define rng(i,a,b) for(int i=(a);i<(b);++i)

const int MOD = 1e9+7;

#ifdef Tomato
template<class T>
ostream& operator<<(ostream &o, const vector<T> &v){
	o<<"{"; for(int i=0;i<sz(v);i++) o<<(i?" ":"")<<v[i]; return o<<"}";
}
template<class A,class B>
ostream& operator<<(ostream &o,const pair<A,B>&p){ return o<<"("<<p.fi<<","<<p.se<<")"; }
template<class... A>
void bug__(int c,A... a){
	cerr<<"\e[1;"<<c<<"m"; ((cerr<<a<<' '),...); cerr<<"\e[0m\n";
}
#define bug_(c,x...) bug__(c,__LINE__,"[" + string(#x) + "]",x)
#define bug(x...) bug_(32,x)
#else
#define bug(x...) ((void)0)
#endif

template<class... T>
constexpr auto min(T... a){ return std::min({a...}); }
template<class... T>
constexpr auto max(T... a){ return std::max({a...}); }

template<class... T> void input(T&... a){ (cin>>...>>a); }

template<class T,class... Ts>
void print(const T& a,const Ts&... b){
	cout<<a; (cout<<...<<(cout<<' ',b)); cout<<'\n';
}
void print(){ cout<<'\n'; }

template<class T> bool chmin(T& a,const T& b){ if(b<a){a=b; return true;} return false; }
template<class T> bool chmax(T& a,const T& b){ if(a<b){a=b; return true;} return false; }

ll gcdll(ll a,ll b){ return b?gcdll(b,a%b):a; }

ll power(ll a, ll b, ll m = MOD){
	ll res = 1 % m;
	a %= m;
	while(b > 0){
		if(b & 1) res = (res * a) % m;
		a = (a * a) % m;
		b >>= 1;
	}
	return res;
}

ll nxt(map<ll,ll> &mp,ll x){
	ll y = x + 1;
	while(true){
		auto it = mp.upper_bound(y);
		if(it != mp.begin()){
			auto jt = prev(it);
			if(jt->fi <= y && y <= jt->se){
				y = jt->se + 1;
				continue;
			}
		}
		break;
	}
	return y;
}

void add(map<ll,ll> &mp,ll x){
	ll L = x, R = x;
	auto it = mp.upper_bound(x);
	if(it != mp.begin()){
		auto jt = prev(it);
		if(jt->se >= x){
			return;
		}
		if(jt->se + 1 == x){
			L = jt->fi;
			mp.erase(jt);
		}
	}
	it = mp.lower_bound(x);
	if(it != mp.end() && it->fi == x){
		return;
	}
	if(it != mp.end() && it->fi == x + 1){
		R = it->se;
		mp.erase(it);
	}
	mp[L] = R;
}

void solve(){
	int n,m;
	input(n,m);
	string s;
	cin>>s;
	vector<ll> a(m);
	rep(i,m) cin>>a[i];
	map<ll,ll> mp;
	if(m){
		ll l = a[0], r = a[0];
		rng(i,1,m){
			if(a[i] == r + 1) r = a[i];
			else{
				mp[l] = r;
				l = a[i];
				r = a[i];
			}
		}
		mp[l] = r;
	}
	vector<ll> pos(n+1);
	pos[0] = 1;
	rep(i,n){
		ll cur = pos[i];
		if(s[i] == 'A'){
			ll nxtpos = cur + 1;
			add(mp,nxtpos);
			pos[i+1] = cur + 1;
		}else{
			ll target = nxt(mp,cur);
			add(mp,target);
			pos[i+1] = nxt(mp,cur);
		}
	}
	vector<ll> res;
	for(auto &p: mp){
		ll l = p.fi, r = p.se;
		for(ll x = l; x <= r; ++x) res.pb(x);
	}
	print(sz(res));
	rep(i,sz(res)) cout<<res[i]<<" \n"[i+1==sz(res)];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T=1;
	if(cin>>T){
		while(T--) solve();
	}
	return 0;
}
