#include "stdafx.h"

#ifdef __cplusplus
extern "C" {
#endif
	void GetVersion(char* ver) {
		std::strcpy(ver, version);
	}

	void GetProduct(char* productInfo) {
		std::strcpy(productInfo, product);
	}

	void* Start(char* configFile) {
		std::vector<bool> flags;
		auto balancer = (new distdb::Balancer(configFile, flags));
		if (std::find(flags.begin(), flags.end(), false) == flags.end())
			return balancer;
		else
			return nullptr;
	}

	bool BatchGet(void* distdbPtr, char* keys, uint64_t* kLens, uint64_t kCount, char* values, uint64_t* vLens, uint64_t* outCount) {
		auto distdb = (distdb::Balancer*)(distdbPtr);
		
		// Reshape keys
		std::vector<uint64_t> kLengths(kLens, kLens + kCount);
		std::vector<std::string> newKeys;
		String::Reshape(keys, kLengths, newKeys);
		newKeys.push_back("random_key");

		std::vector<std::string> retrived(newKeys.size());
		distdb->BatchRead(newKeys, retrived);
	
		for (std::size_t i = 0; i < retrived.size(); i++)
			vLens[i] = retrived[i].size();

		*outCount = retrived.size();

		std::string concateValues;
		String::Concatenate(retrived, concateValues);
		std::memcpy(values, concateValues.data(), concateValues.size());

		return distdb->successful;
	}
	
	bool BatchSet(void* distdbPtr, char* keys, uint64_t* kLens, uint64_t kCount, char* values, uint64_t* vLens) {
		auto distdb = (distdb::Balancer*)(distdbPtr);
	
		// Reshape keys
		std::vector<uint64_t> kLengths(kLens, kLens + kCount);
		std::vector<std::string> newKeys;
		String::Reshape(keys, kLengths, newKeys);
		
		// Reshape values
		std::vector<uint64_t> vLengths(vLens, vLens + kCount);
		std::vector<std::string> newValues;
		String::Reshape(values, vLengths, newValues);
		
		auto t0 = std::chrono::steady_clock::now();
		distdb->BatchWrite(newKeys, newValues);
		std::cout << "distdb->BatchWrite(keys, newValueVec): " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - t0).count() << std::endl;
		return distdb->successful; 
	}

	void Stop(void* distdbPtr) {
		delete (distdb::Balancer*)(distdbPtr);
	}

#ifdef __cplusplus
}
#endif