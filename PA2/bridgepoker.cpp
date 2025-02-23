// this .cpp aims to stimulate the bridge poker game by generating random hands and playing them.
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

const std::vector<char> ranks = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };
const std::vector<char> suits = { 'S', 'H', 'D', 'C' };

struct  Card
{
    char rank;
    char suit;
};

int card_value(char card)
{
    if (card >= '2' && card <= '9')
    {
        return 0;
    }
    if (card == 'T')
    {
        return 0;
    }
    if (card == 'J')
    {
        return 1;
    }
    if (card == 'Q')
    {
        return 2;
    }
    if (card == 'K')
    {
        return 3;
    }
    if (card == 'A')
    {
        return 4;
    }
    std::cout << "wrong card: " << card << std::endl;
    return -1;

}

std::vector<Card> generate_deck()
{
    std::vector<Card> deck;
    for (char suit : suits)
    {
        for (char rank : ranks)
        {
            Card card = { rank, suit };
            deck.push_back(card);
        }
    }
    return deck;
}

void shuffle_deck(std::vector<Card>& deck)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}

void deal_cards_and_calculate_points(const std::vector<Card> &deck) {
    const int num_players = 4;
    const int cards_per_player = 13;
    std::vector<int> player_points(num_players, 0);
   
    for (int i = 0; i < num_players; ++i) {
        std::cout << "Player " << i + 1 << " hand: ";
        for (int j = 0; j < cards_per_player; ++j) {
            Card card = deck[i * cards_per_player + j];
            std::cout << card.rank << card.suit << " ";
            player_points[i] += card_value(card.rank);
        }
        std::cout << "Points: " << player_points[i] << std::endl;
    }
}

int main()
{
std::vector<Card> deck = generate_deck();
shuffle_deck(deck);
deal_cards_and_calculate_points(deck);
return 0;
}
