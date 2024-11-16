#include <iostream>
#include <fstream>
#include <ctime>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>



#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#include <direct.h>
#else
#include <termios.h>
#include <unistd.h>
#include <sys/stat.h>
#endif

using namespace std;
using namespace cv;

//  ANSI COLOR CODE
#define RESET   "\033[0m"
#define RED     "\033[38;5;196m" 
#define GREEN   "\033[38;5;46m"  
#define YELLOW  "\033[38;5;226m" 
#define BLUE    "\033[38;5;75m"     
#define MAGENTA "\033[38;5;201m"    
#define CYAN    "\033[38;5;51m"     
#define WHITE   "\033[37m"  
// Clear Screen Function
void clearScreen() {
   
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function to pause and wait for user input
void returnToMenu() {
       cout << WHITE << "Press any key to return to the menu..." << RESET << endl;
#ifdef _WIN32
    _getch();
#else
    getchar();
#endif
}

    // Function to create a directory if it doesn't exist
void createDirectory(const string& dir) {
#ifdef _WIN32
    _mkdir(dir.c_str());
#else
    mkdir(dir.c_str(), 0777);
#endif
}

// Function to ask for password input
bool password() {
   
const string correctPassword = "helloworld";
string password;

cout << WHITE << "Enter password to Verify : " << RESET;

#ifdef _WIN32
char ch;
while ((ch = _getch()) != '\r') {  
    if (ch == '\b' && !password.empty()) {
        password.pop_back();
        cout << "\b \b";  
    }
    else if (ch != '\r') {
        password.push_back(ch);
        cout << '*';
    }
}
#else
termios oldt, newt;
tcgetattr(STDIN_FILENO, &oldt);  // Get current terminal settings
newt = oldt;
newt.c_lflag &= ~ECHO;  // Turn off ECHO flag to hide input
tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Apply new settings

getline(cin, password);  // Get password input

tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restore old terminal settings
#endif

cout << endl;
return password == correctPassword;
}

// Function to print a multicolor text like FUMB banner

void colorText(const string& text, int delayMicroseconds = 100000) {
    const string colors[] = { CYAN, MAGENTA, YELLOW, GREEN, BLUE, WHITE };
    int colorCount = sizeof(colors) / sizeof(colors[0]);

    for (size_t i = 0; i < text.length(); ++i) {
        cout << colors[i % colorCount] << text[i];
        cout.flush();

#ifdef _WIN32
        Sleep(delayMicroseconds / 1000);  // Convert microseconds to milliseconds for Windows
#else
        usleep(delayMicroseconds);  // Use microseconds for other systems
#endif
    }
    cout << RESET << endl;
}

// Function for FUMB banner with optimized colors
void Banner() {
    string bannerLines[] = {
        "\t\t  _____   _    _   __  __   ____   ",
        "\t\t |  ___| | |  | | |  \\/  | |  _ \\",
        "\t\t | |__   | |  | | | \\  / | | |_) |",
        "\t\t |  __|  | |  | | | |\\/| | |  _ <",
        "\t\t | |     | |__| | | |  | | | |_) | ",
        "\t\t |_|      \\____/  |_|  |_| |____/  "
    };
   
    for (const string& line : bannerLines) {
        colorText(line, 10000);  // Adjust speed here if desired
    }
}
// Function to show the menu 
void Menu() {
      cout << WHITE << "\t1. Mark Student Attendance" << RESET << endl;
    cout << WHITE << "\t2. Mark Teacher Attendance" << RESET << endl;
    cout << WHITE << "\t3. View Student Attendance Log" << RESET << endl;
    cout << WHITE << "\t4. View Teacher Attendance Log" << RESET << endl;
    cout << WHITE << "\t5. View Student Photo Logs" << RESET << endl;
    cout << WHITE << "\t6. View Teacher Photo Logs" << RESET << endl;
    cout << WHITE << "\t7. Add Student to Database" << RESET << endl;
    cout << WHITE << "\t8. Add Teacher to Database" << RESET << endl;
    cout << WHITE << "\t9. View Instructions      " << RESET << endl;
    cout << RED << "\t0. Exit" << RESET << endl;
    cout << CYAN << "\tEnter option: " << RESET;
}

// Class to handle attendance system operations
class AttendanceSystem {
public:
    void markStudentAttendance(const string& name, const string& rollNumber);
    void markTeacherAttendance(const string& name, const string& regNumber);
    void viewStudentAttendance() const;
    void viewTeacherAttendance() const;
    void viewPhotoLogs(const string& photoDir) const;
    bool detectFace(Mat& frame, CascadeClassifier& faceCascade, Rect& face) const;
    bool detectBlink(Mat& faceROI) const;
    VideoCapture selectCamera() const;

private:
    void markAttendance(const string& name, const string& id, const string& logFileName, const string& photoDir) const;
    void displayAttendance(const string& logFileName) const;
};

// Function to add CSV headers if log file is empty
void addCSVHeaders(ofstream& log, const string& logFileName) {
    
    ifstream logCheck(logFileName);
    if (logCheck.peek() == ifstream::traits_type::eof()) { // File is empty
        log << "Date,Name,ID,Photo Path" << endl;
    }
    logCheck.close();
}

void addStudentToDatabase() {
    clearScreen();
    if (!password()) {
        cout << RED << "Access denied. Incorrect password." << RESET << endl;
        returnToMenu();
        return;
    }

    string name, rollNumber;
    clearScreen();
    cout << WHITE << "Enter student name: " << RESET;
    cin >> name;
    cout << WHITE << "Enter roll number: " << RESET;
    cin >> rollNumber;

    ofstream dbFile("database/student_database.csv", ios::app);
    if (dbFile.is_open()) {
        dbFile << name << "," << rollNumber << endl;
        cout << GREEN << "Student added to database successfully." << RESET << endl;
    }
    else {
        cerr << RED << "Error opening student database file." << RESET << endl;
    }
    dbFile.close();
    returnToMenu();
}

void addTeacherToDatabase() {
    clearScreen();
    if (!password()) {
        cout << RED << "Access denied. Incorrect password." << RESET << endl;
        returnToMenu();
        return;
    }

    string name, regNumber;
    clearScreen();
    cout << WHITE << "Enter teacher name: " << RESET;
    cin >> name;
    cout << WHITE << "Enter registration number: " << RESET;
    cin >> regNumber;

    ofstream dbFile("database/teacher_database.csv", ios::app);
    if (dbFile.is_open()) {
        dbFile << name << "," << regNumber << endl;
        cout << GREEN << "Teacher added to database successfully." << RESET << endl;
    }
    else {
        cerr << RED << "Error opening teacher database file." << RESET << endl;
    }
    dbFile.close();
    returnToMenu();
}



bool isInDatabase(const string& databaseFile, const string& name, const string& id) {
    ifstream dbFile(databaseFile);
    string line, db_name, db_id;

    while (getline(dbFile, line)) {
        stringstream ss(line);
        getline(ss, db_name, ','); 
        getline(ss, db_id, ',');  

        // Check if both name and ID match
        if (db_name == name && db_id == id) {
            dbFile.close();
            return true; 
        }
    }
    dbFile.close();
    return false; 
}

// Function to mark student attendance
void AttendanceSystem::markStudentAttendance(const string& name, const string& rollNumber) {
    if (isInDatabase("database/student_database.csv", name, rollNumber)) {
        markAttendance(name, rollNumber, "studentattendance_log.csv", "student_photos");
        clearScreen();
        cout << WHITE << "Attendance marked for today: " << name << " " << rollNumber << RESET << endl;
    }
    else {
        clearScreen();
        cout << RED << "Error: Student " << name << " with Roll Number " << rollNumber << " not found in the database." << RESET << endl;
    }
    returnToMenu();
}

// Function to mark teacher attendance
void AttendanceSystem::markTeacherAttendance(const string& name, const string& regNumber) {
    if (isInDatabase("database/teacher_database.csv", name, regNumber)) {
        markAttendance(name, regNumber, "teacherattendance_log.csv", "teacher_photos");
        clearScreen();
        cout << WHITE << "Attendance marked for today: " << name << " " << regNumber << " " << RESET << endl;
    }
    else {
        clearScreen();
        cout << RED << "Error: Teacher " << name << " with Registration Number " << regNumber << " not found in the database." << RESET << endl;
        
    }
    returnToMenu();
}
// Function to view student attendance log
void AttendanceSystem::viewStudentAttendance() const {
    
    clearScreen();
    displayAttendance("studentattendance_log.csv");
    returnToMenu();
}

// Function to view teacher attendance log with password protection
void AttendanceSystem::viewTeacherAttendance() const {
    
    clearScreen();
    if (password()) {
        displayAttendance("teacherattendance_log.csv");
    }
    returnToMenu();
}



bool AttendanceSystem::detectFace(Mat& frame, CascadeClassifier& faceCascade, Rect& face) const {
    Mat grayFrame;
    cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
    vector<Rect> faces;
    faceCascade.detectMultiScale(grayFrame, faces, 1.1, 4, 0, Size(200, 200));

    if (!faces.empty()) {
        face = faces[0]; // Take the first detected face
        return true;
    }
    return false;
}

// Function to detect blinking as a liveness check
bool AttendanceSystem::detectBlink(Mat& faceROI) const {
    Mat grayFace;
    cvtColor(faceROI, grayFace, COLOR_BGR2GRAY);
    int height = grayFace.rows;
    int width = grayFace.cols;

    Mat upperHalf = grayFace(Rect(0, 0, width, height / 2));
    Mat lowerHalf = grayFace(Rect(0, height / 2, width, height / 2));

    Scalar avgUpper = mean(upperHalf);
    Scalar avgLower = mean(lowerHalf);

    return (avgUpper[0] > avgLower[0]); // Return true if upper half is brighter
}

// Function to prompt user for camera selection
VideoCapture AttendanceSystem::selectCamera() const {
    int cameraChoice;
    clearScreen();
    cout << "Select Camera: 1 for Default Camera (&)  2 for IP Camera" << endl;
    cin >> cameraChoice;

    if (cameraChoice == 2) {
        string ipCameraURL;
        clearScreen();
        cout << "Enter IP Camera URL: ";
        cin >> ipCameraURL;
        VideoCapture cap(ipCameraURL);

        if (cap.isOpened()) {
            cout<<GREEN << "Connected to IP Camera." << endl;
            return cap;
        }
        else {
            cerr<< RED << "Failed to connect to IP Camera. Using default camera." << endl;
        }
    }
    return VideoCapture(0); // Fallback to default camera
}

// Function to mark attendance
void AttendanceSystem::markAttendance(const string& name, const string& id, const string& logFileName, const string& photoDir) const {
    char ready;
    do {
        cout << "Are you ready for face capture? (Y/N): ";
        cin >> ready;
        ready = toupper(ready);
    } while (ready != 'Y' && ready != 'N');

    if (ready == 'N') {
        cout << "Face capture aborted." << endl;
        return;
    }

    VideoCapture cap = selectCamera();

    // If camera fails to open, allow manual attendance marking
    if (!cap.isOpened()) {

        cerr<<RED << "Camera not working! Admin can mark attendance manually." << endl;
        if (password()) {
            ofstream log(logFileName, ios::app);
            time_t now = time(0);
            tm currentDate;
#ifdef _WIN32
            localtime_s(&currentDate, &now);
#else
            localtime_r(&now, &currentDate);
#endif
            addCSVHeaders(log, logFileName);
            log << currentDate.tm_year + 1900 << "-" << currentDate.tm_mon + 1 << "-" << currentDate.tm_mday << ","
                << name << "," << id << "," << "Manual Entry" << endl;
            log.close();
            cout<<GREEN << "Attendance marked manually by admin." << endl;
        }
        else {
            cerr<<RED << "Incorrect password. Attendance not marked." << endl;
        }
        return;
    }

    namedWindow("Face Detection", WINDOW_NORMAL);
    resizeWindow("Face Detection", 640, 480);

    CascadeClassifier faceCascade;
    if (!faceCascade.load("haarcascade_frontalface_default.xml")) {
        cerr << "Error loading face cascade. Check the file path." << endl;
        return;
    }

    createDirectory(photoDir);
    time_t start_time = time(0);
    bool faceDetected = false;
    bool isLive = false;
    auto lastCaptureTime = chrono::steady_clock::now();

    // Main loop for face detection and blink check
    while (true) {
        Mat frame;
        cap >> frame;
        if (frame.empty()) {
            cerr << "Error capturing frame." << endl;
            break;
        }

        Rect face;
        if (detectFace(frame, faceCascade, face)) {
            Rect expandedFace = face;
            expandedFace.x = max(face.x - 30, 0);
            expandedFace.y = max(face.y - 30, 0);
            expandedFace.width = min(face.width + 60, frame.cols - expandedFace.x);
            expandedFace.height = min(face.height + 60, frame.rows - expandedFace.y);
            Mat faceROI = frame(expandedFace);
            rectangle(frame, expandedFace, Scalar(0, 255, 0), 2);

            if (detectBlink(faceROI)) {
                isLive = true;
                string message = "Live Face Detected: " + name + " !";
                putText(frame, message, Point(50, 50), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 255, 0), 2);
            }
            else {
                isLive = false;
                putText(frame, "Blink to Confirm!", Point(50, 50), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 255), 2);
            }

            if (isLive && !faceDetected) {
                auto now = chrono::steady_clock::now();
                auto duration = chrono::duration_cast<chrono::milliseconds>(now - lastCaptureTime).count();

                if (duration > 2000) { // Add a 2-second delay between captures
                    Mat resizedFace;
                    resize(faceROI, resizedFace, Size(300, 300));
                    string photoPath = photoDir + "/" + name + "_" + id + ".jpg";

                    if (imwrite(photoPath, resizedFace)) {
                        cout << "Face image saved: " << photoPath << endl;
                    }
                    else {
                        cerr << "Error saving the face image." << endl;
                    }
                    faceDetected = true;
                    lastCaptureTime = now;
                }
            }
        }
        else {
            putText(frame, "No Face Detected!", Point(50, 50), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(0, 0, 255), 2);
        }

        imshow("Face Detection", frame);

        if (waitKey(1) == 27 || (difftime(time(0), start_time) >= 15)) {
            break;
        }
    }

    destroyAllWindows();

    if (!faceDetected) {
        cerr << "No face detected. Attendance not marked." << endl;
        return;
    }

    time_t now = time(0);
    tm currentDate;
