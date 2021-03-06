// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <immintrin.h>
#include <stdio.h>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

/**
* Expected Result: A vector with the following values:<100 200 300 400 500 0 0 0> each of which are printed to the console (all on same line).
*/
int maskLoadEx() {

	int int_array[8] = { 100, 200, 300, 400, 500, 600, 700, 800 };

	/* Initialize the mask vector */
	__m256i mask = _mm256_setr_epi32(-20, -72, -48, -9, -100, 3, 5, 8);

	/* Selectively load data into the vector */
	__m256i result = _mm256_maskload_epi32(int_array, mask);

	/* Display the elements of the result vector */
	int* res = (int*)&result;
	printf("%d %d %d %d %d %d %d %d\n",
		res[0], res[1], res[2], res[3], res[4], res[5], res[6], res[7]);

	return 0;
}

/**
* Expected Result: A vector containing the following values: <5.0 19.0 5.0 19.0> each of which are printed to the console (all on same line).
*	
*/
int fusedMultiplyEx() {

	__m256d veca = _mm256_setr_pd(6.0, 6.0, 6.0, 6.0);

	__m256d vecb = _mm256_setr_pd(2.0, 2.0, 2.0, 2.0);

	__m256d vecc = _mm256_setr_pd(7.0, 7.0, 7.0, 7.0);

	/* Alternately subtract and add the third vector
	from the product of the first and second vectors */
	__m256d result = _mm256_fmaddsub_pd(veca, vecb, vecc);

	/* Display the elements of the result vector */
	double* res = (double*)&result;
	printf("%lf %lf %lf %lf\n", res[0], res[1], res[2], res[3]);

	return 0;
}

/**
* Expected Result: A vector with elements all equal to 1.0. Each of which are printed to the console (all on same line).
*/
int subtractEx() {

	/* Initialize the two argument vectors */
	__m256 evens = _mm256_set_ps(2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0);
	__m256 odds = _mm256_set_ps(1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0);

	/* Compute the difference between the two vectors */
	__m256 result = _mm256_sub_ps(evens, odds);

	/* Display the elements of the result vector */
	float* f = (float*)&result;
	printf("%f %f %f %f %f %f %f %f\n",
		f[0], f[1], f[2], f[3], f[4], f[5], f[6], f[7]);

	return 0;
}

/**
* Expected Result: A vector containing the following elements: <21.0 57.0 36.0 127.0>  Each of which are printed to the console (all on same line).
*/
int complexMultEx() {

	__m256d vec1 = _mm256_setr_pd(4.0, 5.0, 13.0, 6.0);
	__m256d vec2 = _mm256_setr_pd(9.0, 3.0, 6.0, 7.0);
	__m256d neg = _mm256_setr_pd(1.0, -1.0, 1.0, -1.0);

	/* Step 1: Multiply vec1 and vec2 */
	__m256d vec3 = _mm256_mul_pd(vec1, vec2);

	/* Step 2: Switch the real and imaginary elements of vec2 */
	vec2 = _mm256_permute_pd(vec2, 0x5);

	/* Step 3: Negate the imaginary elements of vec2 */
	vec2 = _mm256_mul_pd(vec2, neg);

	/* Step 4: Multiply vec1 and the modified vec2 */
	__m256d vec4 = _mm256_mul_pd(vec1, vec2);

	/* Horizontally subtract the elements in vec3 and vec4 */
	vec1 = _mm256_hsub_pd(vec3, vec4);

	/* Display the elements of the result vector */
	double* res = (double*)&vec1;
	printf("%lf %lf %lf %lf\n", res[0], res[1], res[2], res[3]);

	return 0;
}


int main() {
	high_resolution_clock::time_point startTime = high_resolution_clock::now();
	subtractEx();
	high_resolution_clock::time_point endTime = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(endTime - startTime).count();
	cout << "Duration: " << duration << "\n";

	startTime = high_resolution_clock::now();
	maskLoadEx();
	endTime = high_resolution_clock::now();
	duration= duration_cast<microseconds>(endTime - startTime).count();
	cout << "Duration: " << duration << "\n";
	
	startTime = high_resolution_clock::now();
	fusedMultiplyEx();
	endTime = high_resolution_clock::now();
	duration = duration_cast<microseconds>(endTime - startTime).count();
	cout << "Duration: " << duration << "\n";

	startTime = high_resolution_clock::now();
	complexMultEx();
	endTime = high_resolution_clock::now();
	duration = duration_cast<microseconds>(endTime - startTime).count();
	cout << "Duration: " << duration << "\n";
}
