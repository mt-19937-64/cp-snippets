vector<vector<int>> manacher(vector<int> a)
{
	int n = a.size();
	vector<vector<int>> d(2, vector<int>(n, 0));
	int oldest = 0;
	for(int i=0; i<n; i++)
	{
		if(2*oldest-i < 0 || a[i]!=a[2*oldest-i])
		{
			d[1][oldest] = i-oldest;
			int dead = oldest;
			oldest++;
			while(oldest<i && (d[1][2*dead-oldest]<i-oldest || a[i] != a[2*oldest-i]))
			{
				d[1][oldest] = min(d[1][2*dead - oldest], i-oldest);
				oldest++;
			}
		}
	}
	d[1][oldest] = n-oldest;
	int over = oldest;
	oldest++;
	while(oldest<n)
	{
		d[1][oldest] = min(d[1][2*over-oldest], n-oldest);
		oldest++;
	}
	oldest = 1;
	for(int i=1; i<n; i++)
	{
		if(2*oldest-i-1 < 0 || a[i]!=a[2*oldest-i-1])
		{
			d[0][oldest] = i-oldest;
			int dead = oldest;
			oldest++;
			while(oldest<i && (d[0][2*dead-oldest]<i-oldest || a[i] != a[2*oldest-i-1]))
			{
				d[0][oldest] = min(d[0][2*dead - oldest], i-oldest);
				oldest++;
			}
			oldest += (oldest == i && a[oldest]!=a[oldest-1]);
		}
	}
	if(oldest<n)
	{
		d[0][oldest] = n-oldest;
		over = oldest;
		oldest++;
		while(oldest<n)
		{
			d[0][oldest] = min(d[0][2*over-oldest], n-oldest);
			oldest++;
		}
	}
	return d;
}
