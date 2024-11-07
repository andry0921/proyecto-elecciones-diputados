#include "Nodo.h"
#include "../Candidato.h"
#include "../Partido.h"
template<class Tipo>
void Nodo<Tipo>::AsigInfo(Tipo in) {
    info = in;
}

template<class Tipo>
Tipo Nodo<Tipo>::ObtInfo() {
    return info;
}

template<class Tipo>
void Nodo<Tipo>::AsigSig(Nodo<Tipo> *p) {
    sig = p;
}

template<class Tipo>
Nodo<Tipo>* Nodo<Tipo>::ObtSig() {
    return sig;
}

// Explicit instantiation
template class Nodo<std::string>;
template class Nodo<Candidato>;
template class Lista<Partido>;