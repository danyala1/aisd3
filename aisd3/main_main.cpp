#include <stdio.h>
#include <iostream>
#include <complex>
#include <conio.h>
#include <list>

using namespace std;


template<typename T>
class Equalization
{
public:
    struct Coefficent {
        double degree;
        T coefficent;
        Coefficent(T coefficent, double degree) : degree(degree), coefficent(coefficent) {}
    };
    int count = 0;
    list<Coefficent> head;
    Equalization(T coefficent, double degree)
    {
        if (coefficent != T(0)) {
            //this->head = new list<T>;
            Coefficent pointer(coefficent, degree);
            head.push_front(pointer);
            //Set(0, coefficent, degree);
            //this->head.degree = degree;
            //this->head->coefficent = coefficent;
            count = 1;
        }
    }

    Equalization() = default;

    ~Equalization() = default;

    Equalization(Equalization<T>& other) = default;

    bool DetectOldDegree(T coefficent, double degree)
    {

        auto i = cbegin();
        while (i != cend())
        {
            if (i->degree == degree) {
                Coefficent pointer(i->coefficent + coefficent, degree);
                //T coefficent = i->coefficent;
                head.erase(i);


                head.push_front(pointer);
                //i->coefficent = i->coefficent + coefficent;
                std::cout << "\nСтепени " << degree << " изменен коэффицент на " << coefficent << endl;
                return true;
            }
            i++;
        }
        return false;
    }
    void Set(T coefficent, double degree)
    {
        if (!DetectOldDegree(coefficent, degree))
        {
            if (coefficent != T(0)) {
                Coefficent pointer(coefficent, degree);
                head.push_front(pointer);
                count++;
            }
        }

    }
    int DeleteElement(double degree) {
        int NowCount = 0;
        auto i = cbegin();
        while (i != cend())
        {
            if (i->degree == degree)
            {
                head.erase(i);
                count--;
                return 1;
            }
            i++;
            NowCount++;
        }
        return 0;
    }
    void Derivative() {
        cout << "\nНаша производная: ";
        for (auto i = this->cbegin(); i != this->cend(); i++)
        {
            if (i->degree != 0)cout << "\n" << i->coefficent * i->degree;
            if (i->degree != 1 && i->degree != 0) {
                cout << "x^" << i->degree - 1;
            }
        }
        cout << "\n";
    }

    void Calculation(T x) {
        //list<T>* FunctionHead = GetHead();
        T sum = 0;
        //while (FunctionHead) {
        auto i = cbegin();
        while (i != cend())
        {
            sum += i->coefficent * T(pow(x, i->degree));
            //FunctionHead = FunctionHead->next;
            i++;
        }
        cout << "При x=" << x << " значение многочлена равно " << sum << endl;
    }
    void operator*(T value) {
        list<Coefficent> tmp;
        for (auto i = this->cbegin(); i != this->cend(); i++)
        {
            Coefficent pointer(i->coefficent * T(value), i->degree);
            tmp.push_front(pointer);
            //i = j;
            //cout << i->coefficent;

        }
        head.clear();
        for (auto i = tmp.cbegin(); i != tmp.cend(); i++) Set(i->coefficent, i->degree);

        //head.
        //head.merge(tmp);
        cout << "\nНаш многочлен успешно был умножен...\n";

    }
    void operator -(Equalization& src)
    {
        list<Coefficent> tmp;
        bool SearchSuccesesful;


        for (auto StartHeadB = src.cbegin(); StartHeadB != src.cend(); StartHeadB++) {
            SearchSuccesesful = false;
            for (auto FunctionHead = cbegin(); FunctionHead != cend(); FunctionHead++) {

                if (FunctionHead->degree == StartHeadB->degree)
                {
                    SearchSuccesesful = true;
                    Coefficent pointer(FunctionHead->coefficent - StartHeadB->coefficent, FunctionHead->degree);
                    tmp.push_front(pointer);
                    //head.erase(FunctionHead);
                    //FunctionHead->coefficent -= StartHeadB->coefficent;
                    break;
                }
                else {
                    Coefficent pointer(FunctionHead->coefficent, FunctionHead->degree);
                    tmp.push_front(pointer);
                }
                //FunctionHead++;
            }
            head.clear();
            for (auto i = tmp.cbegin(); i != tmp.cend(); i++) Set(i->coefficent, i->degree);
            if (!SearchSuccesesful)
            {
                Set(StartHeadB->coefficent * T(-1), StartHeadB->degree);
            }
            //StartHeadB++;
        }
    }
    void operator +(Equalization& src)
    {
        list<Coefficent> tmp;
        bool SearchSuccesesful;


        for (auto StartHeadB = src.cbegin(); StartHeadB != src.cend(); StartHeadB++) {
            SearchSuccesesful = false;
            for (auto FunctionHead = cbegin(); FunctionHead != cend(); FunctionHead++) {

                if (FunctionHead->degree == StartHeadB->degree)
                {
                    SearchSuccesesful = true;
                    Coefficent pointer(FunctionHead->coefficent + StartHeadB->coefficent, FunctionHead->degree);
                    tmp.push_front(pointer);
                    //head.erase(FunctionHead);
                    //FunctionHead->coefficent -= StartHeadB->coefficent;
                    break;
                }
                else {
                    Coefficent pointer(FunctionHead->coefficent, FunctionHead->degree);
                    tmp.push_front(pointer);
                }
                //FunctionHead++;
            }
            head.clear();
            for (auto i = tmp.cbegin(); i != tmp.cend(); i++) Set(i->coefficent, i->degree);
            if (!SearchSuccesesful)
            {
                Set(StartHeadB->coefficent, StartHeadB->degree);
            }
            //StartHeadB++;
        }
    }
    
