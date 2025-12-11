#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class student {
private:
    string name;
    string id;
    int numSubjects;
    vector<string> subjectNames;
    vector<int> creditHours;
    int totalHours;
    int count = 0;
public:
    void setData();
    void saveToExcel();
    void display();
    void DeatailsSubject();
};

void student::setData() {
    cout << "Enter Student Name: ";
    cin >> name;

    cout << "Enter Student ID: ";
    cin >> id;

    cout << "Enter number of subjects: ";
    cin >> numSubjects;

    subjectNames.resize(numSubjects);
    creditHours.resize(numSubjects);
    totalHours = 0;

    for (int i = 0; i < numSubjects; i++) {
        cout << "Enter name of subject " << i + 1 << ": ";
        cin >> subjectNames[i];

        cout << "Enter credit hours for " << subjectNames[i] << ": ";
        cin >> creditHours[i];

        totalHours += creditHours[i];
    }
    count++;
}

void student::saveToExcel() {
    ofstream file;

    file.open("students.csv", ios::out | ios::app);

    if (file.tellp() == 0) {
        file << "Name,ID,NumSubjects,SubjectNames,CreditHours,TotalHours\n";
    }

    file << name << "," << id << "," << numSubjects << ",";

    for (int i = 0; i < numSubjects; i++) {
        file << subjectNames[i];
        if (i < numSubjects - 1) file << "|";
    }
    file << ",";

    for (int i = 0; i < numSubjects; i++) {
        file << creditHours[i];
        if (i < numSubjects - 1) file << "|";
    }

    file << "," << totalHours << "\n";
    file.close();
}

void student::display() {
    if(count == 0){
        cout<<"Not found...\n";
        return;
    }
    cout << "\n=========== Student Data ===========\n";
    cout << "Name: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Number of Subjects: " << numSubjects << endl;

    for (int i = 0; i < numSubjects; i++) {
        cout << "  - " << subjectNames[i] << " (" << creditHours[i] << " hrs)" << endl;
    }

    cout << "Total Credit Hours = " << totalHours << endl;
    cout << "--------------------------------------\n";
}

void student::DeatailsSubject(){
    double grades[count];

    for (int i = 0; i < count; i++) {
        cout << "Enter grade for student " << i + 1 << ": ";
        cin >> grades[i];
    }

    int passCount = 0;
    double sum = 0;

    for (int i = 0; i < count; i++) {
        sum += grades[i];
        if (grades[i] >= 50) {
            passCount++;
        }
    }
    double avg = sum / count;
    double passPercent = (passCount * 100.0) / count;
    double failPercent = 100.0 - passPercent;

    cout << "\nAverage: " << avg << endl;
    cout << "Pass Percent: " << passPercent << "%" << endl;
    cout << "Fail Percent: " << failPercent << "%" << endl;

}

int main() {
    student s;

    while(true){
        int chois;

        cout<<"\n<<<<<<< ====================== >>>>>>>\n";
        cout<<"   STUDENT GRADES MANAGEMENT SYSTEM   \n";
        cout<<"<<<<<<< ====================== >>>>>>>\n";
        cout<<"1. Add Student\n2. View All Students\n3. Save to file\n4. Deatails Subject\n5. Delete Student\n6. Exit\n";
        cout<<"Enter the choose: ";
        cin>>chois;

        if(chois == 6){
            cout<<"Exit program...";
            break;
        }

        else if(chois == 1){
            s.setData();       
        }

        else if(chois == 2){
            s.display();       
        }
        else if(chois == 3){
            s.saveToExcel();
        }
        else if(chois == 4){
            s.DeatailsSubject();
        }
    }

    return 0;
}