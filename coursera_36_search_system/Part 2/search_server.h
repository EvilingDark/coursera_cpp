#pragma once

#include <future>
#include <istream>
#include <mutex>
#include <ostream>
#include <queue>
#include <shared_mutex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
using namespace std;

struct countId {
    countId(size_t id, size_t count = 1u)
        : Id { id }
        , Count { count }
    {
    }
    size_t Id;
    size_t Count;
    bool operator==(const countId& rhs)
    {
        return Id == rhs.Id;
    }
};

class InvertedIndex {
public:
    InvertedIndex() { docs.reserve(12000); }
    void Add(string&& document);
    const vector<countId>& Lookup(const string_view& word) const;

    const string& GetDocument(size_t id) const
    {
        return docs[id];
    }

private:
    unordered_map<string_view, vector<countId>> index;
    vector<string> docs;
    vector<countId> noLookup;
};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input);
    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);
    const vector<countId>& ServerLookup(const string_view word);

private:
    void AddQueriesStreamWorker(istream& query_input, ostream& search_results_output);
    InvertedIndex index;
    queue<future<void>> pool;
    size_t pool_size = 100;
    shared_mutex lockM;
};
