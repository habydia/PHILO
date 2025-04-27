Objectif 

faire en sorte que tous philos menent leur vie (mange, dort, medite, meurent) dans un temp donné. Simulation s'arrete quand 1 philo meurt

Notions :

Synchronisation de THREADS
Chaque philo est representé par un thread, qui effectue des actions comme penser, manger, dormir.
- THREADS
   - executions simultané
   - variable qui Partage la mm espace memoire que d'autre. Ils tournent en parallele. cad execute leur tache simultanement. on peut lui assigner une fontion à executer.

    pthread_create() : lance le tread et execute la tache
    pthread_join() : attend la fin du tread (l'execution de la tache) avant de continuer le programme

MUTEX
- Verrou uttilisé pour proteger une section critique d'un code.
dans notre cas une action qui ne peut etre executé que par un tread à la fois.
-  pthread_mutex_lock()

Les forks ici les ressources que se partage des threads
- il ya une fork entre chaque philosophe 
- chaque thread à besoin de 2 forks pour manger.

! defis : si les threads prennent simultanement une fourchette du meme cote pour manger, il se bloque. (faire en sorte que si un thrads uttilise une ressource). DEADLOCK

! faire en sorte que tout le monde mange dans le temp impartie 

solutions avec MUTEX pour proteger les ressources.
- si attrape ressources, celui à cote doit attendre.
- bloquer ressources avant que l'attrapé par premier.
- deverrouiller une fois finis.


routine type : 
penser, prendre 2 ressourses(mutex), manger, reposer les fourchettes, dormir.

synchroo de sorte que chaqu'un est le temp de suivre sa ressource avant de die.

threads pour actions simultanemment
- penser
- dormir

thread action critique (protégé), avec ressource partagé.
- manger
  - verrouiller deux fourchette, pthread_mutex_lock()
  - deverrouiller apres manger, pthread_mutex_unlock
