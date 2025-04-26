#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cstdio>
#include <ios>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

const int MOD = 1000000007;

struct DSU {
    std::vector<int> parent, rank, parity;
    int components;

    DSU(int n) : parent(n), rank(n, 0), parity(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            components = n;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            int px = find(parent[x]);
            parity[x] ^= parity[parent[x]];
            parent[x] = px;
        }
        return parent[x];
    }

    bool unionSets(int x, int y, int r) {
        int px = find(x);
        int py = find(y);
        if (px == py) {
            return (parity[x] ^ parity[y]) == r;
        }
        if (rank[px] > rank[py]) {
            std::swap(px, py);
            std::swap(x, y);
        }
        parent[px] = py;
        parity[px] = parity[x] ^ parity[y] ^ r;
        --components;
        if (rank[px] == rank[py]) {
            ++rank[py];
        }
        return true;
    }

    int getComponents() const {
        return components;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::freopen("labels.in", "r", stdin);
    std::freopen("labels.out", "w", stdout);

    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> edges(n - 1);
    for (auto& edge : edges) {
        std::cin >> edge.first >> edge.second;
        --edge.first;
        --edge.second;
    }

    int k;
    std::cin >> k;
    std::vector<std::tuple<int, int, int>> queries(k);
    for (auto& query : queries) {
        int u, v, r;
        std::cin >> u >> v >> r;
        queries.push_back({ u - 1, v - 1, r });
    }

    DSU dsu(n);

    for (const auto& [u, v, r] : queries) {
        if (!dsu.unionSets(u, v, r)) {
            std::cout << 0 << '\n';
            return 0;
        }
    }

    long long result = 1;
    for (int i = 0; i < dsu.getComponents() - 1; ++i) {
        result = (result * 2) % MOD;
    }

    std::cout << result << '\n';
    return 0;
}
