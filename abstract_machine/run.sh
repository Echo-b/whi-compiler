#/bin/bash
# result1=(0 5050 9 4 9 2 9 5 8 -2 0 6 4)
result1=(4 4 0 -2 2 5050 0 9 6 9 5 8 9)

# result2=(-1 0 135 12 1 0 7 1 0 -3 0 1 4)
result2=(4 12 0 -3 0 0 -1 135 1 1 1 0 7)
make clean 
make
for i in $(find ./test_file ../src/inst_out -name \*.out); do
  index=${i:0-6:2}
	if [ "$index" -lt "10" ];then
		index=${index:0-1:1}
  fi
	index=`expr $index - 1`
	res=(`./machine "$i"`)
	if [[ ${res[0]} == ${result1[$index]} &&  ${res[1]} == ${result2[$index]} ]]; 
	then
		echo -n "${i}"
	  echo -e "\033[32m OK \033[0m"	
	else
		echo -n "${i}"
		echo -e "\033[31m ERROR \033[0m"	
	fi
done
