FILENAME="Gagnant"
ARGS=$#
if ((ARGS != 1))
then
	echo "Enter dump value"
	break
fi
DUMP=$1
./corewar -dump $DUMP resources_42/vm_champs/$FILENAME.cor > /dev/null 2>&1
./resources_42/vm_champs/corewar -d $DUMP resources_42/vm_champs/$FILENAME.cor > 42.txt
tail -n +3 42.txt > 42corewar.txt
rm 42.txt
echo "diff of $FILENAME at -dump = $DUMP \n $(diff ourcorewar.txt 42corewar.txt)"