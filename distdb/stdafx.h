#pragma once

#include <cstdio>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <random>
#include <numeric>
#include <chrono>

#include <boost/version.hpp>
#include <boost/config.hpp>
#include <boost/algorithm/string.hpp> 

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

#include <boost/filesystem.hpp>
#include <boost/iterator/counting_iterator.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>


#ifdef __linux__ 
#include <tbb/tbb.h>
#include "cryptopp/cryptlib.h"
#include "cryptopp/hex.h"
#include "cryptopp/crc.h"
#include "cryptopp/keccak.h"
#include "cryptopp/sha3.h"

#elif _WIN32
#include <ppl.h>
namespace tbb = Concurrency;
#include "cryptlib.h"
#include "hex.h"
#include "crc.h"
#include "keccak.h"
#include "sha3.h"
#else
#endif




#include "leveldb/db.h"
#include "leveldb/write_batch.h"

#include "version.h"
#include "utility.io.h"
#include "utility.string.h"
#include "db.h"
#include "distdb.h"
#include "distdb.external.h"

#include "distdb_external_test_utiliy.h"
#include "distdb_external_test.h"
// TODO: reference additional headers your program requires here
