#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <math.h>

#include "stegdir.h"
#include "../codegen/lib/matlab_base64/base64Decode.h"
#include "../codegen/lib/matlab_base64/matlab_base64_data.h"
#include "../codegen/lib/matlab_base64/matlab_base64_emxAPI.h"
#include "../codegen/lib/matlab_base64/matlab_base64_initialize.h"
#include "../codegen/lib/matlab_base64/matlab_base64_terminate.h"
#include "../codegen/lib/matlab_base64/matlab_base64_types.h"

#define URLMODE_DECODING 1

/* Check if the string is a valid integer without extra digits inside */
int checkIfStringIsNumber(char* str) {
	char* endptr;
    
    /* Guard against empty string */
    if(*str == '\0') return 0;

	strtol(str, &endptr, 10);
	return (*endptr != '\0') ? 0 : 1;
}

/* Check if the input string is prefixed by a number followed by an underscore,
 * for example "1_0Ocg6aEYR4wA" is a valid entry. If the string is valid, return
 * the pointer at the first character after the underscore, otherwise return
 * NULL */
char* processPrefixedBlock(char* inputString) {
    char *underscoreIndex = strchr(inputString, '_');
    if (underscoreIndex == NULL) return NULL;
    
	*underscoreIndex = '\0';
    int isPrefixValid = checkIfStringIsNumber(inputString);
    *underscoreIndex = '_';   // restore
    
	if (isPrefixValid) return underscoreIndex + 1;
    else return NULL;
}

/* Compare the name of the two directory entries based on the numerical prefix */
int sortDirectoriesByPrefixNumber(const struct dirent **a, const struct dirent **b) {
	return atoi((*a)->d_name) - atoi((*b)->d_name);
}


/* Filter out directories "." and ".." */
int filterDirectoryDots(const struct dirent *d) {
	return d->d_name[0] != '.';
}

int stegdir_decode(char* inputRootDirectory, int outputFileDescriptor) {

	struct dirent **entries;

	/* Search from inputRootDirectory and return all the subdirectories filtered
	 * in numerical order, since they are prefixed with a progressive number.
	 * Directory entries "." and ".." are excluded using the filter function. */
	int numSubdirectories = scandir(inputRootDirectory, &entries, filterDirectoryDots, sortDirectoriesByPrefixNumber);
	
	if (numSubdirectories == -1) {
		perror("Error scanning subdirectories");
		return 1;
	}

	/* Initialize data structures */
    matlab_base64_initialize();
	emxArray_uint8_T *outputData, *encodedData;

	for (int i = 0; i < numSubdirectories; i++) {
	
		/* Allocate block size based on the current entry */
		char* blockStart = processPrefixedBlock(entries[i]->d_name);
		if (blockStart == NULL) {
            printf("invalid block %d\n", i);
            for (int j = i; j < numSubdirectories; j++) {
                free(entries[j]);
            }
            free(entries);
            matlab_base64_terminate();
            return 1;
        }

		int inBlkSize = strlen(blockStart);
		encodedData = emxCreateND_uint8_T(1, &inBlkSize);
		emxInitArray_uint8_T(&outputData, 2);

		memcpy(encodedData->data, blockStart, inBlkSize);
        *encodedData->size = inBlkSize;

		base64Decode(encodedData, URLMODE_DECODING, outputData);
		
		write(outputFileDescriptor, outputData->data, outputData->size[1]);
		
		free(entries[i]);
        emxDestroyArray_uint8_T(encodedData);
        emxDestroyArray_uint8_T(outputData);
	}

	free(entries);
    matlab_base64_terminate();

	return 0;
}
