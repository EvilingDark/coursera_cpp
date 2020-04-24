#pragma once

#include <istream>
#include <list>
#include <map>
#include <ostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

//struct sResult {
//    sResult(size_t f, size_t s)
//        : first { f }
//        , second { s }
//    {
//    }
//    size_t first;
//    size_t second;
//};

//bool operator<(const sResult& lhs, const sResult& rhs)
//{
//    int64_t lhs_docid = lhs.first;
//    int64_t rhs_docid = rhs.first;
//    return make_pair(lhs.second, -lhs_docid) > make_pair(rhs.second, -rhs_docid);
//}

class InvertedIndex {
public:
    void Add(const string& document);
    list<size_t> Lookup(const string& word) const;

    const string& GetDocument(size_t id) const
    {
        return docs[id];
    }

private:
    map<string, list<size_t>> index;
    vector<string> docs;
};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input);
    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
    InvertedIndex index;
};
