#include <bits/stdc++.h>
using namespace std;
#define EPSILON 0.0001

// Kelas Matrix untuk kuis 1 Aljabar Linear
class Matrix {
private:
    int baris, kolom;
    bool statusgauss = false, statusjordan = false;
    double perubahandeterminan = 1.0;
    bool punyainvers;
    vector<double> *matrix, *invers;
    int carisatuutama(int baris) {
        for(int i=0; i<kolom; i++)
            if(fabs(matrix[baris][i] - 0.0) >= EPSILON)
                return i;
        return INT_MAX; // Satu baris isinya nol semua
    }

    void tukarbaris(int src, int dst) {
        printf("Tukar B%d dengan B%d.\n", src + 1, dst + 1);
        vector<double> tmp;
        // Utama
        tmp.swap(matrix[src]);
        matrix[src].swap(matrix[dst]);
        matrix[dst].swap(tmp);

        // Invers
        if(punyainvers) {
            tmp.swap(invers[src]);
            invers[src].swap(invers[dst]);
            invers[dst].swap(tmp);
            tmp.clear();
        }

        printMatrix();
        perubahandeterminan *= -1.0;
        cout<<'\n';
    }

    void kalidantambahbaris(int src, int dst, double pengkali) { // Baris src = Baris dst*pengkali + Baris src
        printf("B%d = B%d * %.4lf + B%d\n", src + 1, dst + 1, pengkali, src + 1);
        // Utama
        for(int i=0; i<kolom; i++)
            matrix[src][i] += matrix[dst][i] * pengkali;

        // Invers
        if(punyainvers)
            for(int i=0; i<kolom; i++)
                invers[src][i] += invers[dst][i] * pengkali;
        printMatrix();
        cout<<'\n';
    }

    void kalibaris(int src, double pengkali) {
        printf("B%d = B%d * %.4lf\n", src + 1, src + 1, pengkali);
        // Utama
        for(auto &i : matrix[src])
            i *= pengkali;

        // Invers
        if(punyainvers)
            for(auto &i : invers[src])
                i *= pengkali;
        printMatrix();
        perubahandeterminan *= 1 / pengkali;
        cout<<'\n';
    }

public:
    Matrix(int baris, int kolom) {
        this->baris = baris;
        this->kolom = kolom;
        matrix = new vector<double>[baris];
        for(int i=0; i<baris; i++)
            matrix[i].resize(kolom);
        for(int i=0; i<baris; i++)
            for(auto &j : matrix[i])
                cin>>j;
        punyainvers = baris == kolom;
        if(punyainvers) {
            invers = new vector<double>[baris];
            for(int i=0; i<baris; i++)
                for(int j=0; j<kolom; j++)
                    if(i == j)
                        invers[i].push_back(1);
                    else invers[i].push_back(0);
        }
        printf("Matrix dengan ukuran %d x %d berhasil dibuat\n", baris, kolom);
    }

    void printMatrix() {
        for(int i=0; i<baris; i++) {
            for(auto &j : matrix[i])
                cout<<j<<' ';
            if(punyainvers) {
                cout<<"| ";
                for(auto &j : invers[i])
                    cout<<j<<' ';
            }
            cout<<'\n';
        }
    }

    void gauss() {
        if(statusgauss) {
            cout<<"Operasi Gauss sudah dilakukan.\n";
            return;
        }

        // for(int i=0; i<kolom; i++) {
        //     int satuutama = carisatuutama(i);
        //     if(satuutama > -1) {
        //         if(satuutama != i) 
        //             tukarbaris(i, satuutama), satuutama = i;
        //         for(int j=i; j<baris; j++) {
        //             if(j == satuutama) {
        //                 if(matrix[j][i] != 1) {
        //                     kalibaris(j, 1.0 / matrix[j][i]);
        //                 }
        //             } else {
        //                 if(matrix[j][i] != 0.0)
        //                     kalidantambahbaris(j, satuutama, -matrix[j][i] / matrix[satuutama][i]);
        //             }
        //         }
        //     }
        // }

        for(int i=0; i<baris; i++) {
            int satuutamaasli = carisatuutama(i);
            int satuutamatmp = satuutamaasli;
            int yanglebihkiri = i;
            for(int j=i + 1; j<baris; j++) {
                int tmp = carisatuutama(j);
                if(tmp < satuutamatmp)
                    satuutamatmp = tmp, yanglebihkiri = j;
            }
            if(satuutamaasli != satuutamatmp)
                tukarbaris(i, yanglebihkiri), satuutamaasli = satuutamatmp;
            else if(satuutamaasli == INT_MAX)
                continue;
            if(fabs(matrix[i][satuutamaasli] - 1.0) >= EPSILON)
                kalibaris(i, 1.0 / matrix[i][satuutamaasli]);
            for(int j=i + 1; j<baris; j++) {
                bool isZero = fabs(matrix[j][satuutamaasli] - 0.0) < EPSILON;
                if(!isZero)
                    kalidantambahbaris(j, i, -matrix[j][satuutamaasli] / matrix[i][satuutamaasli]);
            }
        }
        statusgauss = true;
    }

