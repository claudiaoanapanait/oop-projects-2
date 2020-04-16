#include<iostream>

class Vector {
public:
    int *a, length;
public:
    Vector(int len);

    Vector(Vector const &a2);

    ~Vector();
};

Vector::Vector(int len) {
    int i;
    length = len;
    a = new int[len];
    for (i = 0; i < len; i++)
        std::cin >> a[i];
}

Vector::Vector(Vector const &a2) {
    int i;
    length = a2.length;
    a = new int[length];
    for (i = 0; i < a2.length; i++)
        a[i] = a2.a[i];
}

Vector::~Vector() {
    delete[] a;
}

class Nr_Natural_Mare {
public:
    int nr;
    int len, *A;
public:
    int nrmax(int nrcif, Vector V) {
        int i, j;
        len = nrcif;
        A = new int[len];
        for (int k = 0; k < nrcif; ++k) {
            A[k] = V.a[k];
        }
        for (i = 0; i < nrcif - 1; i++)
            for (j = 0; j < nrcif - 2; j++)
                if (V.a[j] > V.a[j + 1])
                    std::swap(V.a[j], V.a[j + 1]);
        nr = A[len - 1];
    }
};

class Nr_Intreg_Mare : public Nr_Natural_Mare {
protected:
    int nrintreg;
public:
    int nrmaxintr(char semn) {
        if (semn == '+')
            nrintreg = nr;
        if (semn == '-') {
            for (int i = 0; i < len; ++i) {
                if ((A[i] < 0) && (A[i + 1] > 0))
                    nrintreg = A[i];
            }
        }
        return nrintreg;
    }

    int adunare() {
        return nrintreg+nr;
    }

    int scadere() {
        return nrintreg - nr;
    }

    int inmultire() {
        return nrintreg * nr;
    }

    int impartire() {
        return float(nrintreg / nr);
    }
};

int main() {
    int n;
    char semn;
    std::cin >> n;
    Vector vect(n);
    std::cin>>semn;
    Nr_Natural_Mare nr;
    Nr_Intreg_Mare nrintreg;
    nr.nrmax(n, vect);
    nrintreg.nrmaxintr(semn);
    std::cout << "Adunare= " << nrintreg.adunare()<<" ";
    std::cout << "Scadere= " << nrintreg.scadere()<<" ";
    std::cout << "Inmultire= " << nrintreg.inmultire()<<" ";
    std::cout << "Impartire= " << nrintreg.impartire();

    return 0;
}

