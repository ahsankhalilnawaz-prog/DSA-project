#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

// ---------------- STRUCTS ----------------
struct Doctor {
    int id;
    string name;
    string shift;  
};

struct Nurse {
    int id;
    string name;
    string shift;  
};

struct Patient {
    int id;
    string name;
    int priority;
    int doctorId;
};

struct Appointment {
    int patientId;
    int doctorId;
    string timeSlot;  
};

// ---------------- DATA ----------------
vector<Doctor> doctors;
vector<Nurse> nurses;
vector<Patient> patients;
vector<Appointment> appointments;

// ---------------- PRIORITY QUEUE ----------------
struct Compare {
    bool operator()(Patient a, Patient b) {
        return a.priority > b.priority;
    }
};

priority_queue<Patient, vector<Patient>, Compare> pq;

// ---------------- SAVE FILES ----------------
void saveDoctors() {
    ofstream f("doctors.txt");
    for (auto d : doctors)
        f << d.id << " " << d.name << " " << d.shift << endl;
}

void saveNurses() {
    ofstream f("nurses.txt");
    for (auto n : nurses)
        f << n.id << " " << n.name << " " << n.shift << endl;
}

void savePatients() {
    ofstream f("patients.txt");
    for (auto p : patients)
        f << p.id << " " << p.name << " " << p.priority << " " << p.doctorId << endl;
}

void saveAppointments() {
    ofstream f("appointments.txt");
    for (auto a : appointments)
        f << a.patientId << " " << a.doctorId << " " << a.timeSlot << endl;
}

// ---------------- LOAD FILES ----------------
void loadDoctors() {
    ifstream f("doctors.txt");
    Doctor d;
    while (f >> d.id >> d.name >> d.shift)
        doctors.push_back(d);
}

void loadNurses() {
    ifstream f("nurses.txt");
    Nurse n;
    while (f >> n.id >> n.name >> n.shift)
        nurses.push_back(n);
}

void loadPatients() {
    ifstream f("patients.txt");
    Patient p;
    while (f >> p.id >> p.name >> p.priority >> p.doctorId) {
        patients.push_back(p);
        pq.push(p);
    }
}

// ---------------- ADD DOCTOR ----------------
void addDoctor() {
    Doctor d;
    cout << "Doctor ID: ";
    cin >> d.id;
    cout << "Doctor Name: ";
    cin >> d.name;
    cout << "Shift (Morning/Evening/Night): ";
    cin >> d.shift;

    doctors.push_back(d);
    saveDoctors();

    cout << "Doctor Added!\n";
}

// ---------------- ADD NURSE ----------------
void addNurse() {
    Nurse n;
    cout << "Nurse ID: ";
    cin >> n.id;
    cout << "Nurse Name: ";
    cin >> n.name;
    cout << "Shift (Morning/Evening/Night): ";
    cin >> n.shift;

    nurses.push_back(n);
    saveNurses();

    cout << "Nurse Added!\n";
}

// ---------------- ADD PATIENT ----------------
void addPatient() {
    Patient p;
    cout << "Patient ID: ";
    cin >> p.id;
    cout << "Patient Name: ";
    cin >> p.name;
    cout << "Priority (1=Critical,2=Normal): ";
    cin >> p.priority;

    p.doctorId = -1;

    patients.push_back(p);
    pq.push(p);

    savePatients();

    cout << "Patient Added!\n";
}

// ---------------- ASSIGN DOCTOR ----------------
void assignDoctor() {
    int pid, did;
    cout << "Patient ID: ";
    cin >> pid;
    cout << "Doctor ID: ";
    cin >> did;

    for (auto &p : patients) {
        if (p.id == pid) {
            p.doctorId = did;
            savePatients();
            cout << "Doctor Assigned!\n";
            return;
        }
    }
    cout << "Patient not found!\n";
}

// ---------------- APPOINTMENT SYSTEM ----------------
void addAppointment() {
    Appointment a;

    cout << "Patient ID: ";
    cin >> a.patientId;

    cout << "Doctor ID: ";
    cin >> a.doctorId;

    cout << "Time Slot (e.g. 10AM, 2PM, 6PM): ";
    cin >> a.timeSlot;

    appointments.push_back(a);
    saveAppointments();

    cout << "Appointment Booked!\n";
}

// ---------------- SHOW APPOINTMENTS ----------------
void showAppointments() {
    cout << "\n--- Appointments ---\n";
    for (auto a : appointments) {
        cout << "Patient ID: " << a.patientId
             << " Doctor ID: " << a.doctorId
             << " Time: " << a.timeSlot << endl;
    }
}

// ---------------- DUTY ROSTER ----------------
void showRoster() {
    cout << "\n--- Doctor Duty Roster ---\n";
    for (auto d : doctors)
        cout << d.name << " (ID: " << d.id << ") -> " << d.shift << endl;

    cout << "\n--- Nurse Duty Roster ---\n";
    for (auto n : nurses)
        cout << n.name << " (ID: " << n.id << ") -> " << n.shift << endl;
}

// ---------------- TREAT PATIENT ----------------
void treatPatient() {
    if (pq.empty()) {
        cout << "No patients!\n";
        return;
    }

    Patient p = pq.top();
    pq.pop();

    cout << "Treating Patient: " << p.name << endl;
}

// ---------------- MENU ----------------
void menu() {
    int ch;

    do {
        cout << "\n===== HOSPITAL SYSTEM =====\n";
        cout << "1. Add Doctor\n";
        cout << "2. Add Nurse\n";
        cout << "3. Add Patient\n";
        cout << "4. Assign Doctor\n";
        cout << "5. Duty Roster\n";
        cout << "6. Treat Patient\n";
        cout << "7. Add Appointment\n";
        cout << "8. Show Appointments\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        switch (ch) {
        case 1: addDoctor(); break;
        case 2: addNurse(); break;
        case 3: addPatient(); break;
        case 4: assignDoctor(); break;
        case 5: showRoster(); break;
        case 6: treatPatient(); break;
        case 7: addAppointment(); break;
        case 8: showAppointments(); break;
        }
    } while (ch != 0);
}

// ---------------- MAIN ----------------
int main() {
    loadDoctors();
    loadNurses();
    loadPatients();

    menu();
    return 0;
}