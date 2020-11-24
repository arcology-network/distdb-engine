#pragma once

namespace String
{
	static void Reshape(char* inputString, std::vector<uint64_t>& counts, std::vector<std::string>& strVec)	{
		strVec.resize(counts.size());
		std::vector<unsigned> accumPos(counts.size() + 1, 0);

		unsigned total = 0;
		for (unsigned i = 0; i < counts.size(); i++) {
			total += counts[i];
			accumPos[i + 1] = total;
		}

		//for (std::size_t i = 1; i < accumPos.size(); i++)
		tbb::parallel_for(std::size_t(1), accumPos.size(), [&](std::size_t i) {		
			strVec[i - 1].resize(counts[i - 1]); 
			std::copy(&inputString[accumPos[i - 1]], &inputString[accumPos[i]], &strVec[i - 1][0]);
		}
		);	
	}
	
	static unsigned SumTotalLen(std::vector<std::string>& retrived)	{
		return std::accumulate(retrived.begin(), retrived.end(), 0, [&](unsigned sum, auto iter) { return sum + iter.size(); });
	}

	static std::vector<unsigned> GetSubPos(std::vector<std::string>& vec) {
		std::vector<unsigned> indVec(vec.size() + 1, 0);
		unsigned total = 0;
		for (unsigned i = 0; i < vec.size(); i++) {
			total += vec[i].size();
			indVec[i + 1] = total;
		}
		return indVec;
	}


	static int CountLeadingMatches(std::string& _1st, std::string& _2nd) {
		int count = 0;
		for (std::size_t i = 0; i < std::min(_1st.size(), _2nd.size()); i++) {
			if (_1st[i] == _2nd[i])
				count++;
			else
				break;
		}	
		return count;
	}


	static bool IfStartWith(std::string& source, std::string& leadingPattern) {
		return source.substr(0, leadingPattern.size()) == leadingPattern;
	}

	static bool IfStartWith(char* source, char* leadingPattern)	{
		return (std::strcmp(source, leadingPattern) == 0);
	}


	static void ExtractSubString(std::vector<std::string>& stringVec, int begin, int end, std::vector<std::string>& ancestorPaths)	{
		if (end - begin == stringVec.begin()->size()) {
			ancestorPaths = stringVec;
			return;
		}
	
		ancestorPaths.resize(stringVec.size());
		tbb::parallel_for(std::size_t(0), stringVec.size(), [&](std::size_t i) {
			ancestorPaths[i] = stringVec[i].substr(begin, end);
		}
		);
	}

	static std::vector<char> ToVec(std::string string) {
		std::vector<char> vec(string.size());
		std::copy(string.begin(), string.end(), vec.begin());
		return vec;
	}

	static std::string GetFromJson(std::string file, std::string key) {
		boost::property_tree::ptree configTree;
		boost::property_tree::read_json(file, configTree);
		return configTree.get<std::string>(key);
	}

	static void Concatenate(std::vector<std::string>& strVec, std::string& concatenated) {
		std::vector<unsigned> indVec = GetSubPos(strVec);
		concatenated.resize(indVec.back(), '0');

		//for (std::size_t i = 0; i < strVec.size(); i++)
		tbb::parallel_for(std::size_t(0), strVec.size(), [&](std::size_t i) {
			std::copy(strVec[i].begin(), strVec[i].end(), concatenated.data() + indVec[i]);
		}
		);
	}

	static int HexToIdx(char c)	{
		int branch = c;

		if (!(branch >= 48 && branch <= 57) && !(branch >= 97 && branch <= 102))
			branch = -1;

		if (branch >= 48 && branch <= 57)  // [0, 9]
			branch = branch - 48;      // to index

		if (branch >= 97 && branch <= 102) // [a, f]
			branch = branch - 97 + 10; // to index
		return branch;
	}	
};
