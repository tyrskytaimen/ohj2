/* Muistipeli
 *
 * Kuvaus:
 *  Ohjelma toteuttaa yksinkertaisen muistipelin. Pelin alussa käyttäjältä
 * kysytään korttien määrä ja siemenlukua, jonka avulla kortit arvotaan
 * satunnaisesti pelilaudalle.
 *  Joka kierroksella vuorossa olevalta pelaajalta kysytään lahden kortin
 * koordinaatit, minkä jälkeen kortit käännetään ja selviää ovatko kortit
 * parit vai ei. Jos kyseessä on pari, kortit poistetaan pelilaudalta,
 * pelaaja saa pisteen ja hän saa jatkaa vuoroaan. Jos ei löydy paria, vuoro
 * siirtyy seuraavalle pelaajalle ja kortin käännetään takaisin piiloon.
 *  Ohjelma tarkistaa käyttäjän antamat syötteet. Jos syöte ei ole kelvollinen
 * kysytään sitä uudelleen.
 *  Pelilaudan kortit kuvataan isoilla kirjaimilla A:sta alkaen, parien määrän
 * verran. Kortin ollessa piilossa, sitä kuvataan risuaidalla (#).
 * Pelilaudalta poistettu kortti taas kuvataan pisteellä.
 *  Peli päättyy silloin, kun pelilaudalla ei ole enää kortteja. Tällöin
 * kerrotaan kuka on voittaja ja kuinka monta pistettä hänellä on. Tasapeli-
 * tilanteessa kerrotaan kuinka moni pääsi tasoihin ja mikä oli heidän
 * pistemääränsä.
 *
 *
 * Ohjelman kirjoittaja:
 *
 * Nimi: Katariina Tenhunen
 * Opiskelijanumero: H299784
 * Käyttäjätunnus: kgkate
 * E-Mail: katariina.tenhunen@tuni.fi
 *
 * */

#include <player.hh>
#include <card.hh>
#include <iostream>
#include <vector>
#include <random>
#include <string>

using namespace std;

const string INPUT_AMOUNT_OF_CARDS = "Enter the amount of cards (an even number): ";
const string INPUT_SEED = "Enter a seed value: ";
const string INPUT_AMOUNT_OF_PLAYERS = "Enter the amount of players (one or more): ";
const string INPUT_CARDS = "Enter two cards (x1, y1, x2, y2), or q to quit: ";
const string INVALID_CARD = "Invalid card.";
const string FOUND = "Pairs found.";
const string NOT_FOUND = "Pairs not found.";
const string GIVING_UP = "Why on earth you are giving up the game?";
const string GAME_OVER = "Game over!";

using Game_row_type = vector<Card>;
using Game_board_type = vector<vector<Card>>;

// Muuntaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan
// (mikä johtaa laittomaan korttiin myöhemmin).
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Täyttää pelilaudan (kooltaan rows * columns) tyhjillä korteilla.
void init_with_empties(Game_board_type& g_board, unsigned int rows, unsigned int columns)
{
    g_board.clear();
    Game_row_type row;
    for(unsigned int i = 0; i < columns; ++i)
    {
        Card card;
        row.push_back(card);
    }
    for(unsigned int i = 0; i < rows; ++i)
    {
        g_board.push_back(row);
    }
}

// Etsii seuraavan tyhjän kohdan pelilaudalta (g_board) aloittamalla
// annetusta kohdasta start ja jatkamalla tarvittaessa alusta.
// (Kutsutaan vain funktiosta init_with_cards.)
unsigned int next_free(Game_board_type& g_board, unsigned int start)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Aloitetaan annetusta arvosta
    for(unsigned int i = start; i < rows * columns; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY) // vaihdettu
        {
            return i;
        }
    }
    // Jatketaan alusta
    for(unsigned int i = 0; i < start; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY)
        {
            return i;
        }
    }
    // Tänne ei pitäisi koskaan päätyä
    std::cout << "No more empty spaces" << std::endl;
    return rows * columns - 1;
}

