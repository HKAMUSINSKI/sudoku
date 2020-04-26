#include <cstdlib>
#include <iostream>
using namespace std;


//Opracowana przez Huberta Kamusiñskiego 
//20.04.2020

int PLANSZA[9][9] = { 
    {0,5,7,9,4,0,8,0,0},
    {2,0,4,0,0,0,1,9,6},
    {3,9,0,1,0,0,0,0,5},
    {0,3,1,0,0,0,2,0,0},
    {6,0,2,3,5,0,9,8,0},
    {5,0,0,2,0,7,0,0,0},
    {0,0,5,6,0,2,0,0,8},
    {7,6,0,0,1,5,0,0,9},
    {0,0,8,7,3,0,0,0,0} }; // Tablica z pocz¹tkowym sudoku
int GRA[9][9]; // tablica do gry 

int PUSTYCH = 9*9;
int ILE[9][9][1]; // tablica bedzie przechowywaæ ile licz mo¿na wpisaæ w dana komórke
int JAKIE[9][9][9]; // tablica bedzie przechowywaæ jakie mo¿na wpisaæ 
int text = 0;  //  0=nic, 1 poziom, 2 poziom 


void start()
{
    //przepisanie planszy do tablicy na której beda zmiany (GRA), ustawinie startowych parametrów dla pomocnicznych tabel; 
   
    for (int i = 0; i <9 ; i++)   // Pierwsza petla - pierwsza zmienna wspólrzedna X
    {
        for (int j = 0; j < 9; j++) //Druga petla wspólrzedna Y
        {
            GRA[i][j] = PLANSZA[i][j];  // Przepisanie wartosci 

            if (GRA[i][j] == 0)  // Jezeli komórka jest pusta mo¿na wpisaæ tam 9 liczby
            {
                ILE[i][j][0] = 9;
                for (int k = 0; k < 9; k++)
                    JAKIE[i][j][k] = 1; // Je¿eli mo¿na wpisaæ liczbe k+1 to 1 jesli nie to 0 
            }
            else  // Je¿eli komórka nie jest pusta to mozna ju¿ wpisaæ zadnej liczby  
            {
                ILE[i][j][0] = 0;
                PUSTYCH--;
                for (int k = 0; k < 9; k++)
                    JAKIE[i][j][k] = 0; // Je¿eli mo¿na wpisaæ liczbe k+1 to 1 jesli nie to 0 
            }

        }

    }
  
}

void drukuj()
{
    cout << endl;
    cout << "Obecnie nasza tablica prezetntuje sie tak:" << endl;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
            cout << " " << GRA[i][j];

        cout << endl;
    }
    cout << endl;
    cout << "Do wypelnienia pozostalo nam: " << PUSTYCH << endl;
    system("pause");
    cout << endl;
}

void pasujace(int X, int Y)
{
    cout << "A wiec do komorki " << X + 1 << " " << Y + 1 << " moge wpisac  " << ILE[X][Y][0] << " liczby. A sa to: " << endl;
    for (int k = 0; k < 9; k++)
    {
        if (JAKIE[X][Y][k] == 1) cout << k + 1 << endl;

    }

}


void sprawdzanie(int X, int Y)

