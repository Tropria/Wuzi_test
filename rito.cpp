// rito.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b
using namespace std;
int subtractProductAndSum(int n) {
    int prod = 1, sum = 0;
    if (n == 0) return 0;
    int temp = n;
    int cur = 0;
    while (temp > 0) {
        cur = temp % 10;//��ȡ��ǰλ
        temp = temp / 10;
        prod = prod * cur;
        sum = sum + cur;
    }
    cout << prod << " " << sum << endl;
    return prod - sum;
    
}
vector<int> decompressRLElist(vector<int>& nums) {
    int n = nums.size();
    vector<int> res;
    int freq = 0, val = 0;
    for (int i = 0; i < n/2; ++i) {
        freq = nums[2*i];
        val = nums[2 * i + 1];
        for (int j = 0;j < freq;++j) {
            res.push_back(val);
        }
    }
    return res;
}

template<typename T> class Arr {
public:
    Arr():mArray(0), m(3){
        mArray = new T[3 * 3];
        m = 3;
    }
    ~Arr() { 
        delete[] mArray; 
        mArray = 0;
    }
    T& operator()(int x, int y) {
        std::cout << "non-const" << std::endl;
        return mArray[x * m + y];
    }
    const T& operator()(int x, int y) const{
        std::cout << "const" << std::endl;
        return mArray[x * m + y];
    }
    const int& test() const {
        m = 100;
        return m;
    }
private:
    T* mArray;
    int m;
};

class B {
public:
    B() { cout << "B construct" << endl; }
    ~B() { cout << "B destruct" << endl; }
};

class An {
    B b;
    int* ar;
public:
    An() {
        ar = new int[10];
    }
    ~An() {
        delete[] ar;
        ar = 0;
    }

};

//0����û��5���� 1����5��1��2����5��2
int checkIsFive(int a[15][15], int x, int y) {
    int o = a[y][x];//��ǰ����
    //����Ƿ��Ǻ�or��
    if (o != 1 && o != 2) return 0;
    int j = y, i = x;
    //���Ҽ��
    j = y; i = x + 1;
    for (; i < x + 5 && j < 15 && i < 15;) {
        if (a[j][i] != o) break;
        ++i;
    }
    if (i == x + 5) return o;
    //����
    j = y + 1; i = x;
    for (; j < y + 5 && j < 15 && i < 15;) {
        if (a[j][i] != o) break;
        ++j;
    }
    if (j == y + 5) return o;
    //�����¼��
    j = y + 1; i = x + 1;
    for (; i < x + 5 && j < y + 5 && j < 15 && i < 15;) {
        if (a[j][i] != o) break;
        ++j; ++i;
    }
    if (i == x + 5) return o;
    //�����¼��
    j = y + 1; i = x - 1;
    for (; i > x - 5 && j < y + 5 && i >= 0 && j < 15; ) {
        if (a[j][i] != o) break;
        ++j; --i;
    }
    if (j == y + 5) return o;
    return 0;
}
//����Ƿ���4�4������ǰ��Ϊ�գ�������1����1�� ����2����2
int checkIsFourAlive(int a[15][15], int x, int y) {
    int m = a[y][x];//��ǰ����
    int temp;
    //����Ƿ��Ǻ�or��,���������������Ϊ������Ҫ0��ʼ0������
    if (m == 1 || m == 2) return 0;
    int j = y, i = x;
    //���Ҽ��
    j = y; i = x + 1;
    temp = a[j][i];
    if (temp == 0) return 0;
    for (i=i+1; i < x + 5 && i >= 0 && j >= 0 && j < 15 && i < 15;) {
        if (a[j][i] != temp) break;
        ++i;
    }
    if (i == x + 5 && i<15 && a[j][i]==0) return temp;
    //����
    j = y + 1; i = x;
    temp = a[j][i];
    if (temp == 0) return 0;
    for (j = j + 1; j < y + 5 && i >= 0 && j >= 0 && j < 15 && i < 15;) {
        if (a[j][i] != temp) break;
        ++j;
    }
    if (j == y + 5 && j<15 && a[j][i]==0) return temp;
    //�����¼��
    j = y + 1; i = x + 1;
    temp = a[j][i];
    if (temp == 0) return 0;
    for (j=j+1, i=i+1; i < x + 5 && i >= 0 && j >= 0 && j < 15 && i < 15;) {
        if (a[j][i] != temp) break;
        ++j; ++i;
    }
    if (i == x + 5 && j<15 && i<15 &&a[j][i]==0) return temp;
    //�����¼��
    j = y + 1; i = x - 1;
    temp = a[j][i];
    if (temp == 0) return 0;
    for (j=j+1, i=i-1; i > x - 5 && i >= 0 && j >= 0 && j < 15 && i < 15;) {
        if (a[j][i] != temp) break;
        ++j; --i;
    }
    if (j == y + 5 && j<15 && i>=0 && a[j][i]==0) return temp;
    return 0;
}

