/* Luokka: Line
 * ------------
 * Kuvaa yhtä linjaa.
 *
 * Ohjelman kirjoittaja:
 *
 * Nimi: Katariina Tenhunen
 * Opiskelijanumero: H299784
 * Käyttäjätunnus: kgkate
 * E-Mail: katariina.tenhunen@tuni.fi
 *
 * */

#ifndef LINE_HH
#define LINE_HH

#include <string>
#include <vector>
#include <utility>
#include <map>

class Line
{
public:
    Line(const std::string name);
    
    bool has_stop(std::string stop) const;
    bool has_distance(double distance) const;
    bool add_stop(std::string stopname, double distance, bool ckeck_order);
    bool remove_stop(std::string stopname);
    void print_stops() const;
    std::vector<std::string> get_stops() const;
    double distance(std::string stop1, std::string stop2) const;
private:
    std::pair<std::string, double> get_stop_information(std::string stop) const;

    std::string name_;
    std::vector<std::pair<std::string, double>> stops_;
};

#endif // LINE_HH
