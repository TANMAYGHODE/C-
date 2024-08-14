#include<iostream>
#include<thread>
#include<mutex>
#include <fstream> // Include this header for ofstream


using namespace std;

// mutex mu;
/**
void shared_print(string msg,int id){
    
    lock_guard<mutex> guard(mu);//Always be unlocked
    //mu.lock();// locks the resource
    //If cout throws exception then cout is permanently locked 
    cout<< msg << id << endl; // Only one thread will use the resource at a time
    //mu.unlock();// Unlock the resource 
}
**/

class Log {
    mutex m_mutex;
    ofstream f;

public:
    // Constructor to open the log file
    Log() {
        f.open("log.txt");
        if (!f.is_open()) {
            cerr << "Failed to open log.txt" << endl;
        }
    }

    // Destructor to close the log file
    ~Log() {
        if (f.is_open()) {
            f.close();
        }
    }

    // Function to safely print to the log file
    void shared_print(const string &id, int value) {
        lock_guard<mutex> locker(m_mutex); // Always be unlocked
        f << "From " << id << " : " << value << endl;
        // Never return f to the outside world
        // Ex: ofstream &getStream() { return f; }
        // Never pass f as an argument;
        // void processf(void fun(ofstream&)) { fun(f); }
    }
};

void function_1(Log &log) {
    for (int i = 0; i >= -100; i--) {
        log.shared_print("From t1 :", i);
        // cout<<"From t1 "<<i<<endl;
    }
}


void function_2(){
    for(int i=0; i<=100; i++){
        cout<<"From t2 "<<i<<endl;
    }
}

int main() {
    Log log;
    thread t1(function_1, ref(log)); // Pass log by reference

    for (int i = 0; i <= 100; i++) {
        log.shared_print("From main :", i);
        // cout<<"From main "<<i<<endl;
    }

    t1.join(); // Wait for t1 to finish

    return 0;
}
