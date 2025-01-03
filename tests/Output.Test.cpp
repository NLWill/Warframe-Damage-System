#include<iostream>
using namespace std;
int main(){
//std::cout << "Testing" << std::endl;
int i = 1;
for (int j = 0; j < 100; j++) {
	i += j;
	cout << i << "\n";
}
std::cin >> i;
}