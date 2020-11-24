#pragma once

namespace distdb
{
	struct Balancer
	{
		inline const static std::vector<uint8_t> suffixes = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
		std::map<std::string, std::shared_ptr<distdb::DB>> dbs;
		inline const static std::string prefix = "_";
		bool successful = false;

		Balancer(std::string file, std::vector<bool>& flags);

		void BatchRead (std::vector<std::string>& keys, std::vector<std::string>& values);
		bool BatchWrite(std::vector<std::string>& keys, std::vector<std::string>& values);
	};
}