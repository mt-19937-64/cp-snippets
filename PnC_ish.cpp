template<int MOD>
struct Mint
{
        int v;
        Mint(long long x = 0)
        {
                v = int(x % MOD);
                if (v < 0) v += MOD;
        }

        Mint operator+(Mint o) const
        {
                int r = v + o.v;
                if (r >= MOD) r -= MOD;
                Mint m;
                m.v = r;
                return m;
        }
        Mint operator-(Mint o) const
        {
                int r = v - o.v;
                if (r < 0) r += MOD;
                Mint m;
                m.v = r;
                return m;
        }
        Mint operator*(Mint o) const
        {
                Mint m;
                m.v = int((long long)v * o.v % MOD);
                return m;
        }

        Mint& operator+=(Mint o) { return *this = *this + o; }
        Mint& operator-=(Mint o) { return *this = *this - o; }
        Mint& operator*=(Mint o) { return *this = *this * o; }

        Mint po(long long e) const
        {
                Mint r = 1, b = *this;
                while (e > 0)
                {
                        if (e & 1) r *= b;
                        b *= b;
                        e >>= 1;
                }
                return r;
        }
        Mint inv() const { return po(MOD - 2); } 
        Mint operator/(Mint o) const { return *this * o.inv(); }
        Mint& operator/=(Mint o) { return *this = *this / o; }

        bool operator==(Mint o) const { return v == o.v; }
        bool operator!=(Mint o) const { return v != o.v; }

        friend ostream& operator<<(ostream& os, Mint m) { return os << m.v; }
        friend istream& operator>>(istream& is, Mint& m)
        {
                long long x;
                is >> x;
                m = Mint(x);
                return is;
        }
};

const int MOD = 1000000007;
using mint = Mint<MOD>;
const int siz = 200005;
mint fact[siz], inv_fact[siz];

void precomp()
{
        fact[0] = 1;
        for (int i = 1; i < siz; i++)
        {
                fact[i] = fact[i-1] * i;
        }
        inv_fact[siz-1] = fact[siz-1].po(MOD - 2);  // needs prime MOD
        for (int i = siz - 2; i >= 0; i--)
        {
                inv_fact[i] = inv_fact[i+1] * (i + 1);
        }
}

mint nCr(long long n, long long r)
{
        if (n < 0 || r < 0 || r > n) return 0;
        return fact[n] * inv_fact[r] * inv_fact[n-r];
}
