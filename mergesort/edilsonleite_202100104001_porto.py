import sys
import math

code = 0
cnpj = 1
weight = 2
position = 3

def conquer(origin, entry, start_position, middle, final_position, archiveName):
	start_aux = start_position
	ahead_middle = middle + 1
	start_aux_2 = 0
	temp = [None] * (final_position - start_position + 1)
	if start_aux + 1 == ahead_middle:
		if entry[start_aux][position] <= entry[ahead_middle][position]:
			temp[start_aux_2] = entry[start_aux]
			temp[start_aux_2 + 1] = entry[ahead_middle]
		else:
			temp[start_aux_2] = entry[ahead_middle]
			temp[start_aux_2 + 1] = entry[start_aux]
		start_aux = start_aux + 1
		ahead_middle = ahead_middle + 1
	else:
		while start_aux <= middle and ahead_middle <= final_position:
			if entry[start_aux][position] <= entry[ahead_middle][position]:
				temp[start_aux_2] = entry[start_aux]
				start_aux = start_aux + 1
			else:
				temp[start_aux_2] = entry[ahead_middle]
				ahead_middle = ahead_middle + 1
			start_aux_2 = start_aux_2 + 1

	while start_aux <= middle:
		temp[start_aux_2] = entry[start_aux]
		start_aux = start_aux + 1
		start_aux_2 = start_aux_2 + 1
	
	
	while ahead_middle <= final_position:
		temp[start_aux_2] = entry[ahead_middle]
		ahead_middle = ahead_middle + 1
		start_aux_2 = start_aux_2 + 1
	
	if(final_position - start_position  !=  len(entry) - 1):
		for i in range(final_position - start_position + 1):
			entry[start_position + i] = temp[i]
	else:
		golden_output = open(archiveName,'w')
		for i in range(final_position + 1):
			org = origin[temp[i][position]]
			if temp[i][cnpj] != org[cnpj]:
				golden_output.write(temp[i][code] + ": " + org[cnpj] + "<->" + temp[i][cnpj] + "\n")
		for i in range(final_position + 1):
			org = origin[temp[i][position]]
			if temp[i][weight] >= org[weight]:
				difference =  int(temp[i][weight]) - int(org[weight])
				difference_percentage = (difference/int(temp[i][weight]))*100
				
				if difference_percentage > 10:
					golden_output.write(f'{temp[i][code]}: {difference}kg ({round(difference_percentage)}%)\n')
					golden_output.flush()
			else:
				difference = int(org[weight]) - int(temp[i][weight])
				difference_percentage = (difference/int(org[weight]))*100
				
				if difference_percentage > 10:
					golden_output.write(f'{temp[i][code]}: {difference}kg ({round(difference_percentage)}%)\n')
					golden_output.flush()
		
		golden_output.close()

def divide(origin, entry, start_position, final_position, archiveName):
	if(start_position < final_position):
		middle = start_position + (final_position - start_position)/2
		divide(origin,entry, math.trunc(start_position), math.trunc(middle), "")
		divide(origin,entry, math.trunc(middle + 1), math.trunc(final_position), "")
		conquer(origin, entry, math.trunc(start_position), math.trunc(middle), math.trunc(final_position), archiveName)

def main(args):
	golden_input = open(args[1],'r')
	main_list_count = int(golden_input.readline())
	main_list = []
	for i in range(main_list_count):
		main_list.append(golden_input.readline().split())

	arrived_list_count = int(golden_input.readline())
	arrived_list = []
	for i in range(arrived_list_count):
		arrived_item = golden_input.readline().split()
		flag = 0
		main_list_count_aux = 0
		while flag == 0:
			if(arrived_item[0] == main_list[main_list_count_aux][code]):
				arrived_item.append(main_list_count_aux)
				flag = 1
			main_list_count_aux = main_list_count_aux + 1
		arrived_list.append(arrived_item)
	divide(main_list, arrived_list, 0, arrived_list_count - 1, args[2])
	golden_input.close()

if __name__ == '__main__':
	main(sys.argv)