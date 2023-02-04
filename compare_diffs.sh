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
FILENAME="jumper"
INCREMENT=5
run_games() {
	# ./vbrazh/corewar -dump $1 resources_42/vm_champs/$FILENAME.cor > ourcorewar1.txt
	# tail -n +3 ourcorewar1.txt > ourcorewar.txt
	# rm ourcorewar1.txt
	./corewar -dump $1 resources_42/valid_files/byte_code/$FILENAME.cor > ourcorewar_log.txt

	./resources_42/vm_champs/corewar -d $1 resources_42/valid_files/byte_code/$FILENAME.cor > 42.txt
	tail -n +3 42.txt > 42corewar.txt
	rm 42.txt
}

while true; do
	echo "testing with i = $i"
	echo "NOT_PASS = $NOT_PASS \tPASS = $PASS"
	run_games "$i"
	if [[ $(diff ourcorewar.txt 42corewar.txt) != "" ]]
	then
		echo "$i Didn't pass\n"
		if ((i == 0))
		then
			break
		fi
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

		run_games "$PASS"
		echo diff 1 = $(diff ourcorewar.txt 42corewar.txt)

		run_games "$NOT_PASS"
		echo diff 2 = $(diff ourcorewar.txt 42corewar.txt)

		echo "\nPASS = $PASS\tNOT_PASS = $NOT_PASS"
		echo "diff occured at -dump = $NOT_PASS"
		break
	fi
done