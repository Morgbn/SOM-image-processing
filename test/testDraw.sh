gcc som.c -o cx -lm
echo draw$1.png
python img-to-points.py draw$1.png > draw.txt
cx 'draw.txt'