    int operator[](double degree) {
        auto FunctionHead = cbegin();
        //auto StartHeadB = src.cbegin();
        //list<T>* FunctionHead = GetHead();
        while (FunctionHead != cend()) {
            if (FunctionHead->degree == degree)
            {
                double coefficent;
                cout << "Введите новый коэффицент для степени " << FunctionHead->degree << ": ";
                cin >> coefficent;
                if (coefficent != 0) {
                    Coefficent pointer(coefficent, FunctionHead->degree);
                    head.push_front(pointer);
                    head.erase(FunctionHead);
                    //FunctionHead->coefficent = coefficent;
                }
                else { cout << "Нельзя менять на ноль "; }
                return 0;
            }
            FunctionHead++;
        }
        cout << "Нет такого элемента :( \n";
        return 0;
    }
    auto cbegin()  const { return head.begin(); }

    auto cend()  const { return head.end(); }

    bool detect_coefficent_0() {
        auto FunctionHead = cbegin();
        while (FunctionHead != cend())
        {
            if (FunctionHead->coefficent == T(0))
            {
                DeleteElement(FunctionHead->degree);
                return true;
            }
            FunctionHead++;
        }
        return false;
    }
};



template<typename T>
class Equalization<complex<T>>
{
public:
    struct Coefficent {
        double degree;
        complex<T> coefficent;
        Coefficent(complex<T> coefficent, double degree) : degree(degree), coefficent(coefficent) {}
    };
    int count = 0;
    list<Coefficent> head;
    Equalization(complex<T> coefficent, double degree)
    {
        if (real(coefficent) != T(0) || imag(coefficent) != 0) {
            //this->head = new list<T>;
            Coefficent pointer(coefficent, degree);
            head.push_front(pointer);
            //Set(0, coefficent, degree);
            //this->head.degree = degree;
            //this->head->coefficent = coefficent;
            count = 1;
        }
    }
    Equalization() = default;
    ~Equalization() = default;
    Equalization(Equalization<complex<T>>& other) = default;
    bool DetectOldDegree(complex<T> coefficent, double degree)
    {

        auto i = cbegin();
        while (i != cend())
        {
            if (i->degree == degree) {
                Coefficent pointer(i->coefficent + coefficent, degree);
                //T coefficent = i->coefficent;
                head.erase(i);


                head.push_front(pointer);
                //i->coefficent = i->coefficent + coefficent;
                std::cout << "\nСтепени " << degree << " изменен коэффицент на " << coefficent << endl;
                return true;
            }
            i++;
        }
        return false;
    }
    void Set(complex<T> coefficent, double degree)
    {
        if (!DetectOldDegree(coefficent, degree))
        {
            if (real(coefficent) != T(0) || imag(coefficent) != 0) {
                Coefficent pointer(coefficent, degree);
                head.push_front(pointer);
                count++;
            }
        }

    }
    int DeleteElement(double degree) {
        int NowCount = 0;
        auto i = cbegin();
        while (i != cend())
        {
            if (i->degree == degree)
            {
                head.erase(i);
                count--;
                return 1;
            }
            i++;
            NowCount++;
        }
        return 0;
    }
    void Derivative()
    {

        cout << "\nНаша производная: ";
        for (auto i = this->cbegin(); i != this->cend(); i++)
        {
            complex < T > tmp = (i->degree, i->degree);
            if (i->degree != 0)cout << "\n" << i->coefficent * tmp;
            if (i->degree != 1 && i->degree != 0) {
                cout << "x^" << i->degree - 1;
            }
        }
        cout << "\n";
    }
    void Calculation(complex<T> x) {
        //list<T>* FunctionHead = GetHead();
        complex<T> sum = 0;
        //while (FunctionHead) {
        auto i = cbegin();
        while (i != cend())
        {
            sum += i->coefficent * complex<T>(pow(x, i->degree));
            //FunctionHead = FunctionHead->next;
            i++;
        }
        cout << "При x=" << x << " значение многочлена равно " << sum << endl;
    }
    void operator*(complex<T> value) {
        list<Coefficent> tmp;
        for (auto i = this->cbegin(); i != this->cend(); i++)
        {
            Coefficent pointer(i->coefficent * complex<T>(value), i->degree);
            tmp.push_front(pointer);
            //i = j;
            //cout << i->coefficent;

        }
        head.clear();
        for (auto i = tmp.cbegin(); i != tmp.cend(); i++) Set(i->coefficent, i->degree);

        //head.
        //head.merge(tmp);
        cout << "\nНаш многочлен успешно был умножен...\n";

    }
    void operator -(Equalization& src)
    {
        list<Coefficent> tmp;
        bool SearchSuccesesful;


        for (auto StartHeadB = src.cbegin(); StartHeadB != src.cend(); StartHeadB++) {
            SearchSuccesesful = false;
            for (auto FunctionHead = cbegin(); FunctionHead != cend(); FunctionHead++) {

                if (FunctionHead->degree == StartHeadB->degree)
                {
                    SearchSuccesesful = true;
                    Coefficent pointer(FunctionHead->coefficent - StartHeadB->coefficent, FunctionHead->degree);
                    tmp.push_front(pointer);
                    //head.erase(FunctionHead);
                    //FunctionHead->coefficent -= StartHeadB->coefficent;
                    break;
                }
                else {
                    Coefficent pointer(FunctionHead->coefficent, FunctionHead->degree);
                    tmp.push_front(pointer);
                }
                //FunctionHead++;
            }
            head.clear();
            for (auto i = tmp.cbegin(); i != tmp.cend(); i++) Set(i->coefficent, i->degree);
            if (!SearchSuccesesful)
            {
                Set(StartHeadB->coefficent * T(-1), StartHeadB->degree);
            }
            //StartHeadB++;
        }
    }
    void operator +(Equalization& src)
    {
        list<Coefficent> tmp;
        bool SearchSuccesesful;


        for (auto StartHeadB = src.cbegin(); StartHeadB != src.cend(); StartHeadB++) {
            SearchSuccesesful = false;
            for (auto FunctionHead = cbegin(); FunctionHead != cend(); FunctionHead++) {

                if (FunctionHead->degree == StartHeadB->degree)
                {
                    SearchSuccesesful = true;
                    Coefficent pointer(FunctionHead->coefficent + StartHeadB->coefficent, FunctionHead->degree);
                    tmp.push_front(pointer);
                    //head.erase(FunctionHead);
                    //FunctionHead->coefficent -= StartHeadB->coefficent;
                    break;
                }
                else {
                    Coefficent pointer(FunctionHead->coefficent, FunctionHead->degree);
                    tmp.push_front(pointer);
                }
                //FunctionHead++;
            }
            head.clear();
            for (auto i = tmp.cbegin(); i != tmp.cend(); i++) Set(i->coefficent, i->degree);
            if (!SearchSuccesesful)
            {
                Set(StartHeadB->coefficent, StartHeadB->degree);
            }
            //StartHeadB++;
        }
    }
    
