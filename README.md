# Détourage d'image

Somimg est un programme d'édition d'image.
L'application est basée sur Qt, C++ et utilise un réseau de neurones artificiels sous forme de SOM (self organizing maps).
Somimg permet de segmenter des images (les images doivent être au format PNG) et essayer de supprimer l'arrière-plan de celle-ci.

### Installation

```sh
$ install
```

### Exécution du programme

Exécuter le programme avec une interface graphique:
```sh
$ somimg
```
Exécuter le programme en ligne de commande:

```sh
$ somimg -T </path/To/image_to_process.png> </path/To/processed_image.png> [OPTION]
```
##### Options en ligne de commande

Rendre l'arrière-plan transparent (ou pas) [défaut=non]:
```sh
-t {0|1}
```
Choisir le nombre de couleurs pour la segmentation [défaut=2]:
```sh
-n NOMBRE
```
Utiliser un post traitement (ou pas) [défaut=oui]
```sh
-p {0|1}
```
Choisir l'espace de couleur utilisé par l'algorithme SOM [défaut=RGB]:
```sh
{HSV|HSL|HSVRGB|HSVL}
```
### Capture d'écrans
![Somimg screenshot 1](https://i.imgur.com/vWKZL7B.png)

![Somimg screenshot 2](https://imgur.com/XPpe26q.png)

![Somimg screenshot 3](https://imgur.com/4qvb1Vs.png)

## License

Le projet est sous licence gpl-3.0 - voir le fichier [LICENSE](LICENSE) pour plus de détails.
