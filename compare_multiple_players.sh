PASS=0
NOT_PASS=0
i=0
FILE_ID=-1
FILE_NUM=0
FILE_DIR=( resources_42/valid_files/byte_code/*)
OUR_WAR="./corewar"
SCHOOL_WAR="./resources_42/vm_champs/corewar"
INCREMENT=5000
GREEN='\033[32m'
NOCOLOR='\033[0m'
run_games() {
	# ./vbrazh/corewar -dump $1 $FILE > ourcorewar1.txt
	# tail -n +11 ourcorewar1.txt > ourcorewar2.txt
	# rm ourcorewar1.txt
	echo "Commands, used to run:"
	echo "$OUR_WAR -dump $1 ${FILE[@]} > ourcorewar_log.txt"
	$OUR_WAR -dump $1 ${FILE[@]} > ourcorewar_log.txt

	echo "$SCHOOL_WAR -d $1 ${FILE[@]} > 42.txt"
	$SCHOOL_WAR -d $1 ${FILE[@]} > 42.txt
	tail -n +4 42.txt > 42corewar.txt
	rm 42.txt
}

print_chosen() {
	x=0
	echo "${GREEN} Currently chosen files: ${NOCOLOR}"
	while ((x < ARGS_AMOUNT))
	do
		echo "${FILE[$x]}, id = ${FILE_ID_ARR[$x]} "
		((x += 1))
	done
	echo "\n"
}


choose_file() {

	if ((FILE_NUM > 3))
	then
		echo "Max amount of players has been chosen"
		sleep "1"
		return
	fi

	FILE[$FILE_NUM]=${FILE_DIR[FILE_ID]}
	echo "Choose player $FILE_NUM"
	echo "file_id = $FILE_ID"
	echo "${FILE[FILE_NUM]}"

	read -n1 -s -r -p $'\n' key

	case "$key" in
	$'[' )
		((FILE_ID -= 1))
		FILE_ID_ARR[$FILE_NUM]=$FILE_ID
		choose_file ""
		;;
	$']' )
		((FILE_ID += 1))
		FILE_ID_ARR[$FILE_NUM]=$FILE_ID
		choose_file ""
		;;
	$'\e' )
		((FILE_ID = -1))
		exit 1
		;;
	$yes )
		if ((FILE_ID < 0))
		then
			echo "file_id can't be negative"
		else
			((FILE_ID = -1))
			((FILE_NUM += 1))
			((ARGS_AMOUNT += 1))
		fi
		print_chosen""
		choose_file""
		;;
	$'r' )
		if ((FILE_NUM < 1))
		then
			echo "Choose at least one player"
			((FILE_ID = -1))
			choose_file""
		else
			return
		fi
		;;
	* )
		((FILE_ID = -1))
		choose_file ""
		;;
	esac
}

ARGS_AMOUNT=$#
if ((ARGS_AMOUNT >= 1)); then
	for j in "$@"; do
		echo "$j"
		FILE[$FILE_NUM]=${FILE_DIR[j]}
		FILE_ID_ARR[$FILE_NUM]=$j
		((FILE_NUM += 1))
	done
else
	echo "\tPress [ to choose previous file"
	echo "\tPress ] to choose next file"
	echo "\tESC to exit"
	echo "\tPress enter to choose file\n"
	echo "\tPress 'r' to confirm you've chosen all players\n"
	ARGS_AMOUNT=0
	choose_file ""
fi

print_chosen""
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
		echo "diff occured at -dump = $NOT_PASS\n"
		break
	fi
done

echo "Files used:"
print_chosen ""