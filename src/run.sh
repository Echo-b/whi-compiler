make clean 
make
figlet "whi compiler"
outpath="./inst_out/"
pre="t"
post=".out"
star="*"

delname="$outpath$star$post"
rm $delname

for i in $(find ./test_file  -name \*.whi); do
  num=${i:0-6:2}
  outname="$outpath$pre${num}$post"
  touch $outname
	./lexicial "$i" $outname
done
