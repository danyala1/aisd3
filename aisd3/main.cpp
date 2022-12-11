#include <stdio.h>
#include <iostream>
#include "Header.h"
#include <conio.h>
#include <complex>

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, Equalization<T> obj)
{
    bool FirstStart = true;
    cout << "\n���� ������������������: ";
    while (obj.head) {
        if (obj.head->coefficent == T(0))
        {
            obj.DeleteElement(obj.head->degree);
            FirstStart = true;
        }
        if (!FirstStart && obj.head->coefficent > T(0)) cout << "+";
        if (obj.head->coefficent != T(1)) cout << obj.head->coefficent;
        if (obj.head->degree != 0) cout << "x";
        else cout << obj.head->coefficent;
        if (obj.head->degree < 0) { cout << "^(" << obj.head->degree << ")"; }
        else if (obj.head->degree != 1 && obj.head->degree != 0) cout << "^" << obj.head->degree;

        obj.head = obj.head->next;
        FirstStart = false;
    }
    cout << "\n";
    return os;
}

ostream& operator<< (ostream& os, Equalization<complex<float>> obj)
{
    bool FirstStart = true;
    cout << "\n���� ������������������: ";
    while (obj.head) {
        if (real(obj.head->coefficent) == 0 and imag(obj.head->coefficent) == 0)
        {
            obj.DeleteElement(obj.head->degree);
            FirstStart = true;
        }
        if (!FirstStart && real(obj.head->coefficent) > 0) cout << "+";
        if (obj.head->coefficent != complex<float>(1)) cout << obj.head->coefficent;
        if (obj.head->degree != 0) cout << "x";
        else cout << obj.head->coefficent;
        if (obj.head->degree < 0) { cout << "^(" << obj.head->degree << ")"; }
        else if (obj.head->degree != 1 && obj.head->degree != 0) cout << "^" << obj.head->degree;

        obj.head = obj.head->next;
        FirstStart = false;
    }
    cout << "\n";
    return os;
}

ostream& operator<< (ostream& os, Equalization<complex<double>> obj)
{
    bool FirstStart = true;
    cout << "\n���� ������������������: ";
    while (obj.head) {
        if (real(obj.head->coefficent) == 0 and imag(obj.head->coefficent) == 0)
        {
            obj.DeleteElement(obj.head->degree);
            FirstStart = true;
        }
        if (!FirstStart && real(obj.head->coefficent) > 0) cout << "+";
        if (obj.head->coefficent != complex<double>(1)) cout << obj.head->coefficent;
        if (obj.head->degree != 0) cout << "x";
        else cout << obj.head->coefficent;
        if (obj.head->degree < 0) { cout << "^(" << obj.head->degree << ")"; }
        else if (obj.head->degree != 1 && obj.head->degree != 0) cout << "^" << obj.head->degree;

        obj.head = obj.head->next;
        FirstStart = false;
    }
    cout << "\n";
    return os;
}


double CheckDegree()
{
    double number = 0;
    while (!(cin >> number) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Input correct value" << endl;
    }
    return number;
}

int CheckChoise()
{
    int number = 0;
    while (!(cin >> number) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Enter a number" << endl;
    }
    return number;
}

template<class T>
T CheckCoefficient()
{
    T number = 0;
    while (!(cin >> number) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Enter a number" << endl;
    }
    return number;
}


template<typename T>
void Menu1() {
    try
    {
        double degree;
        T coefficent;
        int choice;
        setlocale(LC_ALL, "RUS");
        cout << "��������� ���� �� ������, ������� ���������� ������� ��������: " << endl;
        coefficent = CheckCoefficient<T>();
        cout << "������� ��� �������: " << endl;
        degree = CheckDegree();
        Equalization<T> A(coefficent, degree);
        bool flag = true;
        while (flag) {
            system("cls");
            A.DeleteElement(0);
            cout << A;
            cout << "�������� ��������:\n1)�������� ����� �������\n2)�������� �� ������\n3)��������� �\n4)����� �����������\n5)����� � ������ �����������\n6)������� �� ���� ������ ���������\n7)��������������� ����������\n8)������� �������\n9)�����\n";
            choice = CheckChoise();
            if (choice == 1)
            {
                cout << "������� ���������� ������ ��������: " << endl;
                coefficent = CheckCoefficient<T>();
                cout << "������� ��� �������: " << endl;
                degree = CheckDegree();
                A.Set(coefficent, degree);
            }
            else if (choice == 2) {
                cout << "������� �������� �� ������� ������ ��������: " << endl;
                degree = CheckDegree();
                A.Multiplication(degree);
            }
            else if (choice == 3) {
                cout << "������� �������� �: " << endl;
                degree = CheckDegree();
                A.Calculation(degree);
            }
            else if (choice == 4) {
                A.Derivative();
            }
            else if (choice == 5 || choice == 6) {
                bool SumOperation = false;
                if (choice == 5) SumOperation = true;
                Equalization<T> B(0, 0);
                do {
                    cout << "�������� ���������� �������� ������ ����������: ";
                    coefficent = CheckCoefficient<T>();
                    cout << "�������� ������� �������� ������ ����������: ";
                    degree = CheckDegree();
                    B.Set(coefficent, degree);
                    cout << "�������� ��� ���� ������� � ����������? \n1)��\n2)���\n";
                    choice = CheckChoise();
                } while (choice == 1);
                if (SumOperation) A + B;
                else A - B;
            }
            else if (choice == 7) {
                cout << "�������� ������� �������� ������� �����������: ";
                degree = CheckDegree();
                A[degree];
            }
            else if (choice == 8) {
                cout << "�������� ������� �������� ������� �������: ";
                degree = CheckDegree();
                if (A.DeleteElement(degree) == 0) cout << "��� ������ �������� :(" << endl;
            }
            else if (choice == 9) {
                flag = false;
            }
            else {
                system("CLS");
            }
            system("pause");
        }
    }
    catch (EClassException& err)
    {
        err.Print();
    }

}

int main()
{
    while (true) {
        system("clear");
        cout << "Choose type:" << endl;;
        cout << "[1] - int" << endl;;
        cout << "[2] - float" << endl;;
        cout << "[3] - double" << endl;;
        cout << "[4] - complex (float)" << endl;;
        cout << "[5] - complex (double)" << endl;;
        cout << "[ESC] - Exit" << endl;;

        int Choice = _getch();
        system("cls");
        switch (Choice)
        {
        case 49:
            cout << "type - int" << endl;
            Menu1<int>();
            break;
        case 50:
            cout << "type - float" << endl;
            Menu1<float>();
            break;
        case 51:
            cout << "type - double" << endl;
            Menu1<double>();
            break;
        case 52:
            cout << "type - complex(float)" << endl;
            Menu1<std::complex<float>>();
            break;
        case 53:
            cout << "type - complex(double)" << endl;
            Menu1<complex<double>>();
            break;
        case 27:
            return EXIT_SUCCESS;
        default:
            system("clear");
            break;
        }
        system("cls");
    }
}
