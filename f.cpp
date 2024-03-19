#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll = long long;
using pr = pair<int, int>;
using mint = modint998244353;
ostream &operator<<(ostream &os, const mint &x)
{
    os << x.val();
    return os;
}
struct fast
{
    fast()
    {
        cin.tie(0);
        ios::sync_with_stdio(0);
    }
} fast;
template <class T>
inline bool chmin(T &a, T b)
{
    if (a > b)
    {
        a = b;
        return true;
    }
    return false;
}
template <class T>
inline bool chmax(T &a, T b)
{
    if (a < b)
    {
        a = b;
        return true;
    }
    return false;
}

struct mydsu
{
    mydsu() : _n(0) {}
    explicit mydsu(int n) : _n(n), parent_or_size(n, -1), d(n), r(n) {}

    int merge(int a, int b, int c)
    {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y)
        {
            if (depth(a) + c - depth(b))
                r[x] = 1;
            return x;
        }
        if (-parent_or_size[x] < -parent_or_size[y])
        {
            swap(x, y);
            swap(a, b);
            c = -c;
        }
        d[y] = depth(a) + c - depth(b);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        if (r[y])
            r[x] = 1;
        return x;
    }

    bool same(int a, int b)
    {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int leader(int a)
    {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0)
            return a;
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    int size(int a)
    {
        assert(0 <= a && a < _n);
        return -parent_or_size[leader(a)];
    }

    ll depth(int a)
    {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0)
            return 0;
        return depth(parent_or_size[a]) + d[a];
    }

    string gain(int a, int b)
    {
        if (!same(a, b))
            return "nan";
        if (r[leader(a)])
            return "inf";
        return to_string(depth(b) - depth(a));
    }

    std::vector<std::vector<int>> groups()
    {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++)
        {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++)
        {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++)
        {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            std::remove_if(result.begin(), result.end(),
                           [&](const std::vector<int> &v)
                           { return v.empty(); }),
            result.end());
        return result;
    }

    int _n;
    vector<int> parent_or_size;
    vector<ll> d;
    vector<bool> r;
};

int N, M, Q, A, B, C;

int main()
{
    ifstream ifs("input.txt");
    cin.rdbuf(ifs.rdbuf());
    cin >> N >> M >> Q;
    mydsu d(N);

    for (int i = 0; i < M; ++i)
    {
        cin >> A >> B >> C;
        --A, --B;
        d.merge(A, B, C);
    }
    for (int _ = 0; _ < Q; ++_)
    {
        cin >> A >> B;
        --A, --B;
        cout << d.gain(A, B) << '\n';
    }
}
