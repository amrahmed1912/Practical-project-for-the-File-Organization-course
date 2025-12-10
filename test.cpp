#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class student{
    private:
        string Name;
        double GPA;
        int ID;
        int numSubject;
        vector<string> nameSubject;
        vector<int> CreditHours;
    public:
        void setData();
        void getData();
        void saveToFile(student s);
        
};

void student::saveToFile(student s){
    ofstream file;
    file.open("students.csv" , ios::app);

    if (file.tellp() == 0) {
        file << "Name,ID,GPA,Subjects\n";
    }

    file<<Name <<","<<ID<<","<<GPA<<",";
    for(int i = 0;i < numSubject;i++){
        file<<nameSubject[i]<<" : "<<CreditHours[i]<<" | ";
    }
    
    file << "\n";
    file.close();
}

void student::setData(){
    cout<< "\n=== Add Sttudent ===\n";
    cin.ignore(); 
    cout << "Enter Student Name: \n";
    getline(cin, Name);

    cout<<"Enter Student ID: \n";
    cin>>ID;

    cout<<"Enter Student GPA: \n";
    cin>>GPA;

    cout<<"Enter Student number of Subjects:  \n";
    cin>>numSubject;

    for(int i = 0;i < numSubject; i++){
        cin.ignore();
        cout<<"Enter the name subject: "<< i+1 <<endl;
        
        string name;
        getline(cin, name);
        nameSubject.push_back(name);

        cout<<"CreditHours for subject: "<< i+1 <<endl;
        int hours;cin>>hours;
        CreditHours.push_back(hours);
    }
}

void student::getData(){
    cout<< "\n=== Sttudent Information===\n";
    cout<< "Name: " << Name  <<endl;
    cout<< "ID: "   << ID    <<endl;
    cout<< "GPA: "  << GPA   <<endl;
    for(int i = 0;i < numSubject;i++){
        cout<<"nameSubject: "<<nameSubject[i]<<endl;
        cout<<"CreditHours: "<<CreditHours[i]<<endl;
    }
}

int main(){
    student s;

    while(true){
        int chois;

        cout<<"\n<<<<<<< ====================== >>>>>>>\n";
        cout<<"   STUDENT GRADES MANAGEMENT SYSTEM   \n";
        cout<<"<<<<<<< ====================== >>>>>>>\n";
        cout<<"1. Add Student\n2. View All Students\n3. Save to file\n4. Edit Student\n5. Delete Student\n6. Exit\n";
        cout<<"Enter the choose: ";
        cin>>chois;

        if(chois == 6){
            cout<<"Exit program...";
            break;
        }

        // Add Student
        else if(chois == 1){
            s.setData();
        }
        
        // View All Students
        else if(chois == 2){
            s.getData();
        }

        //  Save to file
        else if(chois == 3){
            s.saveToFile(s);
            cout<<"Saved...\n";
        }

        // Edit Student
        else if(chois == 4){

        }

        // Delete Student
        else if(chois == 5){

        }

        else{
            cout<<"invalid!"<<endl;
        }
    }

    return 0;
}