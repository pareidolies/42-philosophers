# 42-philosophers

Ce projet propose une solution au fameux problème du "dîner des philosophes" énoncé par Edsger Dijkstra en 1965. Pour vous familiariser avec ce sujet : https://en.wikipedia.org/wiki/Dining_philosophers_problem

Usage : make && ./philo [NBR_PHILO] [TIME_TO_DIE] [TIME_TO_EAT] [TIME_TO_SLEEP]

![Enregistrement de l’écran 2022-09-12 à 14 59 30](https://user-images.githubusercontent.com/96736158/189660499-4d400647-4ffc-4176-852e-7341cf104a80.gif)

# La stratégie

Comme nous le propose l'énoncé pour la partie obligatoire, chaque philosophe est représenté par un thread, et chaque fourchette est protégée par un mutex.

Ici, la solution mise en place est très simple : nous faisons partir les philosophes dont l'identifiant est impair un peu après les autres. Ainsi, les philosophes dont l'identifiant est pair vont saisir une fourchette puis l'autre et commencer à manger, et les philosophes dont les identifiants sont impairs vont patienter un peu, puis attendre que les fourchettes soient libérées pour les saisir et ainsi de suite.

# Mes conseils pour le projet

Pour analyser les éventuels problèmes de votre projet pendant que vous testez toutes les idées qui vous passent par la tête, voici les outils utiles : valgrind bien sûr, mais surtout valgrind --tool=helgrind --tool=drd pour repérer les deadlocks, lock order inversion et autres joyeusetés ! N'hésitez pas également à ouvrir un autre terminal et à faire un top pour analyser le %CPU utilisé pendant l'exécution de votre programme.

Si vous êtes à court d'idées d'optimisation ou bien que vous ne parvenez pas à résoudre un problème, voici quelques conseils qui pourront peut-être vous aider :

* Pour éviter les problèmes de "lock order violated", établissez un ordre de saisie des fourchettes différent selon si le philosophe a un identifiant pair ou impair (fourchette droite puis gauche pour les uns, et l'inverse pour les autres).
* Pour être certain que tous vos philosophes partent bien en même temps (cela se joue à la milliseconde près pour avoir les bons timestamps) qu'importe le temps mis pour créer le thread pour chacun, je vous conseille d'établir un "start time" (dans mon cas le gettimeofday + 2 * nbr_philos) et d'écrire une fonction wait_all_philos grâce à laquelle tous vos philos vont attendre se start_time avant de commencer leur routine.
* Pour éviter que votre programme continue à tourner après la mort d'un philosophe dans les cas de très grand time_to_eat ou time_to_sleep, il peut-être judicieux de vérifier dans la fonction my_usleep que vous aurez écrite si un philosophe est mort (toutes les demie-secondes par exemple) et de quitter la boucle si cela est le cas.
* Pour éviter d'accéder à vos informations partagées trop souvent (ce qui sollicite les mutexs et donc crée des files d'attente), je vous conseille de mettre le plus d'information possible dans les structures de chaque philosophe. Cela fait des structures assez chargées en informations avec des redites (entre t_philo et t_data dans mon cas) mais au moins cela évite d'aller chercher les informations dans data trop souvent.
* Concernant la fonction de "surveillance" qui vérifie si les philosophes ont suffisamment mangé ou bien si un philosophe est mort entretemps, n'oubliez pas de rajouter un usleep, sinon elle va tourner en permanence et les performances de votre programme vont en pâtir !
* Pour éviter de trop m'emmêler les pinceaux, j'ai préféré n'utiliser qu'un seul mutex en plus des mutexs qui protègent les fourchettes. En effet, cet unique mutex permet à la fois de protéger l'affichage (pour éviter que les timestamps et actions des philosophes ne s'affichent de façon mélangée sur le terminal) et de protéger l'accès aux informations communes, sachant qu'avant d'afficher une action des philosophes, je vérifie toujours si un philosophe est mort entretemps ou bien si les philosophes ont suffisamment mangé, pour que le dernier message affiché soit toujours celui de la fin du programme.
* pthreadjoin

# Quelques tests utiles



Notions : partage de ressources, thread, mutex, process, sémaphore

Note obtenue : 125/100
