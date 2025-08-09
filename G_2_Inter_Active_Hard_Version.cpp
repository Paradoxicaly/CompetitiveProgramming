#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(v) (v).begin(), (v).end()

int testcaseCount;

int request(const vector<int>& arr, int n) {
    cout << "?";
    for (int i = 1; i <= n; ++i) cout << ' ' << arr[i];
    cout << '\n' << flush;
    int x; cin >> x;
    return x;
}

int determine_bit_width(int x) {
    return 32 - __builtin_clz(x);
}

vector<int> encode(int n, int bitLength, vector<int>& permMap) {
    vector<int> code(n + 1), inv((1 << bitLength));
    int v = 0;
    for (int i = 1; i <= n; ++i) {
        code[i] = (i & 1) ? v++ : ((1 << bitLength) - 1 - v++);
        permMap[code[i]] = i;
    }
    return code;
}

void xor_deduction(int n, int bitLength, const vector<int>& code, vector<int>& xorMap,
                   vector<vector<int>>& fwdCheck, vector<vector<int>>& backCheck,
                   vector<int>& active, vector<int>& inactive, const vector<int>& permMap) {
    for (int b = 0; b < bitLength; ++b) {
        vector<int> groupA, groupB;
        for (int i = 1; i <= n; ++i) {
            if (code[i] & (1 << b)) groupB.push_back(i);
            else groupA.push_back(i);
        }

        int sa = groupA.size(), sb = groupB.size();
        for (int i = 0; i < sa; ++i) {
            vector<int> query(n + 1);
            for (int j = 0; j < sa; ++j) query[j + 1] = groupA[(j + i) % sa];
            for (int j = 0; j < sb; ++j) query[j + sa + 1] = groupB[j];
            int res = request(query, n);
            fwdCheck[b][query[1]] = res;
            backCheck[b][query[sa]] = res;
        }

        for (int i = 0; i < sb; ++i) {
            vector<int> query(n + 1);
            for (int j = 0; j < sb; ++j) query[j + 1] = groupB[(j + i) % sb];
            for (int j = 0; j < sa; ++j) query[j + sb + 1] = groupA[j];
            int res = request(query, n);
            fwdCheck[b][query[1]] = res;
            backCheck[b][query[sb]] = res;
        }

        for (int i = 1; i <= n; ++i)
            if (fwdCheck[b][i] != backCheck[b][i])
                xorMap[i] ^= (1 << b);
    }

    for (int i = 1; i <= n; ++i) {
        if (xorMap[i] == 0) inactive.push_back(i);
        else active.push_back(i);
    }
}

void pairwise_connect(int n, const vector<int>& xorMap, vector<int>& result, const vector<int>& code,
                      const vector<vector<int>>& fwd, const vector<vector<int>>& back, const vector<int>& permMap) {
    for (int pos : active) {
        if (result[pos]) continue;
        int val = xorMap[pos];
        int b = __builtin_ctz(val);

        vector<int> zero, one;
        for (int i = 1; i <= n; ++i) {
            if (code[i] & (1 << b)) one.push_back(i);
            else zero.push_back(i);
        }
        if (code[pos] & (1 << b)) swap(zero, one);

        int offset = 0, sizeZero = zero.size();
        for (int i = 0; i < sizeZero; ++i)
            if (zero[i] == pos) offset = i;

        vector<int> base(n + 1);
        for (int i = 0; i < sizeZero; ++i) base[i + 1] = zero[(i + offset) % sizeZero];
        for (int i = 0; i < one.size(); ++i) base[i + sizeZero + 1] = one[i];

        int L = 2, R = sizeZero;
        while (L < R) {
            int M = (L + R) >> 1;
            vector<int> q(n + 1);
            for (int i = 1; i < M; ++i) q[i] = base[i + 1];
            q[M] = base[1];
            for (int i = M + 1; i <= n; ++i) q[i] = base[i];
            int res = request(q, n);
            if (res != fwd[b][pos]) R = M;
            else L = M + 1;
        }

        int assigned = 0;
        if (back[b][pos] > fwd[b][pos]) result[base[L]] = pos, assigned = base[L];
        else result[pos] = base[L], assigned = pos;

        while (!result[result[assigned]]) {
            int tmp = xorMap[result[assigned]];
            result[result[assigned]] = permMap[tmp ^ code[assigned]];
            assigned = result[assigned];
        }
    }
}

void complete_pairing(int n, const vector<int>& xorMap, vector<int>& result, const vector<int>& permMap) {
    for (int node : inactive) {
        if (result[node]) continue;

        vector<int> candidates, paired;
        for (int i = 1; i <= n; ++i) {
            if (!result[i] && i != node) candidates.push_back(i);
            if (result[i]) paired.push_back(i);
        }

        auto eval = [&](const vector<int>& q) {
            vector<int> inv(n + 1);
            int score = count(all(result), 0) / 2;
            for (int i = 1; i <= n; ++i) inv[q[i]] = i;
            for (int i = 1; i <= n; ++i) if (result[i]) score += (inv[i] < inv[result[i]]);
            return score;
        };

        while (candidates.size() > 1) {
            vector<int> left, right;
            int half = (candidates.size() + 1) / 2;
            vector<int> q = {0};
            for (int i = 0; i < half; ++i) q.push_back(candidates[i]), left.push_back(candidates[i]);
            for (int i = half; i < permMap.size() && q.size() < n; ++i) q.push_back(paired[i - half]);
            q.push_back(node);
            for (int i = half; i < candidates.size(); ++i) q.push_back(candidates[i]), right.push_back(candidates[i]);
            for (int i = q.size(); i < n + 1; ++i) q.push_back(1);

            int r = request(q, n) - eval(q);
            if (r == 0) swap(left, right);
            candidates = left;
            paired.insert(paired.end(), all(right));
        }

        result[node] = candidates[0];
        result[candidates[0]] = node;
    }
}

void handle_test_case() {
    int n; cin >> n;

    int center = (n + 1) / 2;
    int bits = determine_bit_width(n - 1);
    cout << center + 1 << '\n' << flush;

    vector<int> assignment(n + 1), permMap(1 << bits);
    vector<int> code = encode(n, bits, permMap);

    vector<int> xorMap(n + 1);
    vector<vector<int>> fwd(bits, vector<int>(n + 1));
    vector<vector<int>> back(bits, vector<int>(n + 1));

    active.clear(), inactive.clear();
    xor_deduction(n, bits, code, xorMap, fwd, back, active, inactive, permMap);
    pairwise_connect(n, xorMap, assignment, code, fwd, back, permMap);
    complete_pairing(n, xorMap, assignment, permMap);

    cout << "! ";
    for (int i = 1; i <= n; ++i) cout << assignment[i] << " \n"[i == n];
    cout.flush();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> testcaseCount;
    while (testcaseCount--) handle_test_case();
    return 0;
}
