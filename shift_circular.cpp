#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
#ifdef  ONLINE_JUDGE
	#define eprintf(...) 42
#else
        #define eprintf(...) {fprintf(stderr, __VA_ARGS__);fflush(stderr);}
#endif
clock_t startTime;
double getCurrentTime() 
{
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}
vector<long long> pref;
//The following is not AI, I have made this template because I get dizzy when I have to shift arrays/circles etc (this is for circles).
//If I ever use it in future don't call it AI (also it is very filthy, why would you think so, but if you do, you can see it in one of my (practice) submissions to https://codeforces.com/problemset/problem/2234/F).
class circular_fracking
{
	public:
	set<pair<int, int>> intervals;
	vector<long long> h;
	int shift = -1;
	circular_fracking(int size = 0)
	{
		h.resize(size); intervals.insert({0, size-1});
	};
	int set_h(vector<long long> setter)
	{
		h = setter;
		return 0;
	}
	int refresh_intervals()
	{
		intervals.insert({0, (int)h.size()-1});
		return 0;
	}
	int frack(int edge)
	{
		int n = h.size();
		if(shift == -1)
		{
			//make sure the edge we frack is the one from n-1 to 0, assuming edge i is the outgoing edge from node i;
			shift = (n-edge-1);
			return 0;	
			//Now we have reduced it to an array.	
		}
		//There is guaranteed to be an {l, r} which has the "edge", make sure, also the interval size should be >=2.	
		auto itr = *prev(intervals.upper_bound({(edge + shift)%n, 1e18}));
		intervals.erase(itr);
		intervals.insert({itr.first, (edge + shift)%n}); intervals.insert({(edge + shift)%n + 1, itr.second});
		//cerr<<"We are busy fracking: "<<itr.first<<" "<<itr.second<<" -->"<<(edge + shift)%n<<" "<<shift<<endl;
		//make update here
		pref[itr.first] += (itr.second - ((edge+shift)%n + 1) + 1)*h[edge]; pref[(edge + shift)%n + 1] -= (itr.second - ((edge+shift)%n + 1) + 1)*h[edge];
		//cerr<<(itr.second - ((edge+shift)%n + 1) + 1)*h[edge]<<endl;
		pref[(edge+shift)%n + 1] += ((edge+shift)%n - itr.first + 1)*h[edge]; pref[itr.second + 1] -= ((edge+shift)%n - itr.first + 1)*h[edge];
                //cerr<<((edge+shift)%n - itr.first + 1)*h[edge]<<endl;
		//cerr<<"Fracked into ("<<itr.first<<", "<<((edge + shift)%n)<<") and "<<" ("<<((edge + shift)%n + 1)<<", "<<itr.second<<")"<<endl;
		return 0;
	}
};
int solve()
{
 	int n;
	cin>>n;
	pref.assign(n + 1, 0);
	vector<long long> h(n);
	vector<pair<int, int>> sorted_h;
	circular_fracking circle(n);
	for(int i=0; i<n; i++)
	{
		cin>>h[i];
		sorted_h.push_back({h[i], i});		
	}
	circle.set_h(h);
	sort(sorted_h.begin(), sorted_h.end());
	reverse(sorted_h.begin(), sorted_h.end());
	for(int i=0; i<n; i++)
	{
		//cerr<<"Here we go: "<<sorted_h[i].second<<endl;
		circle.frack(sorted_h[i].second);
	}
	for(int i=1; i<=n; i++)
	{
		pref[i]	+= pref[i-1];
	}
	vector<long long> ans(n);
	for(int i=0; i<n; i++)
	{
		//cerr<<circle.shift<<" Here pref["<<i<<"] has the result to node "<<(n+i-circle.shift)%n<<endl;
		ans[(n+i-circle.shift)%n] = pref[i];
	}
	for(int i=0; i<n; i++)
	{
		cout<<ans[i]<<" ";
	}
	cout<<endl;
	return 0;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin>>t;
	startTime = clock();
	while(t--)
	{
		solve();
	}
	eprintf("time = %.5lf\n", getCurrentTime());
	return 0;
}
