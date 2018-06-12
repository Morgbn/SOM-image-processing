DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
echo draw$1.png
python $DIR/img-to-points.py $DIR/draw$1.png > draw.txt
bin/runner 'draw.txt'
