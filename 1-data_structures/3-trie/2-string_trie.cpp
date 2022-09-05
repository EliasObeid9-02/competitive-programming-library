#include <bits/stdc++.h>
using namespace std;

template <char smallest_letter = 'a'>
class StringTrie
{
private:
    const static int ALPHABET = 26;
    struct TrieNode
    {
        array<int, ALPHABET> freq;
        array<int, ALPHABET> next_nodes;
        TrieNode()
        {
            freq.fill(0);
            next_nodes.fill(-1);
        }
    };

    int root;
    vector<TrieNode> nodes;

    int fetchNode()
    {
        nodes.emplace_back(TrieNode());
        return (int)nodes.size() - 1;
    }

    // type is true if adding value otherwise false
    void modifyTrie(const string &word, bool type)
    {
        int current_node = root;
        for (const char &C : word)
        {
            int letter = C - smallest_letter;
            if (nodes[current_node].next_nodes[letter] == -1)
            {
                nodes[current_node].next_nodes[letter] = fetchNode();
            }
            nodes[current_node].freq[letter] += (type ? +1 : -1);
            current_node = nodes[current_node].next_nodes[letter];
        }
    }

public:
    StringTrie()
    {
        root = fetchNode();
    }

    StringTrie(const vector<string> &initial_array)
    {
        for (int i = 0; i < (int)initial_array.size(); ++i)
        {
            insert(initial_array[i]);
        }
    }

    void insert(const string &word)
    {
        modifyTrie(word, true);
    }

    void erase(const string &word)
    {
        modifyTrie(word, false);
    }

    bool find(const string &word)
    {
        int current_node = root;
        for (const char &C : word)
        {
            int letter = C - smallest_letter;
            if (nodes[current_node].next_nodes[letter] == -1 ||
                nodes[current_node].freq[letter] == 0)
            {
                return false;
            }
            current_node = nodes[current_node].next_nodes[letter];
        }
        return true;
    }
};

int main()
{
    int array_size, queries;
    cin >> array_size >> queries;

    vector<string> initial_array(array_size);
    for (int i = 0; i < array_size; ++i)
    {
        cin >> initial_array[i];
    }

    StringTrie<'a'> trie(initial_array);
    for (int i = 0; i < queries; ++i)
    {
        string operation, word;
        cin >> operation >> word;
        if (operation == "add")
        {
            trie.insert(word);
        }
        else if (operation == "erase")
        {
            trie.erase(word);
        }
        else if (operation == "find")
        {
            cout << (trie.find(word) ? "Yes" : "No") << "\n";
        }
        else
        {
            assert(false);
        }
    }
    return 0;
}