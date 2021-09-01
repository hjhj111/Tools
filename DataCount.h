#pragma once
#include<vector>

using namespace std;

template<typename T>
class DataCount
{
public:
	//DataCount() = delete;

	DataCount()
	{
		
	}

	void addData(T t)
	{
		rawData.emplace_back(t);
		if (t < minData)
		{
			minData = t;
		}
		if (t > maxData)
		{
			maxData = t;
		}
	}
	
	void initCount(int dataDividedSize)
	{
		data.resize(dataDividedSize, 0);
		count.resize(dataDividedSize, 0);
		T delt = (maxData - minData) / dataDividedSize;
		//init data
		for (int i = 0; i < dataDividedSize; i++)
		{
			data[i] = minData + delt * i;
		}
		data[dataDividedSize - 1] = maxData;
		//init count
		for (auto& rawdata : rawData)
		{
			for (int i = 0; i < dataDividedSize-1; i++)
			{
				if (rawData >= minData + i * delt && rawdata < minData + (i + 1) * delt)
				{
					count[i]++;
				}				
			}
			if (rawdata >= minData + (dataDividedSize - 1) * delt && rawdata <= maxData)
			{
				count[dataDividedSize - 1]++;
			}
		}
	}

	~DataCount()
	{

	}

private:
	vector<T> data;
	vector<int> count;
	vector<T> rawData;
	T minData;
	T maxData;
};

