gcc som.c -o cx -lm

for (( i = 0; i < $1; i++ )); do
  python genNum.py 200 2 > inPoints.txt
  cx 'inPoints.txt'
  python visual.py
done
