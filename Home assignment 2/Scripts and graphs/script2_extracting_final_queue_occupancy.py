#!/usr/bin/env python
in_file = 'outreach_clean.txt'
out_file = 'final_queue_occupancy.txt'

first_line_int = 0 
line_split = []

with open(in_file) as i, open(out_file,'w') as o:
	for line in i:
		line_split=line.split()
		required_int = line_split[0]

		if required_int==first_line_int:
			pline=line.split()
			continue
		
		elif (required_int != first_line_int and first_line_int!=0):
			first_line_int = required_int
			joineditem=' '.join(pline)
			o.write(joineditem+'\n')

		first_line_int = required_int
		pline=line.split()

	o.write(' '.join(pline))