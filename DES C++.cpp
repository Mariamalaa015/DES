#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
using namespace std;
const int Pc_1[56] =
{ 57  , 49  ,  41  ,  33  ,  25 ,   17,  9,
   1  , 58  ,  50  ,  42  ,  34 ,   26 , 18,
  10  ,  2  ,  59  ,  51  ,  43 ,   35 , 27,
  19  , 11  ,  3   ,  60  ,  52 ,   44 , 36,
  63  , 55  ,  47  ,  39  ,  31 ,   23 , 15,
   7  , 62  ,  54  ,  46  ,  38 ,   30 , 22,
  14  ,  6  ,  61  ,  53  ,  45 ,   37 , 29,
  21  , 13  ,  5   ,  28  ,  20 ,   12 , 4 };
// Initial Permutation table
const int IPtable[64] =
{ 58 ,50 ,42 ,34 ,26 ,18 ,10 ,2 ,
  60 ,52 ,44 ,36 ,28 ,20 ,12 ,4 ,
  62 ,54 ,46 ,38 ,30 ,22 ,14 ,6 ,
  64 ,56 ,48 ,40 ,32 ,24 ,16 ,8 ,
  57 ,49 ,41 ,33 ,25 ,17 ,9  ,1 ,
  59 ,51 ,43 ,35 ,27 ,19 ,11 ,3 ,
  61 ,53 ,45 ,37 ,29 ,21 ,13 ,5 ,
  63 ,55 ,47 ,39 ,31 ,23 ,15 ,7 };
// Inverse Initial Permutation
const int inverse[64] =
{ 40 ,  8 , 48 ,  16  ,  56 ,  24  ,  64 ,  32,
  39 ,  7 , 47 ,  15  ,  55 ,  23  ,  63 ,  31,
  38 ,  6 , 46 ,  14  ,  54 ,  22  ,  62 ,  30,
  37 ,  5 , 45 ,  13  ,  53 ,  21  ,  61 ,  29,
  36 ,  4 , 44 ,  12  ,  52 ,  20  ,  60 ,  28,
  35 ,  3 , 43 ,  11  ,  51 ,  19  ,  59 ,  27,
  34 ,  2 , 42 ,  10  ,  50 ,  18  ,  58 ,  26,
  33 ,  1 , 41 ,  9   ,  49 ,  17  ,  57 ,  25 };
// Expansion Table
const int Expansiontable[48] =
{ 32 ,1  ,2  ,3  ,4  ,5  ,
  4  ,5  ,6  ,7  ,8  ,9  ,
  8  ,9  ,10 ,11 ,12 ,13 ,
  12 ,13 ,14 ,15 ,16 ,17 ,
  16 ,17 ,18 ,19 ,20 ,21 ,
  20 ,21 ,22 ,23 ,24 ,25 ,
  24 ,25 ,26 ,27 ,28 ,29 ,
  28 ,29 ,30 ,31 ,32 ,1 };
// Permutation Table
const int P[32] =
{ 16 ,7  ,20 ,21 ,
  29 ,12 ,28 ,17 ,
  1  ,15 ,23 ,26 ,
  5  ,18 ,31 ,10 ,
  2  ,8  ,24 ,14 ,
  32 ,27 ,3  ,9  ,
  19 ,13 ,30 ,6  ,
  22 ,11 ,4  ,25 };
// Permutation Choice 2 for Key
const int pc_2[48] =
{ 14 ,17 ,11 ,24 ,1  ,5  ,
  3  ,28 ,15 ,6  ,21 ,10 ,
  23 ,19 ,12 ,4  ,26 ,8  ,
  16 ,7  ,27 ,20 ,13 ,2  ,
  41 ,52 ,31 ,37 ,47 ,55 ,
  30 ,40 ,51 ,45 ,33 ,48 ,
  44 ,49 ,39 ,56 ,34 ,53 ,
  46 ,42 ,50 ,36 ,29 ,32 };
