#include "stdafx.h"

#ifdef __cplusplus
extern "C" {
#endif
	static int BATCH_SIZE = 1;
	void distdb_basic_wr_test()	{
		std::vector<std::string> keys =	{
			"05e65ed70a9f25ebbfd4fc317860faa9deaedfe4b8ccdfb63b9240a0e3b695b8",
			"0cbe325f46a08b77bacdb838e9bb87bc9b0c99136ae0f06a5ab44765480dc988",
			"1a9a717f1242b1ed8af6088ecb0a17c8f1a6b4d1a0d51adf3fc732554fce571c",
			//"17150dde78a5cb107e7e9e2ad4931bc430384c46d92a9fc6bd9f7c02eae72d5c",
			//"258211d39642d8dc6fac86d75c8ce21e2d2b34b50969eadee0d07a24e2cc4fbf",
			//"2f686d9a1bc3bb20f0f2d06e50e0ea70069212fbf4ab9f130cac9a8a5e1b3b7b",
			//"36cb7b1703f7fb3dcf0d636d78b3a01b33e40d88cc29dabe5649ee016aa9955e",
			//"4219815bef4f23e75ff13a6ac91b9c9376dd2e5e5775f66a3971a5af8835dbb7",
			//"42acbd103fd4ea323f8a85b5b92b511d215ac58ba961f31e5d95d087b75711ec",
			//"55adc55dd1b961b2b84d06a21755269adca7d9fdebdeb8970e1c4932b73eba01",
			//"6314b234fd7dbef5472d52831c52ef422911e06920243b791527c28724997ffc",
			//"73e0afb97fb3e3ba9576b8b29cae3cde244722e67e6b6b771f1ae9a39cd4db4a",
			//"78cf63feba9a1abb59a2c1786c705e6ede3ca98fc5a17d87dea16bab038c84b6",
			//"798b1cfddb0ed00d96260867f1e78e67264f717a739742a06ba1500b6fa57ea9",
			//"897a23f1d3597bd2609d23c812f761fc69b4c5123655d09e4f327f13b2486a78",
			//"9097e0b7a1ecf20d17b235891f745e545293b2514bf75a06d55ac9f8c5b8de21",
			//"9c78961bbd6fd1a1bb3e9a6d5bf3551d283eae8b748589b90cd0834b4d79b837",
			//"a478babb065a68eb29a9bfd662179563c9bbe01b90389b3b940e3726d2650f93",
			//"b0efcd8beacb460a45a60677b85c43865ad99a818881cc6fc55eb0855ea44563",
			//"b2a6e2d83abe58a2c5ab435836aab376aee4864c862bdeded166bc1354523393",
			//"ba5b160398a5509d121d49db578f6b26cce20010e71c49d64bf04e2d83b40672",
			//"cf76ed7947971c0047512f09cd4f5adb95dccf1f763818a181cbad33c4cca1d8",
			//"d77d2b2015182f67ab330c7741fa32321b5212651cc615cae7be93c30f6825da",
			//"ef1ce67899929d7a3488ca33703d03639c39353d72a9f51242513f98fa7f1f53",
			//"f9055e315331f2bac26ad68b2487107f9badd6a3ceb66f88169590829ddc6809",
			//"fd1dbe12de998b6f2662209a921620b9982b0631285e9e32aa495aa4505f9644"
		};

		std::vector<std::string> values = {
			"0cbe325abc",
			"0cbe325",
			"1a9a717",
			/*"17150dde78a5cb107e7e9e2ad4931bc430384c46d92a9fc6bd9f7c02eae72d5c17150dde78a5cb107e7e9e2ad4931bc430384c46d92a9fc6bd9f7c02eae72d5c",
			"258211d39642d8dc6fac86d75c8ce21e2d2b34b50969eadee0d07a24e2cc4fbf258211d39642d8dc6fac86d75c8ce21e2d2b34b50969eadee0d07a24e2cc4fbf",
			"2f686d9a1bc3bb20f0f2d06e50e0ea70069212fbf4ab9f130cac9a8a5e1b3b7b2f686d9a1bc3bb20f0f2d06e50e0ea70069212fbf4ab9f130cac9a8a5e1b3b7b",
			"36cb7b1703f7fb3dcf0d636d78b3a01b33e40d88cc29dabe5649ee016aa9955e36cb7b1703f7fb3dcf0d636d78b3a01b33e40d88cc29dabe5649ee016aa9955e",
			"4219815bef4f23e75ff13a6ac91b9c9376dd2e5e5775f66a3971a5af8835dbb74219815bef4f23e75ff13a6ac91b9c9376dd2e5e5775f66a3971a5af8835dbb7",
			"42acbd103fd4ea323f8a85b5b92b511d215ac58ba961f31e5d95d087b75711ec42acbd103fd4ea323f8a85b5b92b511d215ac58ba961f31e5d95d087b75711ec",
			"55adc55dd1b961b2b84d06a21755269adca7d9fdebdeb8970e1c4932b73eba0155adc55dd1b961b2b84d06a21755269adca7d9fdebdeb8970e1c4932b73eba01",
			"6314b234fd7dbef5472d52831c52ef422911e06920243b791527c28724997ffc6314b234fd7dbef5472d52831c52ef422911e06920243b791527c28724997ffc",
			"73e0afb97fb3e3ba9576b8b29cae3cde244722e67e6b6b771f1ae9a39cd4db4a73e0afb97fb3e3ba9576b8b29cae3cde244722e67e6b6b771f1ae9a39cd4db4a",
			"78cf63feba9a1abb59a2c1786c705e6ede3ca98fc5a17d87dea16bab038c84b678cf63feba9a1abb59a2c1786c705e6ede3ca98fc5a17d87dea16bab038c84b6",
			"798b1cfddb0ed00d96260867f1e78e67264f717a739742a06ba1500b6fa57ea9798b1cfddb0ed00d96260867f1e78e67264f717a739742a06ba1500b6fa57ea9",
			"897a23f1d3597bd2609d23c812f761fc69b4c5123655d09e4f327f13b2486a78897a23f1d3597bd2609d23c812f761fc69b4c5123655d09e4f327f13b2486a78",
			"9097e0b7a1ecf20d17b235891f745e545293b2514bf75a06d55ac9f8c5b8de219097e0b7a1ecf20d17b235891f745e545293b2514bf75a06d55ac9f8c5b8de21",
			"9c78961bbd6fd1a1bb3e9a6d5bf3551d283eae8b748589b90cd0834b4d79b8379c78961bbd6fd1a1bb3e9a6d5bf3551d283eae8b748589b90cd0834b4d79b837",
			"a478babb065a68eb29a9bfd662179563c9bbe01b90389b3b940e3726d2650f93a478babb065a68eb29a9bfd662179563c9bbe01b90389b3b940e3726d2650f93",
			"b0efcd8beacb460a45a60677b85c43865ad99a818881cc6fc55eb0855ea44563b0efcd8beacb460a45a60677b85c43865ad99a818881cc6fc55eb0855ea44563",
			"b2a6e2d83abe58a2c5ab435836aab376aee4864c862bdeded166bc1354523393b2a6e2d83abe58a2c5ab435836aab376aee4864c862bdeded166bc1354523393",
			"ba5b160398a5509d121d49db578f6b26cce20010e71c49d64bf04e2d83b40672ba5b160398a5509d121d49db578f6b26cce20010e71c49d64bf04e2d83b40672",
			"cf76ed7947971c0047512f09cd4f5adb95dccf1f763818a181cbad33c4cca1d8cf76ed7947971c0047512f09cd4f5adb95dccf1f763818a181cbad33c4cca1d8",
			"d77d2b2015182f67ab330c7741fa32321b5212651cc615cae7be93c30f6825dad77d2b2015182f67ab330c7741fa32321b5212651cc615cae7be93c30f6825da",
			"ef1ce67899929d7a3488ca33703d03639c39353d72a9f51242513f98fa7f1f53ef1ce67899929d7a3488ca33703d03639c39353d72a9f51242513f98fa7f1f53",
			"f9055e315331f2bac26ad68b2487107f9badd6a3ceb66f88169590829ddc6809f9055e315331f2bac26ad68b2487107f9badd6a3ceb66f88169590829ddc6809",*/
			//"fd1dbe12de998b6f2662209a921620b9982b0631285e9e32aa495aa4505f9644fd1dbe12de998b6f2662209a921620b9982b0631285e9e32aa495aa4505f9644"
		};

		std::string platform(BOOST_PLATFORM);
		std::string config;
		if(platform == "Win32")
			config = "./shard-16-win.json";
		else
			config = "./shard-16-linux.json";

		void* distdbInfo = Start((char*)config.c_str());
		distdb_write_read(distdbInfo, keys, values);

		Stop(distdbInfo);
	}


	void distdb_320_byte_x_50m_entries_batch_wr_test()	{
		BATCH_SIZE = 10000;

		std::string config = PrepareDB();
		void* distdbInfo = Start((char*)config.c_str());

		int counter = 0;
		for (auto & p : boost::filesystem::directory_iterator("/mnt/data/test/1m"))	{
			if (!boost::filesystem::exists(p.path().string())) // an xml file 
				std::cout <<"Error: "<< p.path().string() << " does not exist !";
			else
				distdb_batch_write_read(distdbInfo, (char*)config.c_str(), (char*)p.path().string().c_str());

			counter ++;
			if (counter >= BATCH_SIZE)
				break;
		}
		Stop(distdbInfo);
	}

	void distdb_320_byte_x_50m_entries_batch_r_test() {
		BATCH_SIZE = 10000;
	
		std::string config = PrepareDB();
		void* distdbInfo = Start((char*)config.c_str());

		int counter = 0;
		for (auto & p : boost::filesystem::directory_iterator("/mnt/data/test/1m"))	{
			if (!boost::filesystem::exists(p.path().string())) // an xml file 
				std::cout << "Error: " << p.path().string() << " does not exist !";
			else
				distdb_batch_read(distdbInfo, (char*)config.c_str(), (char*)p.path().string().c_str());

			counter++;
			if (counter >= BATCH_SIZE)
				break;
		}
		Stop(distdbInfo);
	}
	
	void distdb_320_byte_x_1m_entries_batch_wr_test() {
		BATCH_SIZE = 1;
		distdb_320_byte_x_50m_entries_batch_wr_test();
	}
	
	void distdb_batch_write_1m_test() {
		std::string config = PrepareDB();
		void* distdbInfo = Start((char*)config.c_str()); // start DB

		for (unsigned batch = 0; batch < 10; batch++) {
			std::vector<std::string> contents(1000000);
			for (unsigned i = 0; i < contents.size(); i++) {
				auto msg = std::to_string(batch) + std::to_string(i);
				CryptoPP::SHA3_256 hasher;
				std::string digest(hasher.DigestSize(), '0');
				hasher.CalculateDigest((unsigned char*)digest.data(), (const unsigned char*)msg.data(), msg.size());
				contents[i] = digest;
			}

			distdb_write(distdbInfo, contents, contents);
			/*	std::vector<std::string> queryKeys(contents.begin(), contents.begin() + 1000);
				std::vector<std::string> buffers(1000000);
				distdb_read(distdbInfo, queryKeys, contents);
				std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - t0).count() << " ms " << std::endl;*/
		}
		Stop(distdbInfo);
	}
#ifdef __cplusplus
}
#endif