{
    int WSP = 10; // Zmienna pomocniczna do przechowywania wspólrzednej wartosci szukanej

    // Sprawdzanie w poziomie 
    if (text == 2) { cout << "Sprawdzam poziom, jak cos znajde dam znac " << endl; }
    for (int j = 0; j < 9; j++)
    {
        if (ILE[X][j][0] == 0)  // Je¿eli komórka nie jest pusta to znaczy ze w  mojej komórce nie mo¿e byc tej wartosci 
        {
            if (text == 2) { cout << "Wyglada na to ze w komorce " << X + 1 << " " << j + 1 << " jest juz wartosc " << GRA[X][j] << endl; }

            WSP = GRA[X][j];
            WSP--;//  wspólrzedna tablicy z mo¿liwoœciami jest o 1 miejsza od wartosci 
            if (JAKIE[X][Y][WSP] == 1)    // sprawdzanie czy te wartosc mo¿na by³o wpisaæ w moja komórke
            {
                JAKIE[X][Y][WSP] = 0;  // to juz nie mozna wpisaæ 
                ILE[X][Y][0]--;  // I mozliwe liczby spadaja o 1
               
                if (text == 2)
                {
                    cout << "O nie wiedzialem tego." << endl;
                    cout << "Teraz juz wiem ze w miejscu " << X + 1 << " " << Y + 1 << " nie moze byc wartosci " << GRA[X][j] << endl;
                    pasujace(X, Y);
                }

            }
            else
            {
                if (text == 2) cout << "Wyglada na to ze nic nowego." << endl;
            
            }

        }

    }

    // Sprawdzanie w pionie 
    if (text == 2) cout << "Sprawdzam pion jak cos znajde dam znac " << endl;
    for (int i = 0; i < 9; i++)
    {
        if (ILE[i][Y][0] == 0)  // Je¿eli komórka nie jest pusta to znaczy ze w  mojej komórce nie mo¿e byc tej wartosci 
        {
            if (text == 2) cout << "Wyglada na to ze w komorce " << i + 1 << " " << Y + 1 << " jest juz wartosc " << GRA[i][Y] << endl;

            WSP = GRA[i][Y] - 1;// wspólrzedna tablicy z mo¿liwoœciami jest o 1 miejsza od wartosci 

            if (JAKIE[X][Y][WSP] == 1)    // sprawdzanie czy te wartosc mo¿na by³o wpisaæ w moja komórke
            {
                JAKIE[X][Y][WSP] = 0;  // to juz nie mozna wpisaæ 
                ILE[X][Y][0]--;  // I mozliwe liczby spadaja o 1 
                if (text == 2)
                {
                    cout << "O nie wiedzialem tego." << endl;
                    cout << "Teraz juz wiem ze w miejscu " << X + 1 << " " << Y + 1 << " nie mo¿e byc wartosci " << GRA[i][Y] << endl;
                    pasujace(X, Y);
                }
            }
            else
            {
                if (text == 2) cout << "Wyglada na to ze nic nowego." << endl;

            }

        }

    }

    // Sprawdzanie w kwadracie 
    // Do ma³ego kwadratu podaje zawsze wpo³rzedne lewego górnego naroznika. Ale poruszam sie po duzym kwadracie 
    int A, B = 10;

    // okreslenie wspolrzednych ma³ego kwadratu
    if (X < 3) A = 0; 
        else 
        {
        if (X < 6) A = 3; else A = 6;
        }   
    if (Y < 3) B = 0;
    else
    {
        if (Y < 6) B = 3; else B = 6;
    }

    if (text == 2) cout << "Sprawdzam kwadrat jak cos znajde dam znac " << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (ILE[A + i][B + j][0] == 0)  // Je¿eli komórka nie jest pusta to znaczy ze w  mojej komórce nie mo¿e byc tej wartosci 
            {
                if (text == 2) cout << "Wyglada na to ze w komorce " << A + i + 1 << " " << B + j + 1 << " jest juz wartosc " << GRA[A + i][B + j] << endl;

                WSP = GRA[A + i][B + j] - 1;// wspólrzedna komórki z mo¿liwoœciami jest o 1 miejsza od wartosci 

                if (JAKIE[X][Y][WSP] == 1)    // sprawdzanie czy te wartosc mo¿na by³o wpisaæ w moja komórke
                {
                    JAKIE[X][Y][WSP] = 0;  // to juz nie mozna wpisaæ 
                    ILE[X][Y][0]--;  // I mozliwe liczby spadaja o 1
                    if (text == 2)
                    {
                        cout << "O nie wiedzialem tego." << endl;
                        cout << "Teraz juz wiem ze w miejscu " << X + 1 << " " << Y + 1 << " nie moze byc wartosci " << GRA[A + i][B + j] << endl;
                        pasujace(X, Y);
                    }
                }
                else
                {
                    if (text == 2) cout << "Wyglada na to ze nic nowego." << endl;

                }


            }
        }
    }

}





void przepisanie(int X, int Y)
{
    if (text == 1) cout << "Super znalazlem rozwiazanie dla " << X + 1 << " " << Y + 1 << endl;
    for (int k = 0; k < 9; k++)
        if (JAKIE[X][Y][k] == 1)
        {
            GRA[X][Y] = k + 1;
            ILE[X][Y][0] = 0;
            if (text == 1)
            {
                cout << endl;
                cout << "Moje rozwiazanie to:  " << GRA[X][Y] << endl;
                

            }
        }
}

int main()
{
    start();
    drukuj();

    

    //Sprawdzanie  jakie mo¿na wpisaæ 
    do
    {
        for (int i = 0; i < 9; i++)
        {

            for (int j = 0; j < 9; j++)
            {
                if (text == 2) cout << "Sprawdzam wspolrzedne " << i + 1 << " " << j + 1 << endl;

                if (GRA[i][j] == 0)
                {
                    if (text == 2) cout << "Wyglada na to ze nic tutaj nie ma. Sprawdzmy co mozemy tutaj wpisac" << endl;
                    if (text == 2) pasujace(i, j);
                    sprawdzanie(i, j);


                    if (ILE[i][j][0] == 1)
                    {
                        przepisanie(i, j);
                        PUSTYCH--;

                        drukuj();
                        

                    }
                }
                else if (text == 2) cout << "Wyglada na to ze mamy juz tutaj " << GRA[i][j] << endl;
                if (PUSTYCH == 0) break;
            }
            if (PUSTYCH == 0) break;
        }




    } while (PUSTYCH > 0);

    cout << "Myœle ze mam juz wszystko. Sprawdzmy" << endl;
    system("pause");
    system("CLS");

    cout << endl;
    cout << "Masza tablica wygladala tak:" << endl;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
            cout << " " << PLANSZA[i][j];

        cout << endl;
    }

    cout << endl;
    cout << "Obecnie nasza tablica prezetntuje sie tak:" << endl;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
            cout << " " << GRA[i][j];

        cout << endl;
    }


    cout << endl << "Nacisnij ENTER aby zakonczyc" << endl;
    system("pause");
    return 0;
}