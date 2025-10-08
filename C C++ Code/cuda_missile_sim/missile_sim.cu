/*

 Author: Paige Smith
 Date: October 2025
 Project Name: missile_sim.cu
 Description:
    Simulate N independent missiles in 2D (x, y) where each
    missile has position, velocity, mass, drag coefficient,
    and optimal thrust. Skills goal: Use CUDA to parallelize
    the simulation of the missiles.
 Tools: Nvidia GPU, CUDA Toolkit, Python, C++
 This was made with the guidance of OpenAI for mathematical equations and code structure.
*/

// Algorithm design:
/*
to keep things simple use linearized drag force: a_drag = -k * v
where k is the drag coefficient and v is the velocity vector

gravity: a_gravity = (0, -g) where g = 9.81 m/s^2
thrust: optional constant acceleration in some direction a_thrust = (a_tx, a_ty)

equation: v += dt * (a_gravity + a_drag + a_thrust)
          pos += dt * v

*/

// includes libraries
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>

// struct object to hold missile data
struct Missile
{
    float x, y;     // position
    float vx, vy;   // velocity
    float mass;     // mass
    float drag_k;   // drag coefficient
    float thrust_x; // thrust in x direction
    float thrust_y; // thrust in y direction
};

// GPU Kernel threading function where each thread simulates one missile across all timesteps
__global__ void simulateKernel(Missile *missiles, int N, float dt, int steps, float g)
{
    // Calculate global thread index
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= N)
        return;

    // Local (registers) copy for speed
    Missile m = missiles[idx];

    // Time integration loop
    for (int s = 0; s < steps; ++s)
    {
        // acceleration components
        float ax = -m.drag_k * m.vx + m.thrust_x;     // linear drag
        float ay = -m.drag_k * m.vy + m.thrust_y - g; // linear drag + gravity

        // Euler integration
        m.vx += ax * dt;
        m.vy += ay * dt;
        m.x += m.vx * dt;
        m.y += m.vy * dt;

        // Ground collision
        if (m.y < 0.0f)
        {
            // Stay at ground and zero vertical velocity
            m.y = 0.0f;
            m.vy = 0.0f;
            // keep simulating or break here
        }
    }

    // Write back to global memory
    missiles[idx] = m;
};

int main(int argc, char **argv)
{
    // Simulation parameters (can be parsed)
    const int N = 100000;   // number of missiles
    const float dt = 0.01f; // time step
    const int steps = 500;  // number of time steps
    const float g = 9.81f;  // gravity m/s^2

    // Allocate host missiles
    std::vector<Missile> h_missiles;
    h_missiles.resize(N);

    // Initialize missiles with random data
    for (int i = 0; i < N; ++i)
    {
        float angle = 30.0f * (i % 20) * 2.0f;             // Vary angle
        float speed = 50.0f + (i % 50);                    // Vary speed
        float rad = angle * 3.14159265f / 180.0f;          // degrees to radians
        h_missiles[i].x = 0.0f;                            // start at origin
        h_missiles[i].y = 0.0f;                            // start at ground level
        h_missiles[i].vx = speed * cosf(rad);              // initial velocity x
        h_missiles[i].vy = speed * sinf(rad);              // initial velocity y
        h_missiles[i].mass = 100.0f;                       // mass in kg
        h_missiles[i].drag_k = 0.1f + ((i % 10) * 0.001f); // vary drag coefficient

        // small thrust for a few missiles
        if (i % 1000 == 0)
        {
            h_missiles[i].thrust_x = 0.0f;
            h_missiles[i].thrust_y = 0.5f; // slight upward thrust
        }
        else
        {
            h_missiles[i].thrust_x = 0.0f;
            h_missiles[i].thrust_y = 0.0f; // no thrust
        }
    }

    // allocate device memory
    Missile *d_missiles = nullptr;
    size_t bytes = sizeof(Missile) * N;
    cudaError_t cerr = cudaMalloc((void **)&d_missiles, bytes);
    if (cerr != cudaSuccess)
    {
        printf("CUDA malloc failed: %s\n", cudaGetErrorString(cerr));
        return 1;
    }

    //copy host to device
    cudaMemcpy(d_missiles, h_missiles.data(), bytes, cudaMemcpyHostToDevice);

    // Launch kernel with enough blocks to cover all missiles
    int blockSizr = 256;
    int gridSize = (N + blockSizr - 1) / blockSizr;

   // warmup or cudaDeviceSynchronize timing
    simulateKernel<<<gridSize, blockSize>>>(d_missiles, N, dt, steps, g);
    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) {
        printf("Kernel launch failed: %s\n", cudaGetErrorString(err));
        cudaFree(d_missiles);
        return 1;
    }
    cudaDeviceSynchronize();

    // Copy back
    cudaMemcpy(h_missiles.data(), d_missiles, bytes, cudaMemcpyDeviceToHost);

    //Save results to CSV file (final positions and velocities)
    std::ofstream out("missiles_results.csv");
    out << "id,x,y,vx,vy,mass,drag_k,thrust_x,thrust_y\n";
    for (int i = 0; i < N; ++i)
    {
        auto &m = h_missiles[i];
        out << i << "," << m.x << "," << m.y << "," << m.vx << "," 
        << m.vy << "," << m.mass << "," << m.drag_k << "," 
        << m.thrust_x << "," << m.thrust_y << "\n";
    }
    out.close();

    // Free device memory
    cudaFree(d_missiles);
    printf
    return 0;
}
