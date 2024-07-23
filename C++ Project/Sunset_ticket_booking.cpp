#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;
int obn, ext, prnt_once = 0, dir_customer = 0;
int m = 0, * p, sn, arg, arg2, tkt, tkt_pr, nt = 0, sti, foundu = 0, foundp = 0, pas_chk = 0, mv_str = 0, data_store = 0;
double cost = 0;
int  pas_rak = 0;
char cus_in;

string name[100], tkt_pnt, pass, cus_id, cus_pas, user, hall_name;
int ar[100][100][100][12][18], tkt_row[12], tkt_col[18], str_tim[100];
//ar[hallNumber][movieNumber][showTiming][rowNumber][columnNumber]
string tim[100][100];
//tim[movieNumber][showTiming]
string timing[100];
class movie_booking
{

public:
    void first();
    void show_seat_frm_file();
    void show();
    void seatdisp(int seats, int time);
    void book(int seats, int time, int a);
    void seatin(int seats, int time);
    void manager();
    void ticket_print();
    void pass_proctect();
    void data_str();
    int password_check();
    void hal_name()
    {
        switch (obn)
        {
        case 1:
            hall_name = "NLH-101";
            break;
        case 2:
            hall_name = "NLH-102";
            break;
        case 3:
            hall_name = "NLH-103";
            break;
        case 4:
            hall_name = "NLH-104";
            break;
        }

    }

};


void movie_booking::first()
{
    int i;
    char in = 'c', ind, cus;//cus is customer and ind is manager input
    cout << "\n\n\t\t\t\t\tTO ENTER MANAGER LOGIN PRESS 'o' or 'O' ELSE ANY OTHER KEY FOR CUSTOMER BOOKING\n";
    cout << "\t\t\t\t\t\t\t";
    cin >> ind;
    int pas_count = 0;
    if ((ind == 'o') || (ind == 'O'))
    {
        while (pas_count < 3)
        {
            (*this).pass_proctect();
            if (pass == "INVALID")
            {
                (*this).manager();
                pas_count = 3;
            }

            else
            {
                cout << "PASSWORD ENTERED IS WRONG!!" << " ATTEMPTS REMAINING = " << 2 - pas_count << " \n";//pas_count is to count no. of attempts left
                pas_count++;
            }

        }
    }

    system("clear");
    cout << "\n\n\t\t\t\t\t\t\tDEAR CUSTOMER TO BOOK SEATS PRESS 'y' or 'Y' \n";
    cout << "\t\t\t\t\t\t\t";
    cin >> cus;
   
    if ((cus == 'y') || (cus == 'Y'))//the customer part starts here
    {
        cout << "\n\t\t\t\t\t\t\tIF YOU ARE NEW CUSTOMER PRESS N/n TO SIGNUP(IF not press ANY OTHER key)\n";
        cout << "\t\t\t\t\t\t\t";
        cin >> cus_in;
        if (cus_in == 'N' || cus_in == 'n')
            (*this).data_str();
        else
        {
            cout << "\n\t\t\t\t\t\t\tWELCOME EXISTING CUSTOMER!!!\n";
            pas_rak = (*this).password_check();

        }

        cout << "\t\t\t\t\t\t\t";
        cout << "PRESS ANY KEY TO CONTINUE\n";
        // CLEAR();
        system("clear");
        if (pas_rak != 0 || data_store != 0)
        {
            cout << "\n\n\t\t\t\t\t\tTHE SEATS AVAILABLE ARE:\n";
            while ((in == 'c') || (in == 'C'))
            {
                cost = 0;
                (*this).show_seat_frm_file();
                cout << "\n\n\t\t\t\t\t\t\tENTER THE MOVIE NUMBER TO BOOK TICKET\n";
                cout << "\t\t\t\t\t\t\t";
                cin >> arg;
                ifstream fin;
                fin.open("/Users/pranavbejgam/Desktop/FINAL PROJECT/C++ Project/movie_test2.csv");
                for (i = 0; i < arg - 1; i++)
                {
                    getline(fin, name[i], '\n');
                }
                getline(fin, name[i], ',');
                fin.close();
                cout << "\n\n\t\t\t\t\t\t\tCHOOSE THE NUMBER CORRENSPONDING TO TIMING TO BOOK TICKET FOR MOVIE(Press 1 for first time slot and 2 for second) :-" << endl;

                cout << "\t\t\t\t\t\t\t" << name[i];
                cout << "\t\t\t\t\t\t\t";
                cin >> sti;

                tkt_pnt = name[i];
                // cout<<"THE ARGUMENT IS ="<<arg<<endl;
                (*this).seatdisp(arg, sti);
                (*this).seatin(arg, sti);
                system("clear");
                (*this).seatdisp(arg, sti);
                //HERE ANOTHER FUNCTION IS TO BE WRITTEN TO PRINT THE TICKETS/
                system("clear");

                (*this).ticket_print();
                cout << "\n\n\t\t\t\t\t\t\tPRESS 'C' or 'c' IF U WANT TO BOOK SEAT AGAIN?\n";
                cin >> in;



            }
        }

        else {
            cout << "\n\n\t\t\t\t\t\t\t YOU PRESSED WRONG USER PASSWORD\n";
            cout << "\n\n\t\t\t\t\t\t\t PROGRAM TERMINATED!!!\n";
            cout << "\n\n\t\t\t\t\t\t\t YOU ENTERED WRONG PASSWORD";
        }

    }
}

