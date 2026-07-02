const int sz = 131072*2;
long long tree[2*sz], lazy[2*sz];
int n, q;
//vector<int> queries, ans;
string s;
int infi = 1e9 + 5;
long long combine(long long A, long long B)
{
	return min(A,B);
}               
long long combineupd(long long A, long long B)
{
	return A+B;
}
long long pull(int index)
{	
	tree[index] = combine(tree[2*index], tree[2*index+1]);
	return 0;
}
int push(int index, long long node_lo, long long node_hi)
{
	tree[index] = combineupd(tree[index], lazy[index]);
    	if(node_lo != node_hi)
    	{
		lazy[2*index] = combineupd(lazy[2*index], lazy[index]);
		lazy[2*index+1] = combineupd(lazy[2*index+1], lazy[index]);
	}
    	lazy[index] = 0;
	return 0;
}
long long query(int node, int node_lo, int node_hi, int quer_lo, int quer_hi)
{
	push(node, node_lo, node_hi);
	if(node_lo>quer_hi || node_hi<quer_lo)
	{
		return infi;
	}
	if(quer_hi>=node_hi && quer_lo<=node_lo)
	{
		return tree[node];
	}
	int sep = (node_hi + node_lo)/2;
	return combine(query(2*node, node_lo, sep, quer_lo, quer_hi), query(2*node+1, sep+1, node_hi, quer_lo, quer_hi));
}
long long upd(int node, int node_lo, int node_hi, int quer_lo, int quer_hi, int inc)
{                              
	//cout<<"hola "<<node_lo<<" "<<node_hi<<" "<<i<<endl;
	push(node, node_lo, node_hi);
	if(node_lo>quer_hi || node_hi<quer_lo)
	{
		return 0;
	}
	if(quer_hi>=node_hi && quer_lo<=node_lo)
	{
		//cout<<"Stalin! "<<node<<endl;
		lazy[node] = inc;
		push(node, node_lo, node_hi);
		return 0;
	}
	int sep = (node_hi + node_lo)/2;
	upd(2*node, node_lo, sep, quer_lo, quer_hi, inc);
	upd(2*node+1, sep+1, node_hi, quer_lo, quer_hi, inc);
	pull(node);
	return 0;	
}
/*int apply()
{                
	for(int i=0; i<2*sz; i++)
	{
		tree[i] = 0; lazy[i] = 0;
	}
	for(int i=0; i<n; i++)
	{
		upd(1, 0, sz-1, i, n-1, (s[i]=='('?1:-1));	
	}
	set<int> reps;
	reps.insert(n-1);
	for(int i=0; i<n-1; i++)
	{
		if(s[i]=='(' && s[i+1] == '(')
		{
			reps.insert(i);
		}
	}
	string p = s;
	for(int i=0; i<q; i++)
	{
		int a = queries[i];
		if(p[a] == '(')
		{
			p[a] = ')';
			if(a<n-1 && p[a+1]=='(')
			{
				reps.erase(a);
			}
			if(a>0 && p[a-1]=='(')
			{
				reps.erase(a-1);
			}
			upd(1, 0, sz-1, a, n-1, -2);
		}
		else
		{
			p[a] = '(';
			if(a<n-1 && p[a+1]=='(')
			{
				reps.insert(a);
			}
			if(a>0 && p[a-1]=='(')
			{
				reps.insert(a-1);
			}
			upd(1, 0, sz-1, a, n-1, 2);
		}
		ans.push_back(query(1, 0, sz-1, 0, *reps.begin()) >= 0);	
	}
	return 0;
}
int solve()
{
	cin>>n>>q;
	cin>>s;
	if(n%2)
	{
		while(q--)
		{
			int bozo;	
			cin>>bozo;
			cout<<"NO"<<endl;
		}
		return 0;
	}
	for(int i=0; i<q; i++)
	{
		int que;
		cin>>que;
		queries.push_back(que-1); 
	}
	apply();
	vector<int> ans1 = ans;
	ans.clear();
	reverse(s.begin(), s.end());
	for(auto& a : s)
	{
		a = '(' + ')' - a;
	}
	for(auto& qu : queries)
	{
		qu = n-1-qu;
	}
	apply();
	for(int i=0; i<q; i++)
	{
		cout<<(ans1[i] && ans[i] ? "YES" : "NO") << endl;
	}
	return 0;		
}*/
