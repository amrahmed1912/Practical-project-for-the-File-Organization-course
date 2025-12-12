#include <iostream>   // مكتبة للإدخال والإخراج (cin, cout)
#include <fstream>    // مكتبة للتعامل مع الملفات (قراءة وكتابة)
#include <vector>     // مكتبة الفيكتور (مصفوفة ديناميكية قابلة للتوسع)
#include <iomanip>    // مكتبة لتنسيق المخرجات (مثل setw لضبط المسافات)
#include <string>     // مكتبة للتعامل مع النصوص

using namespace std; // استخدام فضاء الأسماء القياسي لتجنب كتابة std:: قبل كل أمر

// بداية تعريف كلاس (فئة) الطالب
class student
{
private: // بيانات خاصة لا يمكن الوصول إليها إلا من داخل الكلاس
    string Name;              // متغير لتخزين اسم الطالب
    double GPA;               // متغير لتخزين المعدل التراكمي
    string ID;                // متغير لتخزين الرقم الجامعي (تم جعله string ليقبل حروف وأرقام)
    int numSubject;           // متغير لتخزين عدد المواد المسجلة
    vector<string> nameSubject; // فيكتور لتخزين أسماء المواد (قائمة مرنة)
    vector<int> CreditHours;    // فيكتور لتخزين الساعات المعتمدة لكل مادة

public: // دوال عامة يمكن استدعاؤها من الـ main
    void setData();             // دالة لإدخال بيانات الطالب
    void showRow();             // دالة لطباعة بيانات الطالب كصف في جدول
    void saveRow(ofstream& file); // دالة لحفظ بيانات الطالب داخل ملف خارجي

    // دالة "Get" لاسترجاع الـ ID، مهمة جداً لعمليات البحث والتعديل والحذف
    string getID()
    {
        return ID; // ترجع قيمة الـ ID الخاص بالكائن الحالي
    }
};

// تعريف دالة حفظ صف الطالب داخل الملف
void student::saveRow(ofstream& file)
{
    // كتابة البيانات الأساسية مفصولة بفواصل (CSV Format)
    file << Name << "," << ID << "," << GPA << ",";

    // حلقة تكرارية للمرور على جميع المواد الخاصة بالطالب
    for (int i = 0; i < numSubject; i++)
    {
        // كتابة اسم المادة وساعاتها بشكل نصي داخل الملف
        file << nameSubject[i] << " : " << CreditHours[i] << " | ";
    }
    file << "\n"; // الانتقال لسطر جديد بعد انتهاء بيانات الطالب
}

// تعريف دالة إدخال البيانات من المستخدم
void student::setData()
{
    cout << "\n=== Enter Student Data ===\n"; // طباعة عنوان
    cin.ignore(); // تنظيف ذاكرة الإدخال (Buffer) لتجنب تخطي أمر إدخال الاسم

    cout << "Enter Student Name: "; // طلب الاسم
    getline(cin, Name); // استخدام getline لقراءة الاسم كاملاً حتى لو احتوى مسافات

    cout << "Enter Student ID: "; // طلب الرقم الجامعي
    cin >> ID;

    cout << "Enter Student GPA: "; // طلب المعدل
    cin >> GPA;

    cout << "Enter Student number of Subjects: "; // طلب عدد المواد
    cin >> numSubject;

    // مسح البيانات القديمة من الفيكتورز (مهم جداً في حالة التعديل على طالب موجود مسبقاً)
    nameSubject.clear();
    CreditHours.clear();

    // حلقة تكرارية لإدخال تفاصيل كل مادة بناءً على عدد المواد
    for (int i = 0; i < numSubject; i++)
    {
        cin.ignore(); // تنظيف الذاكرة قبل إدخال نص جديد
        cout << " - Enter name of subject " << i + 1 << ": "; // طلب اسم المادة
        string name;
        getline(cin, name); // قراءة اسم المادة
        nameSubject.push_back(name); // إضافة الاسم للفيكتور

        cout << " - CreditHours for subject " << i + 1 << ": "; // طلب عدد الساعات
        int hours;
        cin >> hours;
        CreditHours.push_back(hours); // إضافة الساعات للفيكتور
    }
}

// تعريف دالة عرض البيانات بشكل جدول
void student::showRow()
{
    // استخدام setw لحجز مسافات ثابتة لضمان محاذاة الأعمدة (left للمحاذاة لليسار)
    cout << left << setw(15) << Name  // حجز 15 مسافة للاسم
         << setw(10) << ID            // حجز 10 مسافات للـ ID
         << setw(8) << GPA            // حجز 8 مسافات للمعدل
         << setw(2) << "| ";          // فاصل شكلي

    // حلقة لطباعة المواد بجانب بيانات الطالب
    for (int i = 0; i < numSubject; i++)
    {
        cout << nameSubject[i] << "(" << CreditHours[i] << ") ";
    }
    cout << endl; // نزول سطر جديد
}

