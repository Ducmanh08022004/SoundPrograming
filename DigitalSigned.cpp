#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

class DigitalSigned
{
private:
    int samplingRate;
    int bitDepth;
    string numChannels;
    vector<int> data;

public:
    DigitalSigned() : samplingRate(0), bitDepth(0), numChannels("") {} // Constructor không tham số

    DigitalSigned(int sr, int bd, string nc, vector<int> d)
        : samplingRate(sr), bitDepth(bd), numChannels(nc), data(d) {} // Constructor có tham số
    DigitalSigned Multiplication(int a)                               // Nhân với hằng số
    {
        DigitalSigned result = *this;
        for (int &i : result.data)
        {
            i *= a;
        }
        return result;
    }

    DigitalSigned Multiplication(DigitalSigned b) // Nhân với tín hiệu khác
    {
        if (b.samplingRate != samplingRate)
        {
            cerr << "Lỗi: Sampling rate không khớp!" << endl;
            return DigitalSigned(); // Trả về object rỗng
        }

        DigitalSigned result(samplingRate, bitDepth, numChannels, {});
        int n = min(data.size(), b.data.size());
        for (int i = 0; i < n; i++)
        {
            result.data.push_back(data[i] * b.data[i]);
        }
        return result;
    }

    DigitalSigned Sum(DigitalSigned b) // Tổng hai tín hiệu
    {
        if (b.samplingRate != samplingRate)
        {
            cerr << "Lỗi: Sampling rate không khớp!" << endl;
            return DigitalSigned();
        }

        int n = max(data.size(), b.data.size());
        DigitalSigned result(samplingRate, bitDepth, numChannels, vector<int>(n, 0));

        for (int i = 0; i < n; i++)
        {
            int a_val = (i < data.size()) ? data[i] : 0;
            int b_val = (i < b.data.size()) ? b.data[i] : 0;
            result.data[i] = a_val + b_val;
        }
        return result;
    }

    DigitalSigned Timereversal() // Phép đảo thời gian
    {
        DigitalSigned result = *this; // Gắn result bằng object hiện tại
        reverse(result.data.begin(), result.data.end());
        return result;
    }

    DigitalSigned DelaySigned(int m) // Dịch thời gian
    {
        DigitalSigned result(samplingRate, bitDepth, numChannels, {});
        if (m > 0) // Dịch phải
        {
            result.data.assign(m, 0); // Chèn m số 0 vào đầu
            result.data.insert(result.data.end(), data.begin(), data.end());
        }
        else if (m < 0) // Dịch trái
        {
            if (abs(m) >= data.size())
                result.data.clear(); // Xóa hết nếu vượt quá giới hạn
            else
                result.data.assign(data.begin() + abs(m), data.end()); // Cắt lấy vector từ vị trí m đến hết
        }
        else
        {
            result.data = data; // Không thay đổi
        }
        return result;
    }

    DigitalSigned upSampling(int newSamplingRate) // Tăng tần số lấy mẫu
    {

        int k = newSamplingRate / samplingRate;
        DigitalSigned result(newSamplingRate, bitDepth, numChannels, {});
        for (int i = 0; i < data.size(); i++)
        {
            result.data.push_back(data[i]);
            for (int j = 1; j < k; j++)
            {
                result.data.push_back(0);
            }
        }
        return result;
    }

    DigitalSigned downSampling(int newSamplingRate) // Giảm tần số lấy mẫu
    {
        int k = samplingRate / newSamplingRate;
        DigitalSigned result(newSamplingRate, bitDepth, numChannels, {});
        for (int i = 0; i < data.size(); i += k)
        {
            result.data.push_back(data[i]);
        }
        return result;
    }

    DigitalSigned Convolution(DigitalSigned h) // Tích chập
    {
        if (h.samplingRate != samplingRate)
        {
            cerr << "Lỗi: Sampling rate không khớp!" << endl;
            return DigitalSigned();
        }

        int n_x = data.size();
        int n_h = h.data.size();
        int n_y = n_x + n_h - 1; // Kích thước kết quả

        DigitalSigned result(samplingRate, bitDepth, numChannels, vector<int>(n_y, 0));

        for (int n = 0; n < n_y; n++)
        {
            for (int m = 0; m < n_x; m++)
            {
                int h_index = n - m;
                if (h_index >= 0 && h_index < n_h)
                {
                    result.data[n] += data[m] * h.data[h_index];
                }
            }
        }
        return result;
    }
    DigitalSigned tuongQuan(DigitalSigned h) // Tương quan chéo
    {
        if (h.samplingRate != samplingRate)
        {
            cerr << "Lỗi: Sampling rate không khớp!" << endl;
            return DigitalSigned();
        }

        int n_x = data.size();
        int n_h = h.data.size();
        int n_y = n_x + n_h - 1; // Kích thước kết quả

        DigitalSigned result(samplingRate, bitDepth, numChannels, vector<int>(n_y, 0));

        for (int n = 0; n < n_y; n++)
        {
            for (int m = 0; m < n_x; m++)
            {
                int h_index = m - n;
                if (h_index >= 0 && h_index < n_h)
                {
                    result.data[n] += data[m] * h.data[h_index];
                }
            }
        }
        return result;
    }
};
