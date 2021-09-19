#include<iostream>
#include<cmath>

using namespace std;

void LogAndExit(const char* log,int exit_code)
{
    printf("exit with log:  %s",log);
    exit(exit_code);
}

//template<typename T>
void CoutInLine()
{
    cout<<endl;
}

template<typename T1, typename ...Args>
void CoutInLine(T1 t1,Args... args)
{
    cout<<t1<<"  ";
    CoutInLine(args...);
}

template<typename T, int N=3>
void CoutNumber(T t)
{    
    if(t<=0)
    {
        return;
    }
    double p=pow(10,N);//p取double 见https://stackoverflow.com/questions/9704195/why-pow10-5-9-999-in-c
    long long t0=std::floor(t/p); 
    //cout<<p<<"++"<<t0<<"__"<<t-p*t0<<"++";   
    CoutNumber(t0);
    if(t0>0)
    {
        cout<<",";
    }
    cout<<t-p*t0;
}


