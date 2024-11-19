# **Laying Gass - Documentation Utilisateur**

## **Introduction**

Bienvenue dans **Laying Gass**, un jeu stratégique où les joueurs placent des tuiles sur un plateau pour former le plus grand carré possible ou occuper un maximum de cases. Ce jeu, conçu pour 2 à 4 joueurs, se déroule en 9 tours. Le joueur avec le score le plus élevé à la fin de la partie remporte la victoire.

---

## **Installation**

### **Prérequis**
- **Système** : Windows.
- **Environnement** : Console prenant en charge UTF-8.
- **Fichiers nécessaires** :
    - L'exécutable du jeu (`Laying_Gass.exe`).
    - Le fichier `tiles.json` contenant les tuiles.

### **Instructions d'installation**
1. Téléchargez ou clonez le dépôt du jeu :
   ```bash
   git clone https://github.com/username/Laying-Game.git
   ```
2. Déplacez-vous dans le bon répertoire et compiler le :
   ```bash
   cd Laying-Game
    cmake .
    make
   ```
3. Assurez-vous que les fichiers LayingGame.exe et tiles.json sont dans le même dossier.

### Lancer le jeu
1. Ouvrez une console.
2. Accédez au dossier du jeu :
    ```bash
    cd Laying-Game/build
    ```
3. lancer le jeu :
    ```bash
    ./LayingGame
    ```
## Règle du jeu
### Objectif

- Former le plus grand carré possible ou occuper un maximum de cases sur le plateau.
### Déroulement
- Le jeu se joue en 9 tours.
- Chaque joueur commence à un point aléatoire du plateau.
- Les joueurs placent leurs tuiles pour étendre leur territoire.
### Conditions de Placement
-  Une tuile doit toucher une case appartenant au joueur ou son point de départ.
- Une tuile ne peut pas chevaucher celles des autres joueurs.
- Les tuiles doivent rester dans les limites du plateau.
### Calcul des points
- <b>Plus grand carré :</b> Taille du plus grand carré formé par le joueur.
- <b>Total de cases occupées :</b> Nombre total de cases contrôlées par le joueur.

## Guide d'Utilisation

### Démarrage
1. Lancez le jeu en suivant les instructions d'installation. 
2. Entrez le nombre de joueurs (2 à 9).

### Jouer un tour
1. <b>Recevez une tuile :</b>
   - Chaque joueur reçoit une tuile affichée sous forme de grille :
    ```shell
    ##
    #
   ```
2. <b>Effectuez une action :</b>
   - <b>R :</b> Pivoter la tuile de 90°.
   - <b>F :</b> Retourner la tuile horizontalement.
   - <b>P :</b> Placer la tuile (saisir les coordonnées X et Y).
3. <b>Placer la tuile :</b>
   - <b>Exemple d'interaction :</b>
   ```bash
   Player 1 (A), c'est votre tour.
   Forme actuelle de la tuile :
   ##
   #
   Appuyez sur 'R', 'F', ou 'P' : P
   Entrez les coordonnées pour placer la tuile (X Y) : 5 10
   ```
### Résultat du tour
- Résultat du tour
- Le tour passe au joueur suivant.
## Fin du Jeu
### Conditions de Victoire

- À la fin des 9 tours, le jeu calcule les scores pour chaque joueur :
  - La taille du plus grand carré formé.
  - Le total des cases occupées.
- Le joueur ayant le <b>plus grand carré</b> l'emporte.
- En cas d'égalité sur les carrés, le nombre total de cases départage les joueurs.
- Si l'égalité persiste, le jeu est déclaré match nul.
#### Exemple de Résultat
```bash
=== Fin du jeu ===
Player 1 - Plus grand carré : 16 cases, Total de cases occupées : 45
Player 2 - Plus grand carré : 25 cases, Total de cases occupées : 40

Le gagnant est : Player 2 avec un carré de 25 cases et un total de 40 cases !
```

## Dépannage
### Problèmes courants
1. <b>"La tuile dépasse les limites de la grille" :</b>
   - Vérifiez les coordonnées saisies.
   - Assurez-vous que toute la tuile reste dans la grille.
2. <b>"La tuile ne touche pas le territoire ou le point de départ du joueur" :</b>
    - Placez la tuile en contact avec vos cases existantes ou votre point de départ.
### Support
- Si vous rencontrez des problèmes, vérifiez les fichiers requis (tiles.json) et réessayez.

## Contributeurs
Créé par Flumz. 

Pour signaler des bugs ou proposer des améliorations, visitez le dépôt GitHub : \
https://github.com/cestmoiwshflumz/Laying-Gass









