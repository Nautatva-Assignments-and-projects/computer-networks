#!/usr/bin/env python
in_file = 'tcp-example.cwnd'

first_line_int = 0
required_int = 0
line_split = []
time=[]
count =0
with open(in_file) as i:
	for line in i:
		line_split=line.split()
		line_split=map(float,line_split)
		required_int = line_split[1]

		if required_int==first_line_int:
			continue
		
		elif required_int>first_line_int:
			first_line_int = required_int
			continue
		
		else:
			count+=1
			time.append(line_split[0])
			first_line_int = required_int

	print count
	print time