//�ж������Ƿ����������ҹ���8������ �е�ĳͬһֱ����
bool isOnSameLine(int a[15][15], int x1, int y1, int x2, int y2) {
    if (x1 == x2 || y1 == y2) {//���ˮƽ���ߴ�ֱ��������ͬ
        return true;
    }
    //�ж��Ƿ���ͬһб�Խ��߷�����
    if ((x1 - x2) == (y1 - y2) || (x1 - x2) == (y2 - y1)) {
        return true;
    }
    return false;
}

//���������ۺ���
int evaluation(int a[15][15], int x_last, int y_last) {
    int curColor = a[y_last][x_last];
    //�������һ������Ϊ������Χ��9*9��Χ
    int y_min = min(y_last - 4, 0);
    int y_max = max(y_last + 4, 14);
    int x_min = min(x_last - 4, 0);
    int x_max = max(x_last + 4, 14);

    int count1m2 = 0;
    //����9*9��Χ
    for (int y = y_min; y <= y_max; ++y) {
        for (int x = x_min; x <= x_max; ++x) {
            //�������5������1����maxint��2����minint
            int temp = checkIsFive(a, x, y);
            if (temp == 1) 
                return INT_MAX;
            if (temp == 2)
                return INT_MIN;
            //�������4�1����maxint, 2����minint
            //ע�⣺���ͬʱ����������4���Ϊ��һ���Ѿ����Ϊ��ʤ�����Լ�֦�󲻻����������
            //�ʲ����������4�������
            int temp2 = checkIsFourAlive(a, x, y);
            if (temp2 == 1)
                return INT_MAX;
            if (temp2 == 2)
                return INT_MIN;
            //������������Ը������ڣ�����������ֵ��Ϊ����ֵ����
            if (a[y][x] == 1) {
                ++count1m2;
            }
            if (a[y][x] == 2) {
                --count1m2;
            }
            if (a[y][x]!=0 && isOnSameLine(a, x_last, y_last, x, y)) {//�����ͬһֱ����
                if (a[y][x] == 1 && curColor == 1) { count1m2 += 1; continue; }
                if (a[y][x] == 1 && curColor == 2) { count1m2 += 2; continue; }//��2��˵�Ļ�ѡ������1Ϊ��
                if (a[y][x] == 2 && curColor == 2) { count1m2 -= 1; continue; }
                if (a[y][x] == 2 && curColor == 1) { count1m2 -= 2; continue; }//��1��˵�Ļ�ѡ������2Ϊ��
            }
        }
    }
    return count1m2;


}
int main()
{
    int a[15][15] = {
        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
        {0,0,0,2,2, 2,2,0,0,0, 0,0,0,0,0},
        {0,0,0,0,1, 1,0,0,0,0, 0,0,0,0,0},
        {0,0,1,1,2, 0,1,0,0,0, 0,0,0,0,0},
        {0,0,0,0,1, 0,0,0,0,0, 0,0,0,0,0},

        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},

        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
        {0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
    };
    cout << "onsame line " << isOnSameLine(a,4,4, 0,0) << endl;
    int n = evaluation(a, 4, 4);
    cout << "evaluation: " << n << endl;
    int x;
    cin >> x;
    return 0;
}
