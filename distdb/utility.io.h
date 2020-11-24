#pragma once


namespace Utility
{
	namespace IO
	{
		static std::string BuildPath(std::string folder, std::string fileName)
		{
			boost::filesystem::path dir(folder);
			boost::filesystem::path file(fileName);
			boost::filesystem::path fullPath = dir / file;

			return fullPath.string();
		}


		template<typename T>
		static void WriteToFile(std::vector<T> vec, std::string fileName)
		{
			std::ofstream stream(fileName);
			for (unsigned i = 0; i < vec.size(); i++)
				stream << vec[i] << std::endl;
			stream.close();
		}


		static std::string FileToString(std::string fileName)
		{
			std::ifstream t(fileName);
			std::stringstream buffer;
			buffer << t.rdbuf();
			return buffer.str();
		}


		static std::vector<std::vector<std::string>> ParseFile(std::string file, std::string rowPrefixDB, std::string colDelimitor)	{
			std::vector<std::vector<std::string>> contents;
			if (boost::filesystem::exists(file)) {// an xml file 			
				std::string fileContents = FileToString(file);

				std::vector<std::string> rows;
				boost::split(rows, fileContents, boost::is_any_of(rowPrefixDB));

				contents.resize(rows.size());
				tbb::parallel_for(std::size_t(0), rows.size(), [&](std::size_t i)
				{
					std::vector<std::string> columns;
					boost::split(columns, rows[i], boost::is_any_of(colDelimitor));
					contents[i] = (columns);
				}
				);

				/*	contents.reserve(rows.size());
				for (unsigned i = 0; i < rows.size(); i++)
				{
					if (!rows[i].empty())
					{
						std::vector<std::string> columns;
						boost::split(columns, rows[i], boost::is_any_of(colDelimitor));

						contents.push_back(columns);
					}
				}*/
			}
			else
			{
				std::cout << file << " does not exist" << std::endl;
			}

			return contents;
		}


	}
}

