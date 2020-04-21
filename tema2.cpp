#include<iostream>

class Vector {
public:
    int *a, length;
public:
    Vector(int len);

    Vector(Vector const &a2, bool citire);

    ~Vector();

    void print(std::ostream &os) const {
        os << "P=";
        os << a[0];
        for (int i = 1; i <= length - 1; i++)
            os << " + " << a[i] << "X^" << i;
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector &V);
};

Vector::Vector(int len) {
    int i;
    length = len;
    a = new int[len];
    for (i = 0; i < len; i++)
        std::cin >> a[i];
}

Vector::Vector(Vector const &a2, bool citire) {
    int i;
    if (citire) {
        length = a2.length + 1;
        a = new int[length];
        for (i = 1; i < a2.length; i++)
            a[i] = a2.a[i];
        a[0] = 0;
    }

    if (!citire) {
        length = a2.length + 2;
        a = new int[length];
        for (i = 2; i < a2.length; i++)
            a[i] = a2.a[i];
        a[0] = 0;
        a[1] = 0;
    }
}

Vector::~Vector() {
    delete[] a;
}

std::ostream &operator<<(std::ostream &os, const Vector &V) {
    V.print(os);
    return os;
}

class Nr_Natural_Mare {
public:
    static Vector A;

    static Vector adunare(int nrcif, Vector V, int nrcif2, Vector V2) {
        int sum, k = nrcif, i = nrcif2, len;
        if (k > i)
            Vector A(k);
        else
            Vector A(i);
        len = A.length;
        while ((k != 0) && (i != 0)) {
            sum = V.a[k] + V2.a[i];
            if (sum < 10)
                A.a[len] = sum;
            if (sum > 10) {
                A.a[len] = sum % 10;
                sum = sum / 10;
                if (k > i)
                    A.a[len - 1] = V.a[k - 1] + sum;
                else
                    A.a[len - 1] = V2.a[k - 1] + sum;
            }
            k--;
            i--;
            len--;
        }
        if (k == i == 0) {
            Vector A(A, true);
            A.a[1] = (V.a[1] + V2.a[0]) % 10;
            A.a[0] = (V.a[1] + V2.a[0]) / 10;
        } else {
            if (k > i) {
                while (k != 0) {
                    if (V.a[k] < 10) {
                        A.a[len] = V.a[k];
                        k--;
                        len--;
                    } else {
                        A.a[len] = V.a[k] % 10;
                        V.a[k - 1] = V.a[k] / 10 + V.a[k - 1];
                        k--;
                        len--;
                    }
                }
                if (V.a[0] > 10) {
                    Vector A(A, true);
                    A.a[1] = V.a[0] % 10;
                    A.a[0] = V.a[0] / 10;
                }
            }
            if (k < i) {
                while (i != 0) {
                    if (V2.a[i] < 10) {
                        A.a[len] = V2.a[i];
                        i--;
                        len--;
                    } else {
                        A.a[len] = V2.a[i] % 10;
                        V2.a[i - 1] = V2.a[2] / 10 + V2.a[i - 1];
                        i--;
                        len--;
                    }
                }
                if (V2.a[0] > 10) {
                    Vector A(A, true);
                    A.a[1] = V2.a[0] % 10;
                    A.a[0] = V2.a[0] / 10;
                }
            }
        }
        return A;
    }

    static Vector inmultire(int nrcif, Vector V, int nrcif2, Vector V2) {
        int mul, k = nrcif, i = nrcif2, len;
        if (k > i)
            Vector A(k);
        else
            Vector A(i);
        len = A.length;
        while ((k != 0) && (i != 0)) {
            mul = V.a[k] * V2.a[i];
            if (mul < 10)
                A.a[len] = mul;
            if (mul > 10) {
                A.a[len] = mul % 10;
                mul = mul / 10;
                if (k > i)
                    A.a[len - 1] = V.a[k - 1] + mul;
                else
                    A.a[len - 1] = V2.a[k - 1] + mul;
            }
            k--;
            i--;
            len--;
        }
        if (k == i == 0) {
            if (V.a[i] * V2.a[i] < 10)
                A.a[0] = V.a[i] * V2.a[i];
            if (V.a[i] * V2.a[i] > 10 && V.a[i] * V2.a[i] < 100) {
                Vector A(A, true);
                A.a[1] = (V.a[1] * V2.a[0]) % 10;
                A.a[0] = (V.a[1] * V2.a[0]) / 10;
            }
            if (V.a[i] * V2.a[i] > 100) {
                Vector A(A, false);
                A.a[2] = (V.a[1] * V2.a[0]) % 10;
                A.a[1] = (V.a[1] * V2.a[0]) / 10;
                A.a[0] = (V.a[1] * V2.a[0]) / 100;
            }

        } else {
            if (k > i) {
                while (k != 0) {
                    if (V.a[k] < 10) {
                        A.a[len] = V.a[k];
                        k--;
                        len--;
                    } else {
                        A.a[len] = V.a[k] % 10;
                        V.a[k - 1] = V.a[k] / 10 + V.a[k - 1];
                        k--;
                        len--;
                    }
                }
                if (V.a[0] > 10) {
                    Vector A(A, true);
                    A.a[1] = V.a[0] % 10;
                    A.a[0] = V.a[0] / 10;
                }
            }
            if (k < i) {
                while (i != 0) {
                    if (V2.a[i] < 10) {
                        A.a[len] = V2.a[i];
                        i--;
                        len--;
                    } else {
                        A.a[len] = V2.a[i] % 10;
                        V2.a[i - 1] = V2.a[2] / 10 + V2.a[i - 1];
                        i--;
                        len--;
                    }
                }
                if (V2.a[0] > 10) {
                    Vector A(A, true);
                    A.a[1] = V2.a[0] % 10;
                    A.a[0] = V2.a[0] / 10;
                }
            }
        }
    }
};

