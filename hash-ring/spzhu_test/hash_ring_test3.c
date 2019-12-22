#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>
#include <string.h>

#include "hash_ring.h"


#ifdef __APPLE__
#include <mach/mach_time.h>
#endif

void startTiming()
{
#ifdef __APPLE__
	opStartTime = mach_absolute_time();
#endif
}

uint64_t endTiming()
{
#ifdef __APPLE__
	uint64_t duration = mach_absolute_time() - opStartTime;

	/* Get the tiembase info */
	mach_timebase_info_data_t info;
	mach_timebase_info(&info);

	/* Convert to nanoseconds */
	duration *= info.numer;
	duration /= info.denom;

	return duration;
#else
	return 0;
#endif
}


void fillRandomBytes(uint8_t *bytes, uint32_t num)
{
	int x;
	for (x = 0; x < num; x++)
	{
		bytes[x] = (rand() % 25) + 97;
	}
}

void addNodes(hash_ring_t *ring, int numNodes)
{
	int x;
	uint8_t nodeName[16];

	printf("generating and sorting %d nodes ...\n", numNodes);
	fflush(stdout);
	for (x = 0; x < numNodes; x++)
	{
		memset(nodeName, 0x00, sizeof(nodeName));
		//fillRandomBytes(nodeName, sizeof(nodeName));
		snprintf(nodeName, sizeof(nodeName), "sh_center%d", x+1);
		printf("node %d name is: %s\n", x, nodeName);
		hash_ring_add_node(ring, nodeName, sizeof(nodeName));
	}

	printf("ring info: ring->numNodes = %d, ring->numItems = %d, ring->mode = %d\n", ring->numNodes, ring->numItems, ring->mode);


	// print the hash_ring_t
	printf("******************** start printing the hash_ring_t info **************************\n");
	hash_ring_print(ring);	
	printf("******************** end printing the hash_ring_t info **************************\n");

	printf("done\n");
}

void generateKeys(uint8_t *keys, int numKeys, int keySize)
{
	printf("generating keys ...\n");
	fflush(stdout);

	int x;
	for (x = 0; x < numKeys; x++)
	{
		fillRandomBytes(&keys[x], keySize);
	}
	printf("done\n");
}

void runBench(HASH_FUNCTION hash_fn, int numReplicas, int numNodes, int numKeys, int keySize)
{
	char *hash = NULL;
	if (hash_fn == HASH_FUNCTION_MD5)
	{
		hash = "MD5";
	}
	else if (hash_fn == HASH_FUNCTION_SHA1)
	{
		hash = "SHA1";
	}

	printf("----------------------------------------------------\n");
	printf("bench (%s): replicas = %d, nodes = %d, keys: %d, ring size: %d\n", hash, numReplicas, numNodes, numKeys, numReplicas * numNodes);
	printf("----------------------------------------------------\n");
	hash_ring_t *ring = hash_ring_create(numReplicas, hash_fn);

	addNodes(ring, numNodes);

	uint8_t *keys = (uint8_t *)malloc(keySize * numKeys);
	generateKeys(keys, numKeys, keySize);
	printf("keys is %s\n", keys);

	printf("running ...\r");

	uint64_t min = 0;
	uint64_t max = 0;
	uint64_t total = 0;
	int times = 100;

	int x, y;
	for (y = 0; y < times; y++)
	{
		startTiming();
		for (x = 0; x < numKeys; x++)
		{
			assert(hash_ring_find_node(ring, keys + (keySize * x), keySize) != NULL);
		}
		uint64_t result = endTiming();
		if (result > max)
		{
			max = result;
		}
		if (min == 0 || result < min)
		{
			min = result;
		}
		total += result;
	}

	printf("stats: total = %.5fs, avg/lookup: %.5fus, min: %.5fus, max: %.5fus, ops/sec: %.0f\n",
			(double)total / 1000000000,
			(((double)(total / numKeys)) / 1000)/ times,
			(double)min / numKeys / 1000,
			(double)max / numKeys/ 1000,
			1000000000 / ((double)(total / (numKeys * times))));

	free(keys);
	hash_ring_free(ring);


}

void runBenchmark()
{
	printf("Starting benchmark ...\n");
	HASH_FUNCTION hash_fn = HASH_FUNCTION_SHA1;

	runBench(hash_fn, 3, 5, 100, 16);


	hash_fn = HASH_FUNCTION_MD5;

	runBench(hash_fn, 4, 3, 100, 16);
}

int main()
{

	runBenchmark();

	return 0;
}
