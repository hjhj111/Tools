/*
 * @Author: your name
 * @Date: 2021-09-19 20:54:49
 * @LastEditTime: 2022-01-05 13:56:33
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \Tools\Main.cpp
 */
#include "Debug.h"
#include "Timer.h"

int main()
{
    CoutInLine(1,2,3,3);
    CoutInLine(4,4,"tre",5,"234344");
    CoutNumber<double,4>(34567890.34);
    cout<<endl;
    CoutNumber<float,3>(7890.348888);
    //cout<<1<<endl;
    //getchar();

    Timer t;
    t.start(5000,[]()
        {
            CoutNumber<double,4>(34567890.34);
        }
    );
}