    void jordan() {
        if(statusjordan) {
            cout<<"Operasi Jordan sudah dilakukan.\n";
            return;
        }

        // for(int i=kolom - 1; i >= 0; i--) {
        //     int j = i - 1;
        //     if(j >= baris)
        //         j = baris - 2;
        //     int satuutama = carisatuutama(i);
        //     for(; j >= 0; j--) {
        //         if(satuutama != -1)
        //             kalidantambahbaris(j, satuutama, -matrix[j][i] / matrix[satuutama][i]);
        //     }
        // }

        for(int i=baris - 1; i > 0; i--) {
            int satuutama = carisatuutama(i);
            if(satuutama == INT_MAX) // Nol semua barisnya
                continue;
            for(int j=i - 1; j>=0; j--) {
                bool isZero = fabs(matrix[j][satuutama] - 0.0) < EPSILON;
                if(!isZero)
                    kalidantambahbaris(j, i, -matrix[j][satuutama] / matrix[i][satuutama]);
            }
        }
        statusjordan = true;
    }

    double determinan() {
        if(!statusgauss) {
            cout<<"Lakukan operasi Gauss terlebih dahulu.\n";
            return INT_MAX;
        }
        if(baris != kolom) {
            cout<<"Bukan matriks persegi, tidak memiliki determinan.\n";
            return INT_MAX;
        }
        double ret = 1.0;
        for(int i=0; i<baris; i++)
            ret *= matrix[i][i];
        return ret * perubahandeterminan;
    }

    void gaussjordan() {
        if(statusgauss && statusjordan) {
            cout<<"Operasi Gauss-Jordan sudah dilakukan.\n";
            return;
        }
        if(!statusgauss)
            gauss();
        if(!statusjordan)
            jordan();
    }
    
    void printinvers() {
        if(!punyainvers) {
            cout<<"Matriks ini tidak memiliki invers.\n";
            return;
        }
        if(!(statusgauss || statusjordan)) {
            cout<<"Operasi Gauss-Jordan perlu dilakukan terlebih dahulu.\n";
            return;
        }

        cout<<"Invers matrix :\n";
        for(int i=0; i<baris; i++) {
            for(auto &j : invers[i])
                cout<<j<<' ';
            cout<<'\n';
        }
    }
};

int main() {
    int baris, kolom;
    cout<<setprecision(4)<<fixed;
    cout<<"Baris : "; cin>>baris;
    cout<<"Kolom : "; cin>>kolom;
    cout<<"Input Matriks : ";
    Matrix matrix1(baris, kolom);
    while(1) {
        cout<<"Fitur : \n";
        cout<<"1. OBE Gauss.\n";
        cout<<"2. Determinan. (Beta)\n";
        cout<<"3. OBE Gauss-Jordan.\n";
        cout<<"4. Invers.\n";
        cout<<"Pilih yang akan dilakukan : ";
        int input;
        cin>>input;
        if(input == 1)
            matrix1.gauss();
        else if(input == 2) {
            matrix1.gauss();
            cout<<"Determinan matriks adalah "<<matrix1.determinan()<<".\n";
        } else if(input == 3)
            matrix1.gaussjordan();
        else if(input == 4)
            matrix1.printinvers();
        else break;
    }
    return 0;
}