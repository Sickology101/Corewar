PASS=0
NOT_PASS=0
i=0
FILE_ID=0
FILE_NUM=0
FILE_DIR=( resources_42/valid_files/byte_code/*)
OUR_WAR="./corewar"
SCHOOL_WAR="./resources_42/vm_champs/corewar"
INCREMENT=5000
RED='\033[31m'
GREEN='\033[32m'
YELLOW='\033[33m'
NOCOLOR='\033[0m'
run_games() {
	$OUR_WAR -dump $1 ${FILE[@]} | tail -n 64 > ourcorewar.txt
	$SCHOOL_WAR -d $1 ${FILE[@]} | tail -n 64 > 42corewar.txt
}

print_chosen_files() {
	x=0
	if (($1 != 1)); then
		echo "${GREEN}Currently chosen files: ${NOCOLOR}"
	else
		echo "Files, used in this run:"
	fi

	if ((ARGS_AMOUNT == 0)); then
		echo "None"
		((x += 1))
	fi
	while ((x < ARGS_AMOUNT))
	do
		if (($1 != 1)); then
			echo "${FILE[$x]}, id = ${FILE_ID_ARR[$x]} "
		else
			echo "\t${FILE[$x]}, id = ${FILE_ID_ARR[$x]} "
		fi
		((x += 1))
	done

	while ((x < 4)); do
		echo ""
		((x += 1))
	done
	echo ""
}

overwrite() {
	echo "\033[11A";
}

choose_file() {
	if ((FILE_ID < 0)); then
		((FILE_ID = (${#FILE_DIR[@]} - 1)))
	fi

	if ((FILE_ID > (${#FILE_DIR[@]} - 1))); then
		((FILE_ID = 0))
	fi

	print_chosen_files 0
	echo "\r\033[KChoose player $FILE_NUM"
	echo "\r\033[Kfile_id = $FILE_ID"
	if (($FILE_ID >= 0)); then
		echo "\r\033[K${FILE_DIR[FILE_ID]}"
	else
		echo "\r\033[KFile_id has to be >= 0"
	fi

	read -n1 -s -r -p $'\n' key

	case "$key" in
	$'[' )
		((FILE_ID -= 1))
		FILE_ID_ARR[FILE_NUM]=$FILE_ID
		overwrite ""
		choose_file ""
		;;
	$']' )
		((FILE_ID += 1))
		FILE_ID_ARR[FILE_NUM]=$FILE_ID
		overwrite ""
		choose_file ""
		;;
	$'\e' )
		((FILE_ID = -1))
		exit 1
		;;
	$yes )
		FILE[FILE_NUM]=${FILE_DIR[FILE_ID]}
		((FILE_ID = 0))
		((FILE_NUM += 1))
		((ARGS_AMOUNT += 1))
		if ((FILE_NUM > 3))
		then
			echo "Max amount of players has been chosen"
			sleep "1"
			return
		fi
		overwrite ""
		choose_file ""
		;;
	$'r' )
		if ((FILE_NUM < 1))
		then
			echo "Choose at least one player"
			((FILE_ID = -1))
			choose_file ""
		else
			return
		fi
		;;
	* )
		overwrite ""
		choose_file ""
		;;
	esac
}

print_commands() {
	echo "Commands, used to run:"

	echo "\t$OUR_WAR -dump $1 ${FILE[@]} | tail -n 64 > ourcorewar.txt"
	echo "\t$SCHOOL_WAR -d $1 ${FILE[@]} | tail -n 64 > 42corewar.txt"
}

ARGS_AMOUNT=$#
if ((ARGS_AMOUNT >= 1)); then
	for j in "$@"; do
		FILE[$FILE_NUM]=${FILE_DIR[j]}
		FILE_ID_ARR[$FILE_NUM]=$j
		((FILE_NUM += 1))
	done
else
	echo "Controls:"
	echo "\tPress [ to choose previous file"
	echo "\tPress ] to choose next file"
	echo "\tESC to exit"
	echo "\tPress enter to choose file\n"
	echo "\tPress 'r' to confirm you've chosen all players\n"
	ARGS_AMOUNT=0
	choose_file ""
fi

strstr() {
  [ "${1#*$2*}" = "$1" ] && return 1
  return 0
}


print_chosen_files 0
while true; do
	echo "Testing with -dump $i"
	run_games "$i"
	if [[ $(diff ourcorewar.txt 42corewar.txt) != "" ]]
	then
		echo "${RED}diff with -dump $i isn't empty${NOCOLOR}\n"
		((NOT_PASS = i))
		((i= PASS + (NOT_PASS - PASS) / 2))
	else
		echo "${GREEN}diff with -dump $i empty${NOCOLOR}\n"
		((PASS = i))
		if  ((NOT_PASS != 0))
		then
			((i= PASS + (NOT_PASS - PASS) / 2))
		else
			((i=i+INCREMENT))
		fi
	fi
	if (((NOT_PASS - PASS) == 1)) || ((i == 0))
	then
		if ((i != 0)); then
			echo "${YELLOW}CHECK THAT FIRST DIFF IS EMPTY, AND SECOND IS NOT"
			echo "OTHERWISE THE SCRIPT GAVE FALSE RESULT${NOCOLOR}\n"

			run_games "$PASS"
			echo diff 1 = $(diff ourcorewar.txt 42corewar.txt)

			run_games "$NOT_PASS"
			echo diff 2 = $(diff ourcorewar.txt 42corewar.txt)
		fi
		echo "${RED}diff occured at -dump $NOT_PASS${NOCOLOR}\n"
		break
	fi
done

echo "Gerenal info:\n"
print_commands $i
print_chosen_files 1