// Left shifting value
const int Left_shift[16] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1 };
const int S[8][4][16] = {
        {
            { 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 },
            { 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8 },
            { 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0 },
            { 15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 }
        },
        {
            { 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10 },
            { 3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5 },
            { 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15 },
            { 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 }
        },
        {
            { 10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8 },
            { 13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1 },
            { 13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7 },
            { 1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 }
        },
        {
            { 7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15 },
            { 13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9 },
            { 10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4 },
            { 3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 }
        },
        {
            { 2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9 },
            { 14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6 },
            { 4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14 },
            { 11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 }
        },
        {
            { 12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11 },
            { 10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8 },
            { 9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6 },
            { 4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 }
        },
        {
            { 4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1 },
            { 13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6 },
            { 1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2 },
            { 6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 }
        },
        {
            { 13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7 },
            { 1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2 },
            { 7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8 },
            { 2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 }
        }
};
string HexToBin(string hexdec)
{
    long int i = 0;
    string output = {};
    while (hexdec[i]) {

        switch (hexdec[i]) {
        case '0':
            output += "0000";
            break;
        case '1':
            output += "0001";
            break;
        case '2':
            output += "0010";
            break;
        case '3':
            output += "0011";
            break;
        case '4':
            output += "0100";
            break;
        case '5':
            output += "0101";
            break;
        case '6':
            output += "0110";
            break;
        case '7':
            output += "0111";
            break;
        case '8':
            output += "1000";
            break;
        case '9':
            output += "1001";
            break;
        case 'A':
        case 'a':
            output += "1010";
            break;
        case 'B':
        case 'b':
            output += "1011";
            break;
        case 'C':
        case 'c':
            output += "1100";
            break;
        case 'D':
        case 'd':
            output += "1101";
            break;
        case 'E':
        case 'e':
            output += "1110";
            break;
        case 'F':
        case 'f':
            output += "1111";
            break;
        default:
            cout << hexdec[i];
        }
        i++;
    }
    return output;
}
string BinToHex(string binary)
{
    string hex = "";
    for (int i = 0; i < binary.size(); i += 4)
    {
        string k = "";
        for (int j = i; j < i + 4; j++)
            k += binary[j];
        if (k == "0000")
            hex += '0';
        else if (k == "0001")
            hex += '1';
        else if (k == "0010")
            hex += '2';
        else if (k == "0011")
            hex += '3';
        else if (k == "0100")
            hex += '4';
        else if (k == "0101")
            hex += '5';
        else if (k == "0110")
            hex += '6';
        else if (k == "0111")
            hex += '7';
        else if (k == "1000")
            hex += '8';
        else if (k == "1001")
            hex += '9';
        else if (k == "1010")
            hex += 'A';
        else if (k == "1011")
            hex += 'B';
        else if (k == "1100")
            hex += 'C';
        else if (k == "1101")
            hex += 'D';
        else if (k == "1110")
            hex += 'E';
        else if (k == "1111")
            hex += 'F';
    }
    return hex;
}
string BinToDec(string n)
{
    int num;
    num = stoi(n);
    int dec_value = 0;
    int base = 1;

    int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;

        dec_value += last_digit * base;

        base = base * 2;
    }
    string decimal = to_string(dec_value);
    return decimal;
}
string DectoBin(int n)
{
    switch (n)
    {
    case 0:
        return "0000";
    case 1:
        return "0001";
    case 2:
        return "0010";
    case 3:
        return "0011";
    case 4:
        return "0100";
    case 5:
        return "0101";
    case 6:
        return "0110";
    case 7:
        return "0111";
    case 8:
        return "1000";
    case 9:
        return "1001";
    case 10:
        return "1010";
    case 11:
        return "1011";
    case 12:
        return "1100";
    case 13:
        return "1101";
    case 14:
        return "1110";
    case 15:
        return "1111";
    }
    return 0;
}
string shiftleft(string input, int numberofshifts) {
    string output = "";
    string x, copy;
    if (numberofshifts == 1)
    {
        for (int i = 1;i < 28;i++)
            copy += input[i];
        for (int i = 0;i < 27;i++)
            output += copy[i];
        output += input[0];
    }
    else if (numberofshifts == 2)
    {
        for (int i = 2;i < 28;i++)
            copy += input[i];
        for (int i = 0;i < 26;i++)
            output += copy[i];
        output += input[0];output += input[1];
    }
    return output;
}
string compression_permutation(string input) {
    string output = "";
    int x;
    for (int i = 0;i < 48;i++) {
        x = pc_2[i] - 1;
        output += input[x];
    }
    return output;
}
string expansion_permutation(string input) {
    string output = "";
    int x;
    for (int i = 0;i < 48;i++) {
        x = Expansiontable[i] - 1;
        output += input[x];
    }
    return output;

}
string XOR(string a, string b, int size) {
    string c = "";
    for (int i = 0; i < size;i++)
    {
        if (a[i] == b[i])
            c += "0";
        else
            c += "1";
    }
    return c;
}
string sbox(string input) {
    string output;
    int j = 0;
    for (int i = 0;i < 48;i += 6)
    {
        string m = input.substr(i, 6);
        string row;
        row += m[0];
        row += m[5];
        string column;
        column = m.substr(1, 4);
        int r = stoi(BinToDec(row));
        int c = stoi(BinToDec(column));
        int result = S[j][r][c];
        output += DectoBin(result);
        j++;
    }
    return output;
}
string permutation_32(string a) {
    string output = "";
    int x;
    for (int i = 0;i < 32;i++) {
        x = P[i] - 1;
        output += a[x];
    }
    return output;
}
string pc_1(string Key_1) {
    // Applying PC_1
    string K_1 = "";
    int x;
    string key_LPT = "", key_RPT = "";
    for (int i = 0;i < 56;i++) {
        x = Pc_1[i] - 1;
        K_1 += Key_1[x];
    }
    return K_1;
}
string Initial_permutation(string input)
{
    // Applying Initial Permutation
    string output = "";
    int x;
    for (int i = 0;i < 64;i++) {
        x = IPtable[i] - 1;
        output += input[x];
    }
    return output;
}
void swapping(string& a, string& b) {
    string temp;
    temp = a;
    a = b;
    b = temp;
}
string FinalPermutation(string input) {
    string output = "";
    int x;
    for (int i = 0;i < 64;i++) {
        x = inverse[i] - 1;
        output += input[x];
    }
    return output;
}
int main(int argc, char** argv) {
   
    // Parsing the input to get the code, operation 

    //string operation = input.substr(12, 7);
    string operation = argv[1];
    //string data = input.substr(20, 16);
    string data = argv[2];
    //string key = input.substr(37, 16);
    string key = argv[3];

    string data_LPT = "", data_RPT = "";
    // Converting the hexa input into binary

    string Key_1 = HexToBin(key);
    string data_1 = HexToBin(data);

    // Applying PC_1 to key
    string K_1 = "";
    int x;
    string key_LPT = "", key_RPT = "";
    for (int i = 0;i < 56;i++) {
        x = Pc_1[i] - 1;
        K_1 += Key_1[x];
    }

    // Splitting the key into LPT and RPT
    for (int i = 0; i < 28; i++)
        key_LPT += K_1[i];
    for (int i = 28; i < 56; i++) {
        key_RPT += K_1[i];
    }

    // Applying Initial Permutation on data
    string data_2 = Initial_permutation(data_1);

    // Splitting the data into LPT and RPT 
    for (int i = 0; i < 32; i++)
        data_LPT += data_2[i];
    for (int i = 32; i < 64; i++)
        data_RPT += data_2[i];

    ;
    // Key transformation using Shift left 
    // 16 rounds //
    string C[16], D[16], generated_keys[16], keys_results[16];
    string expanded[16], data_to_be_expanded[16], XOR_results[16], Sb[16], Pd[16], L[16], R[16];
    string last_results[16];
    if (operation == "encrypt") {
        for (int i = 0;i < 16;i++)
        {
            C[i] = shiftleft(key_LPT, Left_shift[i]);
            D[i] = shiftleft(key_RPT, Left_shift[i]);
            generated_keys[i] = C[i] + D[i];
            keys_results[i] = compression_permutation(generated_keys[i]);
            key_LPT = C[i];
            key_RPT = D[i];
        }
    }
    else if (operation == "decrypt")
    {
        for (int i = 0;i < 16;i++)
        {
            C[i] = shiftleft(key_LPT, Left_shift[i]);
            D[i] = shiftleft(key_RPT, Left_shift[i]);
            generated_keys[i] = C[i] + D[i];
            keys_results[15 - i] = compression_permutation(generated_keys[i]);
            key_LPT = C[i];
            key_RPT = D[i];
        }
    }



    cout << BinToHex(L[0]);
    for (int round = 0;round < 16;round++)
    {

        if (round > 0)
        {
            L[round] = R[round - 1];
        }
        if (round == 0)
        {

            expanded[round] = expansion_permutation(data_RPT);

            // Performing XOR on Expaneded RPT and key
            XOR_results[round] = XOR(expanded[round], keys_results[round], 48);

            // S-Box Permutation 
            Sb[round] = sbox(XOR_results[round]);

            //Applying permutation
            Pd[round] = permutation_32(Sb[round]);

            // Xoring LPT of data and permutated 32 bits
            //R0
            R[0] = XOR(data_LPT, Pd[round], 32);
            L[0] = data_RPT;
        }
        else {
            // Expansion permutation 
            expanded[round] = expansion_permutation(R[round - 1]);

            // Performing XOR on Expaneded RPT and key
            XOR_results[round] = XOR(expanded[round], keys_results[round], 48);

            // S-Box Permutation 
            Sb[round] = sbox(XOR_results[round]);

            //Applying permutation
            Pd[round] = permutation_32(Sb[round]);

            // Xoring LPT of data and permutated 32 bits
            R[round] = XOR(L[round - 1], Pd[round], 32);
        }


        // Swapping at the end of rounds
        if (round == 15)
            swapping(R[round], L[round]);

    }
    string inverse_input = "";
    inverse_input += L[15];
    inverse_input += R[15];
    string final_output;
    final_output = FinalPermutation(inverse_input);
    // Displaying results
    if (operation == "encrypt")
        cout << "cipher:" << BinToHex(final_output) << endl;
    else if (operation == "decrypt")
        cout << "plain:" << BinToHex(final_output) << endl;

    return 0;
}
