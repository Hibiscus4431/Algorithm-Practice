#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    // STL vector and sort example for efficiency
    vector<int> nums = {5, 3, 9, 1};
    sort(nums.begin(), nums.end());
    for (int n : nums)
        cout << n << " ";
}