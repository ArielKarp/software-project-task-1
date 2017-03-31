/*
 * main.c
 *
 *      Author: Ariel
 */

#include <stdio.h>
#include <stdlib.h>

void printIntArr(int* arr, int len) {
	int i = 0;
	printf("\nArr:\n");
	for (; i < len; ++i) {
		printf("%d ", arr[i]);
	}
}

void printCharArr(char* arr) {
	int i = 0;
	printf("\nArr:\n");
	for (; i < 3; ++i) {
		printf("%c", arr[i]);
	}
}

// p >= 0
int powIm(int num, int p) {
	if (p == 0) {
		return 1;
	} else if (p == 1) {
		return num;
	}
	int index = 0, output = num;
	for (; index < (p - 1); ++index) {
		output = output * num;
	}
	return output;
}

int convertNumberToDecimal(int arrIn[], int sizeOfArry, int inBase) {
	int decimalConvert = 0, index = 0;
	for (; index < sizeOfArry; ++index) {
		decimalConvert = decimalConvert
				+ (arrIn[sizeOfArry - index - 1] * powIm(inBase, index));
		printf("Debug# Decimal: %d, arr[i]: %d, pow: %d\n", decimalConvert,
				arrIn[sizeOfArry - index - 1], powIm(inBase, index));
	}
	return decimalConvert;
}

void reveseArray(int arrIn[], int len) {
	int digit = 0;
	int index = 0;
	int end = 0;
	end = len - 1;
	for (; index < len / 2; index++) {
		digit = arrIn[index];
		arrIn[index] = arrIn[end];
		arrIn[end] = digit;
		end--;
	}
}

// codition: len(arrIn) >= len(arrOut)
void sliceArray(int arrIn[], int arrOut[], int lenOut) {
	int index = 0;
	for (; index < lenOut; ++index) {
		arrOut[index] = arrIn[index];
	}
}

// outArr is zero init of size 32
// return - num of digits, split numDec to array
int convertDecimalToNumber(int numDec, int outArr[], int baseOut) {
	int outNum[32] = { 0 };
	int index = 0;
	int count = 0;
	while (numDec > 0) {
		outNum[index] = numDec % baseOut;
		numDec = numDec / baseOut;
		index++;
	}
	count = index;
	int slicedArr[count];
	sliceArray(outNum, slicedArr, count);
	reveseArray(slicedArr, count);
	printIntArr(slicedArr, count);
	printf("\n");
	index = 0;
	for (; index < count; index++) {
		outArr[index] = slicedArr[index];
	}
	return count;
}

void converDecimalToString(int decNum[], char strOut[], int len) {
	int index =0;
	int digit = 0;
	for(; index < len; ++index) {
		digit = decNum[index];
		if (digit >= 0 && digit < 10) {
			strOut[index] = digit + '0';
		} else {
			strOut[index] = digit + '7';
		}
	}
	strOut[len] = '\0';

}

int int_in(int base, int arr[], int len) {
	for (int i = 0; i < len; i++) {
		if (arr[i] == base)
			return 1;
	}
	return 0;
}

int char_in(char ch, char arr[], int len) {
	for (int i = 0; i < len; i++) {
		if (arr[i] == ch)
			return 1;
	}
	return 0;
}

int main() {

	int baseA;
	int baseB;
	int arrA[32] = { 0 };
	int countNum = 0;
	int decNum;
	int finalNumSize;
	int intChar;
	int invalidNum = 0;
	int optionalBases[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	char optionalChars[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
			'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E', 'e', 'F', 'f' };

	printf("Please enter the number's base:\n");
	scanf("%d", &baseA);
	if (!int_in(baseA, optionalBases,
			sizeof(optionalBases) / sizeof(optionalBases[0]))) {
		printf("Invalid input base\n");
		return 0;
	}

	printf("Please enter the desired base:\n");
	scanf("%d", &baseB);
	if (!int_in(baseB, optionalBases,
			sizeof(optionalBases) / sizeof(optionalBases[0]))) {
		printf("Invalid desired base\n");
		return 0;
	}

	printf("Please enter a number in base %d:\n", baseA);

	getchar();
	while ((intChar = getchar()) != '\n' && intChar != EOF) {
		if (!char_in(intChar, optionalChars,
				sizeof(optionalChars) / sizeof(optionalChars[0]))) {
			printf("Invalid number!\n");
			return 0;
		}

		if (47 < intChar && intChar < 58) {
			arrA[countNum] = intChar - 48;
			if (intChar - 48 >= baseA) {
				invalidNum = 1;
			}
		} else if (64 < intChar && intChar < 71) {
			arrA[countNum] = intChar - 55;
			if (intChar - 55 >= baseA) {
				invalidNum = 1;
			}
		} else {
			arrA[countNum] = intChar - 87;
			if (intChar - 87 >= baseA) {
				invalidNum = 1;
			}
		}
		countNum++;
	}
	if (invalidNum) {
		printf("Invalid number!\n");
	}

	int slicedArr[countNum];
	sliceArray(arrA, slicedArr, countNum);
	printIntArr(slicedArr, countNum);
	printf("\n");
	decNum = convertNumberToDecimal(slicedArr, countNum, baseA);
	printf("Debug# Decimal num: %d\n", decNum);
	finalNumSize = convertDecimalToNumber(decNum, slicedArr, baseB);
	printf("Debug# FinalNumSize: %d\n", finalNumSize);
	char strNum[countNum];
	converDecimalToString(slicedArr, strNum, finalNumSize);
	printf("The result is : %s\n", strNum);

	return 0;
}

