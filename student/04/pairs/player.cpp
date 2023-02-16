/* Luokan Player metodit
 *
 * Ohjelman kirjoittaja:
 *
 * Nimi: Katariina Tenhunen
 * Opiskelijanumero: H299784
 * Käyttäjätunnus: kgkate
 * E-Mail: katariina.tenhunen@tuni.fi
 *
 * */

#include "player.hh"
#include <iostream>

// Lisää luokan toteutus tähän.
// Kuhunkin julkiseen metodiin pitäisi riittää 1-2 koodiriviä.
Player::Player(const std::string& name):
    name_(name)
{

}

// Palauttaa pelaajan nimen.
std::string Player::get_name() const
{
    return name_;
}

// Palauttaa pelaajan tähän asti keräämien parien määrän.
unsigned int Player::number_of_pairs() const
{
    return cards_ / 2;
}

// Siirtää annetun kortin pelilaudalta pelaajalle,
// eli lisää kortin pelaajan keräämiin kortteihin
// ja poistaa sen pelilaudalta.
void Player::add_card(Card& card)
{
    cards_ += 1;
    card.remove_from_game_board();
}

// Tulostaa pelaajan tilanteen: nimen ja tähän asti kerättyjen parien määrän.
void Player::print() const
{
    std::cout << "*** " << name_ << " has " << number_of_pairs() << " pair(s).";
}
