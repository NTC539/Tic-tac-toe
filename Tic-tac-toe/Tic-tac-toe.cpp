#include <iostream>
#include <algorithm>

int isTrue = 1;
int MoveNumber;
char space[9]{ '1','2','3','4','5','6','7','8','9' };
int WinCombinations[8][3] = { {1,2,3},{4,5,6},{7,8,9},{1,4,7},{2,5,8},{3,6,9},{1,5,9},{3,5,7} };
int WinMoves[5]{ 5,1,3,7,9 };
int AiMoves[5];
int UserMoves[5];
int* AiWinComb;
int* UserWinComb;
int UserMove;
int countn = 0;
using namespace std;

void printSpace(char space[9]) {

    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            cout << "\n";
        }
        else {
            cout << " | ";
        }
        cout << space[i];
    }
}
bool IsIn1(int arr1[], int arr2[]) {
    for (int i = 0; i < 3; i++){
        for (size_t j = 0; j < 5; j++) {
            if (arr1[i] == arr2[j]) {
                return true;
            }
        }
    }
    return false;
}
bool IsIn2(int arr1[], int arr2[], int value) {
    for (int i = 0; i < 5; i++) {
        if ((arr1[i] == value) || (arr2[i] == value)) {
            return true;
        }
    }
    return false;
}
int* WinCheck(int Moves[5], int OpponentsMoves[5]) {
    int dubs = 0;
    static int MAX[2];
    MAX[0] = 0;
    MAX[1] = 0;
    for (int i = 0; i < 8; i++) {
        for (int n = 0; n < 5; n++) {
            for (int j = 0; j < 3; j++) {
                if (Moves[n] == WinCombinations[i][j]) {
                    dubs++;
                }
            }
        }
        if ((dubs > MAX[0]) && !(IsIn1(WinCombinations[i], OpponentsMoves))) {
            MAX[0] = dubs;
            MAX[1] = i;
        }
        dubs = 0;
    }
    return MAX;
}

void AiMove(){
    int* AiWinComb = WinCheck(AiMoves,UserMoves);
    switch (AiWinComb[0]) {
    case 0:
        for (int i = 0; i < 5; i++) {
            if (!IsIn2(UserMoves, AiMoves, WinMoves[i])) {
                space[WinMoves[i] - 1] = 'o';
                AiMoves[MoveNumber / 2 - 1] = WinMoves[i];
                break;
            }
        }
        break;
    case 1:
        UserWinComb = WinCheck(UserMoves, AiMoves);
        for (int i = 0; i < 3; i++)
        {
            if (!IsIn2(UserMoves, AiMoves, WinCombinations[UserWinComb[1]][i])) {
                countn++;
                space[WinCombinations[UserWinComb[1]][i] - 1] = 'o';
                AiMoves[MoveNumber / 2 - 1] = WinCombinations[UserWinComb[1]][i];
                break;
            }
        }
        if (countn == 0) {
            AiMove();
        }
        countn = 0;
        break;
    case 2:
        for (int i = 0; i < 3; i++) {
            if (!IsIn2(UserMoves, AiMoves, WinCombinations[AiWinComb[1]][i])) {
                space[WinCombinations[AiWinComb[1]][i] - 1] = 'o';
                AiMoves[MoveNumber / 2 - 1] = WinCombinations[AiWinComb[1]][i];
                system("cls");
                printSpace(space);
                cout << endl << "You lose!";
                isTrue = 0;
                break;
            }

        }
        break;
    }
}

int main() {
    while (isTrue == 1) {
        if (MoveNumber < 9) {
            system("cls");
            MoveNumber++;
            cout << "You - +" << endl;
            cout << "Move #" << MoveNumber << endl;
            printSpace(space);
            cout << "\nYour move >> ";
            cin >> UserMove;
            if (!IsIn2(UserMoves, AiMoves, UserMove)) {
                space[UserMove - 1] = '+';
                UserMoves[MoveNumber / 2] = UserMove;
                MoveNumber++;
                UserWinComb = WinCheck(UserMoves,AiMoves);
                switch(UserWinComb[0]) {
                case 1:
                case 2:
                    AiMove();
                    break;
                case 3:
                    system("cls");
                    printSpace(space);
                    cout << endl << "You win!";
                    isTrue = 0;
                }
            }
            else {
                MoveNumber--;
                continue;
            }
        }
        else {
            system("cls");
            printSpace(space);
            cout << endl << "Draw!";
            isTrue = 0;
        }
    }
}