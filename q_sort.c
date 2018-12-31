#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "max_min.h"
#include <stdint.h>

int get_median_of_three(int array[], int *first, int *last)
{
	int middle = (last - first) / 2;

	int important_values[3] = { *first, *(first + middle), *last };
	int sum = 0;

	int *start = important_values;
	int *end = important_values + 3;

	while (start < end) {
		sum += *start;
		start++;
	}

	return sum - max(important_values, 3) - min(important_values, 3);
}


int get_median_of_three_idx(int array[], int *first, int *last)
{
	int median_of_three = get_median_of_three(array, first, last);

	while (first <= last) {
		if (*first == median_of_three)
			return first - array;
		first++;
	}
}

void swap_pivot_with_median(int array[], int *first, int median_idx, int pivot)
{
	int temporary_value = *first;

	*first = pivot;
	*(array + median_idx) = temporary_value;
}

int *partition(int *array, int *first, int *last, int median_idx)
{
	int8_t done = -1;

	int pivot = *(array + median_idx);
	swap_pivot_with_median(array, first, median_idx, pivot);

	int temporary_value = 0;
	
	int *left_ptr = first + 1;
	int *right_ptr = last;

	while (done == -1) {
		while (*left_ptr <= pivot && left_ptr <= right_ptr)
			left_ptr++;
		
		while (*right_ptr >= pivot && right_ptr >= left_ptr)
			right_ptr--;

		if (right_ptr < left_ptr)
			done = 1;
		else {
			temporary_value = *left_ptr;
			*left_ptr = *right_ptr;
			*right_ptr = temporary_value;
		}
	}

	temporary_value = *right_ptr;
	*right_ptr = *(first);
	*(first) = temporary_value;

	return right_ptr;
}


void quick_sort(int array[], int *first, int *last)
{

	if (first < last) {
		int median_idx = get_median_of_three_idx(array, first, last);

		int *split_point = partition(array, first, last, median_idx);

		quick_sort(array, first, split_point - 1);
		quick_sort(array, split_point + 1, last);
	}
	
}

void init_array(int* array, int size)
{
	int *end = array + size;
	int *start = array;

	srand(time(0));

	while (start < end) {
		*start = rand() % 100 - 1;
		start++;
	}
}

int main(void)
{
	char buffer[12];
	int size = 0, sscanf_error_handler = 0;
	int *array;

	printf("Type the size of an array: ");

	if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
		fprintf(stderr, "%s\n", "Typed value is incorrect.");
		return -1;
	} 
	else {
		sscanf_error_handler = sscanf(buffer, "%d", &size);
		if (sscanf_error_handler != 1 || size < 1) {
			fprintf(stderr, "%s\n", "The size of an array must be the positive number.");
			return -1; 
		}
	}

	array = (int *)malloc(size * sizeof(int));

	if (array == NULL) {
		fprintf(stderr, "%s\n", "Memory allocation failed.");
		return -1;
	}
	else {
		init_array(array, size);

		int *start = array;
		int *end = array + size;

		while (start < end) {
			printf("%d\t", *start);
			fflush(stdout);
			start++;
		}

		putchar('\n');

		quick_sort(array, &array[0], array + (size - 1));

		start = array;
		end = array + size;

		while (start < end) {
			printf("%d\t", *start);
			start++;
		}

		putchar('\n');
	}

	free(array);
	return 0;
}