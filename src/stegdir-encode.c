#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

#include "stegdir.h"
#include "../codegen/lib/matlab_base64/base64Encode.h"
#include "../codegen/lib/matlab_base64/matlab_base64_data.h"
#include "../codegen/lib/matlab_base64/matlab_base64_emxAPI.h"
#include "../codegen/lib/matlab_base64/matlab_base64_initialize.h"
#include "../codegen/lib/matlab_base64/matlab_base64_terminate.h"
#include "../codegen/lib/matlab_base64/matlab_base64_types.h"

/* Define the maximum block size in bytes before creating a new folder */
#define INPUT_BLOCK_SIZE 180

int stegdir_encode(int inputFileDescriptor, char* outputRootDirectory) {

	mkdir(outputRootDirectory, 0700);
	
	size_t nReadBytes;

	/* Block size declared as an int variable because emx object requires
	 * the input dimensions to be decalred as an int array */
	const int blockSize = INPUT_BLOCK_SIZE;
	char blockIdString[32];
	
	/* Initialize data structures */
    matlab_base64_initialize();
	emxArray_char_T *encodedData;
  	emxArray_uint8_T *inputData;
	
	inputData = emxCreateND_uint8_T(1, &blockSize);
	emxInitArray_char_T(&encodedData, 2);

	/* Allocate enough memory for the new path, that should contain
	 * the base directory, the subdirectory, plus additional bytes
	 * for the separator and the folder prefix */
	char* outputDirectoryBuf = malloc(ceil((float)INPUT_BLOCK_SIZE * 4 / 3) + 1 + sizeof(blockIdString) + 1 + strlen(outputRootDirectory) + 1);

	int blockIndex = 0;
	while((nReadBytes = read(inputFileDescriptor, inputData->data, INPUT_BLOCK_SIZE)) > 0) {
		
		/* Update data size since the last block size is not known */
		*inputData->size = nReadBytes;

		base64Encode(inputData, URLMODE_ENCODING, encodedData);

		snprintf(blockIdString, sizeof(blockIdString), "%d", blockIndex);
		
		/* Compose subdirectory string */
		strcpy(outputDirectoryBuf, outputRootDirectory);
		strcat(outputDirectoryBuf, "/");
		strcat(outputDirectoryBuf, blockIdString);
		strcat(outputDirectoryBuf, "_");
		strncat(outputDirectoryBuf, encodedData->data, encodedData->size[1]);
		
		if(mkdir(outputDirectoryBuf, 0700)) {
			perror("Error making directory");
            free(outputDirectoryBuf);
            emxDestroyArray_uint8_T(inputData);
            emxDestroyArray_char_T(encodedData);
            matlab_base64_terminate();
			return 1;
		}

		blockIndex++;
	}

    free(outputDirectoryBuf);
    emxDestroyArray_uint8_T(inputData);
    emxDestroyArray_char_T(encodedData);
    matlab_base64_terminate();

	return 0;
}
