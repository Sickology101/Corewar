import os

def assembly_versions(filename):
	path_to_file = sample_files + '/' + filename
	output_filename = filename.replace('.s', '.cor')
	
	os.system('../asm ' + path_to_file)

sample_files = "players_asm_code"

for filename in os.listdir(sample_files):
	assembly_versions(filename)