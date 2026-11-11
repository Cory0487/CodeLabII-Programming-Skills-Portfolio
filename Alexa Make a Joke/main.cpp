// Include the iostream library for displaying text
// and receiving input from the user.
#include <iostream>

// Include fstream to read jokes from a text file.
#include <fstream>

// Include vector to store multiple jokes in memory.
#include <vector>

// Include string to work with text.
#include <string>

// Include utility to store each joke as a pair
// containing the setup and the punchline.
#include <utility>

// Include cstdlib for random number generation.
#include <cstdlib>

// Include ctime to initialise the random number generator.
#include <ctime>

// Allow standard library elements to be used
// without writing std:: before each one.
using namespace std;

// This function loads jokes from a text file.
// Each joke is stored as a pair containing
// the setup (question) and punchline (answer).
// The function returns true if jokes are loaded.
bool loadJokes(const string& filename,
               vector<pair<string, string>>& jokes)
{
    // Open the file using the provided filename.
    ifstream file(filename);

    // Check whether the file opened successfully.
    if (!file.is_open())
    {
        // Display an error if the file cannot be opened.
        cout << "Error: Could not open the jokes file." << endl;

        // Return false because the file could not be read.
        return false;
    }

        // Store each line read from the jokes file.
    string line;

    // Read the file one line at a time until the end.
    while (getline(file, line))
    {
        // Find the question mark separating the two parts.
        size_t position = line.find('?');

        // Check that a question mark exists and
        // that there is text after the question mark.
        if (position != string::npos &&
            position + 1 < line.length())
        {
            // Extract the setup including the question mark.
            string setup = line.substr(0, position + 1);

            // Extract the punchline after the question mark.
            string punchline = line.substr(position + 1);

            // Add the setup and punchline to the vector.
            jokes.push_back(make_pair(setup, punchline));
        }
    }

    // Close the file after reading all the jokes.
    file.close();

    // Return true if at least one joke was loaded.
    return !jokes.empty();
}

// The main function is the starting point of the program.
int main()
{
    // Create a vector to store all the joke pairs.
    // Each pair contains a setup and a punchline.
    vector<pair<string, string>> jokes;

    // Load all jokes from the text file.
    // If loading fails, display an error and stop the program.
    if (!loadJokes("randomJokes.txt", jokes))
    {
        // Inform the user that no jokes could be loaded.
        cout << "Error: No jokes were loaded." << endl;

        // Return 1 to indicate that the program failed.
        return 1;
    }

        // Initialise the random number generator using the current time.
    // This helps produce different random selections each time.
    srand(static_cast<unsigned int>(time(0)));

    // Generate a random index within the number of loaded jokes.
    int index = rand() % jokes.size();

    // Display a welcome message to the user.
    cout << "Alexa, tell me a joke!" << endl;

    // Display the setup (question) of the selected joke.
    cout << jokes[index].first << endl;

        // Ask the user to press Enter to reveal the punchline.
    cout << "Press Enter to see the punchline..." << endl;

    // Pause the program until the user presses Enter.
    cin.ignore();

    // Display the punchline of the selected joke.
    cout << jokes[index].second << endl;

    // Return 0 to indicate successful program execution.
    return 0;
}