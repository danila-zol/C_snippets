/*
 * Implementation of a binary search.
 *
 * binary_search is a general function that takes a function pointer for
 * doing comparisons and works on any datatype similar to bsearch in the
 * C standard library.
 *
 * binary_search_int is simpler, but only works on integers.
 */

#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

void *binary_search(void *arr, size_t len, void* val, size_t val_size, bool (*cmp)(void *, void *))
{
	size_t low = 0, high = len;

	while (low <= high) {
		size_t mid = (low + high) / 2;
		void *guess = arr + mid * val_size;

		if (memcmp(guess, val, val_size) == 0) {
			return guess;
		}

		if (cmp(guess, val)) {
			high = mid - 1;
		} else {
			low = mid + 1;
		}

	}

	return NULL;
}

bool cmp_int(void *i1, void *i2)
{
	return *((int *) i1) > *((int *) i2);
}

long int binary_search_int(int *arr, size_t len, int val)
{
	size_t low = 0, high = len - 1;

	while (low <= high) {
		size_t mid = (low + high) / 2;
		int guess = arr[mid];

		if (guess == val) {
			return mid;
		}

		if (guess > val) {
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}

	return -1;
}
