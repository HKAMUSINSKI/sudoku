#include <cstdlib>
#include <iostream>
using namespace std;


//Opracowana przez Huberta Kamusińskiego 
//20.04.2020

int PLANSZA[4][4];  // Tablica z początkowym sudoku
int GRA[4][4]; // tablica do gry 
int PUSTYCH=16;
int ILE[4][4][1]; // tablica bedzie przechowywać ile licz można wpisać w dana komórke
int JAKIE[4][4][4]; // tablica bedzie przechowywać jakie można wpisać 


void start()
{
    //ustawienia planszy 
    PLANSZA[0][0] = 0;
    PLANSZA[0][1] = 3; 
    PLANSZA[0][2] = 0;
    PLANSZA[0][3] = 0;

    PLANSZA[1][0] = 0;
    PLANSZA[1][1] = 4; 
    PLANSZA[1][2] = 0;
    PLANSZA[1][3] = 0;

    PLANSZA[2][0] = 0;
    PLANSZA[2][1] = 0;
    PLANSZA[2][2] = 2; 
    PLANSZA[3][3] = 0;

    PLANSZA[3][0] = 0;
    PLANSZA[3][1] = 0;
    PLANSZA[3][2] = 3; 
    PLANSZA[3][3] = 0;


    //przepisanie planszy do tablicy na której beda zmiany (GRA), ustawinie startowych parametrów dla pomocnicznych tabel 

    for (int i=0;i<4;i++)   // Pierwsza petla - pierwsza zmienna wspólrzedna X
    {
        for (int j = 0; j < 4; j++) //Druga petla wspólrzedna Y
        {
            GRA[i][j] = PLANSZA[i][j];  // Przepisanie wartosci 
           
            if (GRA[i][j] == 0)  // Jezeli komórka jest pusta można wpisać tam 4 liczby {1,2,3,4}
            {   ILE[i][j][0] = 4;
            for (int k = 0; k < 4; k++)
                JAKIE[i][j][k] = 1; // Jeżeli można wpisać liczbe k+1 to 1 jesli nie to 0 
            }
            else  // Jeżeli komórka nie jest pusta to mozna już wpisać zadnej liczby  
            {
                ILE[i][j][0] = 0;
                PUSTYCH--;
                for (int k = 0; k < 4; k++)
                    JAKIE[i][j][k] = 0; // Jeżeli można wpisać liczbe k+1 to 1 jesli nie to 0 
            }
            
        }

    }
}

void drukuj()
{
    cout << endl;
    cout << "Obecnie nasza tablica prezetntuje sie tak:" << endl;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            cout<<" "<<GRA[i][j];

        cout << endl;
    }
    cout << endl;
    cout << "Do wypelnienia pozostalo nam: " << PUSTYCH << endl;
}

void pasujace(int X, int Y)
{
    cout << "A wiec do komorki " << X + 1 << " " << Y + 1 << " moge wpisac  " << ILE[X][Y][0] << " liczby. A sa to: " << endl;
    for (int k = 0; k < 4; k++)
    {
        if (JAKIE[X][Y][k] == 1) cout << k + 1 << endl; 
      
    }
    
}
void sprawdzanie(int X, int Y)