#ifdef _WIN32
    localtime_s(&currentDate, &now);
#else
    localtime_r(&now, &currentDate);
#endif

    ofstream log(logFileName, ios::app);
    addCSVHeaders(log, logFileName);
    log << currentDate.tm_year + 1900 << "-" << currentDate.tm_mon + 1 << "-" << currentDate.tm_mday << ","
        << name << "," << id << "," << photoDir << "/" << name << "_" << id << ".jpg" << endl;
    log.close();
}

// Function to display attendance from CSV log file
void AttendanceSystem::displayAttendance(const string& logFileName) const {
    
    ifstream log(logFileName);
    string line;

    if (!log.is_open()) {
        cerr << WHITE << "Error opening log file: " << logFileName << RESET << endl;
        return;
    }

    while (getline(log, line)) {
        cout << WHITE << line << RESET << endl;
    }

    log.close();
}

//// Function to view photo logs (display images) with password protection
//void AttendanceSystem::viewPhotoLogs(const string& photoDir) const {
//   
//    clearScreen();
//    if (!password()) {
//        cout << RED << "Access denied. Incorrect password." << RESET << endl;
//        returnToMenu();
//        return;
//    }
//
//    vector<string> photoFiles;
//    VideoCapture cap;
//
//    // List photo files in the directory
//    string filePattern = photoDir + "/*.jpg";
//    glob(filePattern, photoFiles);
//
//    if (photoFiles.empty()) {
//        cerr << WHITE << "No photo logs available." << RESET << endl;
//        return;
//    }
//
//    for (const string& photoFile : photoFiles) {
//        Mat photo = imread(photoFile);
//        if (photo.empty()) {
//            cerr << WHITE << "Error loading image: " << photoFile << RESET << endl;
//            continue;
//        }
//
//        namedWindow(photoFile, WINDOW_NORMAL);
//        imshow(photoFile, photo);
//        waitKey(5000); // Show each image for 5 seconds
//        destroyWindow(photoFile);
//    }
//
//}
void AttendanceSystem::viewPhotoLogs(const string& photoDir) const {
    clearScreen();

    
    if (!password()) {
        cout << RED << "Access denied. Incorrect password." << RESET << endl;
        returnToMenu();
        return;
    }

    
    cout << GREEN << "Would you like to search for a specific image or view all? (Enter 'search' or 'all'): " << RESET;
    string option;
    cin >> option;

    
    transform(option.begin(), option.end(), option.begin(), ::tolower);

    
    if (option != "search" && option != "all") {
        cerr << RED << "Invalid choice. Please enter 'search' or 'all'." << RESET << endl;
        returnToMenu();
        return;
    }

    vector<string> photoFiles;
    string filePattern = photoDir + "/*.jpg";
    glob(filePattern, photoFiles);

    if (photoFiles.empty()) {
        cerr << RED << "No photo logs available." << RESET << endl;
        return;
    }

    if (option == "search") {
       
        cout << CYAN << "Would you like to search by name or ID? (Enter 'name' or 'id'): " << RESET;
        string searchOption;
        cin >> searchOption;

       
        transform(searchOption.begin(), searchOption.end(), searchOption.begin(), ::tolower);

       
        if (searchOption != "name" && searchOption != "id") {
            cerr << RED << "Invalid choice. Please enter 'name' or 'id'." << RESET << endl;
            returnToMenu();
            return;
        }

        string searchQuery;
        cout << GREEN << "Enter the " << searchOption << " to search for: " << RESET;
        cin >> searchQuery;

        bool found = false;

        for (const string& photoFile : photoFiles) {
            string photoName = photoFile.substr(photoFile.find_last_of("/\\") + 1); // Extract filename from path

            // Check if the filename contains the search query (case-insensitive)
            transform(photoName.begin(), photoName.end(), photoName.begin(), ::tolower);
            if (photoName.find(searchQuery) != string::npos) {
                Mat photo = imread(photoFile);
                if (photo.empty()) {
                    cerr << WHITE << "Error loading image: " << photoFile << RESET << endl;
                    continue;
                }
                namedWindow(photoFile, WINDOW_NORMAL);
                imshow(photoFile, photo);
                waitKey(5000); 
                destroyWindow(photoFile);

                found = true;
                break; 
            }
        }

        if (!found) {
            cout << WHITE << "No matching photo found." << RESET << endl;
        }

    }
    else if (option == "all") {
        
        for (const string& photoFile : photoFiles) {
            Mat photo = imread(photoFile);
            if (photo.empty()) {
                cerr << WHITE << "Error loading image: " << photoFile << RESET << endl;
                continue;
            }

            namedWindow(photoFile, WINDOW_NORMAL);
            imshow(photoFile, photo);
            waitKey(5000);
            destroyWindow(photoFile);
        }
    }

    returnToMenu();
}

