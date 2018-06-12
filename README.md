# Détourage d'image

Utilisation de l'algorithme SOM afin de détourer des images automatiquement.

### Installation

```
make
```

### Exécution du programme

```
python test/genNum.py [Nombre de points] [Dimension] > inPoints.txt
bin/runner inPoints.txt
```

### Tests

Visualisation avec pyton (dans include/som.h, ligne 7, mettre #define GNUPLOT 0):

```
make
test/visual.sh [Nombre d'éxection]
```

Test avec des images:

```
make
$ test/testDraw.sh [Numéro du l'image (draw?.png)]
```
