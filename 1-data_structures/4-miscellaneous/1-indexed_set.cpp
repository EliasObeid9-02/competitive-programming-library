#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename number_type>
using indexed_set = tree<
    number_type,
    null_type,
    less<number_type>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename number_type>
using indexed_multiset = tree<
    number_type,
    null_type,
    less_equal<number_type>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

int main()
{
    int queries;
    cin >> queries;

    indexed_set<int> values;
    for (int i = 0; i < queries; ++i)
    {
        string operation;
        cin >> operation;
        if (operation == "find")
        {
            // returns the value at index "index"
            int index;
            cin >> index;
            cout << *values.find_by_order(index) << "\n";
        }
        else if (operation == "order")
        {
            // returns the index of "value" if it was in the indexed_set
            int value;
            cin >> value;
            cout << values.order_of_key(value) << "\n";
        }
        else
        {
            assert(false);
        }
    }
    return 0;
}