#include <algorithm>
#include <iostream>
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5 + 1;
const int MOD = 1e9 + 7;

ll fac[MAXN + 1];
ll inv[MAXN + 1];

ll exp(ll x, ll y, ll p) {
	ll res = 1; x %= p;
	while (y) {
		if (y & 1) {
			res *= x; res %= p; 
		}
		x *= x;
		x %= p;
		y >>= 1;
	}
	return res;
}

void factorial() {
	fac[0] = 1;
	for (int i = 1; i <= MAXN; i++) {
		fac[i] = fac[i - 1] * i % MOD;
	}
}

void inverses() {
	inv[0] = 1;
	for (int i = 1; i <= MAXN; i++) {
		inv[i] = exp(fac[i], MOD - 2, MOD);
	}
}

ll choose(int n, int r) {
	if(n < r) return 0;
	return fac[n] * inv[r] % MOD * inv[n - r] % MOD;
}

void solve(){
	int ans = 0;
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> nums(n);
	vector<int> freq(n+1, 0);
	for(int i = 0; i < n; i++) {
		cin >> nums[i];
		freq[nums[i]]++;
	}
	vector<int> preFreq(n+1, 0); // prefix-array for freq vector;
	for(int i = 1; i <= n; i++){
		preFreq[i] = freq[i] + preFreq[i-1];
	}
	for(int i = 1; i <= n; i++){
		int max_index = min(n, i + k);
		int num_total_elems = freq[max_index] - freq[i-1];
		int num_larger_elems = freq[max_index] - freq[i];
		int curr_ans = (choose(num_total_elems, m) - choose(num_larger_elems, m) + MOD) % MOD;
		ans += curr_ans;
	}
	cout << ans << "\n";
}

int main() {
	factorial();
	inverses();
	int t;
	cin >> t;
	while(t--){
		solve();
	}
}
