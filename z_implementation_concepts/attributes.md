1- hot / cold
	Le processeur charge son cache d'instructions ligne apres ligne (generalement 64o).

	Sans optimisation, des fonctions de rarete differentes sont chargees de facon contigues, ce qui oblige le processeur a utiliser davantage de cycles pour effectuer son travail.

	[fonction_hot_A] [handle_error] [fonction_hot_B] [panic] [fonction_hot_C]
	       ↑               ↑                ↑             ↑            ↑
		souvent          RARE           souvent          RARE        souvent

	cold
		indique au compilateur qu'une fonction a peu de chances d'etre appelee. Il privilegie un code compact plutot que rapide (moins de deroulage de boucles, moins d'inlining agressif...), et deplace les fonctions dans une section texte dediee.

		```c
		// Gestion d'erreurs
		__attribute__((cold))
		void handle_error(const char* msg) {
			perror(msg);
			// traitement d'erreur complexe...
		}

		// Initialisation rare
		__attribute__((cold))
		void initialize_subsystem(void) {
			// code d'init complexe, appelé une seule fois
		}

		// Assertions
		__attribute__((cold))
		void assertion_failed(const char* expr, const char* file, int line) {
			fprintf(stderr, "Assertion failed: %s at %s:%d\n", expr, file, line);
			abort();
		}
		```
		
	hot
		fait exactement l'inverse. A reserver a des sections de code executees des millions de fois par seconde

		```c
		__attribute__((hot))
		void matrix_multiply_kernel(float* A, float* B, float* C, int n) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					float sum = 0.0f;
					for (int k = 0; k < n; k++) {
						sum += A[i*n + k] * B[k*n + j];
					}
					C[i*n + j] = sum;
				}
			}
		}

		// Appelée des millions de fois par seconde
		__attribute__((hot))
		inline float fast_distance(float x1, float y1, float x2, float y2) {
			float dx = x2 - x1;
			float dy = y2 - y1;
			return sqrtf(dx*dx + dy*dy);
		}

		// Comparateur appelé des millions de fois par qsort
		__attribute__((hot))
		int compare_ints(const void* a, const void* b) {
			return (*(int*)a - *(int*)b);
		}

		// Dans un moteur de jeu : 60 fois par seconde
		__attribute__((hot))
		void update_physics(GameState* state, float dt) {
			// simulations physiques...
		}
		```

2- always_inline
	Ordonne au compilateur d'inline la fonctions, tandis que le specifieur inline seul n'est qu'une suggestion. Avec cet ordre, si le compilateur ne peut pas inliner, il renverra une erreur (par exemple une fonction recursive devient alors infinie).
	C'est a reserver a de petites fonctions. Le code peut perdre en efficacite si mal employe (cache d'instructions sature par exemple).

	Ce n'est en revanche pas garanti pour des pointeurs de fonctions :

	```c
	__attribute__((always_inline))
	inline void func() { /* ... */ }

	void (*ptr)() = func;
	ptr();  // Peut ne PAS être inliné (comportement indéfini)
	```

	Les usages toleres sont les suivants :
		- Wrappers triviaux (1-3 lignes)
		- Code cryptographique sensible au timing
		- Primitives atomiques/barrières mémoire
		- Performance mesurée et prouvée critique

	Les mauvais usages :
		- Fonctions > 10 lignes
		- "Ça devrait être plus rapide" (sans preuve)
		- Partout "par précaution"
		- Fonctions appelées depuis peu d'endroits (le compilateur inline déjà)

	Astuce pour tester si c'est necessaire : 

	```sh
	# Compile sans always_inline
	clang -O2 -S code.c -o without.s

	# Compile avec always_inline  
	clang -O2 -S code_with.c -o with.s

	# Compare
	diff without.s with.s

	```

	```c
	// Fonctions de sécurité critiques
	// DOIT être inliné pour éviter les fuites par timing
	__attribute__((always_inline))
	inline int constant_time_compare(const char* a, const char* b, size_t len) {
		volatile unsigned char result = 0;
		for (size_t i = 0; i < len; i++) {
			result |= a[i] ^ b[i];
		}
		return result;

	//Barrières mémoire et atomiques
	__attribute__((always_inline))
	inline void memory_barrier() {
		asm volatile("mfence" ::: "memory");

	// Wrappers ultra-minces autour d'intrinsics
	__attribute__((always_inline))
		inline __m128 vector_add(__m128 a, __m128 b) {
		return _mm_add_ps(a, b);
	}

	// Code critique en temps réel
	// Dans un DSP audio : AUCUNE latence tolérée
		__attribute__((always_inline))
		inline float apply_filter_sample(float input, Filter* f) {
			return input * f->coeff[0] + f->state[0];
	}
	```