void movie_booking::show_seat_frm_file()
{
    int i = 0;
    system("clear");
    cout << "\n\n\t\t\t\t\t\t\tTHE MOVIES RUNNING IN HALL ARE:\n\n\n";
    ifstream fin;
    fin.open("/Users/pranavbejgam/Desktop/FINAL PROJECT/C++ Project/movie_test2.csv");
    if (dir_customer == 0)
       
        m = 10;
       
    while (i < m)
    {
        cout << "\n\t\t\t\t\t\t\t";

        getline(fin, name[i], ',');
        cout << "MOVIE :\t" << i + 1 << "\t" << name[i] << endl << endl;
        cout << "\t\t\t\t\t\t\t";
        cout << "THE TIMINGS OF THE MOVIE : " << name[i] << " :-  " << endl;
        int j = 0;

        getline(fin, tim[i][j], '\n');
        cout << "\t\t\t\t\t\t\t";
        cout << tim[i][j] << endl << endl;

        i++;
    }

}
void movie_booking::show()//this function is for entering the number of movie running in hall
{
    int i, j;
    p = (int*)(malloc(sizeof(int)));
    cout << "\n\n\t\t\t\t\t\t\tENTER THE NUMBER MOVIES YOU WANT TO ADD\n";
    cout << "\t\t\t\t\t\t\t";
    cin >> m;
    (*p) = m;
    ofstream fout;
    fout.open("/Users/pranavbejgam/Desktop/FINAL PROJECT/C++ Project/movie_test2.csv", ios::app);
    for (i = 0; i < m; i++)
    {
        fflush(stdin);
        cout << "\n\n\t\t\t\t\t\t\tENTER THE NAME OF MOVIE " << i + 1 << endl;
        cout << "\t\t\t\t\t\t\t";
        getline(cin, name[i]);
        fflush(stdin);
        fout << name[i] << ",";
        cout << "\n\n\t\t\t\t\t\t\tENTER THE NUMBER OF SHOWS OF MOVIE: " << name[i] << " IN A DAY : ";
        cin >> nt;
        str_tim[i] = nt;
        
        cout << "\n\n\t\t\t\t\t\t\tENTER THE SHOW TIMINGS OF THE MOVIE : " << name[i] << endl;
        for (j = 0; j < nt; j++)
        {
            fflush(stdin);
            cout << "\t\t\t\t\t\t\t";
            getline(cin, tim[i][j]);
            fout << tim[i][j] << ",";

        }
        fout << endl;

    }
    fout.close();
    
    m = m + 10;
    
    (*this).show_seat_frm_file();
}


