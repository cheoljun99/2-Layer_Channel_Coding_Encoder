// 2-layer Channel Coding Encoder
#include<stdio.h>
#include<string.h>

int main() {
	printf("2-layer 인코더 (입력 16-bit, 출력 42-bit)\n");

	while (1)
	{
		char input_D[17] = { 0 };
		int input_D_modify_into_number[24] = { 0, };
		int Divisor_G[9] = { 1,0,0,0,0,0,1,1,1 };
		char temp[25] = { 0 };

		printf("입력: ");
		scanf("%s", input_D);

		///////////////////// crc-8 encoder /////////////////////
		for (int i = 0; input_D[i]; i++) {

			//입력받은 문자열 input_D를 계산의 편의성을 위해 int형으로 변환하는 과정
			input_D_modify_into_number[i] = input_D[i] - '0';

		}

		for (int i = 0; i < 16; i++) {
			//division이 왼쪽으로 n-k만큼 shifit
			//n=24,k=16
			//division이 즉 8만큼 왼쪽으로 shift 되었다고 가정하고
			//맨 왼쪽부터 확인하여 비트가 1인 것을 확인하면 Divisor_G를 가지고 modulo 2 arithmetic 즉 xor연산을 후의 바뀐 division을 계속해서 갱신하는데
			//해당 과정을 Q의 비트의 최대의 개수 즉 몫이 나올수 있는 최대의 횟수 (k) 동안 반복하여 나머지를 구한다.
			if (input_D_modify_into_number[i] == 1) {
				for (int j = 0; j < 9; j++) {
					input_D_modify_into_number[i + j] = Divisor_G[j] ^ input_D_modify_into_number[i + j];
				}
			}
		}
		sprintf(temp, "%s%d%d%d%d%d%d%d%d", input_D, input_D_modify_into_number[16], input_D_modify_into_number[17], input_D_modify_into_number[18], input_D_modify_into_number[19],
			input_D_modify_into_number[20], input_D_modify_into_number[21], input_D_modify_into_number[22], input_D_modify_into_number[23]);
		/////////////////////////////////////////////////////////



		///////////////// (7,4) hamming encoder /////////////////
		int generator_matrix_G[7][4] = {
			//생성행렬
			/*
			1000101
			0100111
			0010110
			0001011
			를 계산에 편의성을 위해 세로로 나누어 배열에 저장*/
			{1,0,0,0},	{0,1,0,0},	{0,0,1,0},
			{0,0,0,1},	{1,1,1,0},	{0,1,1,1},	{1,0,1,1}
		};
		char before_result[6][8] = { 0 };
		char final_result[43] = { 0 };


		for (int k = 0; k < 6; k++) {
			char temp_cat[5] = { 0 };
			strncat(temp_cat, temp + k * 4, 4);
			int temp_s[4] = { 0, };
			int output_t[7] = { 0, };
			char result[8] = { 0 };
			for (int i = 0; temp_cat[i]; i++)
				temp_s[i] = temp_cat[i] - '0';
			for (int i = 0; i < 7; i++) {
				for (int j = 0; j < 4; j++) {
					if (generator_matrix_G[i][j] == 1)
					{
						output_t[i] ^= temp_s[j];
					}
				}
			}
			for (int i = 0; i < 7; i++)
				output_t[i] %= 2;
			sprintf(before_result[k], "%d%d%d%d%d%d%d", output_t[0], output_t[1], output_t[2], output_t[3], output_t[4], output_t[5], output_t[6]);
		}
		/////////////////////////////////////////////////////////

		/*
		////////////////////테스트 출력//////////////////////////
		char final_result_for_test[48] = { 0 };//공백 5개 포함
		sprintf(final_result_for_test, "%s %s %s %s %s %s", before_result[0], before_result[1], before_result[2], before_result[3], before_result[4], before_result[5]);
		printf("출력(공백 포함 테스트용): %s\n", final_result_for_test);
		*/

		sprintf(final_result, "%s%s%s%s%s%s", before_result[0], before_result[1], before_result[2], before_result[3], before_result[4], before_result[5]);
		printf("출력: %s\n", final_result);
	}
	

	return 0;
}