3- flatten
	inline le corps de la fonction, sans depasser les frontieres de la compilation. 

	```c
	void external_func();

	__attribute__((flatten))
	void my_func() {
		external_func();  // Ne sera PAS inlinée (pas de définition visible)
	}
	```

	Toutes les fonctions doivent etre declarees inline ou static.

	```c
	static inline int multiply(int a, int b) {
		return a * b;
	}

	static inline int add(int a, int b) {
		return a + b;
	}

	static inline int complex_calc(int x, int y) {
		int tmp = multiply(x, 2);
		return add(tmp, y);
	}

	// Sans flatten : complex_calc peut être inliné, mais pas forcément multiply/add
	void process(int* data, size_t n) {
		for (size_t i = 0; i < n; i++) {
			data[i] = complex_calc(data[i], 10);
		}
	}

	// Avec flatten : TOUT est inliné (multiply, add, complex_calc)
	__attribute__((flatten))
	void process_flat(int* data, size_t n) {
		for (size_t i = 0; i < n; i++) {
			data[i] = complex_calc(data[i], 10);
		}
	}
	
	// Code équivalent généré
	void process_flat(int* data, size_t n) {
		for (size_t i = 0; i < n; i++) {
			// Tout est inline, pas d'appels
			int tmp = data[i] * 2;
			data[i] = tmp + 10;
		}
	}

		```

	Interaction avec les niveaux d'optimisation
	-O0 (debug) :

	flatten est généralement ignoré (comme inline)
	Les fonctions restent des appels séparés pour le debugger

	-O2 / -O3 :

	flatten est respecté
	Peut produire un code très gros si mal utilisé

	-Os (optimiser la taille) :

	flatten peut être partiellement ignoré si ça augmente trop la taille


4- pure
	Indique au compilateur qu'une fonction est deterministe et sans effet de bord :
		- Son retour ne depend que de ses parametres ou de variables globales. 
		- Elle n'ecrit pas en memoire (sauf localement / temporairement) et n'utilise aucun I/O
		- Produit le meme resultat avec les memes arguments
		
	Exemple:

	```c
	__attribute__((pure))
	int square(int x) {
		return x * x;
	}

	void compute() {
		int a = square(5);  // Calcule 25
		int b = square(5);  // Le compilateur peut réutiliser 25 !
		int c = square(5);  // Idem
	}
	```

	Le compilateur utilise le CSE (Common Subexpression Elimination). 
	Conceptuellement, il fait:

	```c
	void compute() {
		int tmp = square(5);  // Un seul appel
		int a = tmp;
		int b = tmp;  // Réutilise le résultat
		int c = tmp;
	}
	```

	Le compilateur est meme capable de fusionner des appels:

	```c
	__attribute__((pure))
	int expensive_calc(int x);

	int process(int n) {
		int a = expensive_calc(n) + 10;
		int b = expensive_calc(n) * 2;   // Réutilise le résultat
		return a + b;
	}
	```
	devient alors

	```c
	int process(int n) {
		int tmp = expensive_calc(n);  // Un seul appel
		int a = tmp + 10;
		int b = tmp * 2;
		return a + b;
	}
	```

	Exemples de fonctions pures:

	```c
	// Calculs mathématiques purs
	__attribute__((pure))
	int abs(int x) {
		return x < 0 ? -x : x;
	}

	__attribute__((pure))
	double hypot(double x, double y) {
		return sqrt(x*x + y*y);
	}

	// Lecture seule de mémoire
	__attribute__((pure))
	int strlen_custom(const char* s) {
		int len = 0;
		while (s[len]) len++;
		return len;
	}

	__attribute__((pure))
	int memcmp_custom(const void* a, const void* b, size_t n) {
		const unsigned char* pa = a;
		const unsigned char* pb = b;
		for (size_t i = 0; i < n; i++) {
			if (pa[i] != pb[i]) return pa[i] - pb[i];
		}
		return 0;
	}

	// Lecture de structure (pas de modification)
	__attribute__((pure))
	int get_age(const Person* p) {
		return p->age;
	}

	```

5- const
	C'est une version de pure plus stricte:
		- Le retour ne depend que des parametres, qui sont des VALEURS et non des POINTEURS
		- Aucune lecture memoire
		- Aucun effet de bord
		- Aucune lecture de variables globales
		- Deterministe : memes arguments, meme resultat, toujours

	Exemples:

	```c
	// Calculs arithmétiques purs
	__attribute__((const))
	int add(int a, int b) {
		return a + b;
	}

	__attribute__((const))
	int square(int x) {
		return x * x;
	}

	__attribute__((const))
	int max(int a, int b) {
		return a > b ? a : b;
	}

	// Opérations bit-à-bit
	__attribute__((const))
	unsigned int reverse_bits(unsigned int x) {
		unsigned int result = 0;
		for (int i = 0; i < 32; i++) {
			result = (result << 1) | (x & 1);
			x >>= 1;
		}
		return result;
	}

	// Calculs mathématiques complexes (sans appels externes)
	__attribute__((const))
	int factorial_iterative(int n) {
		int result = 1;
		for (int i = 2; i <= n; i++) {
			result *= i;
		}
		return result;
	}

	// Opérations logiques
	__attribute__((const))
	int is_power_of_two(unsigned int x) {
		return (x != 0) && ((x & (x - 1)) == 0);
	}

	```

	Pour bien preciser la difference avec pure, par exemple la fonction suivante: 

	```c
	// Lit de la mémoire via pointeur
	__attribute__((const))  // FAUX !
	int strlen_bad(const char* s) {
		int len = 0;
		while (s[len]) len++;  // Lit s[0], s[1], etc.
		return len;
	}
	
	// Correct : __attribute__((pure))
	```


declarer des variables de la sorte :
const int a = f_int(arg1, arg2, ...);