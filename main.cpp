#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

class Student{
    private:
        // Properities
        string fullname, address;
        int stage, id;
    public:
        // Constructors
        Student(){}
        Student(int id, string fullname, int stage, string address){
            setId(id);
            setFullname(fullname);
            setStage(stage);
            setAddress(address);
        }
        // Functions
        void setId(int id){ this->id = id; }
        int getId(){ return this->id; }
        void setFullname(string fullname){ this->fullname = fullname;}
        string getFullname(){ return this->fullname; }
        void setAddress(string address){ this->address = address; }
        int getStage(){ return this->stage; }
        string getAddress(){ return this->address; }
        void setStage(int stage){ this->stage = stage; }

        static bool is_id_token(vector<Student> students,int id){
            for(auto student: students)
                if(student.getId() == id)
                    return true;

            return false;
        } 

        string getAllData(){
            return to_string(getId()) + "," + getFullname() + "," + to_string(getStage()) + "," + getAddress() + ",";
        }
        
        string getAllDataFormatted(){
            return to_string(getId()) + "\t" + getFullname() + "\t" + to_string(getStage()) + "\t" + getAddress();
        }

};

class Importer{
    private:
    public:
        Importer(){}

        static void import_data(string data)
        {
            ofstream file_writer;
            try
            {
                file_writer.open("student.csv", ios::app);
                file_writer << data;
                file_writer.close();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        static void clear_file(){
            ofstream file_writer;
            try
            {
                file_writer.open("student.csv");
                file_writer.clear();
                file_writer.close();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        static string read_file()
        {
            ifstream file_reader;
            string data = "";
            stringstream ss(data);
            try
            {
                file_reader.open("student.csv");
                
                while( getline(file_reader, data) ){
                    ss << data;
                }
                
                file_reader.close();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            return ss.str();
        }

        static void load_data(vector<Student> &students){
            stringstream data(read_file());
            vector<string> words = split_data(data);
            int j = 0;
            for (int i = 0; i < words.size()/4; i++)
            {
                Student student;
                student.setId(stoi(words[j++]));
                student.setFullname(words[j++]);
                student.setStage(stoi(words[j++]));
                student.setAddress(words[j++]);
                students.push_back(student);
            }
        }
        static inline vector<string> split_data(stringstream& data){
            string new_data = "";
            vector<string> words;
            char c;
            while((c = data.get()) != EOF){
                if(!isDelim(c)){
                    new_data += c;
                }
                else{
                    words.push_back(new_data);
                    new_data = "";
                }
            }   

            return words;
        }
        static inline bool isDelim(char c) 
        {
            const std::string delims(", \n");
            for (int i = 0; i < delims.size(); ++i)
                if (delims[i] == c)
                    return true;
            return false;
        }
};

void add_student(vector<Student>& students);
void edit_student(vector<Student>& students);
void delete_student(vector<Student>& students);
void show_all_students(vector<Student> students);
std::string center(const string s, const int w);

int main()
{
    vector<Student> students;
    Importer::load_data(students);
    bool is_exit = false;
    cout << "Welcome to ISE Student Management System !\n";
    int option;

    
    
    while (!is_exit)
    {
        cout << "0- Exit." << endl;    
        cout << "1- Add a new Student." << endl;    
        cout << "2- Show all students." << endl;    
        cout << "3- Edit student." << endl;    
        cout << "4- Delete student." << endl;    
        cout << "5- Search by ID." << endl; 
        cout << "\n Your option :";
        cin >> option;

        switch (option)
        {
        case 0:
            // Exit the application.
            is_exit = true;
            break;
        case 1:
            // Adding a new Student.
            add_student(students);
        case 2:
            // Show all students.
            system("cls");
            show_all_students(students);
            Sleep(2000);
            break;
        case 3:
            // Edit student
            edit_student(students);
            break;
        case 4:
            // Delete student
            delete_student(students);
            break;
        case 5:
            // Search by ID
            // coming soon...
            break;
        default:
            cout << "Option is WRONG!\n";
            break;
        }   
    }
}

void add_student(vector<Student>& students)
{
    int id;
    string fullname;
    int stage;
    string address;

    cout << "Enter ID :";
    cin >> id;
    while(Student::is_id_token(students, id)){
        cout << "ID is taken please enter a new ID:";
        cin >> id;
    }

    cout << "Enter Fullname :";
    cin >> fullname;
    
    cout << "Enter Stage :";
    cin >> stage;

    cout << "Enter Address :";
    cin >> address;

    Student student(id, fullname, stage, address);
    
    Importer::import_data(student.getAllData() + "\n");
    
    students.push_back(student);
    
}

string center(const string s, const int w) {
    stringstream ss, spaces;
    int padding = w - s.size();
    for(int i=0; i<padding/2; ++i)
        spaces << " ";
    ss << spaces.str() << s << spaces.str();
    if(padding>0 && padding%2!=0)
        ss << " ";
    return ss.str();
}

void show_all_students(vector<Student> students)
{   
    std::cout << std::string(10*4 + 2*4, '-') << "\n";
    cout << center("ID" , 10) << " | " << center("Fullname", 10) << " | " <<
            center("Stage", 10) << " | " << center("Address", 10) << endl;

    std::cout << std::string(10*4 + 2*4, '-') << "\n";

    for(auto student: students){
        cout << center(to_string(student.getId()), 10) << " | " <<
                center(student.getFullname(), 10) << " | " << 
                center(to_string(student.getStage()), 10) << " | " <<
                center(student.getAddress(), 10) << endl;
    }
    std::cout << std::string(10*4 + 2*4, '-') << "\n";

}

void edit_student(vector<Student>& students){
    show_all_students(students);
    cout << "Edit by ID of students :";
    int id_selected;
    cin >> id_selected;
    
    while (!Student::is_id_token(students, id_selected))
    {
        cout << "ID does not exist please try another ID:";
        cin >> id_selected;
    }

    for(int i =0 ;i < students.size(); i++){
        if(students[i].getId() == id_selected){
            string new_name;
            int new_stage;
            string new_address;

            cout << "Enter new name :";
            cin >> new_name;

            cout << "Enter new stage :";
            cin >> new_stage;

            cout << "Enter new address :";
            cin >> new_address;

            students[i].setFullname(new_name);
            students[i].setStage(new_stage);
            students[i].setAddress(new_address);

            Importer::clear_file();
            for(auto student: students)
                Importer::import_data(student.getAllData() + "\n");
            cout << "Edited successfuly ! \n";
            break;
        }
    }
    
}
void delete_student(vector<Student>& students){
    show_all_students(students);
    cout << "Delete by ID of students :";
    int id_selected;
    cin >> id_selected;
    
    while (!Student::is_id_token(students, id_selected))
    {
        cout << "ID does not exist please try another ID:";
        cin >> id_selected;
    }

    for(int i = 0; i < students.size(); i++){
        if(id_selected == students[i].getId()){
            students.erase(students.begin() + i);
            break;
        }
    }
    
    Importer::clear_file();
    for(auto student: students)
        Importer::import_data(student.getAllData() + "\n");
    cout << "Deleted successfuly ! \n";

}