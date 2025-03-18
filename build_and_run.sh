# прост
set -e

mkdir -p build
cd build

cmake ..
make

# запуск парсера с примером входных данных из файла input.txt
echo "Running parser on ../input.txt"
./expr_parser ../input.txt 