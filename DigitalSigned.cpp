#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

class DigitalSigned {
    private:
        int samplingRate;
        int bitDepth;
        string numChannels;
        vector<int> data;
    public:
        vector<int> Multiplication(int a)//Nhân với 1 hằng số
        {
            vector<int> result;
            for (int i:data)
            {
                result.push_back(a*i);
            }
            return result;
        }
        vector<int> Multiplication(vector<int> b)// Nhân với 1 tín hiệu khác
        {
            vector<int> result;
            int n = min(data.size(),b.size());
            for (int i=0;i<n;i++)
                {
                    result.push_back(data[i]*b[i]);
                }
            return result;
        }
        vector<int> Sum(vector<int> b)// Tổng 2 tín hiệu
        {
            vector<int> result;
            int n=max(data.size(),b.size());
            for (int i=0;i<n;i++)
            {
                result.push_back(data[i]+b[i]);
            }
            return result;
        }
        vector<int> Timereversal () // Phép đảo thời gian
        {
                vector<int> result=data;
                reverse(result.begin(),result.end());
                return result;
        }
};