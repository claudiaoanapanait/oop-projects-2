#include<iostream>

class Vector{
public:
    int *a;
    int length;
    char semn;
public:
    Vector(int len, char s);

    Vector(Vector const &a2, bool citire);

    ~Vector();

    virtual void print(std::ostream &os) const {
        for (int i = 0; i <= length - 1; i++)
            os << a[i];
    }

    friend std::ostream &operator<<(std::ostream &os, const Vector &V);
};

Vector::Vector(int len, char s) {
    int i;
    semn = s;
    length = len;
    a = new int[len];
    for (i = 0; i < len; i++)
        std::cin >> a[i];
}

Vector::Vector(Vector const &a2, bool citire) {
    int i;
    if (citire) {
        length = a2.length + 1;
        i = 1;
    }
    a = new int[length];
    a[0] = 0;
    for (int k = i; k < a2.length; k++)
        a[i] = a2.a[i];
}

Vector::~Vector() {
    delete[] a;
}

std::ostream &operator<<(std::ostream &os, const Vector &V) {
    V.print(os);
    return os;
}

class Nr_Natural_Mare : public Vector {
protected:
    Vector A = Vector(0, '+');
public:
    Nr_Natural_Mare(int len, char s, const Vector &V) : Vector(len, s), A{V, false} {}
    void verification(const Vector &V, const Vector &V2, int k, int i, int len) {
        if (k == i) {
            Vector A(A, true);
            A.a[1] = A.a[1] % 10;
            A.a[0] = A.a[1] / 10;
        } else {
            if (k > i) {
                for (int m = k; m >= 0; m--) {
                    if (V.a[k] < 10) {
                        A.a[len] = V.a[k];
                        len--;
                    } else {
                        A.a[len] = V.a[k] % 10;
                        V.a[k - 1] = V.a[k] / 10 + V.a[k - 1];
                        len--;
                    }
                }
            }
            if (k < i) {
                for (int m = i; m >= 0; m--) {
                    if (V2.a[k] < 10) {
                        A.a[len] = V2.a[k];
                        len--;
                    } else {
                        A.a[len] = V2.a[k] % 10;
                        V2.a[k - 1] = V2.a[k] / 10 + V2.a[k - 1];
                        len--;
                    }
                }
            }
        }
    }

    Nr_Natural_Mare adunare(int nrcif, const Vector& V, int nrcif2, const Vector& V2) {
        int sum, k = nrcif - 1, i = nrcif2 - 1, len;
        if (k > i)
            Vector A(k, '+');
        else
            Vector A(i, '+');
        len = A.length - 1;
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
        verification(V, V2, k, i, len);
        std::cout<< A;
    }

    Nr_Natural_Mare inmultire(int nrcif, const Vector& V, int nrcif2, const Vector& V2) {
        int mul, k = nrcif, i = nrcif2, len, m, n;
        Vector A(k + i, '+');
        for (m = k - 1; m >= 0; m--) {
            len = A.length - (A.length - m + i);
            for (n = i - 1; n >= 0; n--) {
                mul = V.a[k] * V2.a[i];
                A.a[len] = mul % 10 + A.a[len];
                A.a[len - 1] = mul / 10 + A.a[len - 1];
                len--;
            }
        }
        std::cout<<A;
    }
    void print (std::ostream &os) const{
        os<<A.semn;
        for (int i = 0; i <A.length ; ++i) {
            os<<A.a[i];
        }
    }
    friend std::ostream &operator <<(std::ostream &os, const Nr_Natural_Mare &V);
};
std::ostream &operator <<(std::ostream &os, const Nr_Natural_Mare &V){
    V.print(os);
    return os;
}

class Nr_Intreg_Mare : public Nr_Natural_Mare{
private:
    Vector B;
public:
    Nr_Intreg_Mare(const Vector &V) : Nr_Natural_Mare(0, 0, V), B(V){}
    void calcul(int sum, Vector &V, int &k, int &i, int &len, int operatie) {
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

    Nr_Intreg_Mare adunarein(int nrcif, Vector V) {
        int sum;
        if (((V.semn == '+') && (A.semn == '+')) || ((V.semn == '-') && (A.semn == '-')))
            Nr_Natural_Mare::adunare(nrcif, V, A.length, A);
        if (((V.semn == '+') && (A.semn == '-')) || ((V.semn == '-') && (A.semn == '+'))) {
            int sum = 0, k = nrcif, i = A.length, len;

            if (k > i)
                Vector B(k, V.semn);
            else
                Vector B(i, A.semn);
            len = B.length;
            if (k > i) {
                calcul(sum, V, k, i, len, V.a[k] - A.a[i]);
                for (int j = k; j >= 0; j--) {
                    B.a[len] = V.a[k];
                    len--;
                }
            }
            if (k < i) {
                calcul(sum, V, k, i, len, A.a[k] - V.a[i]);
                for (int j = k; j >= 0; j--) {
                    B.a[len] = V.a[k];
                    len--;
                }
            }

            if (k == i) {
                if (V.a[0] > A.a[0]) {
                    B.semn = '-';
                    calcul(sum, V, k, i, len, V.a[k] - A.a[i]);
                }

                if (V.a[0] < A.a[0]) {
                    B.semn = '+';
                    calcul(sum, V, k, i, len, A.a[k] - V.a[i]);
                }
            }
            std::cout<<B;
        }
    }

    Nr_Intreg_Mare inmultirein(int nrcif, const Vector& V) {
        Nr_Natural_Mare::inmultire(nrcif, V, A.length, A);
    }

};

int main() {
    int n, m, p;
    char semn;
    std::cin >> n >> m >> p;
    std::cin >> semn;
    Vector vect(n, '+');
    Vector vect2(m, '+');
    Vector vect3(p, semn);
    Nr_Natural_Mare V1(0, 0, vect), V2(0, 0, vect2);
    Nr_Intreg_Mare V3(vect3);
    V1.adunare(n, vect, m, vect2);
    V2.inmultire(n, vect, m, vect2);
    V3.adunarein(p, vect3);
    V3.inmultirein(p, vect3);

    return 0;
}

