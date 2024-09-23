#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void print_array(int *arr, size_t len);

inline static void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

inline static int partition(int *arr, size_t low, size_t high)
{
	int pivot_index = low + (rand() % (high - low));
	swap(&arr[pivot_index], &arr[high]);

	int pivot = arr[high];
	int i = low;

	for (int j = low; j < high; j++) {
		if (arr[j] < pivot) {
			swap(&arr[i++], &arr[j]);
		}
	}

	swap(&arr[i], &arr[high]);
	return i;
}

inline static void quicksort_step(int *arr, int low, int high)
{
	if (low >= high) {
		return;
	}

	int pivot_index = partition(arr, low, high);
	quicksort_step(arr, low, pivot_index - 1);
	quicksort_step(arr, pivot_index + 1, high);
}

void quicksort(int *arr, size_t len) 
{
	srand(time(NULL));
	quicksort_step(arr, 0, len - 1);
}

void print_array(int *arr, size_t len)
{
	printf("Array[");
	for (int n = 0; n < len; n++) {
		printf(n != len - 1 ? "%d, " : "%d", arr[n]);
	}
	printf("]\n");
}

inline static int test_step()
{
	int len = rand() % 7777; 
	printf("Array length: %d\n", len);
	int *arr = malloc(len * sizeof(int));
	for (int n = 0; n < len; n++) {
		arr[n] = rand();
	}
	quicksort(arr, len);

	int e1 = arr[0], e2;
	for (int n = 1; n < len; n++) {
		e2 = arr[n];
		if (e1 > e2) {
			printf("Array is not sorted at %d\n", e1);
			return 0;
		}
		e1 = e2;
	}

	puts("\nArray is sorted correctly.");
	return 1;
}

int test() {
	srand(time(NULL));
	for (int n = 0; n < 10; n++) {
		if (!test_step()) {
			printf("Test %d failed\n", n);
			return 0;
		}
	}

	printf("All test succeeded\n");
	return 1;
}

int main()
{
	test();

	return 0;
}
