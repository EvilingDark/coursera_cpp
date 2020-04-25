#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <iterator>
#include <sstream>

vector<string_view> SplitIntoWords(const string& line)
{
    string_view str(line);
    vector<string_view> words;
    size_t space = 0;
    while (!str.empty() && space != str.npos) {
        if (str[0] != ' ') {
            space = str.find(' ');
            words.push_back(str.substr(0, space));
            str.remove_prefix(space + 1);
        } else
            str.remove_prefix(1);
    }
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
    array<pair<size_t, size_t>, 50000> search_results { make_pair(0, 0) };
    bool editSearch_results = false;
    for (string current_query; getline(query_input, current_query);) {
        const auto words = SplitIntoWords(current_query);

        if (editSearch_results)
            search_results.fill(make_pair(0, 0));
        for (const auto& word : words) {
            for (const auto& docid : index.Lookup(word)) {
                search_results[docid.Id].first = docid.Id;
                search_results[docid.Id].second += docid.Count;
            }
        }
        editSearch_results = true;

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

void InvertedIndex::Add(string&& document)
{
    docs.push_back(move(document));

    const size_t docid = docs.size() - 1;
    for (const auto& word : SplitIntoWords(docs.back())) {
        if (!index[word].empty() && index[word].back().Id == docid)
            ++index[word].back().Count;
        else
            index[word].push_back({ docid });
    }
}

const vector<countId>& InvertedIndex::Lookup(const string_view& word) const
{
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return noLookup;
    }
}
