// this program will map 1-52 to a whole pair of pokers,and complete the function of select a card from a deck of 52 cards.
//by using the random number generator.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

//define the color and value of each card
const std::string suits[] = { "Clubs","Diamonds","Hearts","Spades" };
const std::string values[] = { "2","3","4","5","6","7","8","9","10","Jack","Queen","King","Ace"};

//generate a random number between 1 and 52
int generateRandomNumber(std::vector<int>& usedCards) //use & to pass the vector by reference, so that the vector can be modified inside the function
{
    int num;
    do
    {
        num = rand() % 52 + 1;
    } while (usedCards[num]);
    usedCards[num] = true;
    return num;
}

std::string getCard(int cardNum)
{
    int suitIndex = (cardNum -1) / 13;
    int valueIndex = (cardNum -1) % 13;
    return values[valueIndex] + suits[suitIndex];
}
    
int main()
{
    srand(time(NULL));

    std::vector<int>  usedCards(53, false); //initialize the vector with 52 false values,0 is not used
    
    for (int i = 0; i < 52; i++)
    {
        int cardNum = generateRandomNumber(usedCards);
        std::string stringofCard = getCard(cardNum);
        std::cout << stringofCard << std::endl;
    }


    return 0;

}
