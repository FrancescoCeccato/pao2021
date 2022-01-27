#include "charts_exception.h"


const char* charts_exception::what() const noexcept {
    return "Eccezione nell'esecuzione dell'applicazione Charts.";
}

point_already_present::point_already_present(float _x, float _y) : x(_x),y(_y){}

const char* point_already_present::what() const noexcept {
    return "Il punto è già presente.";
}

const char* point_not_found::what() const noexcept {
    return "Punto richiesto non trovato.";
}
