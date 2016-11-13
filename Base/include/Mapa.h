
#ifndef MAPA_H_
#define	MAPA_H_

#include "../TiposJuego.h"
#include "../aed2.h"
#include <vector>

using namespace aed2;
using namespace std;

class Mapa {
	public:

	    Mapa();
	    ~Mapa();
	    void AgregarCoord( const Coordenada &c);

	    Conj<Coordenada> Coordenadas() const;

	    bool PosExistente(const Coordenada &c) const;

	    bool HayCamino(const Coordenada &c1, const Coordenada &c2) const;

	    Nat Tam() const;

	private:
    
    	vector<vector<vector<vector<bool> > > > _grilla;
    	Nat _tam;

};

#endif
