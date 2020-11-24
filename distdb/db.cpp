#include "stdafx.h"

bool distdb::DB::Init(std::string name)
{
	leveldb::Status status = leveldb::DB::Open(options, name, &db);
	if (!status.ok())
		std::cout << "Unable to open/create database " + name + " : " + status.ToString() << std::endl;
	return status.ok();
}

distdb::DB::DB(std::string name) :name(name)
{
	options.create_if_missing = true;
	successful = Init(name);
}

void distdb::DB::Get(const std::string& key, std::string& deserialized) {
	db->Get(readOptions, key, &deserialized);
}

bool distdb::DB::Put(const std::string& key, std::string& serialized) {
	return db->Put(writeOptions, key, serialized).ok();
}

bool distdb::DB::BatchPut(const std::vector<std::pair<std::string*, std::string*>>& data) {
	leveldb::WriteBatch batch;
	for (unsigned i = 0; i < data.size(); i++)
		if (!data[i].first->empty())
			batch.Put(*data[i].first, *data[i].second);

	leveldb::Status status = db->Write(leveldb::WriteOptions(), &batch);
	if (!status.ok()) {
		std::cout << "Failed to write to db " + name << std::endl;
		return false;
	}		
	return true;
}

bool distdb::DB::BatchPut(const std::vector<std::pair<std::string, std::string>>& data) {
	leveldb::WriteBatch batch;
	for (unsigned i = 0; i < data.size(); i++)
		if (!data[i].first.empty())
			batch.Put(data[i].first, data[i].second);

	leveldb::Status status = db->Write(leveldb::WriteOptions(), &batch);
	if (!status.ok())
		std::cout << "Failed to write to db " + name << std::endl;
	return true;
}