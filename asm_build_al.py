
import os

def assembly_versions(filename):
	path_to_file = sample_files + '/' + filename
	output_filename = filename.replace('.s', '.cor')
	
	os.system('./resources_42/asm ' + path_to_file)
	# os.system('hexdump -v ./valid_files/' + output_filename + ' >> hex1.txt')
	
	# os.system('../assembler ' + path_to_file)
	# os.system('hexdump -v ./valid_files/' + output_filename + ' >> hex2.txt')

	# os.system('diff hex1.txt hex2.txt > diff' + filename)
	# if os.path.getsize('diff' + filename) == 0:
		# os.system('rm diff' + filename)

	# os.system('rm ./valid_files/' + output_filename)
	# os.system('rm ./valid_files/' + output_filename)
	# os.system('rm hex1.txt')
	# os.system('rm hex2.txt')

sample_files = "resources_42/valid_files/"
asm_42_dir = "42asm"
our_asm_dir = "ourAsm"

for filename in os.listdir(sample_files):
	assembly_versions(filename)