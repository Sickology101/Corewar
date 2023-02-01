PASS=0
NOT_PASS=0
i=0
FILENAME="ex"
INCREMENT=1000

while true; do
	./corewar -dump $i resources_42/vm_champs/$FILENAME.cor > ourcorewar_log.txt
	./resources_42/vm_champs/corewar -d $i resources_42/vm_champs/$FILENAME.cor > 42.txt
	tail -n +3 42.txt > 42corewar.txt
	# rm 42.txt
	echo "testing with i = $i"
	echo "NOT_PASS = $NOT_PASS \tPASS = $PASS \n"
	if [[ $(diff -w -B ourcorewar.txt 42corewar.txt) != "" ]]
	then
		((NOT_PASS = i))
		((i= PASS + (NOT_PASS - PASS) / 2))
	else
		((PASS = i))
		if  ((NOT_PASS != 0))
		then
			((i= PASS + (NOT_PASS - PASS) / 2))
		else
			((i=i+INCREMENT))
		fi
	fi
	if (((NOT_PASS - PASS) == 1));
	then
		echo "diff occured at -dump = $NOT_PASS"
		echo "PASS = $PASS NOT_PASS = $NOT_PASS\n"
		echo diff = $(diff -w -B ourcorewar.txt 42corewar.txt)
		break
	fi
done