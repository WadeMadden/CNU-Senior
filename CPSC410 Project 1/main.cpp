#include "utilities.h"
int main(){
	const char* test = "test.txt";
	int num = loadData(test);
	sortData(CPU_TIME);
	saveData("output.txt");
	process_stats g = getNext();
	g = getNext();
	g= getNext();
	g = getNext();
	g = getNext();
	g = getNext();
	g = getNext();
	g = getNext();
	g = getNext();


	return num;
}