// Alustaa annetun pelilaudan (g_board) satunnaisesti arvotuilla korteilla
// annetun siemenarvon (seed) perusteella.
void init_with_cards(Game_board_type& g_board, int seed)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Arvotaan täytettävä sijainti
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, rows * columns - 1);
    // Hylätään ensimmäinen satunnaisluku (joka on aina jakauman alaraja)
    distr(randomEng);

    // Jos arvotussa sijainnissa on jo kortti, valitaan siitä seuraava tyhjä paikka.
    // (Seuraava tyhjä paikka haetaan kierteisesti funktion next_free avulla.)
    for(unsigned int i = 0, c = 'A'; i < rows * columns - 1; i += 2, ++c)
    {
        // Lisätään kaksi samaa korttia (parit) pelilaudalle
        for(unsigned int j = 0; j < 2; ++j)
        {
            unsigned int cell = distr(randomEng);
            cell = next_free(g_board, cell);
            g_board.at(cell / columns).at(cell % columns).set_letter(c);
            g_board.at(cell / columns).at(cell % columns).set_visibility(HIDDEN);
        }
    }
}

// Tulostaa annetusta merkistä c koostuvan rivin,
// jonka pituus annetaan parametrissa line_length.
// (Kutsutaan vain funktiosta print.)
void print_line_with_char(char c, unsigned int line_length)
{
    for(unsigned int i = 0; i < line_length * 2 + 7; ++i)
    {
        cout << c;
    }
    cout << endl;
}

// Tulostaa vaihtelevankokoisen pelilaudan reunuksineen.
void print(const Game_board_type& g_board)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    print_line_with_char('=', columns);
    cout << "|   | ";
    for(unsigned int i = 0; i < columns; ++i)
    {
        cout << i + 1 << " ";
    }
    cout << "|" << endl;
    print_line_with_char('-', columns);
    for(unsigned int i = 0; i < rows; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < columns; ++j)
        {
            g_board.at(i).at(j).print();
            cout << " ";
        }
        cout << "|" << endl;
    }
    print_line_with_char('=', columns);
}

// Kysyy käyttäjältä tulon ja sellaiset tulon tekijät, jotka ovat
// mahdollisimman lähellä toisiaan.
void ask_product_and_calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor)
{
    unsigned int product = 0;
    while(not (product > 0 and product % 2 == 0))
    {
        std::cout << INPUT_AMOUNT_OF_CARDS;
        string product_str = "";
        std::getline(std::cin, product_str);
        product = stoi_with_check(product_str);
    }

    for(unsigned int i = 1; i * i <= product; ++i)
    {
        if(product % i == 0)
        {
            smaller_factor = i;
        }
    }
    bigger_factor = product / smaller_factor;
}

// Kysyy ohjelman käyttäjältä pelaajien määrää, ja palauttaa kokonaisluvun
// saatuaan käyttäjältä kelvollisen syötteen (positiivisen luvun).
int player_amount_with_check()
{
    int number_of_players = 0;
    std::string input = "";
    while(true)
    {
        std::cout << INPUT_AMOUNT_OF_PLAYERS;
        std::cin >> input;
        number_of_players = stoi_with_check(input);
        if(number_of_players < 1)
        {
            continue;
        }
        break;
    }
    return number_of_players;
}

// Kysyy käyttäjältä koordinaatit, tallentaa ne parametrinä annettuun
// vektoriin ja palauttaa totuusarvona haluaako pelaaja
// lopettaa pelin (false) vai jatkaa (true).
bool get_coordinates(std::vector<unsigned int>& coordinates, std::string name)
{
    std::string coordinate = "";

    std::cout << name << ": " << INPUT_CARDS;
    for(int i = 0; i < 4; ++i)
    {
        std::cin >> coordinate;
        if(coordinate == "q")
        {
            std::cout << GIVING_UP << std::endl;
            return false;
        }
        else
        {
            coordinates.at(i) = stoi_with_check(coordinate);
        }
    }
    return true;
}

// Tarkistaa parametrinä saadut koordinaatit ja palauttaa totuusarvona,
// ovatko koordinaatit kelvollisia.
bool is_valid_coordinates(Game_board_type& g_board, std::vector<unsigned int>& coordinates)
{
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    for(int i = 0; i < 4; i += 2)
    {
        if(coordinates.at(i) < 1 or coordinates.at(i + 1) < 1)
        {
            return false;
        }
        else if(coordinates.at(i) > columns or coordinates.at(i + 1) > rows)
        {
            return false;
        }
        else if(g_board.at(coordinates.at(i + 1) - 1).at(coordinates.at(i) - 1)
                .get_visibility() == EMPTY)
        {
            return false;
        }
    }
    if(coordinates.at(0) == coordinates.at(2) and coordinates.at(1) == coordinates.at(3))
    {
        return false;
    }
    return true;
}