void movie_booking::seatdisp(int seats, int time)
//1st argument to display the seats of that particular movie
//2nd arg is for the particular movie time
{
    arg = seats;
    sti = time;
    int i, j;
    char ch = 'A';
    system("clear");
    cout << "\n\nCost of Last 3 rows:Rs 50/-\n";
    cout << "Cost of Middle rows :Rs 30/-\n";
    cout << "Cost of Near screen rows :Rs 15/-\n";
    ifstream fin;
    fin.open("/Users/pranavbejgam/Desktop/FINAL PROJECT/C++ Project/movie_test2.csv");
    cout << "\n\n\t\t\t\t\t\t\tBOOKED SEATS ARE MARKED WITH [x]\n\n";
    for (i = 0; i < arg - 1; i++)
    {
        getline(fin, name[i], '\n');
    }
    getline(fin, name[i], ',');
    cout << "\n\n\t\t\t\t\t\t\tTHIS IS THE SEAT MATRIX FOR MOVIE: " << name[i] << "\n\n";
    fin.close();
    for (i = 0; i < 10; i++)
    {
        ch = 'A';
        ch = ch + i;
        cout << "\t";
        for (j = 0; j < 18; j++)
        {
            if (ar[obn][arg][sti][i][j] == 1)
                cout << "[" << " X" << "]";
            else
            {
                cout << "[" << ch << j + 1 << "]";
            }

            cout << " ";
            //the seat would be displayed in format[A1]

            if (j == 4 || j == 12)
                cout << "\t";

        }
        cout << "\n\n";
        if (i == 9)
        {
            cout << "\n\n\t\t\t\t\t\t SCREEN THIS WAY\n";
            cout << "\t_______________________________________________________________________________________________________________";
        }

    }

}




void movie_booking::book(int seats, int time, int a)//first argument is for the movie number and 3rd argument for manager mode
//2nd arg is for show time
{
    int col, stor, arg;
    arg = seats;
    sti = time;
    arg2 = a;
    if (arg2 == 100)
    {
        cout << "\n\n\t\t\t\t\t\t\tADMIN ENTER THE SEATS WHICH WONT BE AVAILABLE FOR BOOKING\n";
    }

    else
    {
        cout << "\n\n\t\t\t\t\t\t\tCUSTOMER BOOKING\n";
    }

    (*this).seatdisp(arg, sti);
    char ch = 'A', chr;
    cout << "\n\n\t\t\t\t\t\t\tENTER THE SEAT NUMBER\t";

    cin >> chr >> col;
    chr = std::toupper(chr);
    stor = chr - 65;
    col = col - 1;

    if (ar[obn][arg][sti][stor][col] == 0)
    {
        ar[obn][arg][sti][stor][col] = 1;

        tkt_col[tkt] = col;
        tkt_row[tkt] = stor;


    }
    else
    {

        while (ar[obn][arg][sti][stor][col] != 0)
        {
            if (arg2 == 100)
            {
                cout << "\n\n\t\t\t\t\t\t\tADMIN YOU HAVE ALREADY MARKED THIS SEAT AS BOOKED ENTER A NEW SEAT WHICH IS BOOKED\n";
                cout << "\t\t\t\t\t\t\t ";
            }

            else
            {
                cout << "\n\n\t\t\t\t\t\t\tTHE SEAT YOU SELECTED IS ALREADY OCCUPIED ENTER A NEW SEAT\n";
                cout << "\t\t\t\t\t\t\t ";
            }
            cin >> chr >> col;
            chr = std::toupper(chr);
            stor = chr - 65;
            col = col - 1;
        }
        ar[obn][arg][sti][stor][col] = 1;
        tkt_col[tkt] = col;
        tkt_row[tkt] = stor;
    }

}

