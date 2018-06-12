DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
for (( i = 0; i < $1; i++ )); do
  python $DIR/genNum.py 200 2 > inPoints.txt
  bin/runner 'inPoints.txt'
  python $DIR/visual.py
done
