// this .cpp aims to stimulate the bridge poker game by generating random hands and playing them.
//and attention the random number in this program is produced by random devices in linux
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iterator>
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

// 读取指定数量的随机字节
std::vector<unsigned char> read_random_bytes(size_t num_bytes) {
    std::vector<unsigned char> buffer(num_bytes);
    std::ifstream urandom("/dev/urandom", std::ios::binary);
    urandom.read(reinterpret_cast<char*>(buffer.data()), num_bytes);
    return buffer;
}


void shuffle_deck(std::vector<Card>& deck)
{
    auto random_bytes = read_random_bytes(52 * sizeof(size_t));
    std::seed_seq seed(random_bytes.begin(), random_bytes.end());
    std::mt19937 g(seed);
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
 