#include "stdafx.h"

void distdb_write(void* distdbInfo, std::vector<std::string>& keys, std::vector<std::string>& values) {
	std::vector<uint64_t> kLens(keys.size(), 0);
	std::vector<uint64_t> vLens(values.size(), 0);
	for (unsigned i = 0; i < keys.size(); i++) {
		kLens[i] = keys[i].size();
		vLens[i] = values[i].size();
	}

	std::string concatKeys;
	String::Concatenate(keys, concatKeys);

	std::string concatValues;
	String::Concatenate(values, concatValues);

	BatchSet(distdbInfo, concatKeys.data(), kLens.data(), kLens.size(), concatValues.data(), vLens.data());
}
	


void distdb_read(void* distdb, std::vector<std::string>& keys, std::vector<std::string>& values) {
	std::vector<uint64_t> kLens(keys.size(), 0);
	std::vector<uint64_t> vLens(values.size(), 0);
	for (unsigned i = 0; i < keys.size(); i++) {
		kLens[i] = keys[i].size();
		vLens[i] = values[i].size();
	}

	std::string concatKeys;
	String::Concatenate(keys, concatKeys);

	std::string buffer;
	buffer.resize(100000, '0');

	uint64_t count = 0;
	BatchGet(distdb, concatKeys.data(), kLens.data(), kLens.size(), buffer.data(), vLens.data(), &count);

	std::string concatTarget;
	String::Concatenate(values, concatTarget);

	if (concatTarget == buffer.substr(0, concatTarget.size()))
		std::cout << "Successful: All matched !" << std::endl;
	else
		std::cout << "Error: Some entires couldn't be successfully retrived !" << std::endl;;
}


void distdb_write_read(void* distdbInfo, std::vector<std::string>& keys, std::vector<std::string>& values) {
	auto t0 = std::chrono::steady_clock::now();
	distdb_write(distdbInfo, keys, values);
	distdb_read(distdbInfo, keys, values);
}


void distdb_batch_write_read(void* distdbInfo, char* config, char* file) {
	std::cout << "File: " << file << std::endl;
	std::vector<std::vector<std::string>> contents = Utility::IO::ParseFile(file, "\n", ",");
	if (contents.empty()) {
		std::cout << "Error: " << file << " is empty !" << std::endl;
		return;
	}

	std::vector<std::string> keys, values;
	keys.reserve(contents.size());
	values.reserve(contents.size());

	for (unsigned i = 1; i < contents.size(); i++)
		if (!contents[i][0].empty()) {
			keys.push_back(contents[i][0]);
			values.push_back(contents[i][0] + contents[i][0] + contents[i][0] + contents[i][0] + contents[i][0]);  // 
			distdb_write_read(distdbInfo, keys, values);
		}
	distdb_write_read(distdbInfo, keys, values);
}

void distdb_batch_read(void* distdbInfo, char* config, char* file) {
	std::cout << "File: " << file << std::endl;
	std::vector<std::vector<std::string>> contents = Utility::IO::ParseFile(file, "\n", ",");
	if (contents.empty()) {
		std::cout << "Error: " << file << " is empty !" << std::endl;
		return;
	}

	std::vector<std::string> keys, values;
	keys.reserve(contents.size());
	values.reserve(contents.size());

	for (unsigned i = 1; i < 1; i++)
		if (!contents[i][0].empty()) {
			keys.push_back(contents[i][0]);
			values.push_back(contents[i][0] + contents[i][0] + contents[i][0] + contents[i][0] + contents[i][0]);  // 
		}
	distdb_read(distdbInfo, keys, values);
}

std::string  PrepareDB() {
	std::freopen("log.txt", "w", stdout);
	std::ios::sync_with_stdio(false);

	/* product and version information*/
	auto time = std::time(nullptr);
	std::cout << "product: " << product << std::endl;
	std::cout << "version: " << version << std::endl;
	std::cout << "time: " << std::put_time(std::localtime(&time), "%F %T%z") << std::endl;
	
	std::string platform(BOOST_PLATFORM);
	std::string config;
	if (platform == "Win32")
		config = "./shard-16-win.json";
	else
		config = "./shard-16-linux.json";

	return config;	
}
