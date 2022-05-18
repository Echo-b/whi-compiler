#/bin/bash
result=(12 0)
make clean 
make
j=0
for i in $(find -name \*.out); do
	res=(`./machine "$i"`)
	if [[ ${res[0]} == ${result[$j]} ]]; 
	then
		echo -n "${i}"
	        echo -e "\033[32m OK \033[0m"	
	else
		echo "${i} error"	
	fi
	j=`expr $j + 1`
done
