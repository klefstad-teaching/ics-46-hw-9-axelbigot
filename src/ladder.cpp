#include <queue>
#include <fstream>

#include "ladder.h"

void error(string word1, string word2, string msg) {
	fprintf(stderr, "Ladder Error: %s (%s, %s)", msg, word1, word2);
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
	if (str1.length() != str2.length()) return false;

	int diff_sum = 0;
	for (size_t i = 0; i < str1.length(); ++i) {
		if (str1[i] != str2[i]) {
			if (++diff_sum > d) return false;
		}
	}

	return diff_sum == d;
}

bool is_adjacent(const string& word1, const string& word2) {
	return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
	queue<vector<string>> ladders;
	ladders.push({ begin_word });

	set<string> seen;
	seen.insert(begin_word);

	while (!ladders.empty()) {
		int level = ladders.size();
		set<string> level_seen;

		for (int i = 0; i < level; ++i) {
			vector<string> path = ladders.front();
			ladders.pop();

			string latest = path.back();

			if (latest == end_word) return path;

			for (string word : word_list) {
				if (!seen.count(word) && is_adjacent(latest, word)) {
					vector<string> possible_path = path;

					possible_path.push_back(word);
					ladders.push(possible_path);
					level_seen.insert(word);
				}
			}
		}

		for (string word : level_seen)
			seen.insert(word);
	}

	return {};
}

void load_words(set<string> & word_list, const string& file_name) {
	ifstream f(file_name);

	for (string word; f >> word; )
		word_list.insert(word);
	
	f.close();
}

void print_word_ladder(const vector<string>& ladder) {
	for (size_t i = 0; i < ladder.size(); ++i) {
		cout << ladder[i] << " ";
	}
}

void verify_word_ladder() {
	return;
}