    int operator[](double degree) {
        auto FunctionHead = cbegin();
        //auto StartHeadB = src.cbegin();
        //list<T>* FunctionHead = GetHead();
        while (FunctionHead != cend()) {
            if (FunctionHead->degree == degree)
            {
                double coefficent;
                cout << "Введите новый коэффицент для степени " << FunctionHead->degree << ": ";
                cin >> coefficent;
                if (coefficent != 0) {
                    Coefficent pointer(coefficent, FunctionHead->degree);
                    head.push_front(pointer);
                    head.erase(FunctionHead);
                    //FunctionHead->coefficent = coefficent;
                }
                else { cout << "Нельзя менять на ноль "; }
                return 0;
            }
            FunctionHead++;
        }
        cout << "Нет такого элемента :( \n";
        return 0;
    }
    auto cbegin()  const { return head.begin(); }

    auto cend()  const { return head.end(); }

    bool detect_coefficent_0()
    {
        auto FunctionHead = cbegin();
        while (FunctionHead != cend())
        {
            if (real(FunctionHead->coefficent) == T(0) && imag(FunctionHead->coefficent) == T(0))
            {
                DeleteElement(FunctionHead->degree);
                return true;
            }
            FunctionHead++;
        }
        return false;
    }
};

class EClassException
{
protected:
    char _err[256];
public:
    EClassException(const char* err) {
        strncpy_s(_err, err, 255);
        _err[255] = 0;
    }
    void Print()
    {
        std::cout << _err << std::endl;
    }
};

