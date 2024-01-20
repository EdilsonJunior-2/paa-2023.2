import sys
import math

code = 0
cnpj = 1
weight = 2
position = 3

def conquer(entry, start_position, middle, final_position):
	start_aux = start_position
	ahead_middle = middle + 1
	start_aux_2 = 0
	temp = [None] * (final_position - start_position + 1)
	if start_aux + 1 == ahead_middle:
		if entry[start_aux][0] <= entry[ahead_middle][0]:
			temp[start_aux_2] = entry[start_aux]
			temp[start_aux_2 + 1] = entry[ahead_middle]
		else:
			temp[start_aux_2] = entry[ahead_middle]
			temp[start_aux_2 + 1] = entry[start_aux]
		start_aux = start_aux + 1
		ahead_middle = ahead_middle + 1
	else:
		while start_aux <= middle and ahead_middle <= final_position:
			if entry[start_aux][0] <= entry[ahead_middle][0]:
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
	
	for i in range(final_position - start_position + 1):
		entry[start_position + i] = temp[i]

def divide(entry, start_position, final_position):
	if(start_position < final_position):
		middle = start_position + (final_position - start_position)/2
		divide(entry, math.trunc(start_position), math.trunc(middle))
		divide(entry, math.trunc(middle + 1), math.trunc(final_position))
		conquer(entry, math.trunc(start_position), math.trunc(middle), math.trunc(final_position))

def returnErrorString(el):
	return el[1]
def main(args):
	golden_input = open(args[1],'r')
	main_list_count = int(golden_input.readline())
	main_list = []
	for _ in range(main_list_count):
		main_item = golden_input.readline().split()
		main_item[weight] = int(main_item[weight])
		main_list.append(main_item)

	arrived_list_count = int(golden_input.readline())
	arrived_list = []
	cnpj_error_list = []
	cnpj_error_list_count = 0
	weight_error_list = []
	weight_error_list_count = 0
	
	for _ in range(arrived_list_count):
		arrived_item = golden_input.readline().split()
		arrived_item[weight] = int(arrived_item[weight])
		flag = 0
		main_list_count_aux = 0
		while flag == 0:
			if(arrived_item[0] == main_list[main_list_count_aux][code]):
				arrived_item.append(main_list_count_aux)
				if arrived_item[cnpj] != main_list[main_list_count_aux][cnpj]:
					cnpj_error_list.append([main_list_count_aux, f'{arrived_item[code]}: {main_list[main_list_count_aux][cnpj]}<->{arrived_item[cnpj]}'])
					cnpj_error_list_count += 1
				if arrived_item[weight] != main_list[main_list_count_aux][weight]:
					difference = abs(arrived_item[weight] - main_list[main_list_count_aux][weight])
					difference_percentage = (difference/arrived_item[weight])*100
					weight_error_list.append([main_list_count_aux, f'{arrived_item[code]}: {difference}kg ({round(difference_percentage)}%)'])
					weight_error_list_count += 1
				flag = 1
			main_list_count_aux = main_list_count_aux + 1
		arrived_list.append(arrived_item)
	divide(cnpj_error_list, 0, cnpj_error_list_count - 1)
	divide(weight_error_list, 0, weight_error_list_count - 1)
	golden_input.close()
	golden_output = open(args[2], "w")

	for i in range(cnpj_error_list_count):
		golden_output.write(f'{cnpj_error_list[i][1]}\n')
	for i in range(weight_error_list_count):
		golden_output.write(f'{weight_error_list[i][1]}\n')

	golden_output.close()	

if __name__ == '__main__':
	main(sys.argv)