// دالة خارجية (ليست جزءاً من الكلاس) لحفظ قائمة الطلاب كلها في ملف
void saveAllToCSV(vector<student>& allStudents)
{
    ofstream file; // إنشاء كائن للتعامل مع الكتابة في الملفات
    file.open("students.csv", ios::out); // فتح ملف (أو إنشاؤه)، ios::out تمسح المحتوى القديم وتكتب الجديد

    // كتابة سطر العناوين (Header) في بداية الملف
    file << "Name,ID,GPA,Subjects\n";

    // المرور على كل طالب في الفيكتور واستدعاء دالة حفظه
    for (size_t i = 0; i < allStudents.size(); i++)
    {
        allStudents[i].saveRow(file);
    }

    file.close(); // إغلاق الملف لحفظ التغييرات
    cout << "\n[Success] All data has been saved to students.csv\n"; // رسالة تأكيد
}

// الدالة الرئيسية (نقطة انطلاق البرنامج)
int main()
{
    vector<student> studentsList; // إنشاء فيكتور لتخزين قائمة الطلاب (قاعدة البيانات في الذاكرة)

    while (true)   // حلقة لا نهائية لعرض القائمة حتى يختار المستخدم الخروج
    {
        int chois; // متغير لاختيار المستخدم

        // طباعة القائمة الرئيسية
        cout << "\n<<<<<<< =========================== >>>>>>>\n";
        cout << "       STUDENT GRADES MANAGEMENT SYSTEM        \n";
        cout << "<<<<<<< =========================== >>>>>>>\n";
        cout << "1. Add Student\n2. View All Students\n3. Save to File\n4. Edit Student\n5. Delete Student\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> chois; // استقبال الاختيار

        // الخيار 6: الخروج من البرنامج
        if (chois == 6)
        {
            cout << "Exit program...";
            break; // كسر الحلقة وإنهاء البرنامج
        }

        // الخيار 1: إضافة طالب جديد
        else if (chois == 1)
        {
            student s; // إنشاء كائن طالب جديد
            s.setData(); // تعبئة بياناته
            studentsList.push_back(s); // إضافته لقائمة الطلاب
            cout << "\n[+] Student added successfully.\n";
        }

        // الخيار 2: عرض كل الطلاب
        else if (chois == 2)
        {
            if (studentsList.empty())   // التحقق إذا كانت القائمة فارغة
            {
                cout << "\n[!] No students to display.\n";
            }
            else
            {
                // طباعة رأس الجدول
                cout << "\n---------------------------------------------------------------\n";
                cout << left << setw(15) << "Name" << setw(10) << "ID" << setw(8) << "GPA" << "Subjects\n";
                cout << "---------------------------------------------------------------\n";
                // المرور على القائمة وطباعة كل طالب
                for (size_t i = 0; i < studentsList.size(); i++)
                {
                    studentsList[i].showRow();
                }
                cout << "---------------------------------------------------------------\n";
            }
        }

        // الخيار 3: حفظ البيانات في ملف
        else if (chois == 3)
        {
            if (studentsList.empty())   // التحقق من وجود بيانات
            {
                cout << "\n[!] No data to save!\n";
            }
            else
            {
                saveAllToCSV(studentsList); // استدعاء دالة الحفظ
            }
        }

        // الخيار 4: تعديل بيانات طالب
        else if (chois == 4)
        {
            if (studentsList.empty())
            {
                cout << "\n[!] No students to edit.\n";
            }
            else
            {
                string targetID;
                cout << "Enter ID of the student to EDIT: ";
                cin >> targetID; // أخذ الـ ID المراد تعديله

                bool found = false; // متغير منطقي للتأكد من وجود الطالب
                for (size_t i = 0; i < studentsList.size(); i++)
                {
                    // مقارنة الـ ID المدخل مع ID الطالب الحالي
                    if (studentsList[i].getID() == targetID)
                    {
                        cout << "\n[Found] Edit data for student ID: " << targetID << endl;
                        // استدعاء دالة الإدخال مرة أخرى (ستقوم بمسح البيانات القديمة وتحديثها)
                        studentsList[i].setData();
                        cout << "\n[Updated] Student data updated successfully.\n";
                        found = true; // تم العثور عليه
                        break; // الخروج من حلقة البحث
                    }
                }
                if (!found) cout << "\n[!] Student with ID " << targetID << " not found!\n"; // إذا لم يتم العثور عليه
            }
        }

        // الخيار 5: حذف طالب
        else if (chois == 5)
        {
            if (studentsList.empty())
            {
                cout << "\n[!] No students to delete.\n";
            }
            else
            {
                string targetID;
                cout << "Enter ID of the student to DELETE: ";
                cin >> targetID; // أخذ الـ ID المراد حذفه

                bool found = false;
                for (size_t i = 0; i < studentsList.size(); i++)
                {
                    // البحث عن الطالب
                    if (studentsList[i].getID() == targetID)
                    {
                        // استخدام erase لحذف العنصر من الفيكتور باستخدام الـ iterator
                        studentsList.erase(studentsList.begin() + i);
                        cout << "\n[Deleted] Student with ID " << targetID << " has been removed.\n";
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "\n[!] Student with ID " << targetID << " not found!\n";
            }
        }

        // معالجة الإدخال الخاطئ
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }

    return 0; // إنهاء الدالة main بنجاح
}
