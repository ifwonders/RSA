# include <iostream>
# include <cstdlib>
# include <math.h>
# include <vector>

#define mod %

using namespace std;

unsigned int gcd(unsigned int p, unsigned int q) {
	unsigned int limit = (sqrt(p) < sqrt(q)) ? (unsigned int)(sqrt(p)) : (unsigned int)(sqrt(q));
	unsigned int i = 1;
	unsigned int factor = 1;
	for (i = 1; i < limit + 1; ++i) {
		if (p % i == 0 && q % i == 0) {
			factor *= i;
			p /= i; q /= i;
		}
	}
	return factor;
}
unsigned int lcm(unsigned int p, unsigned int q) {
	unsigned int factor = 0;
	factor = gcd(p, q);

	return  p * q / factor;
}
bool isPrime(unsigned int num) {
	for (unsigned int i = 2; i < sqrt(num)+1; ++i) {
		if (num % i == 0)
			return false;
	}
	return true;
}
unsigned int getRandPrime(unsigned int min,unsigned int max) {
	unsigned int randNum = 0;
	do {
		randNum = (unsigned int)((rand() % (max - min)) + min);
	} while (!isPrime(randNum));

	return randNum;
}
unsigned int crypt(unsigned int m, unsigned int e, unsigned int N) {
	unsigned int i = 0;
	unsigned int ret=1;
	for (i = 0; i < e; ++i) {
		ret = ret * m;
		if (ret > N)
			ret = ret % N;
	}

	return ret;
}
void printVec(vector<unsigned int> vec) {
	for (int i = 0; i < vec.size(); i++)
		cout << (unsigned char)vec[i];
	cout << endl;
}
int main() {
	vector<unsigned int>plaintext;
	vector<unsigned int>ciphertext;
	//输入明文
	cout << "请输入明文：";
	unsigned char ch = 0;
	do {
		ch= getchar();
		plaintext.push_back((unsigned int)ch);
	} while (ch != '!');
	
	//输入二进制长度
	unsigned int len = 5;
	//cout << "请输入大素数二进制长度：" << endl;
	//cin >> len;

	//确定素数上下限
	unsigned int min = (unsigned int)pow(2, len - 1);
	unsigned int max = (unsigned int)pow(2, len);

	//选取大素数p, q
	unsigned int p, q = 0;
	do {
		p = getRandPrime(min, max);
		q = getRandPrime(min, max);
	} while (p == q);

	unsigned int N = p * q;
	cout << "本次 N = " << N << endl;

	unsigned int L = lcm(p - 1, q - 1);
	cout << "本次 L = " << L << endl;

	unsigned int E = 0;
	do {
		E = (unsigned int)((rand() % (L - 2)) + 2);
	} while (gcd(E, L) != 1);
	cout << "本次 E = " << E << endl;

	unsigned int D = 0;
	do {
		D = (unsigned int)((rand() % (L - 2)) + 2);
	} while (E * D mod L != 1);
	cout << "本次 D = " << D << endl;

	cout << "加密前明文为：";
	printVec(plaintext);

	for (auto ch : plaintext) {
		ciphertext.push_back(crypt(ch, E, N));
	}
	plaintext.clear();
	cout << "加密后密文为：";
	printVec(ciphertext);

	for (auto ch : ciphertext) {
		plaintext.push_back(crypt(ch, D, N));
	}
	cout << "解密后明文为：";
	printVec(plaintext);
	return 0;
}