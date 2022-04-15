#include <string.h>   
#include <math.h>     
#include <stdio.h>     
#include <stdlib.h>     
#include <malloc.h>  

#include<time.h>//時間相關標頭檔案，可用其中函式計算影象處理速度  

#define   WIDTHBYTES(bits) (((bits)+31)/32*4)//用於使影象寬度所佔位元組數為4byte的倍數  

#define MYDRAW_HEIGHT 1080  //目標影象高度  
#define MYDRAW_WIDTH 1920  //目標影象寬度  

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef long LONG;

//點陣圖檔案頭資訊結構定義  
//其中不包含檔案型別資訊（由於結構體的記憶體結構決定，要是加了的話將不能正確讀取檔案資訊）  

typedef struct tagBITMAPFILEHEADER {
	DWORD  bfSize;          //檔案大小  
	WORD   bfReserved1;     //保留字，不考慮  
	WORD   bfReserved2;     //保留字，同上  
	DWORD  bfOffBits;       //實際點陣圖資料的偏移位元組數，即前三個部分長度之和  
} BITMAPFILEHEADER;

//資訊頭BITMAPINFOHEADER，也是一個結構，其定義如下：  

typedef struct tagBITMAPINFOHEADER {
	//public:  
	DWORD   biSize;             //指定此結構體的長度，為40  
	LONG    biWidth;            //點陣圖寬  
	LONG    biHeight;           //點陣圖高  
	WORD    biPlanes;           //平面數，為1  
	WORD    biBitCount;         //採用顏色位數，可以是1，2，4，8，16，24，新的可以是32  
	DWORD   biCompression;      //壓縮方式，可以是0，1，2，其中0表示不壓縮  
	DWORD   biSizeImage;        //實際點陣圖資料佔用的位元組數  
	LONG    biXPelsPerMeter;    //X方向解析度  
	LONG    biYPelsPerMeter;    //Y方向解析度  
	DWORD   biClrUsed;          //使用的顏色數，如果為0，則表示預設值(2^顏色位數)  
	DWORD   biClrImportant;     //重要顏色數，如果為0，則表示所有顏色都是重要的  
} BITMAPINFOHEADER;

