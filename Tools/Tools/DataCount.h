
#pragma once
#include<vector>
#include<matplot/matplot.h>
#include<matplot/backend/gnuplot.h>

using namespace std;

template<typename T>
class DataCount
{
public:
	//DataCount() = delete;

	DataCount(string name)
		:name_(name)

	{
		
	}

	~DataCount()
	{

	}

	void addData(T t)
	{
		raw_data_.emplace_back(t);
		if (t < min_data_)
		{
			min_data_ = t;
		}
		if (t > max_data_)
		{
			max_data_ = t;
		}
	}
	
	void InitCount(int dataDividedSize)
	{
		data_.resize(dataDividedSize, 0);
		count_.resize(dataDividedSize-1, 0);
		T delt = (max_data_ - min_data_) / dataDividedSize;
		//init data
		for (int i = 0; i < dataDividedSize; i++)
		{
			data_[i] = min_data_ + delt * i;
		}
		data_[dataDividedSize - 1] = max_data_;
		//init count
		for (auto& rawdata : raw_data_)
		{
			for (int i = 0; i < dataDividedSize-1; i++)
			{
				if (rawdata >= min_data_ + i * delt && rawdata < min_data_ + (i + 1) * delt)
				{
					count_[i]++;
				}				
			}
			if (rawdata >= min_data_ + (dataDividedSize - 1) * delt && rawdata <= max_data_)
			{
				count_[dataDividedSize - 2]++;
			}
		}
		//2·Ödata
		for (int i = 0; i < data_.size()-1; i++)
		{
			data_[i] = (data_[i] + data_[i + 1]) / 2.0;
		}
		data_.pop_back();
	}

	void ShowConsole()
	{
		cout << name_ << endl;
		for (auto data : data_)
		{
			cout << data << " " ;
		}
		cout << endl;
		for (auto count : count_)
		{
			cout << count << " " ;
		}
		cout << endl;
	}

	void ShowPlot()
	{
		static constexpr bool windows_should_persist_by_default = true;
		matplot::plot(data_, count_, ":");
		for (int i = 0; i < data_.size(); i++)
		{
			matplot::text(data_[i], count_[i], to_string(count_[i]));
		}
		matplot::save(name_+".svg");
		
		//matplot::hold(true);
	}

	T sum()//not right
	{
		if (sum_flag_)
		{
			return sum_;
		}
		//sum_ = accumulate(raw_data_.begin(), raw_data_.end(), 0);
		//T sum = 0;
		for (int i = 0; i < raw_data_.size(); i++)
		{
			auto sum = sum_ + raw_data_[i];
			//cout << sum <<"  "<< raw_data_[i]<<"++++++++++++++++++ + \n";
			//if (raw_data_[i] != 0)
			//{
			//	exit(-44444);
			//}
			if (sum < sum_)//Òç³ö
			{
				cout << "-----------------------------overflow\n";
				sums_.push_back(sum_);
				sums_flag_ = true;
				sum_ = raw_data_[i];
			}
			else
			{
				sum_ = sum;
			}
		}		
		sum_flag_ = true;
		return sum_;
	}

	T mean()
	{
		if (mean_flag_)
		{
			return mean_;
		}
		
		mean_ = sum() / raw_data_.size();
		if (!sums_flag_)
		{
			mean_flag_ = true;
			return mean_;
		}
		mean_ = 0;
		for (auto sum : sums_)
		{
			mean_ += ((double)sum / size());//ÓÐ½Ø¶ÏÎó²î
		}
		mean_flag_ = true;
		return mean_;
	}

	long long size()
	{
		return raw_data_.size();
	}

private:
	vector<T> data_;
	vector<int> count_;
	vector<T> raw_data_;
	bool sum_flag_ = false;
	bool sums_flag_ = false;
	bool mean_flag_= false;
	T sum_=0;
	vector<T>sums_;
	double mean_=0;

	T min_data_;
	T max_data_;
	string name_;
};

