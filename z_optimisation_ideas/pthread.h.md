/!\ Necessite #define _POSIX_C_SOURCE 200809L

Dans un cas comme miniRT, il existe des outils de parallelisme avance: 

	pthread_barrier_t - synchronisation élégante entre threads
	pthread_spinlock_t - locks sans syscall pour sections critiques courtes
	Thread pools avec pthread_cond_t - éviter création/destruction répétée
	Thread-local storage (__thread) - cache par thread sans mutex


1- Barriers
	Plusieurs threads travaillant sur des parties differentes d'un meme travail global necessitent le plus souvent des temps d'execution differents en fonction de la complexite de leur tache.
	Dans le cas d'une generation d'image par exemple une zone unie sera generee plus vite qu'une zone comportant des reflexions. Exemple:

		Thread 0: ████████░░  (50% ciel vide)      → termine en 2s
		Thread 1: ██████░░░░  (30% objets simples) → termine en 3s  
		Thread 2: ███████░░░  (reflets simples)    → termine en 4s
		Thread 3: ██████████  (100% sphères miroir)→ termine en 10s

	
	Le concept de "barriere" permet de garantir la restitution synchrone du travail attendu.
	
	Le but est de faire attendre les premiers arrives jusqu'a ce que le dernier ait fini son travail:

		Thread 1: ████████░░ (arrive à la barrière, attend)
		Thread 2: ███████░░░ (arrive, attend)
		Thread 3: ██████████ (arrive, attend)
		Thread 4: █████████░ (arrive en dernier)
				↓
				BOUM ! Tous repartent en même temps
		Thread 1: ░░░░░░░░░░████████
		Thread 2: ░░░░░░░░░░███████
		Thread 3: ░░░░░░░░░░██████████
		Thread 4: ░░░░░░░░░░█████████

	Cette fonctionnalite fait partie du header pthread.h, et est disponible via l'API suivante:

	```c
		pthread_barrier_t	barrier;

		int pthread_barrier_init(pthread_barrier_t *barrier, const pthread_barrierattr_t *attr, unsigned count);
		int pthread_barrier_destroy(pthread_barrier_t *barrier);
		int pthread_barrier_wait(pthread_barrier_t *barrier);

		/* Attributs de barrière */
		int pthread_barrierattr_init(pthread_barrierattr_t *attr);
		int pthread_barrierattr_destroy(pthread_barrierattr_t *attr);
		int pthread_barrierattr_setpshared(pthread_barrierattr_t *attr, int pshared);
		int pthread_barrierattr_getpshared(const pthread_barrierattr_t *attr, int *pshared);


	```

	En pratique:
		- La barriere ne connait pas les threads participant, seulement le count a attendre
		- Les threads participant s'idientifient eux-memes via pthread_barrier_wait

		pthread_barrier_wait

2- Mecanismes de lock (mutex / spinlock)

	Afin d'acquerir une ressource protegee, 3 strategies existent:
		- bloquer jusqu'a acquisition								-> mutex
		- essayer d'acquerir une fois et passer a autre chose 		-> mutex
		- essayer d'acquerir en continu								-> spinlock

	L'element de departage entre ces deux outils est la duree de l'action a mener:
		- Si l'action est courte, le spinlock l'emporte
		- Si l'action est longue, le mutex l'emporte

	2.1- Mutex

		Le principe du mutex est d'essayer d'acquerir une ressource de deux manieres:

			- En bloquant sur le mutex jusqu'a liberation (lock -> cout d'endormissement et de reveil)
			- En essayant une fois et en faisant un aure travail sinon (trylock)

		Le schema de fonctionnement d'un mutex est le suivant:
		
			Thread essaie mutex_lock() sur lock occupé
			↓
			Syscall (entre en kernel) - ~500 cycles
			↓
			Kernel suspend le thread - ~1000-5000 cycles
			↓
			Changement de contexte complet :
			- Sauvegarde registres
			- Flush TLB
			- Change table pages mémoire
			↓
			... lock libéré ailleurs ...
			↓
			Kernel réveille le thread - ~1000-5000 cycles
			↓
			Changement de contexte inverse
			↓
			Thread reprend - ~500 cycles
			---------------------------------
			TOTAL : 3000-10000+ cycles


			Les mutex sont disponibles via l'API suivante:

			```c
				pthread_mutex_t	mutex;

				int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
				int pthread_mutex_destroy(pthread_mutex_t *mutex);
				int pthread_mutex_lock(pthread_mutex_t *mutex);
				int pthread_mutex_trylock(pthread_mutex_t *mutex);
				int pthread_mutex_unlock(pthread_mutex_t *mutex);

				/* Attributs de mutex */
				int pthread_mutexattr_init(pthread_mutexattr_t *attr);
				int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
				int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);
				int pthread_mutexattr_gettype(const pthread_mutexattr_t *attr, int *type);

			```
			

	2.1- Spinlock

		Le principe du spinlock est d'essayer d'acquerir en continu la ressource, sans sommeil. 
		Le cout CPU devient alors important mais mais, dans le cas de temps d'attente courts, il compense le cout d'endormissement et de reveil des threads.

		Exemple :

		```c
			for (int i = 0; i < 1000000; i++) {
				pthread_mutex_lock(&mutex);
				counter++;						// action simple
				pthread_mutex_unlock(&mutex);
			}

			// Coût par itération : ~6000 cycles (syscalls + contexte)
			// Total : 6 milliards de cycles
			// Temps : ~2 secondes sur CPU 3 GHz
		```

		```c
			for (int i = 0; i < 1000000; i++) {
				pthread_spin_lock(&spinlock);
				counter++;
				pthread_spin_unlock(&spinlock);
			}

			// Coût par itération : ~50 cycles (attente active courte)
			// Total : 50 millions de cycles
			// Temps : ~0.015 secondes
		```

		Les spinlock sont disponibles via l'API suivante:

		```c
			pthread_spinlock_t spinlock;

			int pthread_spin_init(pthread_spinlock_t *lock, int pshared);
			int pthread_spin_destroy(pthread_spinlock_t *lock);
			int pthread_spin_lock(pthread_spinlock_t *lock);
			int pthread_spin_trylock(pthread_spinlock_t *lock);
			int pthread_spin_unlock(pthread_spinlock_t *lock);

		```
		

	2.3- mutex vs spinlock

		Dans un projet comme miniRT, les mutex devraient etre plus interessants car, meme s'ils consomment beaucoup de cycles, le travail a effectuer pour du ray tracing est long. Des spinlocks devraient saturer le processeur pour rien.







		
