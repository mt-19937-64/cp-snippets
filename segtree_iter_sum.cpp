const int SZ = 131072;
long long seg[2*SZ];
long long combine(long long a, long long b)
{
	return a + b;
}
int update(int p, long long value)
{
	p += SZ;
	seg[p] = value;
	for (; p > 1; p >>= 1)
	{
        	seg[p>>1] = combine(seg[(p|1)^1], seg[p|1]);
	}
	return 0;
}
long long query(int l, int r)
{
    long long resL = 0, resR = 0; r++;
    for (l += SZ, r += SZ; l < r; l >>= 1, r >>= 1) {
        if (l&1) resL = combine(resL, seg[l++]);
        if (r&1) resR = combine(seg[--r], resR);
    }
    return combine(resL, resR);
}
