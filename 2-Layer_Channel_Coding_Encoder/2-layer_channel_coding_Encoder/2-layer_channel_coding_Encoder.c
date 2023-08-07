// 2-layer Channel Coding Encoder
#include<stdio.h>
#include<string.h>

int main() {
	printf("2-layer ���ڴ� (�Է� 16-bit, ��� 42-bit)\n");

	while (1)
	{
		char input_D[17] = { 0 };
		int input_D_modify_into_number[24] = { 0, };
		int Divisor_G[9] = { 1,0,0,0,0,0,1,1,1 };
		char temp[25] = { 0 };

		printf("�Է�: ");
		scanf("%s", input_D);

		///////////////////// crc-8 encoder /////////////////////
		for (int i = 0; input_D[i]; i++) {

			//�Է¹��� ���ڿ� input_D�� ����� ���Ǽ��� ���� int������ ��ȯ�ϴ� ����
			input_D_modify_into_number[i] = input_D[i] - '0';

		}

		for (int i = 0; i < 16; i++) {
			//division�� �������� n-k��ŭ shifit
			//n=24,k=16
			//division�� �� 8��ŭ �������� shift �Ǿ��ٰ� �����ϰ�
			//�� ���ʺ��� Ȯ���Ͽ� ��Ʈ�� 1�� ���� Ȯ���ϸ� Divisor_G�� ������ modulo 2 arithmetic �� xor������ ���� �ٲ� division�� ����ؼ� �����ϴµ�
			//�ش� ������ Q�� ��Ʈ�� �ִ��� ���� �� ���� ���ü� �ִ� �ִ��� Ƚ�� (k) ���� �ݺ��Ͽ� �������� ���Ѵ�.
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
			//�������
			/*
			1000101
			0100111
			0010110
			0001011
			�� ��꿡 ���Ǽ��� ���� ���η� ������ �迭�� ����*/
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
		////////////////////�׽�Ʈ ���//////////////////////////
		char final_result_for_test[48] = { 0 };//���� 5�� ����
		sprintf(final_result_for_test, "%s %s %s %s %s %s", before_result[0], before_result[1], before_result[2], before_result[3], before_result[4], before_result[5]);
		printf("���(���� ���� �׽�Ʈ��): %s\n", final_result_for_test);
		*/

		sprintf(final_result, "%s%s%s%s%s%s", before_result[0], before_result[1], before_result[2], before_result[3], before_result[4], before_result[5]);
		printf("���: %s\n", final_result);
	}
	

	return 0;
}