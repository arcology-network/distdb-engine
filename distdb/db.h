#pragma once
namespace distdb
{
	struct DB
	{
		std::string name = "";
		std::string location = "";

		DB(std::string name);

		void Get(const std::string& key, std::string& deserialized);
		bool Put(const std::string& key, std::string& serialized);

		bool BatchPut(const std::vector<std::pair<std::string, std::string>>& data);
		bool BatchPut(const std::vector<std::pair<std::string*, std::string*>>& data);

		bool successful = false;

	private:
		leveldb::DB* db;
		leveldb::Options options;
		leveldb::WriteOptions writeOptions;
		leveldb::ReadOptions readOptions;

		bool Init(std::string name);
	};
}