{
    int WSP = 5; // Zmienna do przechowywania wspólrzednej wartosci szukanej

    // Sprawdzanie w poziomie 
    cout << "Sprawdzam poziom, jak cos znajde dam znac " <<endl;
    for (int j = 0; j < 4; j++)
    {
        if (ILE[X][j][0] == 0)  // Jeżeli komórka nie jest pusta to znaczy ze w  mojej komórce nie może byc tej wartosci 
        {
            cout << "Wyglada na to ze w komorce "<<X+1<<" "<<j+1<<" jest juz wartosc "<<GRA[X][j] << endl;
            
            WSP = GRA[X][j];
            WSP--;// wspólrzedna komórki z możliwościami jest o 1 miejsza od wartosci 
            if (JAKIE[X][Y][WSP] == 1)    // sprawdzanie czy te wartosc można było wpisać w moja komórke
            {
                JAKIE[X][Y][WSP] = 0;  // to juz nie mozna wpisać 
                ILE[X][Y][0]--;  // I mozliwe liczby spadaja o 1
                cout << "O nie wiedzialem tego." << endl;
                cout << "Teraz juz wiem ze w miejscu " <<X + 1 << " " << Y + 1 <<" nie moze byc wartosci "<< GRA[X][j]<<endl;
                pasujace(X, Y);
                              
               
                        }
            else
            {
                cout << "Wyglada na to ze nic nowego."  << endl;
                
                
            }
         
         }
        
    }

    // Sprawdzanie w pionie 
    cout << "Sprawdzam pion jak cos znajde dam znac " << endl;
    for (int i = 0; i < 4; i++)
    {
        if (ILE[i][Y][0] == 0)  // Jeżeli komórka nie jest pusta to znaczy ze w  mojej komórce nie może byc tej wartosci 
        {
            cout << "Wyglada na to ze w komorce " << i +1 << " " << Y + 1 << " jest juz wartosc " << GRA[i][Y] << endl;
            
            WSP = GRA[i][Y] - 1;// wspólrzedna komórki z możliwościami jest o 1 miejsza od wartosci 

            if (JAKIE[X][Y][WSP] == 1)    // sprawdzanie czy te wartosc można było wpisać w moja komórke
            {
                JAKIE[X][Y][WSP] = 0;  // to juz nie mozna wpisać 
                ILE[X][Y][0]--;  // I mozliwe liczby spadaja o 1 
                cout << "O nie wiedzialem tego." << endl;
                cout << "Teraz juz wiem ze w miejscu " << X + 1 << " " << Y + 1 << " nie może byc wartosci " << GRA[i][Y] << endl;
                pasujace(X, Y);
                               
            }
            else
            {
                cout << "Wyglada na to ze nic nowego." << endl;
                
            }
         
        }
        
    }
    
    // Sprawdzanie w kwadracie 
    // Do małego kwadratu podaje zawsze wpołrzedne lewego górnego naroznika. Ale poruszam sie po duzym kwadracie 
    int A, B = 3;

    if (X < 2) A = 0; else A = 2;  // okreslenie wspolrzednych małego kwadratu
    if (Y < 2) B = 0; else B = 2;

    cout << "Sprawdzam kwadrat jak cos znajde dam znac " << endl;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (ILE[A + i][B + j][0] == 0)  // Jeżeli komórka nie jest pusta to znaczy ze w  mojej komórce nie może byc tej wartosci 
            {
                cout << "Wyglada na to ze w komorce " << A + i + 1 << " " << B + j + 1 << " jest juz wartosc " << GRA[A + i][B + j] << endl;
                
                WSP = GRA[A+i][B+j]-1;// wspólrzedna komórki z możliwościami jest o 1 miejsza od wartosci 

                if (JAKIE[X][Y][WSP] == 1)    // sprawdzanie czy te wartosc można było wpisać w moja komórke
                {
                    JAKIE[X][Y][WSP] = 0;  // to juz nie mozna wpisać 
                    ILE[X][Y][0]--;  // I mozliwe liczby spadaja o 1
                    cout << "O nie wiedzialem tego." << endl;
                    cout << "Teraz juz wiem ze w miejscu " << X + 1 << " " << Y + 1 << " nie moze byc wartosci " << GRA[A+i][B+j] << endl;
                    pasujace(X, Y);
                                       
                }
                else
                {
                    cout << "Wyglada na to ze nic nowego." << endl;
                    
                }
                

            }
        }
    }
    
}





void przepisanie(int X, int Y)
{
    cout << "Super znalazlem rozwiazanie dla " << X + 1 << " " << Y + 1 << endl;
    for (int k = 0; k < 4; k++)
        if (JAKIE[X][Y][k] == 1)
        {
            GRA[X][Y] = k + 1;
            ILE[X][Y][0] = 0;
            cout << endl;
            cout << "Moje rozwiazanie to:  " << GRA[X][Y] << endl;
            system("pause");
                    }
}

int main()
{
    start();
    drukuj();

    system("pause");

    //Sprawdzanie  jakie można wpisać 
    do
    {
        for (int i = 0; i < 4; i++)
        {
            
            for (int j = 0; j < 4; j++)
            {
                cout << "Sprawdzam wspolrzedne " << i + 1 << " " << j + 1 << endl;
                
                if (GRA[i][j] == 0)
                {
                    cout << "Wyglada na to ze nic tutaj nie ma. Sprawdzmy co mozemy tutaj wpisac" << endl;
                    pasujace(i, j);
                    sprawdzanie(i, j);

                
                    if (ILE[i][j][0] == 1)
                    {
                        przepisanie(i, j);
                        PUSTYCH--;

                        drukuj();
                        system("pause");

                    }
                }
                else cout << "Wyglada na to ze mamy juz tutaj " << GRA[i][j] << endl;
                if (PUSTYCH == 0) break;
            }
            if (PUSTYCH == 0) break;
        }
               
  
       
        
    } while (PUSTYCH > 0);

    cout << "Myśle ze mam juz wszystko. Sprawdzmy"<<endl;
    system("pause");
    system("CLS");

    cout << endl;
    cout << "Masza tablica wygladala tak:" << endl;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            cout << " " << PLANSZA[i][j];

        cout << endl;
    }

    cout << endl;
    cout << "Obecnie nasza tablica prezetntuje sie tak:" << endl;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            cout << " " << GRA[i][j];

        cout << endl;
    }


    cout << endl << "Nacisnij ENTER aby zakonczyc" << endl;
    system("pause");
    return 0;
}



