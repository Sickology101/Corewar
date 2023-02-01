low=0
high=0
i=0
FILENAME="ex"

while true; do
	./corewar -dump $i resources_42/vm_champs/$FILENAME.cor
	./resources_42/vm_champs/corewar -d $i resources_42/vm_champs/$FILENAME.cor > 42.txt
	tail -n +3 42.txt > 42corewar.txt
	# rm 42.txt
	echo "testing with i = $i"
	echo "high = $high low = $low"
	if [[ $(diff -w -B ourcorewar.txt 42corewar.txt) != "" ]]
	then
		let "high=i"
		echo "diffs differ, dump = $i"
		((i=low + (high-low)/2))
		echo "high = $high low = $low"
		echo "setting i to $i"
	else
		((low=i))
		if  ((high != 0))
		then
			((i=low + (high-low)/2))
		else
			((i=i+50))
		fi
	fi
	if (((high - low) == 1));
	then
		echo "diff occured at -dump = $high"
		echo "low=$low high=$high"
		echo diff = $(diff -w -B ourcorewar.txt 42corewar.txt)
		break
	fi
done