void main()
{
	long now = 0;
	now = clock();//儲存影象處理開始時間  

	BITMAPFILEHEADER bitHead, writebitHead;
	BITMAPINFOHEADER bitInfoHead, writebitInfoHead;
	FILE* pfile;//輸入檔案  
	FILE* wfile;//輸出檔案  

	char strFile[50] = "demo.bmp";//開啟影象路徑，BMP影象必須為24位真彩色格式  
	char strFilesave[50] = "16.bmp";//處理後圖像儲存路徑  
	fopen_s(&pfile, strFile, "rb");//檔案開啟影象  
	fopen_s(&wfile, strFilesave, "wb");//開啟檔案為儲存修改後影象做準備  
									   //讀取點陣圖檔案頭資訊  
	WORD fileType;
	fread(&fileType, 1, sizeof(WORD), pfile);
	fwrite(&fileType, 1, sizeof(WORD), wfile);
	if (fileType != 0x4d42)
	{
		printf("file is not .bmp file!");
		return;
	}
	//讀取點陣圖檔案頭資訊  
	fread(&bitHead, 1, sizeof(tagBITMAPFILEHEADER), pfile);
	writebitHead = bitHead;//由於擷取影象頭和原始檔頭相似，所以先將原始檔頭資料賦予擷取檔案頭  
						   //讀取點陣圖資訊頭資訊  
	fread(&bitInfoHead, 1, sizeof(BITMAPINFOHEADER), pfile);
	writebitInfoHead = bitInfoHead;//同位圖檔案頭相似  

	writebitInfoHead.biHeight = MYDRAW_HEIGHT;//為擷取檔案重寫點陣圖高度  
	writebitInfoHead.biWidth = MYDRAW_WIDTH;//為擷取檔案重寫點陣圖寬度  
	int mywritewidth = WIDTHBYTES(writebitInfoHead.biWidth*writebitInfoHead.biBitCount);//BMP影象實際點陣圖資料區的寬度為4byte的倍數，在此計算實際資料區寬度  
	writebitInfoHead.biSizeImage = mywritewidth*writebitInfoHead.biHeight;//計算點陣圖實際資料區大小  

	writebitHead.bfSize = 54 + writebitInfoHead.biSizeImage;//點陣圖檔案頭大小為點陣圖資料區大小加上54byte  
	fwrite(&writebitHead, 1, sizeof(tagBITMAPFILEHEADER), wfile);//寫回點陣圖檔案頭資訊到輸出檔案  
	fwrite(&writebitInfoHead, 1, sizeof(BITMAPINFOHEADER), wfile);//寫回點陣圖資訊頭資訊到輸出檔案  

	int width = bitInfoHead.biWidth;
	int height = bitInfoHead.biHeight;
	//分配記憶體空間把源圖存入記憶體     
	int l_width = WIDTHBYTES(width*bitInfoHead.biBitCount);//計算點陣圖的實際寬度並確保它為4byte的倍數  
	int write_width = WIDTHBYTES(writebitInfoHead.biWidth*writebitInfoHead.biBitCount);//計算寫點陣圖的實際寬度並確保它為4byte的倍數  

	BYTE    *pColorData = (BYTE *)malloc(height*l_width);//開闢記憶體空間儲存影象資料  
	memset(pColorData, 0, height*l_width);

	BYTE    *pColorDataMid = (BYTE *)malloc(mywritewidth*MYDRAW_HEIGHT);//開闢記憶體空間儲存影象處理之後資料  
	memset(pColorDataMid, 0, mywritewidth*MYDRAW_HEIGHT);

	long nData = height*l_width;
	long write_nData = mywritewidth*MYDRAW_HEIGHT;//擷取的點陣圖資料區長度定義  

												  //把點陣圖資料資訊讀到數組裡     
	fread(pColorData, 1, nData, pfile);//影象處理可通過操作這部分資料加以實現  

	/*******************影象處理部分******************/
	/*******************雙線性插值******************/
	for (int hnum = 0; hnum < MYDRAW_HEIGHT; hnum++)
		for (int wnum = 0; wnum < MYDRAW_WIDTH; wnum++)
		{
			double d_original_img_hnum = hnum*height / (double)MYDRAW_HEIGHT;
			double d_original_img_wnum = wnum*width / (double)MYDRAW_WIDTH;
			int i_original_img_hnum = d_original_img_hnum;
			int i_original_img_wnum = d_original_img_wnum;
			double distance_to_a_x = d_original_img_wnum - i_original_img_wnum;//在原影象中與a點的水平距離  
			double distance_to_a_y = d_original_img_hnum - i_original_img_hnum;//在原影象中與a點的垂直距離  

			int original_point_a = i_original_img_hnum*l_width + i_original_img_wnum * 3;//陣列位置偏移量，對應於影象的各畫素點RGB的起點,相當於點A    
			int original_point_b = i_original_img_hnum*l_width + (i_original_img_wnum + 1) * 3;//陣列位置偏移量，對應於影象的各畫素點RGB的起點,相當於點B  
			int original_point_c = (i_original_img_hnum + 1)*l_width + i_original_img_wnum * 3;//陣列位置偏移量，對應於影象的各畫素點RGB的起點,相當於點C   
			int original_point_d = (i_original_img_hnum + 1)*l_width + (i_original_img_wnum + 1) * 3;//陣列位置偏移量，對應於影象的各畫素點RGB的起點,相當於點D   
			if (i_original_img_hnum +1== MYDRAW_HEIGHT - 1)
			{
				original_point_c = original_point_a;
				original_point_d = original_point_b;
			}
			if (i_original_img_wnum +1== MYDRAW_WIDTH - 1)
			{
				original_point_b = original_point_a;
				original_point_d = original_point_c;
			}

			int pixel_point = hnum*write_width + wnum * 3;//對映尺度變換影象陣列位置偏移量  
			pColorDataMid[pixel_point] =
				pColorData[original_point_a] * (1 - distance_to_a_x)*(1 - distance_to_a_y) +
				pColorData[original_point_b] * distance_to_a_x*(1 - distance_to_a_y) +
				pColorData[original_point_c] * distance_to_a_y*(1 - distance_to_a_x) +
				pColorData[original_point_c] * distance_to_a_y*distance_to_a_x;
			pColorDataMid[pixel_point + 1] =
				pColorData[original_point_a + 1] * (1 - distance_to_a_x)*(1 - distance_to_a_y) +
				pColorData[original_point_b + 1] * distance_to_a_x*(1 - distance_to_a_y) +
				pColorData[original_point_c + 1] * distance_to_a_y*(1 - distance_to_a_x) +
				pColorData[original_point_c + 1] * distance_to_a_y*distance_to_a_x;
			pColorDataMid[pixel_point + 2] =
				pColorData[original_point_a + 2] * (1 - distance_to_a_x)*(1 - distance_to_a_y) +
				pColorData[original_point_b + 2] * distance_to_a_x*(1 - distance_to_a_y) +
				pColorData[original_point_c + 2] * distance_to_a_y*(1 - distance_to_a_x) +
				pColorData[original_point_c + 2] * distance_to_a_y*distance_to_a_x;

		}
	/*******************雙線性插值******************/
	/*******************影象處理部分******************/

	fwrite(pColorDataMid, 1, write_nData, wfile);   //將處理完影象資料區寫回檔案  
	fclose(pfile);
	fclose(wfile);

	printf("影象處理完成\n");
	printf("執行時間為：%dms\n", int(((double)(clock() - now)) / CLOCKS_PER_SEC * 1000));//輸出影象處理花費時間資訊  
}
