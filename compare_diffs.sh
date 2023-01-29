i=1

while true; do
	./corewar -dump $i resources_42/vm_champs/champs/ex.cor
	./resources_42/vm_champs/corewar -d $i resources_42/vm_champs/champs/ex.cor > 42.txt
	tail -n +3 42.txt > 42edited.txt
	rm 42.txt
	echo diff = $(diff -w -B mycore.txt 42edited.txt)
	if [[ $(diff -w -B mycore.txt 42edited.txt) != "" ]]
	then
		echo "diffs differ, dump = $i"
		break
	else
		let "i=i+1"
		echo $i
	fi
done