#include <iostream>
#include <cmath>
#include "capacitor.h"
#include <iomanip>

int main(){
    
    const double dt = 1e-10;
    const double tf = 5e-6;
    const int numSteps = 50000;
    const double R = 1e3;
    const double C = 100e-12;
    const double It = 1e-2;
    const double V0 = 10.0;

    // Constant current case
    Capacitor cCurrent;
    
    // memory allocation
    cCurrent.time = new double[numSteps];
    cCurrent.voltage = new double[numSteps];
    cCurrent.current = new double[numSteps];
    cCurrent.C = C;

    // initial condititions
    cCurrent.time[0] = 0;
    cCurrent.voltage[0] = 0;
    cCurrent.current[0] = It;
    
    std::cout << std::endl
              << "Calculating Voltage and Current for Constant Current Circuit..."<< std::endl;
    std::cout << "\n";

    // loop to calculate the voltage
    for (int i = 1; i < numSteps; i++){
        
        cCurrent.time[i] = cCurrent.time[i-1] +  dt;
        cCurrent.current[i] = cCurrent.current[i-1];
        cCurrent.voltage[i] = cCurrent.voltage[i-1] +
                              (cCurrent.current[i-1] * dt * (1.0 / cCurrent.C));
        if (i % 200 == 0){
        std::cout << std::scientific << std::setprecision(2) << "Time: " <<  cCurrent.time[i]
                      << " | Voltage: " << cCurrent.voltage[i]
                      << " | Current: " << cCurrent.current[i] << std::endl;
        }
    }
    
    // memory deallocation
    delete[] cCurrent.time;
    delete[] cCurrent.voltage;
    delete[] cCurrent.current; 

    // Constant voltage case
    Capacitor cVoltage;

    // memory allocation
    cVoltage.time = new double[numSteps];
    cVoltage.voltage = new double[numSteps];
    cVoltage.current = new double[numSteps];
    cVoltage.C = C;

    // initial conditions
    cVoltage.time[0] = 0;
    cVoltage.voltage[0] = 0;
    cVoltage.current[0] = V0 / R;
    std::cout << std::endl
              << "Calculating Voltage and Current for Constant Voltage Circuit..."<< std::endl;
    std::cout << "\n";
    
    // loop to calculate current and then voltage using ohms law
    for (int i = 1; i < numSteps; i++){
        cVoltage.time[i] = cVoltage.time[i-1] + dt;
        cVoltage.current[i] = cVoltage.current[i-1] - (cVoltage.current[i-1] / (R * cVoltage.C)) * dt; 
        cVoltage.voltage[i] = V0 - (cVoltage.current[i] * R); 
    
        if (i % 200 == 0){
            std::cout << std::scientific << std::setprecision(2) << "Time: " <<  cVoltage.time[i]
                      << " | Voltage: " << cVoltage.voltage[i]
                      << " | Current: " << cVoltage.current[i] << std::endl;
        }


    }
    
    // memory deallocation
    delete[] cVoltage.time;
    delete[] cVoltage.voltage;
    delete[] cVoltage.current;
}