// Kääntää parametrinä annettuja koordinaatteja vastaavat kortit ja palauttaa
// totuusarvona tiedon siitä, olivatko kortit parit (true) vai ei (false).
bool turn_cards_and_check_pairs(Game_board_type& g_board,
                                std::vector<unsigned int>& coordinates, Player* player)
{
    Card& card1 = g_board.at(coordinates.at(1) - 1).at(coordinates.at(0) - 1);
    Card& card2 = g_board.at(coordinates.at(3) - 1).at(coordinates.at(2) - 1);

    card1.turn();
    card2.turn();
    print(g_board);

    if(card1.get_letter() == card2.get_letter())
    {
        player->add_card(card1);
        player->add_card(card2);
        std::cout << FOUND << std::endl;
        return true;
    }
    else
    {
        card1.turn();
        card2.turn();
        std::cout << NOT_FOUND << std::endl;
        return false;
    }
}

// Palauttaa tiedon siitä, onko pelilauta tyhjä (true) ja peli ohi.
bool is_game_over(Game_board_type& g_board, std::vector<Player>& players)
{
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    int sum = 0;
    int max_pairs = (rows * columns) / 2;
    int length = players.size();

    for (int i = 0; i < length; ++i)
    {
        sum += players.at(i).number_of_pairs();
    }

    if(sum < max_pairs)
    {
        return false;
    }
    else
    {
        std::cout << GAME_OVER << std::endl;
        return true;
    }
}

// Tulostaa voittajan tai useamman voittajan määrän
// ja pisteet.
void print_winner(std::vector<Player>& players)
{
    int best_score = 0;
    int new_points = 0;
    int length = players.size();
    vector<Player> winners;

    for(int i = 0; i < length; ++i)
    {
        new_points = players.at(i).number_of_pairs();
        if(new_points > best_score)
        {
            while(winners.size() != 0)
            {
                winners.pop_back();
            }
            winners.push_back(players.at(i));
            best_score = new_points;
        }
        else if(new_points == best_score)
        {
            winners.push_back(players.at(i));
            best_score = new_points;
        }
    }

    int number_of_winners = winners.size();
    if(number_of_winners == 1)
    {
        std::cout << winners.at(0).get_name() << " has won with "
                  << winners.at(0).number_of_pairs() << " pairs." << std::endl;
    }
    else
    {
        std::cout << "Tie of " << number_of_winners << " players with "
                  << winners.at(0).number_of_pairs() << " pairs." << std::endl;
    }
}


int main()
{
    Game_board_type game_board;

    unsigned int factor1 = 1;
    unsigned int factor2 = 1;
    ask_product_and_calculate_factors(factor1, factor2);
    init_with_empties(game_board, factor1, factor2);

    string seed_str = "";
    std::cout << INPUT_SEED;
    std::getline(std::cin, seed_str);
    int seed = stoi_with_check(seed_str);
    init_with_cards(game_board, seed);

    int number_of_players = 0;
    number_of_players = player_amount_with_check();

    // Kysytään pelaajien nimet ja tallennetaan niitä
    // vastaavat oliot vektoriin.
    std::cout << "List " << number_of_players << " players: ";
    std::string name = "";
    std::vector<Player> players;
    for (int i = 0; i < number_of_players; ++i)
    {
        std::cin >> name;
        players.push_back(Player(name));
    }
    print(game_board);

    Player* in_turn = 0;
    int turn = 0;
    std::vector<unsigned int> coordinates(4, 0);

    while(true)
    {
        in_turn = &players.at(turn);
        while(true)
        {
            // Kutsutaan funktiota, josta saadaan pelaajan koordinaatit.
            if (not get_coordinates(coordinates, in_turn->get_name()))
            {
                return EXIT_SUCCESS;
            }
            // Tutkitaan ovatko koordinaatit kelvolliset.
            if(not is_valid_coordinates(game_board, coordinates))
            {
                std::cout << INVALID_CARD << std::endl;
                continue;
            }
            else
            {
                break;
            }
        }        
        if(not turn_cards_and_check_pairs(game_board, coordinates, in_turn))
        {
            turn += 1;
            if(turn == number_of_players)
            {
                turn = 0;
            }
        }
        // Tulostetaan sekä pelaajien pistesaldo, että pelilauta
        // kierroksen jälkeen.
        for(int i = 0; i < number_of_players; ++i)
        {
            std::cout << "*** " << players.at(i).get_name() << " has "
                      << players.at(i).number_of_pairs() << " pair(s)." << std::endl;
        }
        print(game_board);

        if (is_game_over(game_board, players))
        {
            print_winner(players);
            break;
        }
    }

    return EXIT_SUCCESS;
}

