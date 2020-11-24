#include "stdafx.h"

distdb::Balancer::Balancer(std::string file, std::vector<bool>& flags) {
	if (file.empty() || !boost::filesystem::exists(file)) {
		std::cout << "Couldn't locate DB configuration file !" << std::endl;
		return;
	}

	boost::property_tree::ptree dbLocationTree;
	boost::property_tree::read_json(file, dbLocationTree);

	flags.resize(suffixes.size(), false);
	for (std::size_t i = 0; i < suffixes.size(); i++) {
		std::string dbTag = prefix + std::to_string(suffixes[i]);
		std::string dbLoc = dbLocationTree.get<std::string>(dbTag);

		auto v = std::shared_ptr<distdb::DB>(new distdb::DB(dbLoc));
		flags[i] = v->successful;
		dbs.insert(std::make_pair(dbTag, v));
	}
	successful = std::find(flags.begin(), flags.end(), false) == flags.end();
}

void distdb::Balancer::BatchRead(std::vector<std::string>& keys, std::vector<std::string>& retrived) {
	if (retrived.size() != keys.size())
		retrived.resize(keys.size());

	//for (std::size_t i = 0; i < keys.size(); i++) {
	tbb::parallel_for(std::size_t(0), keys.size(), [&](std::size_t i) {
		auto db = dbs[prefix + std::to_string(std::abs((keys[i][0]) % 16)) ];
		db->Get(keys[i], retrived[i]);
	}
	);
}

bool distdb::Balancer::BatchWrite(std::vector<std::string>& keys, std::vector<std::string>& values) {
	std::vector<unsigned> countVec(suffixes.size(), 0);
	for (std::size_t i = 0; i < keys.size(); i++)
		countVec[std::abs((keys[i][0]) % 16)] ++;

	std::vector<bool> flags(suffixes.size(), false);

	//for (std::size_t i = 0; i < suffixes.size(); i++)  {
	tbb::parallel_for(std::size_t(0), (std::size_t)suffixes.size(), [&](std::size_t i) {
		std::vector<std::pair<std::string*, std::string*>> kvPairs(countVec[i]);
		int ind = 0;
		for (std::size_t j = 0; j < keys.size(); j++) {
			int v = std::abs(keys[j][0] % 16);
			if (std::abs(keys[j][0] % 16) == suffixes[i]) {
				kvPairs[ind++] = std::make_pair(&keys[j], &values[j]);
			}
		}
	
		if (!kvPairs.empty()) {
			auto db = dbs[prefix + std::to_string(suffixes[i])];
			db->BatchPut(kvPairs);
			flags[i] = db->successful;
		}
	}
	);
	return std::find(flags.begin(), flags.end(), false) == flags.end(); // all successful
}
