void listAllTxt(){
    #ifdef _WIN32
        system("dir /S /B *.bmp");
    #else
        system("find . -name '*.bmp'");
    #endif

}
void help(){
    cout<<"here is the list of available commands:"<<endl;
    cout<<"intro:  show the introduction of this app."<<endl;
    cout<<"help:   show the list of available commands."<<endl;
    cout<<"exit:   close this app."<<endl;
    cout<<"color:  show image in full color mode."<<endl;
    cout<<"gray1:  show image in grayscale mode using grayscale ansi palette."<<endl;
    cout<<"gray2:  show image in grayscale mode using pure ascii."<<endl;
    cout<<"edge:   show image in full color mode(if it is egde,will have \"*\")"<<endl; 
    cout<<"author: go to ZhiFeng's personal website."<<endl;
    cout<<"set:    you can setup the file you want to open."<<endl;
    return;
}
void intro(){
    cout<<"Welcome to ASCII maker."<<endl;
    cout<<"This maker is created by ZhiFeng."<<endl;
    cout<<"If you want to know the list of available commands, you can input \"help\"."<<endl;
    return;
}
void author(){
    system("start http://shane-test.nde.tw/blog/%e5%82%99%e5%af%a9/");
    return;
}
void test_front(int i,char c='#'){
    cout<<"\e[38;5;"<<i<<"m"<<c<<"\e[0m";
}
void test_back(int i,char c=' '){
    cout<<"\e[48;5;"<<i<<"m"<<c<<"\e[0m";
}
void set(BMP &bmp){
	cout<<"here is list of .bmp:"<<endl;
	listAllTxt();
    string filename;
    cout<<"Input the file name(just name):";
    cin>>filename;
    bmp.read(filename);
}
void list(BMP &bmp){
    for(int i=0;i<bmp.height();i++){
        for(int j=0;j<bmp.width();j++){
            cout<<"(";
            cout<<bmp.bitmap[i][j][2]<<",";
            cout<<bmp.bitmap[i][j][1]<<",";
            cout<<bmp.bitmap[i][j][0];
            cout<<")";
        }
        cout<<endl;
    }
}

static int rgb_to_x256(uint8_t r, uint8_t g, uint8_t b){
	#define v2ci(v) (v < 48 ? 0 : v < 115 ? 1 : (v - 35) / 40)
    int ir = v2ci(r), ig = v2ci(g), ib = v2ci(b);
	#define color_index() (36 * ir + 6 * ig + ib)
    int average = (r + g + b) / 3;
    int gray_index = average > 238 ? 23 : (average - 3) / 10;

    static const int i2cv[6] = {0, 0x5f, 0x87, 0xaf, 0xd7, 0xff};
    int cr = i2cv[ir], cg = i2cv[ig], cb = i2cv[ib];
    int gv = 8 + 10 * gray_index;
	#define dist_square(A,B,C, a,b,c) ((A-a)*(A-a) + (B-b)*(B-b) + (C-c)*(C-c))
    int color_err = dist_square(cr, cg, cb, r, g, b);
    int gray_err  = dist_square(gv, gv, gv, r, g, b);
    return color_err <= gray_err ? 16 + color_index() : 232 + gray_index;
}

int abs(int a){
	if(a>=0)return a;
	else a*-1;
}
void edge(BMP &bmp){
    for(int i=0;i<bmp.height();i++){
        for(int j=0;j<bmp.width();j++){
        	int c=rgb_to_x256(bmp.bitmap[i][j][2],bmp.bitmap[i][j][1],bmp.bitmap[i][j][0]);  
			int cu=0,cd=0,cl=0,cr=0; 
			if(i!=0 && i!=bmp.height()-1 && j!=0 && j!=bmp.width()-1){	
       			cu=rgb_to_x256(bmp.bitmap[i][j+1][2],bmp.bitmap[i][j+1][1],bmp.bitmap[i][j+1][0])-16;
       			cd=rgb_to_x256(bmp.bitmap[i][j-1][2],bmp.bitmap[i][j-1][1],bmp.bitmap[i][j-1][0])-16;
        		cl=rgb_to_x256(bmp.bitmap[i-1][j][2],bmp.bitmap[i-1][j][1],bmp.bitmap[i-1][j][0])-16;
       			cr=rgb_to_x256(bmp.bitmap[i+1][j][2],bmp.bitmap[i+1][j][1],bmp.bitmap[i+1][j][0])-16;
        	}
        	if(abs(cu%36-(c-16)%36)>5 || abs(cl%36-(c-16)%36)>5 || abs(cd%36-(c-16)%36)>5 || abs(cr%36-(c-16)%36)>5){
        		test_back(c,'*');
			} 
            else test_back(c);
        }
        cout<<endl;
    }
}
void color(BMP &bmp){
    for(int i=0;i<bmp.height();i++){
        for(int j=0;j<bmp.width();j++){
            test_back(rgb_to_x256(bmp.bitmap[i][j][2],bmp.bitmap[i][j][1],bmp.bitmap[i][j][0]));
        }
        cout<<endl;
    }
}
void gray1(BMP &bmp){
    for(int i=0;i<bmp.height();i++){
        for(int j=0;j<bmp.width();j++){
            #define v2ci(v) (v < 48 ? 0 : v < 115 ? 1 : (v - 35) / 40)
    		int ir = v2ci(bmp.bitmap[i][j][2]), ig = v2ci(bmp.bitmap[i][j][1]), ib = v2ci(bmp.bitmap[i][j][0]);
			#define color_index() (36 * ir + 6 * ig + ib)
  			int c=color_index()/10;
            if(c<=23)test_back(c+232);
            else test_back(255);
        }
        cout<<endl;
    }
}
void gray2(BMP &bmp){
    for(int i=0;i<bmp.height();i++){
        for(int j=0;j<bmp.width();j++){
            int c=(bmp.bitmap[i][j][2]+bmp.bitmap[i][j][1]+bmp.bitmap[i][j][0])/30;
            if(c<=5)test_front(255,' ');
            else if(c<=10)test_front(255,'.');
            else if(c<=15)test_front(255,'-');
            else test_front(255,'#');
        }
        cout<<endl;
    }
}

