mt19937_64 gen((uint64_t) chrono::steady_clock::now().time_since_epoch().count()
             ^ (uint64_t) (uintptr_t) make_unique<char>().get());
struct ordered_hash
{
        static const long long MOD0 = 1000000007LL;
        static const long long MOD1 = 1000000123LL;
        static const int MIN_BASE = 100213;

        static inline array<long long, 2> base = {0, 0};
        static inline array<vector<long long>, 2> p_pow;

        static void init_bases()
        {
                if (base[0]) return;
                uniform_int_distribution<int> rnd(MIN_BASE, 2 * MIN_BASE);
                base[0] = rnd(gen);
                do
                {
                        base[1] = rnd(gen);
                }
                while (base[1] == base[0]);
        }

        static void ensure_pow(int len)
        {
                init_bases();
                for (int k = 0; k < 2; k++)
                {
                        long long mod = (k == 0 ? MOD0 : MOD1);
                        if (p_pow[k].empty()) p_pow[k].push_back(1);
                        while ((int)p_pow[k].size() <= len)
                        {
                                p_pow[k].push_back(p_pow[k].back() * base[k] % mod);
                        }
                }
        }

        array<vector<long long>, 2> h;
        int n = 0;

        ordered_hash() = default;

        template<class T>
        ordered_hash(const T& s)
        {
                build(s);
        }

        template<class T>
        void build(const T& s)
        {
                init_bases();
                n = (int)s.size();
                ensure_pow(n);
                for (int k = 0; k < 2; k++)
                {
                        long long mod = (k == 0 ? MOD0 : MOD1);
                        h[k].assign(n + 1, 0);
                        for (int i = 0; i < n; i++)
                        {
                                h[k][i + 1] = (h[k][i] * base[k] + (long long)s[i]) % mod;
                        }
                }
        }

        pair<long long, long long> get(int l, int r) const
        {
                int len = r - l + 1;
                long long a = (h[0][r + 1] - h[0][l] * p_pow[0][len]) % MOD0;
                if (a < 0) a += MOD0;
                long long b = (h[1][r + 1] - h[1][l] * p_pow[1][len]) % MOD1;
                if (b < 0) b += MOD1;
                return {a, b};
        }
};
