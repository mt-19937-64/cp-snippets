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
        Mint inv() const { return po(MOD - 2); }  // only valid when MOD is prime
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
