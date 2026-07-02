mt19937_64 gen((uint64_t) chrono::steady_clock::now().time_since_epoch().count()
             ^ (uint64_t) (uintptr_t) make_unique<char>().get());
