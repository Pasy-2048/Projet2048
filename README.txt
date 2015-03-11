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
03/11 (AR)

Nous avons un problème.
J'ai besoin dans les fonctions pour la stratégie avancée du nombre de cases libres dans la grille.
Une solution 'évidente' est d'appeler get_free_tiles(); mais elle n'est présente que dans grid.c, et n'as pas son prototype dans grid.h.
Dans ce cas me direz-vous, pourquoi ne pas déplacer get_free_tiles HORS de grid.c? La réponse est simple; je ne peut pas.
get_free_tiles() va chercher une donnée membre directement dans un objet s_grid*, il faut donc qu'elle sache la composition d'une telle structure,
composition qui n'est donnée que dans grid.c.
Deux solutions complètes sont réalisables: 
1): Inclure grid.c au lieu de grid.h dans les fichiers nécessitant la fonction get_free_tile()
2): Déplacer la définition de s_grid dans fonctions-sup.h. grid.c deviendrait définitivement dépendant de fonctions-sup.h.

'Il faudra surement mettre grid.c sous forme de librairie par la suite...'
Il faut simplement fournir les fichier nécessaires à l'établissement d'une libraire. Rien ne demande à ce qu'on la monte nous-mêmes.