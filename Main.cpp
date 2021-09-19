#include "Debug.h"

int main()
{
    CoutInLine(1,2,3,3);
    CoutInLine(4,4,"tre",5,"234344");
    CoutNumber<double,4>(34567890.34);
    cout<<endl;
    CoutNumber<float,3>(7890.348888);
    //cout<<1<<endl;
    getchar();
}