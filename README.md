Minestorm
Jarod Sengkeo

description du jeu:
Le joueur controle un vaisseau avec les touches R, D, G et tirent sur les ennemies avec F. Deux grands ennemies apparaissent par niveau et ils se divisent pour donner 14 ennemies au total par niveau.
Il y a plusieurs type d'ennemi.
Le joueur a 3 vies.
Le joueur peut mettre le jeu en pause avec P.

Menu:
- 1 joueur (F)
- 2 joueurs (K)
- quitter le jeu (ESC)

Menu pause:
- reprendre le jeu (P)
- retour au menu principal (ENTREE)

Joueur 1: mode 1 joueur ou 2 joueur
- avancer (R)
- tourner (D, G)
- tirer (F)
- se teleporter (E, T)

Joueur 2: mode 2 joueur
- avancer (I)
- tourner (J, L)
- tirer (K)
- se teleporter (U, O)

boites a outils:
- circle : mycircle.hpp
- concave polygon : myconcavepolygon.hpp
- convex polygon : myconvexpolygon.hpp
- range : myrange.hpp
- rectangle : myrectangle.hpp
- referential : myreferential2.hpp
- vector : myvector2.hpp

methodes d'application du modele dynamique newtonien:
- ficher : player.cpp
- methode : move()
- ligne : 149

methode de gestion du drift:
- ficher : player.cpp
- methode : update()
- ligne : 241

methodes de changement de referentiel:
- ficher : myreferential2.cpp
- methodes : posLocalGlobal()
			 posGlobalLocal()
			 vectorLocalGlobal()
			 vectorGlobalLocal()
- ligne : 12

methodes SAT de detection de collision:
- ficher : collisiondetection.hpp
- methodes : cPlayerEnemy()
			 cPlayerPlayer()
			 cBulletEnemy()
			 cFireballPlayer()
- ligne : 34

methodes mathematiques:
- fichier math.hpp

Bugs:
- mode 2 joueurs:
	le jeu a tendance a planter lorsque le joueur 1 meurt (perd ses 3 vies).

Reste a faire:
- liberer la memoire (pour les polygones concaves des entites).