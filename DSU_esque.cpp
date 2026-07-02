const int SZ = 26; 
int parent[SZ], siz[SZ];          
long long leader(int a)
{
	if(parent[a]==a)
	{
		return a;
	}
	return parent[a] = leader(parent[a]);
}
int unite(long long a, long long b)
{
	a = leader(a);
	b = leader(b);
	if(siz[a]>siz[b])
	{
		swap(a, b); 
	}
	parent[a] = b;
	siz[b] += siz[a];
	return 0;	
}