class Nr_Intreg_Mare : public Nr_Natural_Mare {
public:
    static Vector B;

    static Vector adunarein(char semn, int nrcif, Vector V) {
        int sum;
        char semn1;
        if (semn == '+') {
            std::cout << semn;
            return Nr_Natural_Mare::adunare(nrcif, V, A.length, A);
        }
        if (semn == '-') {
            int sum, k = nrcif, i = A.length, len;

            if (k > i)
                Vector B(k);
            else
                Vector B(i);
            len = B.length;
            if (k > i) {
                semn1 = '-';
                while (i != 0) {
                    if (A.a[i] > V.a[k]) {
                        V.a[k - 1]--;
                        V.a[k] = V.a[k] * 10;
                    }
                    sum = V.a[k] - A.a[i];
                    B.a[len] = sum;
                    k--;
                    i--;
                    len--;
                }
                for (int j = k; j >= 0; j--) {
                    B.a[len] = V.a[k];
                    len--;
                }
            }
            if (k < i) {
                semn1 = '+';
                while (i != 0) {
                    if (A.a[i] > V.a[k]) {
                        V.a[k - 1]--;
                        V.a[k] = V.a[k] * 10;
                    }
                    sum = A.a[k] - V.a[i];
                    B.a[len] = sum;
                    k--;
                    i--;
                    len--;
                }
                for (int j = k; j >= 0; j--) {
                    B.a[len] = V.a[k];
                    len--;
                }
            }

            if (k == i) {
                if (V.a[0] > A.a[0]) {
                    semn1 = '-';
                    while (i != 0) {
                        if (A.a[i] > V.a[k]) {
                            V.a[k - 1]--;
                            V.a[k] = V.a[k] * 10;
                        }
                        sum = V.a[k] - A.a[i];
                        B.a[len] = sum;
                        k--;
                        i--;
                        len--;
                    }
                }

                if (V.a[0] < A.a[0]) {
                    semn1 = '+';
                    std::cout << semn1;
                    while (i != 0) {
                        if (A.a[i] > V.a[k]) {
                            V.a[k - 1]--;
                            V.a[k] = V.a[k] * 10;
                        }
                        sum = A.a[k] - V.a[i];
                        B.a[len] = sum;
                        k--;
                        i--;
                        len--;
                    }
                }
            }
            std::cout << semn1;
            return B;
        }
    }

    static Vector inmultirein(char semn, int nrcif, Vector V) {
        B = Nr_Natural_Mare::inmultire(nrcif, V, A.length, A);
        std::cout << semn;
        return B;
    }

};

int main() {
    int n, m, p;
    char semn;
    std::cin >> n >> m >> p;
    Vector vect(n);
    Vector vect2(m);
    Vector vect3(p);
    std::cin >> semn;
    Vector V1 = Nr_Natural_Mare::adunare(n, vect, m, vect2);
    std::cout << "Adunare= " << V1 << std::endl;
    Vector V2 = Nr_Natural_Mare::inmultire(n, vect, m, vect2);
    std::cout << "Inmultire= " << V2 << std::endl;
    Vector V3 = Nr_Intreg_Mare::adunarein(semn, p, vect3);
    std::cout << "Adunare= " << V3 << std::endl;
    V3 = Nr_Intreg_Mare::inmultirein(semn, p, vect3);
    std::cout << "Inmultire= " << V3;

    return 0;
}

