//Стандарт языка C++ ISO 14 
//Компиляция происходила в IDE Visual Studio 2019 при стандартных настройках 
/* 
Программа представляет из себя игру "Быки и коровы" с возможностью играть  
как с компьютером так и против игрока 
*/ 
#include <iostream> 
#include <windows.h> 
  
using namespace std; 
  
bool exists(int arr[], int item)//Function constains item in array 
{ 
    for (int i = 0; i < 4; i++) 
    { 
        if (arr[i] == item) 
        { 
            return true; 
        } 
    } 
    return false; 
} 
  
bool hasDubs(int code)//Function has dublicates in array 
{ 
    int Code[4]; 
  
    Code[0] = code / 1000; 
    Code[1] = (code % 1000) / 100; 
    Code[2] = (code % 100) / 10; 
    Code[3] = code % 10; 
  
    int cod[4]; 
    int indx = 0; 
    for (int i = 0; i < 4; i++) 
    { 
        if (exists(cod, Code[i])) 
        { 
            return true; 
        } 
        else 
        { 
            cod[indx] = Code[i]; 
            indx++; 
        } 
    } 
    return false; 
} 
  
int GetBulls(int origin_code, int code)//Function Get Bulls 
{ 
    int count = 0; 
  
    int a = code / 1000; 
    int b = (code % 1000) / 100; 
    int c = (code % 100) / 10; 
    int d = code % 10; 
  
    int sa = origin_code / 1000; 
    int sb = (origin_code % 1000) / 100; 
    int sc = (origin_code % 100) / 10; 
    int sd = origin_code % 10; 
  
    if (sa == a) count += 1; 
    if (sb == b) count += 1; 
    if (sc == c) count += 1; 
    if (sd == d) count += 1; 
  
    return count; 
} 
  
int GetCows(int origin_code, int code)//Function Get Cows 
{ 
    int count = 0; 
  
    int Code[4]; 
    Code[0] = code / 1000; 
    Code[1] = (code % 1000) / 100; 
    Code[2] = (code % 100) / 10; 
    Code[3] = code % 10; 
  
    int SCode[4]; 
    SCode[0] = origin_code / 1000; 
    SCode[1] = (origin_code % 1000) / 100; 
    SCode[2] = (origin_code % 100) / 10; 
    SCode[3] = origin_code % 10; 
  
    for (int i = 0; i < 4; i++) 
    { 
        for (int j = 0; j < 4; j++) 
        { 
            if (Code[i] == SCode[j]) 
            { 
                count+=1; 
            } 
        } 
    } 
  
    return count - GetBulls(origin_code,code); 
} 
  
short rand_range(short start, short end) { return start + (rand() % ((end + 1) - start)); }//Function ranged random 
  
int GetCode()//Function get random code 
{ 
    int code = 0; 
    code += rand_range(1,9) * 1000; 
    code += rand_range(1,9) * 100; 
    code += rand_range(1,9) * 10; 
    code += rand_range(1,9); 
  
    return code; 
} 
  
