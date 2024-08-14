#include<iostream>
#include<thread>
using namespace std;

void function_1(){
    cout<<"Beauty is the only skin-deep"<< endl;
}


class C1{
    public:
    void operator()(string& msg){


        for(int i=0;i>-100;i--){
            cout<<"From t1"<< i << endl;
            cout<<msg<<endl;
            msg="New Message";
        }
    }
} ;
int main(){
    function_1();
    C1 demo;

    string s="Hello World";

    thread t1((C1()),ref(s)); //t1 start running
    cout<<t1.get_id()<<endl;

    
    try{
        for(int i=0;i<100;i++){
        cout<<"main Thread "<<i<<endl;
    }
    }
    catch(...){
        t1.join();
        throw;
    }
    t1.join(); // main thread wait for t1 to finish 
    cout<<s;

    // thread t2(function_1);// t2 will freely on its own --deamon process
    // t2.detach();

    // if(t2.joinable()){
    //     t2,join();
    // }

    return 0;
}