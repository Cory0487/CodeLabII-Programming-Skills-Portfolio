#include <iostream>
#include <iomanip>
#include <limits>
#include <cctype>
using namespace std;

// CO2 Calculator - Estimate emissions from a car journey.
// Fuel consumption is 9.66 litres per 100 miles.

// Calculate the amount of fuel used for a journey.
double calculateFuel(double miles) {
    return (miles / 100.0) * 9.66;
}

// Calculate CO2 emissions using the selected fuel factor.
double calculateCO2(double litres, double factor) {
    return litres * factor;
}

int main() {
    double miles;
    char fuelType;

    cout << "CO2 Emissions Calculator" << endl;
    cout << "------------------------" << endl;

    // Ask the user for the journey distance.
    cout << "Enter journey distance in miles: ";
    cin >> miles;

    // Validate the distance entered by the user.
    while (cin.fail() || miles < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid distance. Enter a number of miles (0 or more): ";
        cin >> miles;
    }

    // Ask whether the car uses diesel or petrol.
    cout << "Enter fuel type (D for Diesel, P for Petrol): ";
    cin >> fuelType;
    fuelType = toupper(static_cast<unsigned char>(fuelType));

    // Only accept D or P as a valid fuel type.
    while (fuelType != 'D' && fuelType != 'P') {
        cout << "Invalid fuel type. Enter D or P: ";
        cin >> fuelType;
        fuelType = toupper(static_cast<unsigned char>(fuelType));
    }

    // Estimate the fuel consumed by the journey.
    double fuelUsed = calculateFuel(miles);

    // Example emission factors in kg CO2 per litre.
    // These are approximate values, not exact vehicle measurements.
    const double petrolFactor = 2.31;
    const double dieselFactor = 2.68;

    double emissionFactor;

    if (fuelType == 'P') {
        emissionFactor = petrolFactor;
    } else {
        emissionFactor = dieselFactor;
    }

    double totalCO2 = calculateCO2(fuelUsed, emissionFactor);

    // Display the calculation results.
    cout << fixed << setprecision(2);
    cout << "\nJourney Results" << endl;
    cout << "Distance: " << miles << " miles" << endl;
    cout << "Fuel type: "
         << (fuelType == 'P' ? "Petrol" : "Diesel") << endl;
    cout << "Fuel used: " << fuelUsed << " litres" << endl;
    cout << "Estimated CO2 emissions: " << totalCO2 << " kg" << endl;

    return 0;
}