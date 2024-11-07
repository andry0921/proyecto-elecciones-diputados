#ifndef NODO_H
#define NODO_H

template<class Tipo>
class Nodo {
private:
    Tipo info;
    Nodo<Tipo> *sig;
public:
    void AsigInfo(Tipo in);
    Tipo ObtInfo();
    void AsigSig(Nodo<Tipo> *p);
    Nodo<Tipo>* ObtSig();
};

#endif // NODO_H