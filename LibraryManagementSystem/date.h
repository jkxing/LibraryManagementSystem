#pragma once
#include <iostream>
#include <string>
const int monthDay[13]{0,31,28,31,30,31,30,31,31,30,31,30,31 };
class Date {
    void init();
public:
    long long tothour;
    int year, month, day, hour;
    Date();
    Date(int y, int m=1,int d=1,int h=0);
    Date(long long t);
    Date(std::string s);
    long long toHour();
    std::string toString();
    virtual bool operator <(const Date &a) const;
    virtual bool operator <=(const Date &a) const;
    virtual bool operator >(const Date &a) const;
    virtual bool operator >=(const Date &a) const;
    friend std::ostream& operator<< (std::ostream&out, const Date &x);
    friend std::istream& operator>> (std::istream&in, Date &x);
};
class TimeLen :public Date {
    void init();
public:
    TimeLen() {}
    TimeLen(int y, int m=0, int d=0, int h=0);
    TimeLen(long long t);
    friend std::ostream& operator<< (std::ostream&out, const TimeLen &x);
    friend std::istream& operator>> (std::istream&in, TimeLen &x);
};
Date operator -(const Date &a, const TimeLen &b);
Date operator +(const Date &a, const Date &b);
Date operator +(const Date &a, const TimeLen &b);
TimeLen operator -(const Date &a, const Date &b);
bool operator ==(const Date &a, const Date &b);
bool operator ==(const TimeLen &a, const TimeLen &b);
