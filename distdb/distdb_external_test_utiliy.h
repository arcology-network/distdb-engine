#pragma once
void distdb_write(void* distdbInfo, std::vector<std::string>& keys, std::vector<std::string>& values);
void distdb_read(void* distdbInfo, std::vector<std::string>& keys, std::vector<std::string>& values);
void distdb_write_read(void* distdbInfo, std::vector<std::string>& keys, std::vector<std::string>& values);
void distdb_batch_write_read(void* distdbInfo, char* config, char* file);
void distdb_batch_read(void* distdbInfo, char* config, char* file);
std::string PrepareDB();


