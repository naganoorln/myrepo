#include<stdio.h>
void reverse_number_bits(int num) {
	int res=0;
	for(int i=0; i<32; i++) {
		res = res << 1;
		res = res | num & 1;
		num = num >> 1;
	}
	printf("the reversed integer %b", res);
}
int main() {
	int num=7;
	reverse_number_bits(num);
	return 0;
}