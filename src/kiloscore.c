#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>

#define FIB_N 45  // Number of Fibonacci numbers to compute
#define MAX_THREADS 32  // Maximum number of threads for multi-core test
#define REPEAT_COUNT 100000  // Number of times to compute Fibonacci per thread
#define RUNS 50  // Number of times to run the benchmark and average results

volatile uint64_t result = 0; // Prevent compiler optimization

uint64_t fibonacci(int n) {
	if (n <= 1) return n;
	uint64_t a = 0, b = 1, temp;
	for (int i = 2; i <= n; i++) {
		temp = a + b;
		a = b;
		b = temp;
	}
	return b;
}

void *benchmark(void *arg) {
	uint64_t local_result = 0;
	for (int i = 0; i < REPEAT_COUNT; i++) {
		local_result += fibonacci(FIB_N); // Compute Fibonacci number iteratively
	}
	result += local_result; // Store result to prevent optimization
	return NULL;
}

uint64_t run_benchmark(int num_threads) {
	pthread_t threads[num_threads];
	struct timespec start, end;

	clock_gettime(CLOCK_MONOTONIC, &start);
	for (int i = 0; i < num_threads; i++) {
		pthread_create(&threads[i], NULL, benchmark, NULL);
	}
	for (int i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &end);

	return (end.tv_sec - start.tv_sec) * 1000000000ULL + (end.tv_nsec - start.tv_nsec);
}

int main() {
	uint64_t runtime_ns = 0;

	printf("Running single-core benchmark ...\n");
	uint64_t single_core_runtime_total = 0;
	uint64_t single_core_runtimes[RUNS];
	for (int i = 0; i < RUNS; i++) {
		runtime_ns = run_benchmark(1);
		single_core_runtimes[i] = runtime_ns;
		single_core_runtime_total += runtime_ns;
		if (i % 10 == 0) {
			printf("\tRun #%2d finished in %lu ns\n", i+1, runtime_ns);
		}
	}
	uint64_t single_core_time = single_core_runtime_total / RUNS;
	printf("\t\tSingle-core average execution time: %lu ns\n", single_core_time);

	printf("Running multi-core benchmark ...\n");
	uint64_t multi_core_runtime_total = 0;
	uint64_t multi_core_runtimes[RUNS];
	for (int i = 0; i < RUNS; i++) {
		runtime_ns = run_benchmark(MAX_THREADS);
		multi_core_runtimes[i] = runtime_ns;
		multi_core_runtime_total += runtime_ns;
		if (i % 10 == 0) {
			printf("\tRun #%2d finished in %lu ns\n", i+1, runtime_ns);
		}
	}
	uint64_t multi_core_time = multi_core_runtime_total / RUNS;
	printf("\t\tMulti-core average execution time (%d threads): %lu ns\n", MAX_THREADS, multi_core_time);

	// Compute a relative score (lower time = higher score)
	double multiplier = 50.0 * 1000.0 * 1000.0;
	double single_core_score = multiplier / single_core_time;
	double multi_core_score = multiplier * MAX_THREADS / multi_core_time;

	printf("Single-core average score: %.2f\n", single_core_score);
	printf("Multi-core average score: %.2f\n", multi_core_score);
	if (result < 10) {
		// This will almost certainly never be printed
		printf("Final accumulated result (ignore this, for optimization prevention): %lu\n", result);
	}

	return 0;
}
