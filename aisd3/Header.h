#include <stdio.h>
#include <iostream>
#include <list>

using namespace std;

template<typename T>
struct List {
    double degree;
    T coefficent;
    List* next;
};

template<typename T>
class Equalization
{
public:

    list<List<T>> head;

    int count = 0;

    auto begin() { return head.begin(); }

    auto end() { return head.end(); }

    auto cbegin() const { return head.cbegin(); }

    auto cend() const { return head.cend(); }

    Equalization(T coefficent, double degree);
    ~Equalization();

    List<T>* GetHead();

    void SetHead(List<T>* head);

    bool DetectOldDegree(T coefficent, double degree);

    void Set(T coefficent, double degree);

    int DeleteElement(double degree);

    void Derivative();

    void Multiplication(T value);

    void Calculation(T x);


    void operator -(Equalization& src);

    void operator +(Equalization& src);


    int operator[](double degree);

};


class EClassException
{
protected:
    char _err[256];
public:
    EClassException(const char* err);
    void Print();
};