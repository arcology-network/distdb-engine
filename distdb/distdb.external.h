#pragma once

/*Adding headers for cgo*/
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
	void* Start(char* configFile);
	void Stop(void* hpmtPtr);

	bool BatchGet(void* distdbPtr, char* keys, uint64_t* kLens, uint64_t kCount, char* values, uint64_t* vLens, uint64_t* count);
	bool BatchSet(void* distdbPtr, char* keys, uint64_t* kLens, uint64_t kCount, char* values, uint64_t* vLens);

	void GetVersion(char* version);
	void GetProduct(char* product);

#ifdef __cplusplus
}
#endif