void Instructions() {
   
    clearScreen();
    cout << WHITE << "\t======================================================================================" << endl;
    cout << RED << "\t\t\t\t\t  INSTRUCTIONS" << endl;
    cout << WHITE << "\t======================================================================================" << endl;
    cout << WHITE << "\t1. MAKE SURE YOUR FACE IS CLEARLY VISIBLE IN SCREEN." << endl;
    cout << WHITE << "\t2. IF YOUR FACE IS NOT CLEAR, WE DON'T COUNT IT AS ATTENDANCE." << endl;
    cout << WHITE << "\t3. TRY TO ENTER THE CORRECT ROLL NO." << endl;
    cout << WHITE << "\t4. YOU CAN SEE YOUR PHOTO LOG BY ENTERING THE PASSWORD THAT THE DEVELOPER GIVES YOU." << endl;
    cout << WHITE << "\t5. YOU CAN ALSO SEE AN EXCEL SHEET OF YOUR ATTENDANCE LOG." << endl;
    cout << WHITE << "\t6. IF YOU HAVE ANY QUERIES, CONTACT US AT PH: 03213021673." << endl;
    cout << CYAN << "\t=======================================================================================" << endl;
    cout << WHITE << "\t\t\t\t\t  THANK YOU" << endl;
    cout << CYAN << "\t=======================================================================================" << endl;

#ifdef _WIN32
    Sleep(5000); // Rest for 5 seconds on Windows
#else
    usleep(5000000); // Rest for 5 seconds on Linux/Unix
#endif
}


