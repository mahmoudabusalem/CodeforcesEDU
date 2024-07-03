#include <bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC target("avx,avx2,fma")

#define input_txt                     \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);

#define fast                 \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);

#define dpp(arr, val) memset(arr, val, sizeof(arr))
#define ll long long
#define ull unsigned long long
#define dd double
#define ld long double
#define PQ priority_queue
#define pii pair<int, int>
#define pll pair<ll, ll>
#define S second
#define F first
#define MP make_pair
#define endl "\n"
#define PI 3.14159265
#define mod 1000000007
#define tests   \
    ll t;       \
    cin >> t;   \
    ll i_t = 0; \
    while (i_t++ < t)

#define loop(n) for (ll i = 0; i < (n); i++)
#define SetPre(n, x) cout << fixed << setprecision(n) << x
#define forn(i, n) for (int i = 0; i < (int)n; ++i)
#define forp(i, a, b) for (ll i = a; i < b; i++)
#define forn(i, a, b) for (ll i = a; i > b; i--)
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define spc << " "
#define sp << " " <<
#define trav(i, a) for (auto &i : a)
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define si(a) ((int)(a).size())
#define ins insert
#define pb push_back
#define mp make_pair
#define si(a) ((int)(a).size())
#define gcd(a, b) __gcd(a, b)
#define mem(b, z) memset(b, z, sizeof(b))
#define rn return

using namespace std;
#define int long long

struct Node
{
    int mx;

    Node() : mx(0) {}
    Node(int x) : mx(x) {}
};

struct SegTree
{
    int tree_size;
    vector<Node> seg_data;

    SegTree(int n)
    {
        tree_size = 1;
        while (tree_size < n)
            tree_size *= 2;
        seg_data.resize(2 * tree_size, Node());
    }

    Node merge(const Node &lf, const Node &ri)
    {
        Node res;
        res.mx = max(lf.mx, ri.mx);
        return res;
    }

    void init(const vector<int> &nums, int ni, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (lx < (int)nums.size())
            {
                seg_data[ni] = Node(nums[lx]);
            }
            return;
        }
        int mid = (lx + rx) / 2;
        init(nums, 2 * ni + 1, lx, mid);
        init(nums, 2 * ni + 2, mid, rx);
        seg_data[ni] = merge(seg_data[2 * ni + 1], seg_data[2 * ni + 2]);
    }

    void init(const vector<int> &nums)
    {
        init(nums, 0, 0, tree_size);
    }

    void set(int idx, int value, int node, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            seg_data[node] = Node(value);
            return;
        }
        int mid = (lx + rx) / 2;
        if (idx < mid)
            set(idx, value, 2 * node + 1, lx, mid);
        else
            set(idx, value, 2 * node + 2, mid, rx);
        seg_data[node] = merge(seg_data[2 * node + 1], seg_data[2 * node + 2]);
    }

    void set(int idx, int value)
    {
        set(idx, value, 0, 0, tree_size);
    }

    int find(int k, int node, int lx, int rx)
    {
        if (seg_data[node].mx < k)
            return -1; // No element >= k in this segment

        if (rx - lx == 1)
        {
            return lx; // Found the minimum index satisfying the condition
        }

        int mid = (lx + rx) / 2;
        if (seg_data[2 * node + 1].mx >= k)
            return find(k, 2 * node + 1, lx, mid);
        else
            return find(k, 2 * node + 2, mid, rx);
    }

    int find(int k)
    {
        return find(k, 0, 0, tree_size);
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    SegTree tree(n);
    tree.init(a);

    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int idx, val;
            cin >> idx >> val;
            tree.set(idx, val);
        }
        else if (type == 2)
        {
            int x;
            cin >> x;
            cout << tree.find(x) << endl;
        }
    }
}

signed main()
{
    fast;
    solve();
    return 0;
}
