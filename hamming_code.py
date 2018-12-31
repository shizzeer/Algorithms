#!/usr/bin/python3
import sys

def set_parity_bits(hamming_code_word, len_of_hamming_code_word):
	for i in range(len_of_hamming_code_word):
		if value_is_power_of_two(i + 1):
			bits_to_check = get_bits_to_check(hamming_code_word, len_of_hamming_code_word, i + 1)
			check_number_of_ones = [bit for bit in bits_to_check if bit == '1']
			if len(check_number_of_ones) % 2 == 0:
				hamming_code_word[i] = '0'
			else:
				hamming_code_word[i] = '1'

	return hamming_code_word


def get_bits_to_check(hamming_code_word, len_of_hamming_code_word, position_of_parity_bit):
	bits_to_check = []

	number_of_bits_to_check = position_of_parity_bit
	checking_loop_idx = position_of_parity_bit - 1

	while checking_loop_idx < len_of_hamming_code_word:
		if number_of_bits_to_check != 0:
			bits_to_check.append(hamming_code_word[checking_loop_idx])
			number_of_bits_to_check -= 1
			checking_loop_idx += 1
		else:
			for x in range(position_of_parity_bit):
				number_of_bits_to_check += 1
				checking_loop_idx += 1
	
	return bits_to_check


def value_is_power_of_two(value):
	return value != 0 and (value & (value - 1) == 0) 

def init_hamming_code_word(user_value, len_of_hamming_code_word):
	hamming_code_word = [0] * len_of_hamming_code_word
	user_value_idx = 0

	for i in range(len_of_hamming_code_word):
		if not value_is_power_of_two(i + 1):
			hamming_code_word[i] = user_value[user_value_idx]
			user_value_idx += 1

	return hamming_code_word
			
def get_number_of_parity_bits(user_value):
	position_of_parity_bit = 1
	number_of_parity_bits = 0

	while position_of_parity_bit <= len(user_value):
		position_of_parity_bit <<= 1
		number_of_parity_bits += 1

	return number_of_parity_bits

def get_len_of_hamming_code_word(user_value, number_of_parity_bits):
	len_of_hamming_code_word = len(user_value) + number_of_parity_bits

	if value_is_power_of_two(len_of_hamming_code_word):
		return len_of_hamming_code_word + 1
	else:
		return len_of_hamming_code_word

def main():
	
	if len(sys.argv) == 2: 
		user_value = bin(int(sys.argv[1]))[2:]
		
		number_of_parity_bits = get_number_of_parity_bits(user_value)
		len_of_hamming_code_word = get_len_of_hamming_code_word(user_value, number_of_parity_bits)
		
		hamming_code_word = init_hamming_code_word(user_value, len_of_hamming_code_word)
		hamming_code_word = set_parity_bits(hamming_code_word, len_of_hamming_code_word)
		
		print(''.join(hamming_code_word))
	else:
		sys.stderr.write("usage: ./hamming_code <value to parse>\n")

if __name__ == '__main__':
	main()
