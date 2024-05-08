#include <iostream>
#include <eigen3/Eigen/Dense>
#include <cmath>
#include "space.hpp"

using namespace space;
using namespace std;

const float dt=0.0625;

int main()
{
    //initializes the 3 elements used in this program.
    object Earth;
    object Sun;
    object Moon;
    Sun.initialize_object
    (
        -1.191989205285392*1000*pow(10, 6), 
        -4.347654370292560*1000*pow(10, 5), 
        3.146124454779254*1000*pow(10, 4),
        1
    );

    Earth.initialize_object
    (
        -2.600298246493929*1000*pow(10, 7),
        1.445600958366426*1000*pow(10, 8),
        2.324604087693989*1000*pow(10, 4),
        2
    );

    Moon.initialize_object
    (
        -2.637093499608123*1000*pow(10, 7),
        1.447266276319263*1000*pow(10, 8),
        4.842335848964751*1000*10*pow(10, 4),
        3
    );
    //take in the simulation duration.
    cout << "Input the simulation duration> ";
    string input;
    cin >> input;
    int dur = stoi(input);
    cout << "Time: " << time(dur)[0] << "Days," << time(dur)[1] << "Hours," << time(dur)[2] << "Minutes," << time(dur)[3] << "Seconds" << std::endl;
    //calculates the position and pushes data to log.
    for(int i = 0; i <= static_cast<int>(dur/dt); ++i) 
    {
        Sun.calculate(1);
        Earth.calculate(2);
        Moon.calculate(3);
    }
    //writes log to csv.
    Sun.write_to_csv(1);
    Earth.write_to_csv(2);
    Moon.write_to_csv(3);
    exit(0);
}