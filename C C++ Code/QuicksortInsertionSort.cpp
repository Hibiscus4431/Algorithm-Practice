/*
Paige Smith
Professor Hauenstein
Project 2 description:
Implement quicksort and insertionsort algorithms to count how many three-way comparisons
are done by each when used for various inputs. Use either Hoare's or Lomuto's partitions
for quicksort using the first element as the pivot point. 

*/

#include <iostream>
#include <string>
#include <array>
#include <iomanip>
#include <algorithm>
#include <fstream>

using namespace std;

//function and global variable initialization
int lomutopart(int array[], int low, int high);
void quickSort(int array[], int low, int high, int arraysize);
void worstQuick(int array[], int arraysize);
void insertionSort(int array[], int arraysize);
void worstInsert(int array[], int arraysize);

int quickcount = 0;

int main()
{
    //variable declaration
    ifstream infile;
    int arraysize = 0;

    //read in integer file and check if correct
    infile.open("C:/Users/Paige/OneDrive/Documents/CS317/500RandomInts.txt");

    //confirm file opened properly
    if (!infile)
    {
        cout << "Unable to open random integers file. Exiting program."
            << endl;
        system("pause");
        return 1;
    }
    cout << "File opened successfully." << endl << endl;

    //request user input for array size
    cout << "Enter a size for a random integer array: ";
    cin >> arraysize;

    //make two arrays of same given size to run through both sorting algorithms
    int array1[arraysize];
    int array2[arraysize];
    for (int a = 0; a < arraysize; a++)
    {
        infile >> array1[a];
    }
    infile.close();

    //reopen file to start from beginning for array 2
    infile.open("C:/Users/Paige/OneDrive/Documents/CS317/500RandomInts.txt");
    if(!infile)
    {
        cout << "Unable to open random integers file. Exiting program."
            << endl;
        system("pause");
        return 2;
    }
    cout << "File opened successfully (2)." << endl;

    //make second array
    for (int b = 0; b < arraysize; b++)
    {
        infile >> array2[b];
    }
    infile.close();



    //variables for sorting function calls
    int low = 0;
    int high = arraysize-1;

    //run quicksort
    quickSort(array1, low, high, arraysize);
    cout << "The number of comparisons for quicksort for an array of size " << arraysize
        << " is " << quickcount << endl;

    //run insertion sort
    insertionSort(array2, arraysize);
    
    //run worst case quicksort
    worstQuick(array1, arraysize);

    cout<< "test"<< endl;

    //run worst case insertion sort
    worstInsert(array2, arraysize);


    system("pause");
    return 0;
}

////////////////////////////////////////////////////////////
//                    FUNCTIONS                           //
////////////////////////////////////////////////////////////

int lomutopart(int array[], int low, int high)
{
    int pivot = array[high]; 
    int index = low-1;

    for (int current = low; current <= high-1; current++)
    {
        if (array[current] <= pivot)
        {
            index++;
            //swap and count the comparison made
            swap(array[index], array[current]);
            quickcount++;
        }
    }

    //swap and count the comparison made
    swap(array[index+1], array[high]);
    quickcount++;
    return(index+1);
}


void quickSort(int array[], int low, int high, int arraysize)
{
    //low being the first element of the array
    //high being the last element - 1 of the array
    //count number of times quicksort called
    quickcount++;
    if(low >= high)
    {
        return;
    }
    else
    {
        //run partitioning algorithm
        int pivot = lomutopart(array, low, high);
        //call function recursively until if condition met
        quickcount++;
        quickSort(array, low, pivot-1, arraysize);
        quickSort(array, pivot+1, high, arraysize);
    }

    return;
}

void worstQuick(int array[], int arraysize)
{
    //sort array into ascending order because we use
    //the array[0] as our pivor point
    //then run quicksort algorithm to find number of comparisons
    sort(array,array+arraysize);

    int low = 0;
    int high = arraysize-1;

    //run quicksort algorithm to count number of comparisons
    quickSort(array, low, high, arraysize);

    cout << "For Worst Case Quicksort: " << endl;
    cout << "The number of comparisons for quicksort for an array of size " << arraysize
        << " is " << quickcount << endl;

    return;
}

void insertionSort(int array[], int arraysize)
{
    //initialize variables
    int currelement = 0;
    int compelement = 0;
    int compcount = 0;

    //loop through array
    for (int i = 1; i < arraysize - 1; i++)
    {
        //set pivot point
        currelement = array[i];
        compelement = i - 1;

        while (compelement >= 0 && array[compelement] > currelement)
        {
            //run comparisons and swaps
            array[compelement+1] = array[compelement];
            compelement = compelement - 1;
            compcount++;
        }

        array[compelement+1] = currelement;
        compcount++;
    }

    cout << "The number of comparisons for insertion sort for list size " << arraysize
        << " is " << compcount << endl;

    return;
}

void worstInsert(int array[], int arraysize)
{
    //sort the array in descending order, then call insertion sort to resort array
    int temp;

    //run for loop for descending sorted array
    for (int i = 0; i < arraysize; i++)
    {
        for (int j = i+1; j < arraysize; j++)
        {
            //compare array elements and swap 
            if(array[i] < array[j])
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    //array is now in descending order, call insertion sort function for number of comparisons
    cout << "For Worst Case Insertion Sort: " << endl;
    insertionSort(array, arraysize);

    return;
}