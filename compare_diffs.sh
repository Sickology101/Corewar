i=1

while true; do
	./corewar -dump $i resources_42/vm_champs/slider2.cor
	./resources_42/vm_champs/corewar -d $i resources_42/vm_champs/slider2.cor > 42.txt
	tail -n +3 42.txt > 42corewar.txt
	rm 42.txt
	if [[ $(diff -w -B ourcorewar.txt 42corewar.txt) != "" ]]
	then
		echo "diffs differ, dump = $i"
		echo diff = $(diff -w -B ourcorewar.txt 42corewar.txt)
		break
	else
		let "i=i+1"
		echo $i
	fi
done