void movie_booking::seatin(int seats, int time)//1st argument for the particular movie seat booking
//2nd arg is for particular show time of particular movie
{

    int n, i;
    arg = seats;
    sti = time;
    //cout<<"THE ARGUMENT IS nest="<<arg<<endl;
    cout << "\n\n\t\t\t\t\t\t\tENTER THE NUMBER OF SEATS TO BE BOOKED" << endl;
    ifstream fin;
    fin.open("/Users/pranavbejgam/Desktop/FINAL PROJECT/C++ Project/movie_test2.csv");
    cout << "\n\n\t\t\t\t\t\t\tBOOKED SEATS ARE MARKED WITH [x]\n\n";

    for (i = 0; i < arg - 1; i++)
    {
        getline(fin, name[i], '\n');
    }
    getline(fin, name[i], ',');

    cout << "\t\t\t\t\t\t\t MOVIE NAME=" << name[i] << endl;
    fin.close();
    cout << "\t\t\t\t\t\t\t ";
    cin >> n;
    tkt_pr = n;
 
    for (tkt = 0; tkt < n; tkt++)
    {
        
        (*this).book(arg, sti, 20);
        cout << "LOOP IS RUNNING\n";
        system("clear");
        (*this).seatdisp(arg, sti);

    }
    cout << "\n\n\t\t\t\t\t\t\tPRESS ANY KEY TO CONTINUE\n";
    // CLEAR();
    system("clear");

}




void movie_booking::manager()
{
    char mov = 'c', in = 'c';
    (*this).show();
    while ((mov == 'c') || (mov == 'C'))
    {
        cout << "\n\n\t\t\t\t\t\t\t ENTER THE SHOW NUMBER WHOSE SEATS U WANT TO ASSIGN FOR BOOKING\n";
        cout << "\t\t\t\t\t\t\t";
        cin >> sn;
        cout << "\n\n\t\t\t\t\t\t\t ENTER THE NUMBER CORRESPONDING TO THE TIME TO BOOK TICKET\n";
        cout << "\t\t\t\t\t\t\t";
        cin >> sti;
        tkt_pnt = name[sn];

        while ((in == 'c') || (in == 'C'))
        {
            (*this).book(sn, sti, 100);
            system("clear");
            (*this).seatdisp(sn, sti);
            cout << "\n\n\t\t\t\t\t\t\tPRESS 'C' or 'c' IF U WANT TO CONTINUE ENTERING THE BOOKED SEATS\n";
            cout << "\t\t\t\t\t\t\t";
            cin >> in;
        }

        cout << "\n\n\t\t\t\t\t\t\tPRESS 'C' or 'c' IF U WANT TO CONTINUE ENTERING FOR OTHER MOVIES\n";
        cout << "\t\t\t\t\t\t\t";
        cin >> mov;
        in = 'c';
    }
    mv_str++;

}

