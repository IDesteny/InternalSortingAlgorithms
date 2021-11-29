#pragma once
#include <windows.h>

typedef VOID(*OUT_DATA_CALLBACK)(PINT, INT);

VOID
BubbleSort(
	PINT arr,
	INT size,
	PINT comp,
	PINT perm,
	PULONGLONG time,
	OUT_DATA_CALLBACK callback);

VOID
SelectionSort(
	PINT arr,
	INT size,
	PINT comp,
	PINT perm,
	PULONGLONG time,
	OUT_DATA_CALLBACK callback);

VOID
InclusionSort(
	PINT arr,
	INT size,
	PINT comp,
	PINT perm,
	PULONGLONG time,
	OUT_DATA_CALLBACK callback);

VOID
ShellSort(
	PINT arr,
	INT size,
	PINT comp,
	PINT perm,
	PULONGLONG time,
	OUT_DATA_CALLBACK callback);

VOID
LinearSort(
	PINT arr,
	INT size,
	PINT comp,
	PINT perm,
	PULONGLONG time,
	OUT_DATA_CALLBACK callback);