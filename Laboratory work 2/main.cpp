#include <iostream>
using namespace std;

int main()
{
    int Summa;
    int i;
    int ArrayNumbers[] = { 50, 2, 198, 202 };
    int n = sizeof(ArrayNumbers) / sizeof(ArrayNumbers[0]);
    for (i = 0; i < n; i++) {
        cout << "Value in the array: " << ArrayNumbers[i];
        if ((ArrayNumbers[i]) & (1 << 7)) {
            ArrayNumbers[i] = ArrayNumbers[i] >> 1;
            cout << " | " << ArrayNumbers[i] << " <- Value after checking the conditions \n";
        }
        else {
            cout << " | " << ArrayNumbers[i] << "  <- Value after checking the conditions \n";
        }
    }
    Summa = 0;
    for (i = 0; i < sizeof(ArrayNumbers) / sizeof(ArrayNumbers[0]); i++) {
        Summa = Summa + ArrayNumbers[i];
    }
    cout << "Summa: " << Summa << endl;
    system("PAUSE");
    return 0;
}
