// this program is a bridge poker game with 4 players and 13 cards each.
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

class Card {
public:
    char rank;
    char suit;

    Card(char r, char s) : rank(r), suit(s) 
    {
        //std::cout<<"Card created: "<<rank<<suit<<std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Card& card) {
        os << card.rank << card.suit;
        return os;
    }
};

class Deck {
private:
    std::vector<Card> cards;

    void initialize_deck() {
        std::vector<char> ranks = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
        std::vector<char> suits = {'S', 'H', 'D', 'C'};
        for (char suit : suits) {
            for (char rank : ranks) {
                cards.emplace_back(rank, suit);
            }
        }
    }

public:
    Deck() {
        initialize_deck();
    }

    void shuffle_deck() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }

    std::vector<std::vector<Card>> deal_cards(int num_players,int num_cards_per_player)
    {
        std::vector<std::vector<Card>> player_hands(num_players);
        
        for (int i = 0; i < num_players; ++i)
        {
            for (int j = 0; j < num_cards_per_player; ++j)
            {
                player_hands[ i ].push_back(cards[i * num_cards_per_player +j]);
            }
        }
        return player_hands;
    }
};


class BridgeGame {
private:
    Deck deck;

public:
    void play_game()
    {
        deck.shuffle_deck();
        std::vector<std::vector<Card>> player_hands(4); // 4 players

        // Deal cards to players
        player_hands = deck.deal_cards(4,13);

        // Calculate points for each player
        std::vector<int> player_points(4, 0);
        for (int i = 0; i < 4; ++i) {
            for (const Card& card : player_hands[i]) {
                player_points[i] += card_value(card.rank);
            }
            std::cout << "Player " << (i + 1) << " hand: ";
            for (const Card& card : player_hands[i]) {
                std::cout << card << " ";
            }
            std::cout << "Points: " << player_points[i] << std::endl;
        }
    }

    int card_value(char card) 
    {
        switch (card) 
        {
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return 0;
            case 'T': // 10
                return 0;
            case 'J': // Jack
                return 1;
            case 'Q': // Queen
                return 2;
            case 'K': // King
                return 3;
            case 'A': // Ace
                return 4;
            default:
                std::cerr << "Invalid card value: " << card << std::endl;
                return -1;
        }
    }
};


int main() 
{
    BridgeGame game;
    game.play_game();
    return 0;
}