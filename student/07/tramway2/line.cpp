/* Luokan Line metodit
 *
 * Ohjelman kirjoittaja:
 *
 * Nimi: Katariina Tenhunen
 * Opiskelijanumero: H299784
 * Käyttäjätunnus: kgkate
 * E-Mail: katariina.tenhunen@tuni.fi
 *
 * */

#include "line.hh"
#include <iostream>
#include <algorithm>

Line::Line(const std::string name):
    name_(name)
{

}

// Palauttaa totuusarvona tiedon siitä, onko linjalla
// parametrinä saatu pysäkki.
bool Line::has_stop(std::string stop_to_find) const
{
    for (auto stop : stops_)
    {
        if (stop.first == stop_to_find)
        {
            return true;
        }
    }
    return false;
}

// Palauttaa totuusarvona tiedon siitä, onko linjn jollain
// pysäkillä sama parametrinä saatu etäisyys.
bool Line::has_distance(double distance_to_find) const
{
    for (auto stop : stops_)
    {
        if (stop.second == distance_to_find)
        {
            return true;
        }
    }
    return false;
}

// Lisää linjalle uuden pysäkin, jos samannimistä pysäkkiä ei ole ja
// ja samalla etäisyydellä olevaa pysäkkiä ei ole. Palauttaa paluuarvona
// tottuusarvona tiedon, onko pysäkin lisääminen onnistunut.
bool Line::add_stop(std::string stopname, double distance, bool check_order = true)
{
    if (has_stop(stopname) or has_distance(distance))
    {
        return false;
    }
    if (stops_.size() == 0 or check_order == false)
    {
        stops_.push_back(make_pair(stopname, distance));
        return true;
    }
    unsigned int index_to_add = 1;
    bool reached_end = false;
    std::vector<std::pair<std::string, double>> new_stops = {};
    if (distance > 0)
    {
        new_stops.push_back({stops_.at(0)});
        for (unsigned int i = 1; i < stops_.size(); ++i)
        {
            double previous = stops_.at(i - 1).second;
            double next = stops_.at(i).second;
            if (distance > previous and distance < next)
            {
                index_to_add = i;
                break;
            }
            else if (i == (stops_.size() - 1))
            {
                stops_.push_back(make_pair(stopname, distance));
                reached_end = true;
                break;
            }
            new_stops.push_back(stops_.at(i));
        }
    }
    if (not reached_end)
    {
        new_stops.push_back(make_pair(stopname, distance));
        if (distance == 0)
        {
            index_to_add = 0;
        }
        for (unsigned int i = index_to_add; i < stops_.size(); ++i)
        {
            new_stops.push_back(stops_.at(i));
        }
        stops_ = new_stops;
    }
    return true;
}

// Poistaa linjalta annetun pysäkin ja palauttaa totuusarvona
// tiedon, onko pysäkin poisto onnistunut.
bool Line::remove_stop(std::string stopname)
{
    if (not has_stop(stopname))
    {
        return false;
    }
    unsigned int index_to_remove = 0;
    std::vector<std::pair<std::string, double>> stops = {};
    for (unsigned int i = 0; i < stops_.size(); ++i)
    {
        if (stops_.at(i).first == stopname)
        {
            index_to_remove = i;
            break;
        }
        else
        {
            stops.push_back(stops_.at(i));
        }
    }
    for (unsigned int i = index_to_remove + 1; i < stops_.size(); ++i)
    {
        stops.push_back(stops_.at(i));
    }
    stops_ = stops;
    return true;
}

// Tulostaa kaikki linjan pysäkit siinä järjestyksessä,
// missä ne on tallennettuna.
void Line::print_stops() const
{
    std::cout << "Line " << name_ << " goes through these stops in the order they are listed:" << std::endl;
    for (unsigned int i = 0; i < stops_.size(); ++i)
    {
        std::cout << "- " << stops_.at(i).first
                  << " : " << stops_.at(i).second << std::endl;
    }
}

// Palauttaa vektorin, joka sisältää kaikkien linjan pysäkkien nimet.
std::vector<std::string> Line::get_stops() const
{
    std::vector<std::string> stops = {};
    for (auto stop : stops_)
    {
        stops.push_back(stop.first);
    }
    return stops;
}

// Palauttaa desimaalilukuna annettujen pysäkkien etäisyyden.
double Line::distance(std::string stop1, std::string stop2) const
{
    double x1 = get_stop_information(stop1).second - get_stop_information(stop2).second;
    double x2 = get_stop_information(stop2).second - get_stop_information(stop1).second;

    if (x1 == x2)
    {
        return 0;
    }
    else if (x1 > x2)
    {
        return x1;
    }
    else
    {
        return x2;
    }
}

// Palauttaa parina yhden pysäkin tiedot.
std::pair<std::string, double> Line::get_stop_information(std::string stopname) const
{
    for (auto stop : stops_)
    {
        if (stop.first == stopname)
        {
            return stop;
        }
    }
    std::pair<std::string, double> empty = {"", 0};
    return empty;
}