void movie_booking::ticket_print()
{
    int i, a = 0, b = 0, d = 0;
    char c;
    string time;

    for (i = 0; i < tkt_pr; i++)
    {


        if (tkt_row[i] == 0 || tkt_row[i] == 1)
        {
            cost = cost + 50;
            a++;
        }
        else if (tkt_row[i] > 1 && tkt_row[i] < 7)
        {
            cost = cost + 30;
            b++;
        }
        else { cost = cost + 15; d++; }


    }
    cout << "\n\n\n\t\t\tCOST : " << endl;
    if (a != 0)
        cout << "\t\t\t       " << a << " * 50" << endl;
    if (b != 0)
        cout << "\t\t\t      +" << b << " * 30" << endl;
    if (c != 0)
        cout << "\t\t\t      +" << d << " * 15" << endl;
    cout << "GST 18% = " << cost * 0.18 << endl;
    cost = cost + cost * (0.18);
    cout << "\n\n\n\n\t\t\tTHE TOTAL TICKET COST = Rs " << cost << "/-" << endl;
    cout << "\n\nPRESS ANY KEY TO CONTINUE\n";
    //    CLEAR();
    system("clear");

    system("clear");
    ifstream fin;
    fin.open("/Users/pranavbejgam/Desktop/FINAL PROJECT/C++ Project/movie_test2.csv");

    for (i = 0; i < arg - 1; i++)
    {
        getline(fin, name[i], '\n');
    }
    getline(fin, name[i], ',');

    for (int j = 0; j < sti; j++)
    {
        getline(fin, time, ',');
    }
    fin.close();
    (*this).hal_name();
    cout << "\n\n\n\n\t\t\t______________________________________________________________________________|\n";
    cout << "\t\t\t|                                                                                 |\n";
    cout << "\t\t\t|   Dear Customer,                                                                |\n";
    cout << "\t\t\t|                      Congratulation!! Your tickets has been booked.             |\n";
    cout << "\t\t\t|                                                                                 |\n";
    cout << "\t\t\t|                  THE DETAILS:                                                   |\n";
    cout << "\t\t\t|                            MOVIE HALL: " << hall_name << "                      |\n";
    cout << "\t\t\t|                            MOVIE NAME: " << name[i] << "                        |\n";
    cout << "\t\t\t|                            SHOW STARTS:" << time << "                           |\n";
    cout << "\t\t\t|                            NUMBER OF TICKETS BOOKED: " << tkt_pr << "           |\n";
    cout << "\t\t\t|                 THE SEAT NUMBERS ARE: "; for (i = 0; i < tkt_pr; i++)
    {
        c = tkt_row[i] + 65;
        cout << c << tkt_col[i] + 1;
        if (i < tkt - 1)
        {
            cout << ",";
        }
    }
    cout << "                        \n";
    cout << "\t\t\t|                                                       QR CODE:                   |\n";
    cout << "\t\t\t|                                                       blahblah                   |\n";
    cout << "\t\t\t|                                                       blahblah                   |\n";
    cout << "\t\t\t|                                                       blahblah                   |\n";
    cout << "\t\t\t|                                                       blahblah                   |\n";
    cout << "\t\t\t|_________________________________________________________________________________ |\n";

}

void movie_booking::pass_proctect()//to protect the password
{

    int ps = 0, star = 0;// to count the characters in password

    //star is to print the password in * format
                
    cout << "\n\n\t\t\t\t\t\t\tENTER THE MANAGER PASSWORD\n";
    cout << "\t\t\t\t\t\t\t";

    cin >> pass;
    ps = pass.length();
    system("clear");
    while (star < ps)
    {
        if (star == 0)
        {
            cout << "\n\n\t\t\t\t\t\t\tENTER THE MANAGER PASSWORD\n\n";

            cout << "\t\t\t\t\t\t\t\t";

        }

        cout << " * ";
        star++;
    }

}