int main() {
   
    AttendanceSystem system;
    int option;

    do {
       
        clearScreen();
        Banner();
  
        cout << RED << "\t===========================================================" << endl;
        cout<< WHITE << "\t  ATTENDANCE SYSTEM DESIGNED BY FAHEES UMER MUSAB BURHAN " << RESET<<endl;
        cout << RED << "\t===========================================================" << endl;
       

   
        Menu();
        cin >> option;

        string name, rollNumber, regNumber;
        

        switch (option) {
        case 1:
            clearScreen();
            cout << WHITE << "Enter student name: " << RESET;
            cin >> name;
            cout << WHITE << "Enter roll number: " << RESET;
            cin >> rollNumber;
            system.markStudentAttendance(name, rollNumber);
            break;
        case 2:
            clearScreen();
            cout << WHITE << "Enter teacher name: " << RESET;
            cin >> name;
            cout << WHITE << "Enter registration number: " << RESET;
            cin >> regNumber;
            
            system.markTeacherAttendance(name, regNumber);
            break;
        case 3:
            system.viewStudentAttendance();
            break;
        case 4:
            system.viewTeacherAttendance();
            break;
        case 5:
            system.viewPhotoLogs("student_photos");
            break;
        case 6:
            system.viewPhotoLogs("teacher_photos");
            break;
       
        case 7:
            addStudentToDatabase();
            break;
        case 8:
            addTeacherToDatabase();
            break;
        case 9:
            Instructions();
            returnToMenu();
            break;
        case 0:
            cout << CYAN << "\t\t======  Thanks For Using FUMB =======" << RESET << endl;
            cout << RED << "\tExiting the system..." << RESET << endl;
            
            break;
         default:
            cout << RED << "Invalid option, please try again." << RESET << endl;
            returnToMenu();
        }
    } while (option != 0);

    return 0;
}





