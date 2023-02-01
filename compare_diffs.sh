# So, this script tests both programs with -dump=0
# Then it compares the output and if it's the same then 
# it sets i += INCREMENT, which you can change,  if you want, and tests again
# If output is different then it tests with 50
# If if passes with 50, tests with 75
# If 75 fails, then it tests 67 and so on, until it finds 2 consecutive
# numbers, the smaller one should pass the test and the larger one should fail it

PASS=0
NOT_PASS=0
i=0
FILENAME="ex"
INCREMENT=1000

while true; do
	echo "testing with i = $i"
	echo "NOT_PASS = $NOT_PASS \tPASS = $PASS"
	./corewar -dump $i resources_42/vm_champs/$FILENAME.cor > /dev/null 2>&1
	./resources_42/vm_champs/corewar -d $i resources_42/vm_champs/$FILENAME.cor > 42.txt
	tail -n +3 42.txt > 42corewar.txt
	rm 42.txt
	if [[ $(diff ourcorewar.txt 42corewar.txt) != "" ]]
	then
		echo "$i Didn't pass\n"
		((NOT_PASS = i))
		((i= PASS + (NOT_PASS - PASS) / 2))
	else
		echo "$i passed\n"
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
		echo "CHECK THAT FIRST DIFF IS EMPTY, AND SECOND IS NOT"
		echo "OTHERWISE THE SCRIPT GAVE FALSE RESULT\n"

		./corewar -dump $PASS resources_42/vm_champs/$FILENAME.cor > ourcorewar_log.txt
		./resources_42/vm_champs/corewar -d $PASS resources_42/vm_champs/$FILENAME.cor > 42.txt
		tail -n +3 42.txt > 42corewar.txt
		rm 42.txt
		echo diff = $(diff ourcorewar.txt 42corewar.txt)

		./corewar -dump $NOT_PASS resources_42/vm_champs/$FILENAME.cor > ourcorewar_log.txt
		./resources_42/vm_champs/corewar -d $NOT_PASS resources_42/vm_champs/$FILENAME.cor > 42.txt
		tail -n +3 42.txt > 42corewar.txt
		rm 42.txt
		echo diff = $(diff ourcorewar.txt 42corewar.txt)

		echo "\nPASS = $PASS\tNOT_PASS = $NOT_PASS"
		echo "diff occured at -dump = $NOT_PASS"
		break
	fi
done