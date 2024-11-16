Face Detection Attendance System
Overview
This system automates attendance marking using face recognition. Designed for students and teachers, it offers a password-protected, interactive interface for seamless attendance management. Users can view logs, analyze trends, and perform various tasks via a menu-driven interface.

Interactive Features
1. User-Friendly Menu System
A clear, interactive menu allows users to choose tasks such as marking attendance, viewing logs, and exporting data.
Separate menus for students and teachers.
2. Guided Prompts
Users are guided step-by-step with clear prompts during every operation, such as face registration, attendance marking, and log access.
3. Visual Feedback
Displays real-time detection results (e.g., recognized faces and their names).
Progress indicators for tasks like exporting logs or securing files.
4. Custom Alerts
Alerts for incorrect passwords, successful logins, and operation completions.
5. Error Handling
Prevents invalid inputs with interactive error messages and re-prompting.
Features in Detail
1. Login System
Students and teachers log in with credentials to access personalized features.
2. Face Registration
Step-by-step instructions for registering faces for the system.
3. Attendance Marking
Automatic recognition of faces during attendance with real-time visual confirmation.
4. Log Access
Securely view CSV attendance logs and photo logs with a password.
5. Data Export
Export logs with a single menu option for analysis in external tools.
6. Multi-User Support
Different functionalities for students and teachers.
7. Real-Time Notifications
Alerts for tasks such as attendance marking and file-saving status.
System Requirements
OS: Windows/Linux
Compiler: GCC/MinGW with OpenCV installed
Libraries:
OpenCV for face recognition
File handling for CSV generation
Setup Instructions
1. Install Dependencies
Install OpenCV and configure it with your C++ environment.

2. Clone the Repository
bash
Copy code
git clone https://github.com/yourusername/face-detection-attendance-system.git
cd face-detection-attendance-system
3. Build the Application
bash
Copy code
g++ -o attendance_system main.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_face -lopencv_imgcodecs
4. Run the Application
bash
Copy code
./attendance_system
Future Enhancements
Real-time web integration for live attendance tracking.
Advanced analytics dashboards for attendance trends.
Biometric login for added security.
License
Licensed under the MIT License. See LICENSE for more details.

