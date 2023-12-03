#include "../header.h"


class Solution {
public:
    int countPrimes(int n) {
        // 错误写法
        if (n <= 2) return 0;

        vector<bool> prime(n, true);
        int cnt = n - 2;
        for (int i = 2; i <= n; ++i) {
            if (prime[i]) {
                // target the multiples of i
                for (int j = 2 * i; j < n; j += i) {
                    if (prime[j]) {
                        prime[j] = false;
                        --cnt;
                    }
                }
            }
        }    

        return cnt;
    }

    int countPrime2(int n) {
        vector<int> primes;
        vector<bool> isPrime(n, true);

        for (int i = 2; i < n; ++i) {
            if (isPrime[i]) {
                primes.push_back(i);
            }
            for (int j = 0; j < primes.size() && i * primes[j] < n; ++j) {
                isPrime[i * primes[j]] = false;
                // 如果成立，那么就一定会在后面出现 x/primes[j] (小于 i) 被 prime[y] 标记
                // 只会被最小因子标记一次，不会重复标记
                if (i % primes[j] == 0) {
                    break;
                }
            }
        }

        return primes.size();
    }
};