#include "CacheSim.h"
// WRITE NO ALLOCATE -> sense assignacio 
// si és MISS d'escriptura NO porto de MP a MC

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */
struct linea {
	unsigned int v;
	unsigned int tag;
};

struct linea Cache[128];
unsigned int num_miss = 0;
unsigned int num_hit = 0;


/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al comen�ar cada un dels tests.
 * */
void init_cache ()
{
	/* Escriu aqui el teu codi */
	for (int i = 0; i < 128; ++i) Cache[i].v = 0;
}

/* La rutina reference es cridada per cada referencia a simular */ 
void reference (unsigned int address, unsigned int LE)
{
	unsigned int byte; // 5 menys pes
	unsigned int bloque_m; // 27 mes pes
	unsigned int linea_mc; // 7 menys pes del bloc
	unsigned int tag; // 20 mes pes del bloc
	unsigned int miss;
	unsigned int lec_mp; // bool
	unsigned int mida_lec_mp;
	unsigned int esc_mp; // bool
	unsigned int mida_esc_mp;
	unsigned int replacement; // bool
	unsigned int tag_out;

	/* Escriu aqui el teu codi */
	byte = address%32;
	bloque_m = address/32;
	linea_mc = bloque_m%128;
	tag = bloque_m/128;

	if (LE == lectura) {
		// HIT
		if (Cache[linea_mc].v == 1 && Cache[linea_mc].tag == tag) {
			lec_mp = 0;
			mida_lec_mp = 0;
			replacement = 0;
			miss = 0;
			++num_hit;
		}
		else { // MISS
			lec_mp = 1;
			mida_lec_mp = 32;
			miss = 1;
			++num_miss;
			if (Cache[linea_mc].v == 1) { // replacement
				replacement = 1;
				tag_out = Cache[linea_mc].tag;
			}
			else { // estava buit
				replacement = 0;
				Cache[linea_mc].v = 1;
			}
			Cache[linea_mc].tag = tag; // mou el bloc de MP a MC
		}
		esc_mp = 0;
		mida_esc_mp = 0;
	}
	else { // LE == escriptura
		if (Cache[linea_mc].v == 1 && Cache[linea_mc].tag == tag) { // HIT
			// escric a Cache i a MP
			miss = 0;
			++num_hit;
			replacement = 0;

		}
		else { // MISS
			// no em porto el bloc només escric a MP
			miss = 1;
			++num_miss;
		}
		esc_mp = 1;
		mida_esc_mp = 1; // acces a nivell de byte
		lec_mp = 0;
		mida_lec_mp = 0;
	}

	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual
	 * */
	test_and_print (address, LE, byte, bloque_m, linea_mc, tag,
			miss, lec_mp, mida_lec_mp, esc_mp, mida_esc_mp,
			replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */ 
void final ()
{
 	/* Escriu aqui el teu codi */ 
	printf("Numero de MISS: %d\n", num_miss);
	printf("Numero de HIT: %d\n", num_hit);
}
