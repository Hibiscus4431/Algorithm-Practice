// Memory/pointer practice

#include <iostream>
using namespace std;

// int main()
// {
//     int n = 5;
//     // Dynamic memory allocation to compute squares
//     int *arr = new int[n];
//     for (int i = 0; i < n; i++)
//         arr[i] = i * i;

//     for (int i = 0; i < n; i++)
//         cout << arr[i] << " ";

//     delete[] arr; // Free allocated memory
// }

// Projectile class
#include <cmath>

class Projectile
{
    double vel, angle;

public:
    // Constructor
    Projectile(double vel, double angle)
    {
        this->vel = vel;
        this->angle = angle;
    }

    // Function to compute position at time t
    pair<double, double> position(double t)
    {
        double g = 9.81;
        // Kinematic equations
        double x = vel * cos(angle) * t;
        double y = vel * sin(angle) * t - 0.5 * g * t * t;
        return {x, y};
    }
};

int main()
{
    Projectile p(50, 45);
    auto pos = p.position(2);
    cout << pos.first << " " << pos.second << endl;
    return 0;   
}