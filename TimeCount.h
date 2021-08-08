#pragma once
#include<iostream>
#include<vector>
#include<chrono>

using namespace std;

class TC
{
public:
	TC(int n)
	{
		sections.resize(n, 0);
		nums.resize(n, 0);
	}
	chrono::high_resolution_clock::time_point t0;
	chrono::high_resolution_clock::time_point t1;
	vector<long long> sections;
	vector<long long> nums;
	inline void checkIn(int i)
	{
		t0 = chrono::high_resolution_clock::now();
	}
	inline void checkOut(int i)
	{
		t1 = chrono::high_resolution_clock::now();
		sections[i] += chrono::duration_cast<chrono::nanoseconds>(t1 - t0).count();
		nums[i]++;
	}
	inline void show()
	{
		int i = 0;
		for (auto section : sections)
		{
			cout <<i<<"   "<<section<<" nums "<<nums[i]<<" mean"<<(nums[i]>0 ? section/nums[i] : 0) << endl;
			i++;
		}
	}
};

class TS
{
public:
	chrono::high_resolution_clock::time_point t00;
	chrono::high_resolution_clock::time_point t0;
	inline TS()
		:t00(chrono::high_resolution_clock::now()),
		t0(chrono::high_resolution_clock::now())
	{	
		std::cout << "TS start...\n";
	}
	inline ~TS()
	{
		std::cout << "TS end...\n";
		std::cout<<"sum of time  "<< chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t00).count()<<endl;
	}
	inline void check(string str)
	{
		std::cout << str << "   " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t0).count()<<endl;
		t0 = chrono::high_resolution_clock::now();
	}
};