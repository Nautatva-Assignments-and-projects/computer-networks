#!/usr/bin/env python
in_file = 'tcp-example.tr'
out_file = 'outreach_clean.txt'

with open(in_file) as i, open(out_file, 'w') as o:
	queue_occupancy=0
	for line in i:
		cleaned = []
		items = line.split()
		check=1
		for item in items:
	            
	            if item.startswith("r") or item.startswith('d'):	
	                check=0
	                break
	            elif item.startswith('+'):	
	            	# enqueue operation
	            	queue_occupancy+=1

	            elif item.startswith('-'):
	            	# dequeue operation
	            	queue_occupancy-=1

	            elif item.startswith("/N"):
	                break

	            else:
	                cleaned.append(item)

		if check!=0:
			char_queue_occupancy=str(queue_occupancy)
			cleaned.append(char_queue_occupancy)
			joined_line = ' '.join(cleaned)
			o.write(joined_line+'\n')
