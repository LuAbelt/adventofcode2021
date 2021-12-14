//
// Created by lukas on 03/12/2021.
//

#include <iostream>
#include <vector>
#include <map>

using namespace std;

using CharPair = std::pair<char,char>;
using Mappings = std::map<CharPair,char>;

Mappings parseMappings(){
	string line;
	Mappings res;

	while (getline(cin,line) && !line.empty()){
		res.emplace(std::make_pair(line[0],line[1]),line[line.length()-1]);
	}

	return res;
}

string performReplacements(string &input, Mappings &mappings){
	string res;
	char last = input[0];
	for (int i = 1; i < input.length(); ++i) {
		char cur = input[i];
		res.push_back(last);
		auto itr = mappings.find({last,cur});
		if(itr!=mappings.end()){
			res.push_back(itr->second);
		}
		last = cur;
	}
	res.push_back(last);

	return res;
}

void part1(){
    std::string polymer;
    std::string line;

    getline(cin, polymer);
	//Skip empty line
	getline(cin,line);

	auto mapping = parseMappings();

	for (auto& m : mapping) {
		//cout << m.first.first<<m.first.second<<":"<<m.second<<endl;
	}

	for (int i = 0; i < 10; ++i) {
		polymer = performReplacements(polymer,mapping);
		//cout << polymer.length() << endl;
		//cout << polymer << endl;
	}

	size_t maxOccurences = 0;
	size_t minOccurences = std::numeric_limits<size_t>::max();

	for(char c = 'A';c<='Z';++c){
		size_t occurences = std::count(polymer.begin(), polymer.end(),c);
		maxOccurences = max(maxOccurences,occurences);
		if(occurences>0) {
			minOccurences = min(minOccurences, occurences);
		}
	}

	cout << maxOccurences << endl;
	cout << minOccurences << endl;
	cout << maxOccurences-minOccurences << endl;
}

void part2(){
	std::string polymer;
	std::string line;

	getline(cin, polymer);
	//Skip empty line
	getline(cin,line);

	auto mapping = parseMappings();

	std::map<CharPair,size_t> pairCounts;
	std::map<char,size_t> occurences;

	for (auto c : polymer) {
		occurences[c]++;
	}

	{
		char last = polymer[0];
		for (int i = 1; i < polymer.length(); ++i) {
			char cur = polymer[i];
			auto p = make_pair(last,cur);
			auto itr = mapping.find(p);
			if(itr!=mapping.end()){
				pairCounts[p]++;
			}
			last = cur;
		}
	}

	for (int i = 0; i < 40; ++i) {
		std::map<CharPair,size_t> newPairs;
		for (const auto& entry:pairCounts) {
			auto pattern = entry.first;
			auto itr = mapping.find(pattern);

			occurences[itr->second]+=entry.second;

			//Add new pairs for next iteration
			auto p = make_pair(pattern.first,itr->second);
			if(mapping.find(p)!=mapping.end()){
				newPairs[p]+=entry.second;
			}
			p = make_pair(itr->second,pattern.second);
			if(mapping.find(p)!=mapping.end()){
				newPairs[p]+=entry.second;
			}
		}
		pairCounts = newPairs;
	}

	size_t maxOccurences = 0;
	size_t minOccurences = numeric_limits<size_t>::max();

	for (auto &entry:occurences) {
		maxOccurences = max(entry.second,maxOccurences);
		minOccurences = min(entry.second, minOccurences);
	}

	cout << maxOccurences << endl;
	cout << minOccurences << endl;
	cout << maxOccurences-minOccurences << endl;
}

int main(int argc, char* argv[]){
  if(std::string(argv[1])=="--one"){
    part1();
  } else if(std::string(argv[1])=="--two"){
    part2();
  } else {
    std::cout << "Wrong usage. Allowed arguments: '--one' or '--two'";
  }
}

