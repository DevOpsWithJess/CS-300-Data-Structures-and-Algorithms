//  Jessica Johnson
//  SNHU CS300
//  Data Structures and Algorithms
//  Project Two- ABC Universisty Software
//  This program loads a list of courses from a data file allowing users to 
//  View the full list of courses, Search a specific course, and View Prerequisites
//  04/19/2025
//

// Include the libraries need for this program
#include <iostream>     // Allows input and output: cin and cout
#include <string>       // Allows string types
#include <vector>       // For using a vector with the Prerequisite list
#include <unordered_map>// Allows hash table
#include <fstream>      // Allows files to be read in
#include <sstream>      // To read lines in CSV
#include <algorithm>    //  Allows algorithms

using namespace std;    // Allows standard library features without having to type std::

//  Define Course structure, include number/title/prerequisites
struct Course {
    string courseNumber;    // Example: CSCI400
    string courseTitle;     // Example: Large Software Development
    vector<string> prerequisites;   // Example: CSCI350

//  Function to load the CSV file into a hash table- unordered_map
//  Key is the courseNumber in final hash table
unordered_map<string, Course> loadCourses(const string& filename) {
    unordered_map<string, Course> courseTable;  // Hash Table storing courses
    ifstream file(filename);                    // CS 300 ABCU_Advising_Program_Input.csv read in
    string line;

    // Read file line by line
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {       // Seperate line data by commas
            tokens.push_back(token);
        }

        if (tokens.size() < 2) {                // How to handle bad input
            cout << "Invalid line format: " << line << endl;
            continue;
        }

        // Create courses from the while loop for each one
        Course course;
        course.courseNumber = tokens[0];
        course.courseTitle = tokens[1];

        // Store the remaining tokens as prerequisites
        for (size_t i = 2; i < tokens.size(); ++i) {
            course.prerequisites.push_back(tokens[i]);
        }

        // Assign course to hashtable using the course number as the key
        courseTable[course.courseNumber] = course;
    }
    return courseTable;
}
// Display the list of courses, sorted by course number
// Using the hash table courseCatalog data and sorting it in a vector
void printCourseList(const unordered_map<string, Course>& courseCatalog) {
    vector<Course> sortedCourses;               // Creates temporary location to hold courses while sorting them

    // Copy courseCatalog into sortedCourses
    for (const auto& pair : courseCatalog) {
        sortedCourses.push_back(pair.second);
    }

    //  Sort the courses in alphanumeric order by courseNumber
    sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
        });

    // Display sorted courseNumber, courseTitle
    for (const auto& course : sortedCourses) {
        cout << course.courseNumber << ", " << course.courseTitle << endl;
    }
}
//  Print a Specific Course and its details
void printCourse(const unordered_map<string, Course>& courseCatalog, const string& courseNumber) {
    auto it = courseCatalog.find(courseNumber);         // iterate through the hashtable using thee courseNumber as the key
    if (it == courseCatalog.end()) {                    // Course not found displayed if no match is found
        cout << "Course not found." << endl;
        return;
    }

    const Course& course = it->second;                  // If found, determine reference location

    // Display courseNumber, courseTitle
    cout << course.courseNumber << ", " << course.courseTitle << endl;

    // Check for prerequisites
    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites: ";

        // Display each prerequisite separated by commas
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) cout << ", ";
        }
        cout << endl;
    }
}
// The one and only main function
// Displays Menu for user to load data, print all courses, or search for a specific course
// Directs User Input
int main() {
    unordered_map<string, Course> courseCatalog;        // Hash Table for course data
    bool dataLoaded = false;                            // Has the data file been loaded?
    int choice;                                         // Users menu input ex. 1

    cout << "Welcome to ABC University course planner!" << endl;    // Welcome Message to User

    // Main Menu Display and Loop
    while (true) {
        cout << "\n1. Load Data Structure.\n";
        cout << "2. Print Course List.\n";
        cout << "3. Print Course.\n";
        cout << "9. Exit.\n";
        cout << "\nWhat would you like to do? ";
        cin >> choice;

        // Option 1: Load Data Structure from CSV 
        if (choice == 1) {
            courseCatalog = loadCourses("CS 300 ABCU_Advising_Program_Input.csv");
            dataLoaded = true;
            cout << "Data structure loaded successfully." << endl;
        }
        // Option: 2 Print Course List
        else if (choice == 2) {
            if (!dataLoaded) {
                cout << "Please load course data first." << endl;
            }
            else {
                printCourseList(courseCatalog);
            }
        }
        // Option 3: Print Course- Search
        else if (choice == 3) {
            if (!dataLoaded) {
                cout << "Please load course data first." << endl;
            }
            else {
                string courseNumber;
                cout << "What course do you want to know about? ";
                cin >> courseNumber;

                // Convert input to uppercase to match CSV
                transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);

                printCourse(courseCatalog, courseNumber);
            }
        }
        // Option 9: Exit
        else if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
            break;
        }
        // Invalid Input 
        else {
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0; // End of Program
}

