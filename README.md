# cbash
mise à disposition des fonctionnalités du bash en langage c ( inspirateur: Christophe Blaess )

Cbash est destiné à tous les utilisateurs de linux qui ont une sainte horreur du bash.

Il connaîtra des améliorations ( éditeur, récursivité, bdd, barre de progression, exécution d’un code partiel à des fins de vérification ). Sa forme actuelle est archaïque.

Cbash permet l’exécution des programmes/routines systèmes ( et des programmes installés ) les uns à la suite des autres. Je qualifie ces programmes de modules.

En utilisant une procédure permettant de rediriger la sortie ET l’entrée d’un module fils, on peut le piper avec le fils suivant jusqu’à exécution de la chaîne des modules que j’appelle string.

Ce string de modules est alors exécuté et le résultat de l’opération est stocké pour un usage prochain dans l’un des strings suivants jusqu’à obtention du résultat escompté par le programme ainsi édité.

Certaines fonctionnalités ont dû être intégrées au programme :

* La fonction cd fait en sorte que ce soit le programme père qui change de répertoire.
* La fonction concat concatène des strings ( au sens du langage c ) en vu d’être traitées par un module tel que sed pour insérer des variables au seins des scripts de l’éditeur.
* La fonction file permet l’écriture dans un fichier de résultats de strings ( au sens de cbash ).

L’usage en est simple mais rébarbatif pour le moment. Cela dit, c’est  un hommage à Dennis Ritchie et à son langage sans lequel linux ne serait pas.

C’est de plus, l’application pure et simple d’un algorithme trouvé dans le bouquin de Christophe Blaess ( __programmation système sous linux__ ) dont j’ai saisi les capacités et compte bien instituer l’importance.

Cbash est livré avec un exemple d'utilisation nommé youtube2mp3.c permettant de télécharger du contenu de playlist youtube, d'en faire des mp3 et d'y injecter les métadonnées. il s'utilise de la manère suivante.
./youtube2mp3 URL_PLAYLIST ARTISTE

Il est nécessaire, pour cet exemple, de disposer de [pup](https://github.com/ericchiang/pup/releases/tag/v0.4.0) et de [youtube-dl](https://github.com/ytdl-org/youtube-dl), ce dernier devant être à jour.

Bonne réception et collaboration.

**AUTEUR
Amaury Benard
gunsailor66@gmail.com**
