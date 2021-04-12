# !/bin/bash
# Compile and create executable
gcc src/*.c -o rede
mkdir -p saida
printf "\033[93mStartint script\033[0m\n"
time ./rede entrada/N10_S3_C3_M3.txt >saida/1.txt
echo "time ./rede entrada/N10_S3_C3_M3.txt >saida/1.txt"
time ./rede entrada/N100_S20_C30_M5.txt >saida/2.txt
echo "time ./rede entrada/N100_S20_C30_M5.txt >saida/2.txt"
time ./rede entrada/N1000_S50_C300_M10.txt >saida/3.txt
echo "time ./rede entrada/N1000_S50_C300_M10.txt >saida/3.txt"
time ./rede entrada/N10000_S50_C300_M10.txt >saida/4.txt
echo "time ./rede entrada/N10000_S50_C300_M10.txt >saida/4.txt"
printf "\033[92mEnd Test\033[0m\n"
