/*
Paige Smith
Professor Hauenstein
Project 3 Description:
Implement a dynamic programming solution to the knapsack problem using either the
bottom-up approach or the memory function (top-down) approach.

*/

#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <string_view>

using namespace std;

void knapsack(int cap, int weight[], int value[], int elements);

int main()
{
    //initialize necessary variables
    fstream infile;
    string file_name = "";
    int cap, elements;
    int* element;
    int* weight;
    int* value;

    cout << "Enter file name to read from: " << endl;
    cin >> file_name;

    infile.open(file_name);

    if (!infile)
    {
        cout << "Unable to open input file." << endl;
        system("pause");
        return 1;
    }

    //read in capacity of items and number of items
    infile >> cap;
    infile>> elements;

    weight = new int[elements];
    element = new int[elements];
    value = new int[elements];

    //read weights and values from the input file
    for (int i = 0; i < elements; i++)
    {
        infile >> weight[i];
        infile >> value [i];
    }

    int p = 1;
    //set up item array from 1 to amount of items
    for (int i = 0; i <= elements; i++)
    {
        element[i] = p;
        p++;
    }

    //output details
    cout << endl << "Problem Details: " << endl
         << "Knapsack Capacity: " << cap << endl
         << "Items: " << elements << endl
         << "item" << setw(7) << "weight" << setw(7)
         << "value" << endl;

    for (int i = 0; i < elements; i++)
    {
        cout << setw(4) << element[i] << setw(7) << weight[i] << setw(7) << value[i] << endl;
    }

    //call knapsack fucntion
    knapsack(cap, weight, value, elements);


    infile.close();
    system("pause");
    return 0;
}


//////////////////////////////FUNCTIONS///////////////////////////

void knapsack(int cap, int weight[], int value[], int elements)
{
    //create 2d array and other required variables
    int ** k = new int*[elements + 1];
    int result;

    for (int i = 0; i < (elements + 1); i++)
    {
        k[i] = new int[cap +1];
    }

    for (int i = 0; i <= elements; i++)
    {
        for (int w = 0; w <= cap; w++)
        {
            if (i == 0 || w ==0)
            {
                //sets all values in 2D array to zero
                k[i][w] = 0;
            }

            else if (weight[i-1] <= w) //see if item fits
            {
                //determine if item should be added
                k[i][w] = max(value[i-1] + k[i-1][w-weight[i-1]], k[i-1][w]);
            }

            else
            {
                //item didn't fit and isn't added
                k[i][w] = k[i-1][w];
            }
        }
    }

    cout << endl << "Solution Table: " << endl;
    //print the solution table
    for (int i = 0; i <=elements; i++)
    {
        for (int j = 0; j <= cap; j++)
        {
            //format and print element of array
            cout << setw(3) << k[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    //backtracking
    result = k[elements][cap];
    int w = cap;
    int num = 5;
    for (int i = elements; i > 0 && result > 0 && w != 0; i--)
    {
        num--;

        if (result ==k[i-1][w])
        {
            cout << "Item " << num << " was not included" << endl;
        }
        else 
        {
            cout << "Item " << num << " was included" << endl;
            //final value and weight for next item
            result = result - value[i - 1];
            w = w - weight[i - 1];
        }
    }

    return;
}


