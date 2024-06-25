#include <iostream>
#include <cmath>

enum VectorState {
    OK,
    DIV_BY_ZERO,
    NULL_POINTER_ERROR
};

class Vector3D {
private:
    double v[3];
    int state;

public:
    static int count; // лічильник об'єктів класу

    // Конструктори
    Vector3D() {
        v[0] = 0.0;
        v[1] = 0.0;
        v[2] = 0.0;
        state = OK;
        count++;
    }

    Vector3D(double value) {
        v[0] = value;
        v[1] = value;
        v[2] = value;
        state = OK;
        count++;
    }

    Vector3D(double* ptr) {
        if (ptr == nullptr) {
            state = NULL_POINTER_ERROR;
            v[0] = 0.0;
            v[1] = 0.0;
            v[2] = 0.0;
        }
        else {
            for (int i = 0; i < 3; ++i) {
                v[i] = ptr[i];
            }
            state = OK;
        }
        count++;
    }

    // Деструктор
    ~Vector3D() {
        std::cout << "Vector3D destructed. State: " << state << std::endl;
        count--;
    }

    // Функція для присвоєння значення всьому вектору
    void assign(double value = 0.0) {
        for (int i = 0; i < 3; ++i) {
            v[i] = value;
        }
    }

    // Функція для отримання елемента вектору
    double get(int index) {
        if (index >= 0 && index < 3) {
            return v[index];
        }
        else {
            std::cerr << "Index out of range." << std::endl;
            return NAN; // Not-a-Number для позначення помилки
        }
    }

    // Функції друку
    void print() {
        std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")" << std::endl;
    }

    // Арифметичні операції
    Vector3D add(Vector3D& other) {
        Vector3D result;
        for (int i = 0; i < 3; ++i) {
            result.v[i] = v[i] + other.v[i];
        }
        return result;
    }

    Vector3D subtract(Vector3D& other) {
        Vector3D result;
        for (int i = 0; i < 3; ++i) {
            result.v[i] = v[i] - other.v[i];
        }
        return result;
    }

    Vector3D crossProduct(Vector3D& other) {
        Vector3D result;
        result.v[0] = v[1] * other.v[2] - v[2] * other.v[1];
        result.v[1] = v[2] * other.v[0] - v[0] * other.v[2];
        result.v[2] = v[0] * other.v[1] - v[1] * other.v[0];
        return result;
    }

    // Ділення на ціле
    Vector3D divide(short divisor) {
        Vector3D result;
        if (divisor == 0) {
            std::cerr << "Division by zero." << std::endl;
            result.state = DIV_BY_ZERO;
        }
        else {
            for (int i = 0; i < 3; ++i) {
                result.v[i] = v[i] / divisor;
            }
            result.state = OK;
        }
        return result;
    }

    // Функції порівняння
    bool lessThan(Vector3D& other) {
        double mag1 = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
        double mag2 = sqrt(other.v[0] * other.v[0] + other.v[1] * other.v[1] + other.v[2] * other.v[2]);
        return mag1 < mag2;
    }

    bool equalTo(Vector3D& other) {
        return v[0] == other.v[0] && v[1] == other.v[1] && v[2] == other.v[2];
    }

    static int getCount() {
        return count;
    }
};

int Vector3D::count = 0;

// Функція для тестування всіх можливостей класу
int main() {
    Vector3D v1;
    v1.print();

    Vector3D v2(2.0);
    v2.print();

    double arr[] = { 1.0, 2.0, 3.0 };
    Vector3D v3(arr);
    v3.print();

    Vector3D v4(nullptr);
    v4.print();

    Vector3D v5;
    v5.assign(5.0);
    v5.print();

    Vector3D v6 = v3.add(v5);
    v6.print();

    Vector3D v7 = v3.subtract(v5);
    v7.print();

    Vector3D v8 = v3.crossProduct(v5);
    v8.print();

    Vector3D v9 = v3.divide(2);
    v9.print();

    Vector3D v10 = v3.divide(0); // Ділення на 0
    v10.print();

    std::cout << "v3 less than v5: " << std::boolalpha << v3.lessThan(v5) << std::endl;
    std::cout << "v3 equal to v5: " << std::boolalpha << v3.equalTo(v5) << std::endl;

    std::cout << "Number of Vector3D objects created: " << Vector3D::getCount() << std::endl;

    return 0;
}
