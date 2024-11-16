# **🎯 Face Detection Attendance System**

## **📜 Overview**  
The **Face Detection Attendance System** is a modern, secure, and interactive application developed in **C++** for automating attendance management. Using advanced facial recognition technology, this system simplifies attendance logging for **students** and **teachers** while ensuring data security and ease of use.

---

## **✨ Features**  

### **🔒 Secure Login**  
- Password-protected system with different roles for students and teachers.

### **📸 Face Detection & Recognition**  
- Automatically detects and identifies faces to mark attendance.  

### **📂 Attendance Logs**  
- Saves attendance records in **CSV format**, making them easy to access and analyze.  

### **🖼️ Photo Logs**  
- Captures and stores photo logs during attendance marking for verification.  

### **📊 Data Export**  
- Export logs to external formats for detailed analysis.  

### **🎭 Dual User Modes**  
- **Students**: View personal attendance records securely.  
- **Teachers**: Manage and analyze class attendance trends.  

### **⚙️ Extensibility**  
- Designed for future web integration and cloud compatibility.  

---

## **🖥️ System Requirements**  

- **Operating System**: Windows/Linux  
- **Compiler**: GCC or MinGW with OpenCV configured  
- **Libraries**:  
  - **OpenCV**: For facial recognition and image processing  
  - **File Handling**: To manage CSV and photo logs  

---

## **📦 Setup Instructions**

### **1️⃣ Install Dependencies**  
- Install OpenCV and set it up in your C++ development environment.

### **2️⃣ Clone the Repository**  
```bash
git clone https://github.com/umerqureshi409/C-Face-Detection-Attendance-System.git
cd C-Face-Detection-Attendance-System
```

### **3️⃣ Build the Application**  
Compile the system with the required OpenCV libraries:  
```bash
g++ -o C-Face-Detection-Attendance-System main.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_face -lopencv_imgcodecs
```

### **4️⃣ Run the System**  
Start the application:  
```bash
./C-Face-Detection-Attendance-System
```

---

## **📚 Usage Instructions**  

1. **🔑 Login**  
   - Choose your role (Student or Teacher).  
   - Enter your password to access system functionalities.  

2. **📜 Select Features**  
   - A menu will guide you through options such as:  
     - `📋 Mark Attendance`  
     - `📝 Register Face`  
     - `📊 View Logs`  
     - `📤 Export Data`  
     - `❌ Exit`  

3. **📋 Attendance Marking**  
   - Enable the camera to detect faces and automatically log attendance.  

4. **🔓 Secure Log Access**  
   - View or export CSV and photo logs with password protection.  

5. **📤 Export Data**  
   - Export attendance records to external formats for further analysis.

---

## **🚀 Future Enhancements**  
- 🌐 **Web Portal**: Integrate real-time attendance tracking via a web interface.  
- 📈 **Analytics Dashboard**: Advanced tools for visualizing attendance trends.  
- 🛡️ **Biometric Security**: Include fingerprint or retina-based login for added security.  

---

## **📜 License**  
Licensed under the **MIT License**. See `LICENSE` for details.  

---

## **📬 Contact**  
For questions or support, reach out:  
- **Name**: [Umer Qureshi]  
- **Email**: [aa1660025@gmail.com]  
- **GitHub**: [https://github.com/umerqureshi409](https://github.com/umerqureshi409)  

---
