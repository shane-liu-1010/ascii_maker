#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

#include "bmp_handler.h"
#include "func.hpp"

int main(){

    #ifdef _WIN32
        system("chcp 65001");
    #endif

	string cmd;
	BMP bmp("cat-heart.bmp");
	intro();

	while(cout<<">>>",cin>>cmd){
		if(cmd=="set")set(bmp);
		else if(cmd=="list")list(bmp);
		else if(cmd=="color")color(bmp);
		else if(cmd=="gray1")gray1(bmp);
		else if(cmd=="gray2")gray2(bmp);
		else if(cmd=="edge")edge(bmp);
		else if(cmd=="help")help();
		else if(cmd=="intro")intro();
		else if(cmd=="author")author();
		else if(cmd=="exit")exit(0);
		else cout<<"command not found:"<<cmd<<endl;
	}

    return 0;
}
