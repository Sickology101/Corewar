FILES=("resources_42/valid_files/byte_code/Machine-Gun.cor")
ARGS=$#
if ((ARGS != 1))
then
	echo "Enter dump value"
	break
fi
DUMP=$1
../corewar -dump $1 ${FILES[@]} > ourcorewar_log.txt

./vm_champs/corewar -d $1 ${FILES[@]} > 42.txt
tail -n +3 42.txt > 42corewar.txt
rm 42.txt
echo "diff of $FILENAME at -dump = $DUMP \n $(diff ourcorewar.txt 42corewar.txt)"