import sys
import math

code = 0
cnpj = 1
weight = 2
position = 3
main_list_count = 0
main_list = []
arrived_list_count = 0
arrived_list = []
error_list = []

def conquer(out, entry, start_position, middle, final_position):
    start_aux = start_position
    ahead_middle = middle + 1
    start_aux_2 = start_position
    print(start_position, middle, final_position, out, entry)
    while(start_aux <= middle & ahead_middle <= final_position):
        if(entry[start_aux][position] <= entry[ahead_middle][position]):
            print(start_aux, start_aux_2)
            out[start_aux_2 + 1] = entry[start_aux + 1]
        else:
            out[start_aux_2 + 1] = entry[ahead_middle + 1]

def divide(out, entry, start_position, final_position):
    if(start_position < final_position):
        middle = start_position + (final_position - start_position)/2
        divide(out,entry, math.trunc(start_position), math.trunc(middle))
        divide(out,entry, math.trunc(middle + 1), math.trunc(final_position))
        conquer(out, entry, math.trunc(start_position), math.trunc(middle), math.trunc(final_position))

def main(args):
    #Ilustrando uso de argumentos de programa
    print(args)
    print("#ARGS = %i"%len((args)))
    print("PROGRAMA = %s"%(args[0]))
    #Abrindo Arquivos
    golden_input = open("porto.input",'r')
    golden_output = open("porto.output",'w')
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
        error_list.append([])

    divide(error_list, arrived_list, 0, arrived_list_count - 1)
    print(error_list)
    golden_input.close()
    golden_output.close()

if __name__ == '__main__':
    main(sys.argv)