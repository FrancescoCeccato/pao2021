#include <cmath>
#include <algorithm>
#include <polar_chart.h>

polar_chart::polar_chart(const std::string& title) : comparison_chart(1, title) {}

std::pair<int, std::string> polar_chart::find_max() const {
    std::pair<int,std::string> max;
    for(uint i = 0; i<entries.size(); ++i){
        if(*entries[i] > max.first){
            max.first = *entries[i];
            max.second = entries[i]->give_label();
        }
    }
    return max;
}

double polar_chart::mean() const{
    double mean = 0;
    auto size = entries.size();
    if(size != 0){
        for(uint i = 0; i<size; i++)
            mean += entries[i]->give_value(0);
        return mean/size;
    }
    return mean;
}

double polar_chart::give_completion_percentage() const
{
    double sum = 0;
    for(uint i = 0; i<entries.size(); i++)
        sum += *entries[i]/find_max().first;
    return sum/entries.size()*100;
}

int polar_chart::midrange() const {
    if(entries.size() != 0) {
        std::vector<double> v;
        for(uint i = 0; i<entries.size(); i++)
            v.push_back(*entries[i]);
        auto pair = std::minmax_element(v.begin(),v.end());
        return (*(pair.second) - *(pair.first));
    }
    return 0;
}

void polar_chart::insert_entry(uint index, double *val, const std::string &label, bool overwrite) {
    for(uint i = 0; i<values_per_entry; i++)
        val[i] = std::round(val[i]);
    insert_entry_generic(index,val,label,overwrite);
}

std::vector<std::string> polar_chart::chart_info()const{
    std::vector<std::string> info = chart::chart_info();
    info.push_back("La media delle entrate è " + std::to_string(mean()) + "/" + std::to_string(find_max().first));
    info.push_back("La completion percentage del grafico è del: " + std::to_string(give_completion_percentage())+"%");
    info.push_back("L'entrata con il valore piu alto è " + find_max().second + ": " + std::to_string(find_max().first));
    info.push_back("Il range tra l'entrata più alta e quella più bassa del grafico è: " + std::to_string(midrange()));
    return info;
}

std::string polar_chart::description(){
    return "Il polar chart è un grafico che permette di osservare i diversi parametri di un certo dato, paragonandoli fra loro e analizzando quali parametri influiscono di più e quali di meno.";
}

