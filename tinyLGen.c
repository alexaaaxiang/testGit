#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	FILE *oFile=fopen("sample2.tinyL", "w");
	int times=100000;

	fprintf(oFile, "!a;b=");
	int count=0;
	int count2=0;
	while(count<=times){
		fprintf(oFile, "+");
		count++;
	}
	while(count2<=times+1){
		fprintf(oFile, "1");
		count2++;
	}
	fprintf(oFile, ";#b.");
	fclose(oFile);
	return 0;
}
