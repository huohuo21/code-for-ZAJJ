#include "fit.C"
void run_fit(){
	fit(25,35);
	fit(35,45);
	fit(45,60);
	fit(60,80);
	fit(80,120);
	fit(120,400);
}

int main(){
	run_fit();
	return 0;
}
