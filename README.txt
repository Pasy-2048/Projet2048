# Projet2048
Codes source 2048

1): Faites des branches et bossez dedans. Arrètez de poster des fichiers à moitié mergés qui ne marchent pas à la compilation et donnent 3 milliards d'erreurs.. (Sans déconner j'ai bien cru que vous aviez pété grid.c...)
2): Il faut inclure fonctions-sup.c pour compiler hidee et showee. Sinon tout marche.
3): Puisque les prototypes ne sont pas présents dans le .h, certaines fonctions de grid.c ne peuvent pas être utilisées en dehors. Et impossible de les délocaliser; il manquerait la description de la struct grid_s.
4): Le "erreur" c'est juste que git ne permet pas de changer la description qu'on vient de donner, même si on a pas fini. Les deux derniers commits doivent donc s'annuller l'un-l'autre.
5): Oubliez pas git push et git pull pour mettre/prendre en ligne; juste les commits et les checkout c'est pas trop utile.. 


/**********************************************************************************************/
03/05 (PL)

Ajout du CMakefile :

Usage : cmake .
	make

Il faudra surement mettre grid.c sous forme de librairie par la suite...

/**********************************************************************************************/
