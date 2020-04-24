#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <iterator>
#include <sstream>

vector<string> SplitIntoWords(const string& line)
{
    vector<string> words;
    string w;
    for (auto& ch : line) {
        if (!isspace(ch))
            w.push_back(ch);
        else if (!w.empty())
            words.push_back(move(w));
    }
    if (!w.empty())
        words.push_back(move(w));
    return words;
}

SearchServer::SearchServer(istream& document_input)
{
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input)
{
    InvertedIndex new_index;

    for (string current_document; getline(document_input, current_document);) {
        new_index.Add(move(current_document));
    }

    index = move(new_index);
}

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output)
{
    array<size_t, 50000> docid_count { 0 };
    array<pair<size_t, size_t>, 50000> search_results;
    for (string current_query; getline(query_input, current_query);) {
        const auto words = SplitIntoWords(current_query);

        for (const auto& word : words) {
            for (const size_t docid : index.Lookup(word)) {
                docid_count[docid]++;
            }
        }

        for (size_t i = 0; i < docid_count.size(); ++i) {
            search_results[i] = { i, docid_count[i] };
        }

        docid_count.fill(0);

        partial_sort(search_results.begin(), search_results.begin() + 5, search_results.end(),
            [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
                int64_t lhs_docid = lhs.first;
                int64_t rhs_docid = rhs.first;
                return make_pair(lhs.second, -lhs_docid) > make_pair(rhs.second, -rhs_docid);
            });

        search_results_output << current_query << ':';
        for (auto [docid, hitcount] : Head(search_results, 5)) {
            if (hitcount > 0) {
                search_results_output << " {"
                                      << "docid: " << docid << ", "
                                      << "hitcount: " << hitcount << '}';
            }
        }
        search_results_output << endl;
    }
}

void InvertedIndex::Add(const string& document)
{
    docs.push_back(move(document));

    const size_t docid = docs.size() - 1;
    for (const auto& word : SplitIntoWords(docs.back())) {
        index[word].push_back(docid);
    }
}

list<size_t> InvertedIndex::Lookup(const string& word) const
{
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return {};
    }
}
