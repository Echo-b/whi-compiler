#/bin/bash
result1=(0 1275 9 4 9 2 9 5 8 1 0 1 4)
result2=(-1 0 135 12 1 0 -4 1 0 1 0 2080 4)
make clean 
make
j=0
for i in $(find ./test_file ../src/inst_out -name \*.out); do
	res=(`./machine "$i"`)
	if [[ ${res[0]} == ${result1[$j]} &&  ${res[1]} == ${result2[$j]} ]]; 
	then
		echo -n "${i}"
	  echo -e "\033[32m OK \033[0m"	
	else
		echo -n "${i}"
		echo -e "\033[31m ERROR \033[0m"	
	fi
	j=`expr $j + 1`
done
