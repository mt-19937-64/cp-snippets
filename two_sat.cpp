class scc_graph
{
	public:
		int n = 1, m=0, timer = 0;
		vector<vector<int>> fwd, bwd;
		vector<int> tout, compo;	
		vector<bool> vis1;
		scc_graph(int assi = 1)
		{
			n = assi;
			fwd.resize(n); bwd.resize(n); tout.resize(n); vis1.resize(n); compo.resize(n, -1);	
		};
		int add_edge(int u, int v)
		{
			fwd[u].push_back(v);
			bwd[v].push_back(u);
			m++;	
			return 0;
		}
		int dfs_time(int node)
		{
			vis1[node] = 1;
			timer++;
			for(auto stuff : fwd[node])
			{	
				if(!vis1[stuff])
				{
					dfs_time(stuff);	
				}	
			}       	
			timer++;
			tout[node] = timer; timer++;
			return 0;
		}			
		int dfs_assn(int node, int assn)
		{
			vis1[node] = 1;
			compo[node] = assn;
			for(auto stuff : bwd[node])
			{
				if(!vis1[stuff])
				{
					dfs_assn(stuff, assn);	
				}
			}
			return 0;
		}
		int scc()
		{       
			for(int i=0; i<n; i++)
			{
				if(!vis1[i])
				{
					dfs_time(i);	
				}		
			}
			pair<int, int> ord[n];
			for(int i=0; i<n; i++)
			{
				ord[i] = {tout[i], i};
			}
			sort(ord, ord+n); reverse(ord, ord+n);
			for(int i=0; i<n; i++)
			{
				vis1[i] = 0;
			}
			for(int i=0; i<n; i++)
			{
				if(!vis1[ord[i].second])
				{
					dfs_assn(ord[i].second, i);
				}
			}		
			return 0;
		}
		vector<vector<int>> scc_DAG()
		{
			vector<vector<int>> g(n);
			for(int i=0; i<n; i++)
			{
				for(auto nexti : fwd[i])
				{
					if(compo[i]!=compo[nexti])
					{
						g[compo[i]].push_back(compo[nexti]);
					}
				}
			}
			return g;
		}
};
class two_sat
{
	public:
		int n = 1;
		scc_graph sccish;
		vector<bool> ans;
		two_sat(int assi = 1)
		{
			n = assi;
			sccish = scc_graph(2*n); ans.resize(n); 	
		};	
		int add_clause(int m_1, bool status_1, int m_2, bool status_2)
		{
			sccish.add_edge(2*m_1 + (status_1^1), 2*m_2 + status_2);
			sccish.add_edge(2*m_2 + (status_2^1), 2*m_1 + status_1);
			return 0;
		}
		bool satisfiable()
		{
			sccish.scc();
			for(int i=0; i<n; i++)
			{
				if(sccish.compo[2*i]==sccish.compo[2*i+1])
				{
					return false;
				}
				ans[i] = sccish.compo[2*i] < sccish.compo[2*i+1];
			}
			return true;
		}
};
