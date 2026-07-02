mt19937_64 gen((uint64_t) chrono::steady_clock::now().time_since_epoch().count()
             ^ (uint64_t) (uintptr_t) make_unique<char>().get());
uniform_int_distribution<long long> rnd(0,LLONG_MAX);
const long long mod = 998244353;
const int siz = 300005;
long long fact[siz], C[siz], inv[siz];
map<long long, long long> diff, freq;
long long po(long long x, long long y)
{
	long long ans = 1;
	x %= mod;
	while(y>0)
	{
		if(y&1)
		{
			ans = (ans*x) % mod;
		}
		y /= 2;
		x = (x * x)% mod; 
	}
	return ans;
}
long long nCrmo(long long n, long long r)
{
	if(n<0 || n<r)
	{
		return 0;	
	}
	long long ans = fact[n];
	ans *= inv[r]; ans%=mod;
	ans *= inv[n-r+1]; ans%=mod;
	return ans;	
}
long long precomp()
{
	fact[0] = 1;
	inv[0] = 1;
	for(int i=1; i<siz; i++)
	{	
		fact[i] = (fact[i-1]*i) % mod;
		inv[i] = po(fact[i],mod-2);
	}
	for(int i=0; i*2<siz; i++)
	{
		C[i*2] = nCrmo(2*i, i);
	}
	return 0;
}
int add_interval(long long l, long long r)
{
	long long Hash = rnd(gen);
	diff[l] ^= Hash; diff[r+1] ^= Hash;
	return 0;
}
int solve()
{
	diff.clear(); freq.clear();
	int n, k;
	cin>>n>>k;
	add_interval(1,n);
	for(int i=0; i<k; i++)
	{
		long long l, r;
		cin>>l>>r;
		add_interval(l, r);	
	}
	long long Hash = diff[1];
	for(map<long long, long long>::iterator member = next(diff.begin()); member!=diff.end(); member++)
	{
		freq[Hash] += member->first - prev(member)->first;
		Hash ^= member->second;	
	}
	long long ans = 1;
	for(const auto& it : freq)
	{
		ans*=C[it.second];
		ans%=mod;
	}
	cout<<ans<<endl;
	return 0;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin>>t;
	precomp();
	while(t--)
	{
		solve();
	}
	return 0;
}	
