#include <charts_exception.h>

const char* charts_exception::what() const noexcept {
    return "Eccezione nell'esecuzione dell'applicazione Charts.";
}

const char* point_already_present::what() const noexcept {
    return "Si sta tentando di inserire un punto già presente.";
}

const char* point_not_found::what() const noexcept {
    return "Un punto richiesto non è stato trovato.";
}

const char* chart_not_valid::what() const noexcept {
    return "Scegliere un tipo di grafico valido.";
}
