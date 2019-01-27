//  SortingTests.cpp
//  Project 5: Sorting
//  Created by Harneet Kaur on 11/24/18.
//  This program will generate various types of arrays (random, in-order ascending, in-order descending, last ten random, and random using nums 0-9).
//  Using the generatable array it can sort them using selection sort, insertion sort, or merge sort.
//  Lastly this program will measure the average runtime of the sorting function on the various array over 10 runs.
//  The goal of this program is to analyze different sorting algorithms by time and space. You can see which algorithms work better on different sizes and inputs.

#include <cstring>
#include <stdio.h>
#include <numeric>
#include "SortingTests.hpp"

using std::cout;
using std::endl;

/*****************************************************************/
/********************* SORTING FUNCTIONS *************************/
/*****************************************************************/

//Sorts a given array in ascending order.
void selectionSort(int a[], size_t size){
    for (int i = 0; i < size-1; i++){
        int small = i;
        for (int j = i+1; j < size; j++){
            if (a[j] < a[small])
                small = j;
        }
        //Swap two elements:
        int temp = a[i];
        a[i] = a[small];
        a[small] = temp;
    }
}

//Sorts an array in ascending order using the insertion sort algorithm.
//Maintains a 'sublist' whish is sorted.
void insertionSort(int a[], size_t size){
    int i, j, num;
    for (i = 1; i < size; i++){
        num = a[i];
        for (j = i-1; j >= 0 && a[j] > num; j--){
            a[j+1] = a[j];
        }
        a[j+1] = num;
    }
}

/**
 @post Sorts the elements in a range of a array.
 @param a the array with the elements to sort
 @param from the first position in the range to sort
 @param to the last position in the range to sort (included)
 */
void mergeSort(int a[], int from, int to){
    int middle;
    if (from < to){
        middle=(from+to)/2;
        mergeSort(a, from, middle);
        mergeSort(a, middle+1, to);
        
        // We have low to mid and mid+1 to high already sorted.
        int i, j, k;
        int *temp = new int[to-from+1];
        i = from;
        k = 0;
        j = middle + 1;
        
        // Merge the two parts into temp[].
        while (i <= middle && j <= to){
            if (a[i] < a[j]){
                temp[k] = a[i];
                k++;
                i++;
            }
            else{
                temp[k] = a[j];
                k++;
                j++;
            }
        }
        
        // Insert all the remaining values from i to mid into temp[].
        while (i <= middle){
            temp[k] = a[i];
            k++;
            i++;
        }
        
        // Insert all the remaining values from j to high into temp[].
        while (j <= to){
            temp[k] = a[j];
            k++;
            j++;
        }
        
        // Assign sorted data stored in temp[] to a[].
        for (i = from; i <= to; i++){
            a[i] = temp[i-from];
        }
        delete [] temp;
    }
}

/*********************************************************************/
/****************** ARRAY POPULATING FUNCTIONS ***********************/
/*********************************************************************/

//Generates an array of random numbers corresponding to the size.
void generateRandomArray(int values[], size_t size){
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < size; i++){
        values[i] = rand() % size;
    }
}

//Generates an array on numbers in ascending order.
//The array will range from 1 to the size of array.
void generateAscendingArray(int values[], size_t size){
    std::iota(values, values+size, 1); 
}

//attempted with iota-rbegin, rend - didn't work
//Generates an array of numbers in descending order.
//The array will range from the size of the array to 1.
void generateDescendingArray(int values[], size_t size){
    int count = (int) size; //cast size to int
    for (int i = count; count > 0; count--){
        values[i] = count;
    }
}

//Generates an array of numbers in ascending order till the last ten numbers.
//The last ten numbers of the array will random.
void generateLastTenRandomArray(int values[], size_t size){
    std::iota(values, values+size, 1);
    int count = (int) size;
    srand(static_cast<unsigned>(time(0)));
    for (int i = count-10; i < size; i++){
        values[i] = rand() % count;
    }
}

//Generates an array of size and populates it randomly with numbers 0-9.
/**
 @post Populates values with integers in randomly generated in range size/10
 @param values the array to populate
 @param size of the array to be populated
 */
void generateFewRandomArray(int values[], size_t size){
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < size; i++){
        values[i] = rand() % (size/10);
    }
}


/*****************************************************************/
/****************** RUNTIME TEST FUNCTIONS ***********************/
/*****************************************************************/


/**
 @post Sorts values in ascending order and averages its runtime over 10 runs
 @param sortingFunction the function used to sort the array
 @param values the array to sort
 @param size of the array to sort
 @return the average runtime in microseconds
 */
double sortTest(void (*sortingFunction)(int a[], size_t size), int values[], size_t size){
    float runTimeSum = 0;
    for (int i = 0; i < 10; i++){
        int *duplicate = new int[size];
        std::copy(values, values+size, duplicate); //Create a copy of array to be sorted.
        
        auto startTime = high_resolution_clock().now();
        (*sortingFunction)(duplicate, size);
        auto endTime = high_resolution_clock().now();
        duration<float, std::micro> runTime = duration_cast<microseconds>(endTime - startTime);
        runTimeSum += runTime.count();
        
        delete [] duplicate;
    }
    return runTimeSum/10;
}

/**
 @post Sorts values in ascending order using mergeSort and averages its runtime over 10 runs
 @param values the array to sort
 @param size of the array to sort
 @return the average runtime in microseconds
 */
double mergeSortTest(int values[], size_t size){
    float runTimeSum = 0;
    for (int i = 0; i < 10; i++){
        int *duplicate = new int[size];
        std::copy(values, values+size, duplicate);
        auto startTime = high_resolution_clock().now();
        mergeSort(values, 0, size);
        auto endTime = high_resolution_clock().now();
        duration<float, std::micro> runTime = duration_cast<microseconds>(endTime - startTime);
        runTimeSum += runTime.count();
        
        delete [] duplicate;
    }
    return runTimeSum/10;
}
