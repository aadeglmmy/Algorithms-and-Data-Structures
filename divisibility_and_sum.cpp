#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <array>
#include <cstdio>
#include <ios>
#include <iostream>
#include <vector>

std::array<std::array<std::array<std::array<long long, 2>, 316227>, 100>, 13> adp;
std::array<std::array<std::array<std::array<long long, 2>, 316227>, 100>, 13> bdp;

int getDigitSum(long long num) {
    int sum = 0;
    while (num != 0) {
        sum += num % 10;
        num /= 10;
    }

    return sum;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::freopen("lucky.in", "r", stdin);
    std::freopen("lucky.out", "w", stdout);

    long long k;
    int p, q;
    long long a, b;
    std::cin >> k >> p >> q >> a >> b;

    if (k > 316227) {
        long long tmp = k;

        while (tmp < a) {
            tmp += k;
        }

        long long counter = 0;

        while (tmp <= b) {
            int digitSum = getDigitSum(tmp);
            if (digitSum >= p && digitSum <= q) {
                ++counter;
            }

            tmp += k;
        }

        std::cout << counter << '\n';

        return 0;
    }

    adp[0][0][0][1] = 1;
    bdp[0][0][0][1] = 1;

    std::vector<int> aDigits;
    std::vector<int> bDigits;

    --a;

    while (a != 0) {
        aDigits.push_back(a % 10);
        a /= 10;
    }

    std::reverse(aDigits.begin(), aDigits.end());

    while (b != 0) {
        bDigits.push_back(b % 10);
        b /= 10;
    }

    std::reverse(bDigits.begin(), bDigits.end());

    std::size_t bSize = bDigits.size();

    int tmpS = 0;
    long long tmpR = 1;
    int sd;

    for (std::size_t i = 1; i <= bSize; ++i) {
        tmpS += 9;
        for (int s = 0; s <= tmpS && s <= q; ++s) {
            for (int r = 0; r < tmpR && r < k; ++r) {
                for (int d = 0; d < 10; ++d) {
                    sd = s + d;
                    if (sd <= q && sd <= tmpS) {
                        bdp[i][sd][(10 * r + d) % k][0] += bdp[i - 1][s][r][0];
                        if (d <= bDigits[i - 1]) {
                            bdp[i][sd][(10 * r + d) % k][d == bDigits[i - 1]] += bdp[i - 1][s][r][1];
                        }
                    }
                }
            }
        }

        tmpR *= 10;
    }

    long long fb = 0;
    for (int s = p; s <= q; ++s) {
        fb += bdp[bSize][s][0][0] + bdp[bSize][s][0][1];
    }

    std::size_t aSize = aDigits.size();

    tmpS = 0;
    tmpR = 1;

    for (std::size_t i = 1; i <= aSize; ++i) {
        tmpS += 9;
        for (int s = 0; s <= tmpS && s <= q; ++s) {
            for (int r = 0; r < tmpR && r < k; ++r) {
                for (int d = 0; d < 10; ++d) {
                    sd = s + d;
                    if (sd <= tmpS && sd <= q) {
                        adp[i][sd][(10 * r + d) % k][0] += adp[i - 1][s][r][0];
                        if (d <= aDigits[i - 1]) {
                            adp[i][sd][(10 * r + d) % k][d == aDigits[i - 1]] += adp[i - 1][s][r][1];
                        }
                    }
                }
            }
        }

        tmpR *= 10;
    }

    long long fa = 0;
    for (int s = p; s <= q; ++s) {
        fa += adp[aSize][s][0][0] + adp[aSize][s][0][1];
    }

    std::cout << fb - fa;

    return 0;
}