void movie_booking::data_str()
{
    ofstream fout;
    fout.open("/Users/pranavbejgam/Desktop/FINAL PROJECT/C++ Project/database1.csv", ios::app);
    string name1, name2, usr_id, usr_psd;
    
    fflush(stdin);


    cout << "\t\t\t\t\t\t\tENTER THE FIRST NAME\n";
    fflush(stdin);
    getline(cin, name1);
    cout << "\t\t\t\t\t\t\tENTER THE LAST NAME\n";
    fflush(stdin);
    getline(cin, name2);
    cout << "\t\t\t\t\t\t\tENTER THE USER ID\n";
    fflush(stdin);
    getline(cin, usr_id);
    cout << "\t\t\t\t\t\t\tENTER THE USER PASSWORD\n";
    fflush(stdin);
    getline(cin, usr_psd);
    fout << name1 << "," << name2 << "," << usr_id << "," << usr_psd << endl;

    fout.close();
    data_store = 1;
}
int movie_booking::password_check()
{
    cout << "\n\n\t\t\t\t\t\t\tENTER YOUR USER ID\n";
    fflush(stdin);
    cout << "\t\t\t\t\t\t\t";

    cin >> cus_id;
    ifstream myfile;
    myfile.open("/Users/pranavbejgam/Desktop/FINAL PROJECT/C++ Project/database1.csv");
    while (!myfile.eof())
    {
        getline(myfile, user, ',');
        getline(myfile, user, ',');
        getline(myfile, user, ',');
        getline(myfile, pass, '\n');
        fflush(stdin);

        fflush(stdin);
        if (user == cus_id || pass == cus_id)
        {
            foundu++;
            prnt_once++;
            if (prnt_once == 1)
                cout << "\n\n\t\t\t\t\t\t\tUSER ID FOUND\n";
        }


    }

    if (foundu == 0)
    {
        cout << "\n\n\t\t\t\t\t\t\tUSER ID NOT FOUND\n";
        myfile.close();
    }
    else
    {
        myfile.close();
        cout << "\n\n\t\t\t\t\t\t\tENTER YOUR USER PASSWORD\n";
        fflush(stdin);
        cout << "\t\t\t\t\t\t\t";
        cin >> cus_pas;
        myfile.open("/Users/pranavbejgam/Desktop/FINAL PROJECT/C++ Project/database1.csv");
        while (!myfile.eof())
        {
            getline(myfile, user, ',');
            getline(myfile, user, ',');
            getline(myfile, user, ',');
            getline(myfile, pass, '\n');
            fflush(stdin);

            fflush(stdin);
            if (pass == cus_pas)
            {
                foundp++;
                cout << "\n\n\t\t\t\t\t\t\tPASSWORD MATCHED\n";
            }


        }

    }

    if (foundp == 0)
        cout << "\n\n\t\t\t\t\t\t\tPASSWORD IS WRONG\n";


    myfile.close();
    return foundp;


}

int main()
{
    prnt_once = 0;
    movie_booking obj[4];
    while (1)
    {
        cout << "\n\n\t\t\t\t\t\t\t PRESS 1 TO BOOK TICKET IN NLH-101";
        cout << "\n\n\t\t\t\t\t\t\t PRESS 2 TO BOOK TICKET IN NLH-102";
        cout << "\n\n\t\t\t\t\t\t\t PRESS 3 TO BOOK TICKET IN NLH-103";
        cout << "\n\n\t\t\t\t\t\t\t PRESS 4 TO BOOK TICKET IN NLH-104";
        cout << "\n\n\t\t\t\t\t\t\t TO EXIT PROGRAM PRESS 9 ";
        cout << "\n\n\t\t\t\t\t\t\t ";
        cin >> obn;
        switch (obn)
        {
        case 1:
            cout << "\t\t\t\t\t\t\t";
            cout << "NLH-101 IS SELECTED\n";
            obj[0].first();
            break;
        case 2:
            cout << "\t\t\t\t\t\t\t";
            cout << "NLH-102 IS SELECTED\n";
            obj[1].first();
            break;
        case 3:
            cout << "\t\t\t\t\t\t\t";
            cout << "NLH-103 IS SELECTED\n";
            obj[2].first();
            break;
        case 4:
            cout << "\t\t\t\t\t\t\t";
            cout << "NLH-104 IS SELECTED\n";
            obj[3].first();
            break;
        case 9:
            goto bye;
            break;
        default:
            cout << "Enter a valid number\n";
            goto bye;
            break;
        }


    }



bye:
    cout << "its working WITH file handling \n";
    system("clear");
    cout << "\n\n\n\n\t\t\t\t\t\t\t THANK YOU FOR USING OUR APPLICATION!!!!";
    return 0;

}