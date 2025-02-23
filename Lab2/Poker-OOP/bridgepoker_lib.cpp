// This is the library file for bridge poker game.
#include <iostream>
#include <vector>

#include <string>
#include "random.h"

const int PlayerNum = 4;
const int CardNum = 52;
const int SuitNum = 4;
const int RankNum = 13;

const char* SuitStr[SuitNum] = {"Spa", "Hea", "Dia", "Clu"};
const char* RankStr[RankNum] = {"2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};
const char* PlayerStr[PlayerNum] = {"Player1", "Player2", "Player3", "Player4"};

enum {Player1, Player2, Player3, Player4};

int isValidcard[CardNum] = {0};

int count = 0;

void delay(int i,int j);

class CardNode 
{
public:
    int order;
    const char* suit() {return SuitStr[order/RankNum];}
    const char* rank () {return RankStr[order%RankNum];}
    int value();
    class CardNode* next;
};

class HandCardList
{
protected:
    class CardNode* head;
    int number;
    friend class Player;
public:
    HandCardList(): head(nullptr), number(0) {}
    ~HandCardList()
    {
        while(head)
        {
            CardNode* temp = head;
            head = head->next;
            delete temp;
        }
   }
};

class Player
{
private:
    int playerID;
   
    HandCardList handCardList;

public:
    int score;
    Player(int _player): playerID(_player), score(0) {}
    ~Player() {}
    void insertCard(int order);
    void showHandCard();
    const char* Name(){return PlayerStr[playerID];}
};


int CardNode::value()
{
    if (rank() == "A")
    {
        return 1;
    }
    else if ( rank() == "J" )
    {
        return 2;
    }
    else if ( rank() == "Q" )
    {
        return 3;
    }
    else if ( rank() == "K" )
    {
        return 4;
    }
    else
    {
        return 0;
    }
}


void Player::insertCard(int order)
{
    CardNode *current, *previous, *newNode;

    newNode = new CardNode;
    if (newNode == nullptr)
    {
        std::cout << "Memory allocation failed in insertCard()" << std::endl;
        return;
    }

    newNode->order = order;

    for (current = handCardList.head, previous = nullptr; 
    current!= nullptr && newNode->order > current->order; 
    previous = current, current = current->next)
    {
        ;
    }

    newNode->next = current;

    if (previous == nullptr)
    {
        handCardList.head = newNode;
    }
    else
    {
        previous->next = newNode;
    }
    score += newNode->value();

    handCardList.number++;
    
}

void Player::showHandCard()
{
    CardNode* point;

    printf("%8s %2d %2d:",Name(),handCardList.number,score);

    if (handCardList.number == 0)
    {
        printf(" No cards\n");
        return;
    }

    for (point = handCardList.head; point!= nullptr; point = point->next)
    {
        printf(" %8s%s", point->suit(), point->rank());
    }

    printf("\n");
}


void delay(int i,int j)
{
     for( ;j>0 ;j--)
        for( ;i>0 ;i--)
        ;
}


int main()
{
    printf("Welcome to Bridge Poker Game!\n");
    printf("There are 4 players, each has a hand card list.\n");
    printf("The game will start after all players have placed their cards.\n");
    printf("The game will end when all players have played their cards.\n");
    printf("player1 and player2 are in the same team, player3 and player4 are in the same team.\n");
    delay(999999999,999999999);
    Player players[PlayerNum] = {Player(Player1), Player(Player2), Player(Player3), Player(Player4)};

    Randomize();

    while(true)
    {
        if (count == CardNum)
        {
            break;
        }
        system("clear");
        int order = GenerateRandomNumber(0, CardNum-1);

        if (isValidcard[order] == 0)
        {
            isValidcard[order] = 1;
            int playerID = count % PlayerNum ;
            count ++;
            players[playerID].insertCard(order);
            printf("%s's turn\n", players[playerID].Name());
            for (int i = 0; i < PlayerNum; i++)
            {
                players[i].showHandCard();
            }

            delay(999999999,9999900);
        }
        int team1wholescore = players[Player1].score + players[Player2].score;
        int team2wholescore = players[Player3].score + players[Player4].score;

        printf("Team1's whole score is %d\n", team1wholescore);
        printf("Team2's whole score is %d\n", team2wholescore);

    }
    delay(9999999,9999999);
    return 0;
}
