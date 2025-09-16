/*
Paige Smith
Professor Hauenstein
Project 1 description:
Implement both binary search and sequential (a.k.a linear) search on a
set of given integers. Read in the integers and created sorted lists,
then implement each search algorithm and count the amount of comparisons
for each. Do this for 10 different varying list lengths.


*/
#include <iomanip>
#include <string_view>
#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <functional>
#include <algorithm>

using namespace std;

void sequentialSearch(int array[], int key[], int arraysize);
void binarySearch(int array[], int key[], int arraysize);

int main()
{
    ifstream infile;
    int arraysize = 0;

    //open random integers file
    infile.open("C:/Users/Paige/OneDrive/Documents/CS317/500RandomInts.txt");
    //check if file opened properly
    if(!infile)
    {
        cout << "Unable to open random integers file. Exiting program."
            << endl;
        system("pause");
        return 1;
    }
    cout << "File opened successfully." << endl;

    //request user input for array size
    cout << "Enter a size for a random int array: ";
    cin >> arraysize;

    //make two arrays of same given size and fill with same random integers from file
    int array1[arraysize];
    int array2[arraysize];
    for (int a = 0; a < arraysize; a++)
    {
        infile >> array1[a];
    }
    infile.close();

    //repeat above and file opening for array2
    infile.open("C:\\Users\\Paige\\Documents\\GitHub\\Skills-Lab\\C C++ Code\\500RandomInts.txt");
    if(!infile)
    {
        cout << "Unable to open random integers file. Exiting program."
            << endl;
        system("pause");
        return 2;
    }
    cout << "File opened successfully (2)." << endl;

    for (int b = 0; b < arraysize; b++)
    {
        infile >> array2[b];
    }
    infile.close();

    //sort one array to compare against
    sort(array1, array1+arraysize);

    //compare array2 keys against array1 elements
    //prints out number of comparisons in function and average
    binarySearch(array1,array2,arraysize);
    sequentialSearch(array1,array2,arraysize);


    return 0;
}

////////////////Functions////////////////

//function for sequential search
void sequentialSearch(int array[], int key[], int arraysize)
{
    //nonrecursive sequential search using loops to go through key and elements
    //Input: int array[] will be list that int key will be compared against, arraysize
    //  for loop parameters
    //Output: number of comparisons done with given array and key
    int comps = 0;
    double average = 0;
    int comparisons[arraysize];
    cout << setprecision(3) << fixed;

    //outer loop to go through key array
    //inner loop to compare key array to sorted array, count comparisons
    for (int k = 0; k < arraysize; k++)
    {
        comps = 0;

        for (int j = 0; j < arraysize; j++)
        {
            if (key[k]==array[j])
            {
                comps++;
                break;
            }
            else 
            {
                comps++;
            }
        }
        comparisons[k] = comps;
    }

    //loop to count sum of comparisons
    for (int i = 0; i < arraysize; i++)
    {
        average = average + comparisons[i];
    }

    average = average/arraysize;

    cout << "Number of comparisons for Sequential Search for list of " << arraysize 
        << " elements is: " << average << endl;
    return;
}

//function for binary search
void binarySearch(int array[], int key[], int arraysize)
{
    //nonrecursive binary search based off in-class pseudocode
    //Input: int array[] will be list that int key will be compared against, arraysize
    //  for loop parameters
    //output: number of comparisons done with given array and key
    int left = 0;
    int right = arraysize-1;
    int middle;
    int comps = 0;
    double average = 0;
    int comparisons[arraysize];
    cout << setprecision(3) << fixed;

    //for loop to go through keys array
    for (int a = 0; a < arraysize; a++)
    {
        //reset numbers for next key
        left = 0;
        right = arraysize;
        comps = 0;

        //while loop to compare
        while (left <= right)
        {
            middle = (left+right)/2;
            if (key[a] == array[middle])
            {
                comps++;
                break;
            }
            else if (key[a] < array[middle])
            {
                right = middle-1;
                comps++;
            }
            else
            {
                left = middle+1;
                comps++;
            }
        }
        comparisons[a] = comps;
    }

    //loop through comparisons array to make sum for average
    for (int b = 0; b < arraysize; b++)
    {
        average = average + comparisons[b];
    }

    average = average/arraysize;

    cout << "Number of average comparisons for Binary Search for list of " << arraysize 
        << " elements: " << average << endl;
    return;
}