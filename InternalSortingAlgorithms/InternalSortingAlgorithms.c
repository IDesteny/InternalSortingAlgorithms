#include "InternalSortingAlgorithms.h"

VOID
BubbleSort(
	PINT arr,
	INT size,
	PINT comp,
	PINT perm,
	PULONGLONG time,
	OUTPUT_DATA_CALLBACK callback)
{
	INT tmp, _comp = 0, _perm = 0;
	ULONGLONG t = GetTickCount64();

	for (INT i = 0; i < size - 1; ++i)
	{
		for (INT j = 0; j < size - i - 1; ++j)
		{
			++_comp;
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				++_perm;
			}
		}

		if (callback) callback(arr, size);
	}

	if (time) *time = GetTickCount64() - t;
	if (comp) *comp = _comp;
	if (perm) *perm = _perm;
}

VOID
SelectionSort(
	PINT arr,
	INT size,
	PINT comp,
	PINT perm,
	PULONGLONG time,
	OUTPUT_DATA_CALLBACK callback)
{
	INT min, temp, _comp = 0, _perm = 0;
	ULONGLONG t = GetTickCount64();

	for (INT i = 0; i < size - 1; ++i)
	{
		min = i;

		for (INT j = i + 1; j < size; ++j)
		{
			++_comp;
			if (arr[j] < arr[min])
			{
				min = j;
			}
		}

		temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
		++_perm;

		if (callback) callback(arr, size);
	}

	if (time) *time = GetTickCount64() - t;
	if (comp) *comp = _comp;
	if (perm) *perm = _perm;
}

VOID
InclusionSort(
	PINT arr,
	INT size,
	PINT comp,
	PINT perm,
	PULONGLONG time,
	OUTPUT_DATA_CALLBACK callback)
{
	INT key, j, _comp = 0, _perm = 0;
	ULONGLONG t = GetTickCount64();

	for (INT i = 1; i < size; ++i)
	{
		key = arr[i];
		j = i - 1;

		while (++_comp && j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			--j;
		}

		arr[j + 1] = key;
		++_perm;

		if (callback) callback(arr, size);
	}

	if (time) *time = GetTickCount64() - t;
	if (comp) *comp = _comp;
	if (perm) *perm = _perm;
}

VOID
ShellSort(
	PINT arr,
	INT size,
	PINT comp,
	PINT perm,
	PULONGLONG time,
	OUTPUT_DATA_CALLBACK callback)
{
	INT tmp, j, _comp = 0, _perm = 0;
	ULONGLONG t = GetTickCount64();

	for (INT gap = size >> 1; gap; gap >>= 1)
	{
		for (INT i = gap; i < size; ++i)
		{
			tmp = arr[i];

			for (j = i; ++_comp && j >= gap && arr[j - gap] > tmp; j -= gap)
				arr[j] = arr[j - gap];

			arr[j] = tmp;
			++_perm;
		}

		if (callback) callback(arr, size);
	}

	if (time) *time = GetTickCount64() - t;
	if (comp) *comp = _comp;
	if (perm) *perm = _perm;
}

VOID
LinearSort(
	PINT arr,
	INT size,
	PINT comp,
	PINT perm,
	PULONGLONG time,
	OUTPUT_DATA_CALLBACK callback)
{
	INT min, index, k, _comp = 0, _perm = 0;

	for (INT i = 0; i < size - 1; ++i)
	{
		min = arr[i];
		index = i;

		for (INT j = i + 1; j < size; ++j)
		{
			if (min > arr[j])
			{
				min = arr[j];
				index = j;
			}
		}

		k = arr[i];
		arr[i] = min;
		arr[index] = k;

		if (callback) callback(arr, size);
	}

	if (time) *time = 0;
	if (comp) *comp = _comp;
	if (perm) *perm = _perm;
}