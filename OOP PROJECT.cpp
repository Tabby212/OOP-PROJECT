#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>

using namespace std;

// Abstract base class
class Person {
protected:
    string name;
    int id;

public:
    Person(const string& name, int id) : name(name), id(id) {}
    virtual ~Person() {}

    virtual void display() const = 0; // Pure virtual function
    string getName() const { return name; } // Getter for name
    int getId() const { return id; } // Getter for id
};

// Derived class for doctors
class Doctor : public Person {
private:
    string specialty;

public:
    Doctor(const string& name, int id, const string& specialty)
        : Person(name, id), specialty(specialty) {}

    void display() const override {
        cout << "Doctor ID: " << id << ", Name: " << name << ", Specialty: " << specialty << endl;
    }
};

// Derived class for patients
class Patient : public Person {
private:
    string ailment;

public:
    Patient(const string& name, int id, const string& ailment)
        : Person(name, id), ailment(ailment) {}

    void display() const override {
        cout << "Patient ID: " << id << ", Name: " << name << ", Ailment: " << ailment << endl;
    }
};

// Function to save data to a file
void saveToFile(const vector<Person*>& people) {
    ofstream outFile("hospital_data.txt");
    if (!outFile) {
        throw runtime_error("Error opening file for writing.");
    }

    for (const auto& person : people) {
        if (dynamic_cast<Doctor*>(person)) {
            outFile << "Doctor," << person->getName() << "," << person->getId() << endl;
        } else if (dynamic_cast<Patient*>(person)) {
            outFile << "Patient," << person->getName() << "," << person->getId() << endl;
        }
    }

    outFile.close();
}

// Function to display menu
void displayMenu() {
    cout << "Hospital Management System" << endl;
    cout << "1. Add Doctor" << endl;
    cout << "2. Add Patient" << endl;
    cout << "3. Display All" << endl;
    cout << "4. Save to File" << endl;
    cout << "5. Exit" << endl;
    cout << "Choose an option: ";
}

// Main function
int main() {
    vector<Person*> people;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        if (choice == 1) {
            string name, specialty;
            int id;
            cout << "Enter Doctor's Name: ";
            cin >> name;
            cout << "Enter Doctor's ID: ";
            cin >> id;
            cout << "Enter Doctor's Specialty: ";
            cin >> specialty;
            people.push_back(new Doctor(name, id, specialty));
        } else if (choice == 2) {
            string name, ailment;
            int id;
            cout << "Enter Patient's Name: ";
            cin >> name;
            cout << "Enter Patient's ID: ";
            cin >> id;
            cout << "Enter Patient's Ailment: ";
            cin >> ailment;
            people.push_back(new Patient(name, id, ailment));
        } else if (choice == 3) {
            for (const auto& person : people) {
                person->display();
            }
        } else if (choice == 4) {
            try {
                saveToFile(people);
                cout << "Data saved successfully." << endl;
            } catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
        }

    } while (choice != 5);

    // Clean up memory
    for (auto person : people) {
        delete person;
    }

    return 0;
}