int main() 
{ 
Begin: 
    system("cls");//Clear screen 
    const int COMPUTER_MODE = 0x1; 
    const int PVP_MODE = 0x2; 
    int mode; 
  
    cout << "Select mode: \n\n"; 
  
    cout << "1-Player vs Computer" << endl; 
    cout << "2-Player vs Player" << endl; 
    cout << ">>>"; 
  
    cin >> mode;//Get mode 
  
    if (mode == COMPUTER_MODE) 
    { 
        system("cls");//Clear screen 
        cout << "Let's start!" << endl; //Write 
  
        int acts = 0; //Actions count 
        int SCODE = GetCode();//Getting secret code 
        int CODE=0; // 
  
        while(GetBulls(SCODE,CODE)!=4) 
        { 
            cout << ">>>"; 
            cin >> CODE;//Get code 
  
            if(CODE > 9999 || CODE < 1000)// if code more 4 digits or less than 4 digits 
            { 
                cout << "Code must be equals 4 numbers!" << endl; 
            } 
            else if (hasDubs(CODE))//Has dublicates 
            { 
                cout << "In the code has dublicates!" << endl; 
            } 
            else 
            { 
                cout << GetBulls(SCODE, CODE) << " Bulls," << GetCows(SCODE, CODE) << " Cows." << endl; 
                acts++;//Count actions 
            } 
        } 
        cout << "You win!" << endl; 
        cout << "Actions: " << acts<<endl; 
    } 
    else if (mode == PVP_MODE) 
    { 
        system("cls");//Clear screen 
    PVP: 
  
        GetAsyncKeyState(0x30 + 2);//Needed code for work "special symbols" 
  
        int Player1_SCODE = 0;//Player 1 Secure Code 
        int Player1_CODE = 0;//Player 1 Code 
  
        string Player1_Nick = ""; 
        string Player2_Nick = ""; 
  
        //Player enter names 
        cout << "Enter Player 1 Name: "; 
        cin >> Player1_Nick; //Enter Player 1 Nick 
  
        cout << "Enter Player 2 Name: "; 
        cin >> Player2_Nick; //Enter Player 2 Nick 
  
        system("cls");//Clear screen 
  
        //Player 1 enter secret code 
        Player1_EnterCode: 
        cout << Player1_Nick << " Enter Number: "; 
        int mul = 1000; 
        int count = 0; 
        while (count != 4) 
        { 
            for (int i = 0x30; i <= 0x39; i++) // 0x30 - 0x39 Digit keys on keyboard 
            { 
                int keystate = GetAsyncKeyState(i); // Get status of keys 
                if (keystate == 1 || keystate == -32767) // if pushed 
                { 
                    cout << '*'; //write * 
                    Player1_SCODE += (i - 0x30) * mul; //Set code 
                    mul /= 10; 
                    count++;//Count value increment 
                } 
            } 
        } 
        cout << endl; 
        if (Player1_SCODE > 9999 || Player1_SCODE < 1000)// if code more 4 digits or less than 4 digits 
        { 
            cout << "Code must be equals 4 numbers!" << endl; 
            goto Player1_EnterCode; 
        } 
        else if (hasDubs(Player1_SCODE))//Has dublicates 
        { 
            cout << "In the code has dublicates!" << endl; 
            goto Player1_EnterCode; 
        } 
  
        //Clear input buffer 
        for (int i = 0; i < 1000; i++) 
        { 
            keybd_event(0x08, 0, 0, 0);//Push key down 
            keybd_event(0x08, 0, KEYEVENTF_KEYUP, 0);//Push key up 
        } 
  
        int Player2_SCODE = 0;//Player 2 Secure Code 
        int Player2_CODE = 0;//Player 2 Code 
  
        //Player 2 enter secret code 
        Player2_EnterCode: 
        cout << Player2_Nick << " Enter Number: "; 
        mul = 1000; 
        count = 0; 
        while (count != 4) 
        { 
            for (int i = 0x30; i <= 0x39; i++)// 0x30 - 0x39 Digit keys on keyboard 
            { 
                int keystate = GetAsyncKeyState(i);// Get status of keys 
                if (keystate == 1 || keystate == -32767)// if pushed 
                { 
                    cout << '*';//write * 
                    Player2_SCODE += (i - 0x30) * mul;//Set code 
                    mul /= 10; 
                    count++;//Count value increment 
                } 
            } 
        } 
        cout << endl; 
        if (Player2_SCODE > 9999 || Player2_SCODE < 1000)// if code more 4 digits or less than 4 digits 
        { 
            cout << "Code must be equals 4 numbers!" << endl; 
            //Clear input buffer 
            for (int i = 0; i < 1000; i++) 
            { 
                keybd_event(0x08, 0, 0, 0);//Push key down 
                keybd_event(0x08, 0, KEYEVENTF_KEYUP, 0);//Push key up 
            } 
            goto Player2_EnterCode; 
        } 
        else if (hasDubs(Player2_SCODE))//Has dublicates 
        { 
            cout << "In the code has dublicates!" << endl; 
            goto Player2_EnterCode; 
        } 
  
        //Clear input buffer 
        for (int i = 0; i < 1000; i++) 
        { 
            keybd_event(0x08, 0, 0, 0);//Push key down 
            keybd_event(0x08, 0, KEYEVENTF_KEYUP, 0);//Push key up 
        } 
  
        system("cls");//Clear screen 
  
        //GAMEPLAY 
  
        int counter = 0; 
        bool first_win = false, second_win = false; 
  
        for (;;) 
        { 
            Player1_Turn: 
            //Player 1 Plays 
            cout << Player1_Nick << ": "; 
            cin >> Player1_CODE; 
  
            if (Player1_CODE > 9999 || Player1_CODE < 1000)// if code more 4 digits or less than 4 digits 
            { 
                cout << "Code must be equals 4 numbers!" << endl; 
                goto Player1_Turn; 
            } 
            else if (hasDubs(Player1_CODE))//Has dublicates 
            { 
                cout << "In the code has dublicates!" << endl; 
                goto Player1_Turn; 
            } 
            else 
            { 
                cout << GetBulls(Player2_SCODE, Player1_CODE) << " Bulls," << GetCows(Player2_SCODE, Player1_CODE) << " Cows." << endl; 
                counter++; 
            } 
  
            if (GetBulls(Player2_SCODE, Player1_CODE) == 4 && counter != 1) 
            { 
                cout << endl; 
                cout << Player1_Nick << " Win!" << endl; 
                break; 
            } 
            else 
            { 
                first_win = true; 
                goto Player2_Turn; 
            } 
  
            Player2_Turn: 
            //Player 2 Plays 
            cout << Player2_Nick << ": "; 
            cin >> Player2_CODE; 
  
            if (Player2_CODE > 9999 || Player2_CODE < 1000)// if code more 4 digits or less than 4 digits 
            { 
                cout << "Code must be equals 4 numbers!" << endl; 
                goto Player2_Turn; 
            } 
            else if (hasDubs(Player2_CODE))//Has dublicates 
            { 
                cout << "In the code has dublicates!" << endl; 
                goto Player2_Turn; 
            } 
            else 
            { 
                cout << GetBulls(Player1_SCODE, Player2_CODE) << " Bulls," << GetCows(Player1_SCODE, Player2_CODE) << " Cows." << endl; 
                counter++; 
            } 
  
            if (GetBulls(Player1_SCODE, Player2_CODE) == 4) 
            { 
                if (first_win == true)//if win both players in the begin of game 
                { 
                    cout << endl; 
                    cout << "Even!" << endl; 
                    break; 
                } 
                cout << endl; 
                cout << Player2_Nick << " Win!" << endl; 
                break; 
            } 
        } 
    } 
    else //If mode not 1 or 2 
    { 
        cout << "Error! Current mode not exists\n" << endl; 
  
        cout << "Press enter to continue..." << endl; 
  
        system("pause");//Continue function 
  
        goto Begin;//Go begin 
    } 
  
    system("pause");//Continue function 
  
    goto Begin; 
  
    return 0; 
}
