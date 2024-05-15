#include <iostream>
#include <cmath>
#include <string>

using namespace std;



//завдання 2

// Абстрактний базовий клас Прогресія
class Progression {
protected:
    double a0; // перший член прогресії
    double constant; // постійна прогресії

public:
    Progression(double first, double constant) : a0(first), constant(constant) {}
    virtual ~Progression() {}

    // Віртуальна функція для обчислення суми прогресії
    virtual double sum(int n) const = 0;
};

// Клас для арифметичної прогресії
class ArithmeticProgression : public Progression {
public:
    ArithmeticProgression(double first, double diff) : Progression(first, diff) {}

    // Реалізація суми для арифметичної прогресії
    double sum(int n) const override {
        double an = a0 + n * constant;
        return (n + 1) * (a0 + an) / 2;
    }
};

// Клас для геометричної прогресії
class GeometricProgression : public Progression {
public:
    GeometricProgression(double first, double ratio) : Progression(first, ratio) {}

    // Реалізація суми для геометричної прогресії
    double sum(int n) const override {
        if (constant == 1.0) {
            return a0 * (n + 1);
        }
        else {
            double an = a0 * std::pow(constant, n);// pow це степінь
            return (a0 - an * constant) / (1 - constant);
        }
    }
};

//завдання 3
//Визначення класу File
class File {
    //Ключове слово, що вказує, що наступні члени класу будуть доступні тільки в класі та його похідних класах
protected:
    string fileName;// Поле класу для зберігання назви файлу
    int fileSize;//Поле класу для зберігання розміру файлу 

public:
    File(const string& name, int size) : fileName(name), fileSize(size) {}//Конструктор класу File, який приймає два аргументи: назву файлу і його розмір
    virtual ~File() {}//Віртуальний деструктор класу File

    virtual void printInfo() const {
        cout << "File Name: " << fileName << endl;
        cout << "File Size: " << fileSize << " bytes" << endl;
    }//Віртуальний метод, який виводить інформацію про файл. Викликається для виведення інформації про об'єкт

    friend ostream& operator<<(ostream& os, const File& file) {
        os << "File Name: " << file.fileName << endl;
        os << "File Size: " << file.fileSize << " bytes" << endl;
        return os;
    }//Перевантаження оператора виведення << для класу File, щоб зручно виводити об'єкти цього класу

    friend istream& operator>>(istream& is, File& file) {
        cout << "Enter File Name: ";
        is >> file.fileName;
        cout << "Enter File Size (in bytes): ";
        is >> file.fileSize;
        return is;
    }//Перевантаження оператора введення >> для класу File, щоб зручно вводити дані для об'єктів цього класу
};

class ReadableFile : public File {//Визначення класу WritableFile, який також успадковує клас File
public:
    ReadableFile(const string& name, int size) : File(name, size) {}

    void printInfo() const override {
        File::printInfo();
        cout << "Type: Readable File" << endl;
    }
};

class WritableFile : public File {
public:
    WritableFile(const string& name, int size) : File(name, size) {}

    void printInfo() const override {
        File::printInfo();
        cout << "Type: Writable File" << endl;
    }
};

class ReadWritableFile : public ReadableFile, public WritableFile {//Визначення класу ReadWritableFile, який успадковує класи ReadableFile та WritableFile, реалізуючи множинне успадкування
public:
    ReadWritableFile(const string& name, int size) : ReadableFile(name, size), WritableFile(name, size) {}

    void printInfo() const override {
        ReadableFile::printInfo();
        cout << "Type: Read-Writable File" << endl;
    }
};


void Task2(){
    double a0, constant;
    int n;

    // Введення даних для арифметичної прогресії
    std::cout << "Enter the first term of the arithmetic progression (a0): ";
    std::cin >> a0;
    std::cout << "Enter the difference of the arithmetic progression (d): ";
    std::cin >> constant;
    std::cout << "Enter the number of terms (n): ";
    std::cin >> n;

    Progression* ap = new ArithmeticProgression(a0, constant);

    // Введення даних для геометричної прогресії
    std::cout << "Enter the first term of the geometric progression (a0): ";
    std::cin >> a0;
    std::cout << "Enter the ratio of the geometric progression (r): ";
    std::cin >> constant;
    std::cout << "Enter the number of terms (n): ";
    std::cin >> n;

    Progression* gp = new GeometricProgression(a0, constant);

    std::cout << "Sum of arithmetic progression: " << ap->sum(n) << std::endl;//ap це вказівник
    std::cout << "Sum of geometric progression: " << gp->sum(n) << std::endl;

    delete ap;
    delete gp;
}

void Task3(){
    ReadableFile rFile("document.txt", 1024);
    WritableFile wFile("data.txt", 2048);
    ReadWritableFile rwFile("combined.txt", 4096);

    cout << "Readable File Info:" << endl;
    rFile.printInfo();
    cout << endl;

    cout << "Writable File Info:" << endl;
    wFile.printInfo();
    cout << endl;

    cout << "Read-Writable File Info:" << endl;
    rwFile.printInfo();
    cout << endl;

    cout << "Enter information for a new Readable File:" << endl;
    cin >> rFile;
    cout << "New Readable File Info:" << endl;
    cout << rFile << endl;
}
int main() {
    int choice;

    cout << "Choose task(1, 2, 3):\n";
    cin >> choice;

    switch (choice) {
    case 2:
        Task2();
        break;
    case 3:
        Task3();
        break;
    default:
        cout << "Wrong choice!\n";
        break;
    }

    return 0;
}
