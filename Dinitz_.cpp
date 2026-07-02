const long long infi = 1e18;
class dinitz
{
	public:

		struct edge
		{
			int to, rev;
			long long cap, ocap;
			long long flow()
			{
				return max(ocap-cap, 0ll);
			}
		};
		vector<vector<edge>> edg;
		vector<int> level, q, ptr;
		dinitz(int n) 
		{
			level = q = ptr = vector<int>(n); edg = vector<vector<edge>>(n);
		}
		void add_edge(int a, int b, long long c, long long r_cap = 0)
		{
			edg[a].push_back({b, (int)edg[b].size(), c, c});
			edg[b].push_back({a, (int)edg[a].size()-1, r_cap, r_cap});		
		}
		long long dfs(int v, int t, long long f)
		{
			if(v==t || !f)
			{
				return f;
			}
			for(int& i=ptr[v]; i<(int)edg[v].size(); i++)
			{
				edge& e = edg[v][i];
				if(level[e.to]==level[v]+1)
				{
					if(long long p = dfs(e.to, t, min(f, e.cap)))
					{
						e.cap -= p; edg[e.to][e.rev].cap += p;
						return p;
					}		
				}
			}	
			return 0;
		}
		long long calci(int s, int t)
		{
			long long flow = 0;
			q[0] = s;
			for(int i=0; i<31; i++)
			{
				do
				{
					level = ptr = vector<int>(q.size());
					int qi = 0, qe = level[s] = 1;
					while(qi<qe && !level[t])
					{
						int v = q[qi++];
						for(edge e : edg[v])	
						{
							if(!level[e.to] && e.cap>>(30-i))
							{
								q[qe++] = e.to; level[e.to] = level[v] + 1;
							}
						}	
					}
					while(long long p = dfs(s, t, infi))
					{
						flow += p;
					}
				}
				while(level[t]);
			}
			return flow;
		}			
};