template<typename T>
ostream& operator<<(ostream& os, Equalization<T> Obj)
{
    while (Obj.detect_coefficent_0()) Obj.detect_coefficent_0();
    for (auto i = Obj.cbegin(); i != Obj.cend(); i++) {

        cout << "\n" << i->coefficent;
        if (i->degree > 0 && i->degree != 1)cout << "x^" << i->degree;
        if (i->degree < 0) cout << "x^(" << i->degree << ")";
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

template <typename T>
void Menu1() {
    try
    {
        double degree;
        T coefficent;
        int choice;
        setlocale(LC_ALL, "RUS");
        cout << "Введите коэфффицент первого элемента: " << endl;
        coefficent = CheckCoefficient<T>();
        cout << "Введите степень первого элемента: " << endl;
        degree = CheckDegree();
        Equalization<T> A(coefficent, degree);
        bool flag = true;
        while (flag) {
            system("cls");
            cout << A;
            cout << "Выберите действие:\n1)Добавить новый элемент\n2)Умножить на скаляр\n3)Вычислить х\n4)Найти производную\n5)Сумма с другим многочленом\n6)Вычесть из него другой многочлен\n7)Средактировать коэффицент\n8)Удалить элемент\n\n9)Выход\n";
            choice = CheckChoise();
            if (choice == 1)
            {
                cout << "Введите коэффицент нового элемента: " << endl;
                coefficent = CheckCoefficient<T>();
                cout << "Введите степень нового элемента: " << endl;
                degree = CheckDegree();
                A.Set(coefficent, degree);
            }
            else if (choice == 2) {
                cout << "Введите значение скаляра: " << endl;
                coefficent = CheckCoefficient<T>();
                A* coefficent;
            }
            else if (choice == 3) {
                cout << "Введите значение х при котором вычисляем: " << endl;
                coefficent = CheckCoefficient<T>();
                A.Calculation(coefficent);
            }
            else if (choice == 4) {
                A.Derivative();
            }
            else if (choice == 5 || choice == 6) {
                bool SumOperation = false;
                if (choice == 5) SumOperation = true;
                Equalization<T> B(0, 0);
                do {
                    cout << "Введите коэффицент первого элемента нового многочлена: ";
                    coefficent = CheckCoefficient<T>();
                    cout << "Введите степень первого элемента нового многочлена: ";
                    degree = CheckDegree();
                    B.Set(coefficent, degree);
                    cout << "Хотите добавить ещё один элемент? \n1)Да\n2)Нет\n";
                    choice = CheckChoise();
                } while (choice == 1);
                if (SumOperation) A + B;
                else A - B;
            }
            else if (choice == 7) {
                cout << "Выберите степень выбранного элемента";
                degree = CheckDegree();
                A[degree];
            }
            else if (choice == 8) {
                cout << "Выберите степень выбранного элемента: ";
                degree = CheckDegree();
                if (A.DeleteElement(degree) == 0) cout << "Нет такого элемента :(" << endl;
            }
            else if (choice == 9) {
                flag = false;
            }
            else {
                cout << "Нет такого варианта\n";

            }
            cout << "Для продолжения нажмите любую клавишу\n";
            _getch();

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
