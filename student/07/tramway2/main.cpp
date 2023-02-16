/* Rasse2
 *
 * Kuvaus:
 *  Ohjelmassa käyttäjä pystyy hakemaan, lisäämään ja poistamaan ratikka-
 * linjoihin liittyvää tietoa. Ohjelman käynnistyessä käyttäjältä kysytään
 * mistä tiedostosta luetaan tiedot ohjelmaa varten.
 *  Jos tiedoston luku ei onnistu, tulostaa ohjelma virheilmoituksen ja
 * ohjelman suorittaminen loppuu. Jos tiedoston luku on taas onnistunut,
 * jää ohjelma odottamaan käyttäjän syötettä.
 *  Ohjelman aikana käyttäjällä on käytettävissä komennot "LINES", "LINE",
 * "STOPS", "STOP" ja "DISTANCE", jotka tulostavat tietoa linjoista ja pysäkeistä.
 * Komennot "ADDNLIE", "ADDSTOP" ja "REMOVE" lisäävät tai poistavat tietoa
 * tietorakenteesta, mutta eivät tee muokkauksia itse tiedostoon.
 *  Ohjelman suoritus ei pysähdy virheellisen syötteeseen, vaan ohjelma
 * tulostaa virheilmoituksen ja kysyy komentoa uudelleen. Jos komentoa
 * ei löydy tai sitä varten ei ole tarpeeksi parametrejä, ilmoittaa
 * ohjelma virheellisestä syötteestä. Ohjelma ei tarkista onko parametrejä
 * annettu liikaa, vaan ne jätetään vain käyttämättä. Jos komennon jälkeen
 * annetut parametrit taas ovat virheelliset, tulostaa ohjelma niitä
 * vastaavan virheilmoituksen.
 *  Ohjelmaa suoritetaan niin kauan, kunnes käyttäjä antaa komennon "QUIT".
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

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "line.hh"

const std::string FILE_ERROR = "Error: File could not be read.";
const std::string INVALID_FORMAT = "Error: Invalid format in file.";
const std::string STOP_LINE_ERROR = "Error: Stop/line already exists.";
const std::string INVALID_INPUT = "Error: Invalid input.";
const std::string LINE_NOT_FOUND = "Error: Line could not be found.";
const std::string STOP_NOT_FOUND = "Error: Stop could not be found.";


// The most magnificent function in this whole program.
// Prints a RASSE
void print_rasse()
{
    std::cout <<
                 "=====//==================//===\n"
                 "  __<<__________________<<__   \n"
                 " | ____ ____ ____ ____ ____ |  \n"
                 " | |  | |  | |  | |  | |  | |  \n"
                 " |_|__|_|__|_|__|_|__|_|__|_|  \n"
                 ".|                  RASSE   |. \n"
                 ":|__________________________|: \n"
                 "___(o)(o)___(o)(o)___(o)(o)____\n"
                 "-------------------------------" << std::endl;
}

std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

// Luetaan tiedostosta linjoihin liityvä tieto ja tallennetaan se
// parametrinä annettuun tietorakenteeseen.
bool read_file(std::map<std::string,Line>& lines)
{
    std::cout << "Give a name for input file: ";
    std::string filename = "";
    getline(std::cin, filename);
    std::ifstream file(filename);
    if (not file)
    {
        std::cout << FILE_ERROR << std::endl;
        return false;
    }

    std::string line = "";
    while(getline(file, line))
    {
        // Jaetaan tiedostosta luettu rivi osiin välimerkin kohdalta
        // ja jos rivi on virheellinen, palautetaan paluuarvona false.
        std::vector<std::string> parts = split(line, ';');
        if (parts.size() > 3 or parts.size() < 2)
        {
            std::cout << INVALID_FORMAT << std::endl;
            return false;            
        }
        
        std::string linename = parts.at(0);
        std::string stop = parts.at(1);
        // Etäisyyden arvo on vakiona 0, mutta jos rivillä on annettu
        // etäisyydelle arvo, asetetaan se etäisyydeksi.
        double distance = 0;        
        if (parts.size() == 3 && parts.at(2).length() != 0)
        {
           distance = stod(parts.at(2)); 
        }

        if (lines.find(linename) == lines.end())
        {
            lines.insert({linename, Line(linename)});
        }
        // Jos pysäkin lisääminen ei onnistu, palautetaan paluuarvona false.
        if (not lines.at(linename).add_stop(stop, distance, false))
        {
            std::cout << STOP_LINE_ERROR << std::endl;
            return false;
        }
    }
    file.close();
    return true;
}

// Lisää tietorakenteeseen uuden linjan. Jos samanniminen linja on jo olemassa
// ei uutta linjaa lisätä, vaan tulostetaan virheilmoitus.
void add_line(std::map<std::string,Line>& lines, std::string linename)
{
    if (lines.find(linename) == lines.end())
    {
        lines.insert({linename, Line(linename)});
        std::cout << "Line was added." << std::endl;
    }
    else
    {
        std::cout << STOP_LINE_ERROR << std::endl;
    }
}

// Lisää parametrinä saadun pysäkin annettuun linjaan. Jos linjalla on jo
// samanniminen pysäkki tai pysäkki on samalla etäisyydellä kuin joku
// pysäkeistä, tulostaa virheilmoituksen.
void add(std::map<std::string,Line>& lines, std::string line, std::string stopname, double distance)
{
    if (not lines.at(line).add_stop(stopname, distance, true))
    {
        std::cout << STOP_LINE_ERROR << std::endl;
    }
    else
    {
        std::cout << "Stop was added." << std::endl;
    }
}

// Poistaa parametrinä saadun pysäkin jokaiselta linjalta, mihin se
// kuuluu.
void remove(std::map<std::string,Line>& lines, std::string stop)
{
    for (auto& line : lines)
    {
        line.second.remove_stop(stop);
    }
    std::cout << "Stop was removed from all lines." << std::endl;
}

// Tarkistaa onko parametrinä saatu pysäkki tietorakenteessa ja palauttaa
// joko totuusarvon true linjan löytyessä tai false.
bool is_valid_stop(std::map<std::string,Line>& lines, std::string stop)
{
    for (auto line : lines)
    {
        if (line.second.has_stop(stop))
        {
            return true;
        }
    }
    std::cout << STOP_NOT_FOUND << std::endl;
    return false;
}

// Tarkistaa onko parametrinä saatu linja tietorakenteessa ja palauttaa
// joko totuusarvon true linjan löytyessä tai false.
bool is_valid_line(std::map<std::string,Line>& lines, std::string line)
{
    if (lines.find(line) != lines.end())
    {
       return true;
    }
    std::cout << LINE_NOT_FOUND << std::endl;
    return false;
}

// Tulostaa kaikki linjat mitä tietorakenteeseen on tallennettu.
void print_all_stops(const std::map<std::string,Line>& lines)
{
    std::vector<std::string> stops;
    for (auto line : lines)
    {
        for (auto stop : line.second.get_stops())
        {
            if (find(stops.begin(), stops.end(), stop) == stops.end())
            {
                stops.push_back(stop);
            }
        }
    }
    std::cout << "All stops in alphabetical order:" << std::endl;
    sort(stops.begin(), stops.end());
    for (auto stop : stops)
    {
        std::cout << stop << std::endl;
    }
}

// Tulostaa kaikki ne linjat, joille parametrinä annettu pysäkki
// kuuluu.
void print_stops_lines(std::map<std::string,Line>& lines, std::string stop)
{
    std::vector<std::string> lines_with_stop;
    for (auto line : lines)
    {
        if (line.second.has_stop(stop))
        {
            lines_with_stop.push_back(line.first);
        }
    }
    std::cout << "Stop " << stop << " can be found on the following lines:" << std::endl;
    sort(lines_with_stop.begin(), lines_with_stop.end());
    for (auto line : lines_with_stop)
    {
        std::cout << " - " << line << std::endl;
    }
}

// Tulostaa paramtereinä saatujen pysäkkien etäisyyden toisistaan, jos pysäkit
// ovat samalla linjalla.
void print_distance(std::map<std::string,Line>& lines, std::string line, std::string stop1, std::string stop2)
{
    if (lines.at(line).has_stop(stop1) and lines.at(line).has_stop(stop2))
    {
        std::cout << "Distance between " << stop1 << " and " << stop2 << " is "
               << lines.at(line).distance(stop1, stop2) << std::endl;
    }
    else
    {
        std::cout << STOP_NOT_FOUND << std::endl;
    }
}

// Kysyy käyttäjältä komennon ja palauttaa vektorin, joka sisältää saadun syötteen
// osat ilman välimerkkiä ' " '.
std::vector<std::string> get_parts()
{
    std::cout << "tramway> ";
    std::string input;
    getline(std::cin, input);
    std::vector<std::string> parts = split(input, '"', true);

    if (parts.size() == 1)
    {
        std::vector<std::string> all_parts = split(input, ' ');
        return all_parts;
    }
    else
    {
        std::vector<std::string> all_parts = split(parts.at(0), ' ', true);
        all_parts.push_back(parts.at(1));
        if (parts.size() == 3)
        {
            std::vector<std::string> parts_after = split(parts.at(2), ' ', true);
            for (unsigned int i = 0; i < parts_after.size(); ++i)
            {
                all_parts.push_back(parts_after.at(i));
            }
        }

        return all_parts;
    }
}

std::string upper_case(std::string word)
{
    std::string upper_word;
    for (char c : word)
    {
        upper_word += toupper(c);
    }
    return upper_word;
}

int main()
{
    print_rasse();
    // Tallennetaan linjojen tieto map-tietorakenteeseen, jossa
    // avaimena on linjan nimi, ja hyötykuormana Linja-luokkainen olio.
    std::map<std::string,Line> lines;

    // Luetaan tiedosto ja virhetilanteessa lopetetaan ohjelman
    // suoritus.
    if (not read_file(lines))
    {
        return EXIT_FAILURE;
    }

    while(true)
    {        
        std::vector<std::string> parts = get_parts();
        std::string command = upper_case(parts.at(0));

        if (command == "LINES")
        {
            std::cout << "All tramlines in alphabetical order:" << std::endl;
            for (auto line : lines)
            {
                std::cout << line.first << std::endl;
            }
        }
        else if (command == "LINE" and parts.size() >= 2)
        {
            std::string line = parts.at(1);
            if (is_valid_line(lines, line))
            {
                lines.at(line).print_stops();
            }
        }
        else if (command == "STOPS")
        {
            print_all_stops(lines);
        }
        else if (command == "STOP" and parts.size() >= 2)
        {
            std::string stop = parts.at(1);
            if (is_valid_stop(lines, stop))
            {
                print_stops_lines(lines, stop);
            }
        }
        else if (command == "DISTANCE" and parts.size() >= 4)
        {
            std::string line = parts.at(1);
            std::string first_stop = parts.at(2);
            std::string second_stop = parts.at(3);
            if (is_valid_line(lines, line))
            {
                print_distance(lines, line, first_stop, second_stop);
            }
        }
        else if (command == "ADDLINE" and parts.size() >= 2)
        {
            std::string new_line = parts.at(1);
            add_line(lines, new_line);
        }
        else if (command == "ADDSTOP" and parts.size() >= 4)
        {
            std::string line = parts.at(1);
            std::string new_stop = parts.at(2);
            double distance = stod(parts.at(3));
            if (is_valid_line(lines, line))
            {
                add(lines, line, new_stop, distance);
            }
        }
        else if (command == "REMOVE" and parts.size() >= 2)
        {
            std::string stop_to_remove = parts.at(1);
            if (is_valid_stop(lines, stop_to_remove))
            {
                remove(lines, stop_to_remove);
            }
        }
        else if(command == "QUIT")
        {
            return EXIT_SUCCESS;
        }
        else
        {
            std::cout << INVALID_INPUT << std::endl;
        }
    }
}
