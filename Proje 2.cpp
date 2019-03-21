#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/time.h>

#define ING_UZ 37
#define TR_UZ 90
#define KAYDIR 127
#define SATIR 5721
#define UYUM 35

int Hash(char* key,int TABLO_BOYUTU)
{
	int sum=0;
	
 	for(int i=0;i<ING_UZ;i++)
 	{
 		sum=sum+key[i];
 	}
 	
  	sum=sum%TABLO_BOYUTU;	//Tablo büyüklüðü kadar modunu al.
  	return sum;
}

int dou_Hash(char *key,int TABLO_BOYUTU)
{
	int sum=0;
	
	for(int i=0;i<ING_UZ;i++)
 	{
 		sum=sum+key[i];
 	}
	
	TABLO_BOYUTU=TABLO_BOYUTU-7;	//Ikinci hash için rastgele bir asal sayi seçip, tablo boyutundan çýkardýk.
	
	sum=TABLO_BOYUTU-(sum%TABLO_BOYUTU);
	return sum;
}

int TabloBoyutuGir()
{
	int boyut;
	printf("HASH TABLOSUNUN BOYUTUNU GIRINIZ: ");
	scanf("%d",&boyut);
	
	return boyut;
}

 	FILE *soz,*lin,*qua,*dou,*sor;
	char ingilizce[SATIR][ING_UZ];
	char turkce[SATIR][TR_UZ];
 	int Adr;
 	int Temp;
	char c;
	clock_t basla,bitir;

void LineerRelativeOlustur(int TABLO_BOYUTU)
{
	long int boyut;
	int cakisma=0;
	basla=clock();
	//LÝNEER RELATÝVE OLUÞTURMA	
 	soz = fopen("sozluk.txt", "r");
	lin = fopen("lineer.txt", "w+");
	
	for(int i=0;i<TABLO_BOYUTU;i++)
	{
		fseek(lin,i*KAYDIR,0);
		fputc('*',lin);
	}

	for(int i=0;i<SATIR;i++)
	{
		int sayac=0;
		
		fgets(ingilizce[i],ING_UZ,soz);
		fgets(turkce[i],TR_UZ,soz);
		
		for(int j=0;j<TR_UZ;j++)
		{
			if(turkce[i][j]!=10 && turkce[i][j+1]!=0)
			sayac++;
		}
		
		Adr=Hash(ingilizce[i],TABLO_BOYUTU);	//hash fonksiyonundan gelen tablo deðerini Adr deðiþkenine atar.
		fseek(lin,Adr*KAYDIR,0);	//lineer metin belgesindeki imlecin yerini Adr*KAYDIR karakter kadar kaydýrýr.
		c=fgetc(lin);			//bir sonraki karakteri okur ve int olarak c deðiþkeninde saklar.
		
		Temp=Adr;				//Adr deðiþkenindeki deðeri Temp'e atar.
		
		while(c!='*')
		{
			
			Adr=(Adr+1)%TABLO_BOYUTU;		//Adr deðiþkenini 1'er arttýrarak tablo oluþturur.
			cakisma++;
			
			if(Adr==Temp)
			{
				printf("TABLO DOLU !\n");
				break;
			}
			
			fseek(lin,Adr*KAYDIR,0);	//tablodaki satýr dolu olduðundan baþka bir satýra yazmak için lineer metin belgesini Adr*KAYDIR karakter kadar kaydýrýr.
			c=fgetc(lin);			//bir sonraki karakteri okur ve int olarak c deðiþkeninde saklar.
			
		}
		
		fseek(lin,Adr*KAYDIR,0);		//lineer metin belgesindeki imlecin yerini Adr*45 karakter kadar kaydýrýr.
		fprintf(lin,"%s",ingilizce[i]);			//ingilizce dizisindeki kelimeyi lineer.txt dosyasýna yazar.
		for(int a=0;a<sayac;a++)		//turkce dizisindeki kelimeyi lineer.txt dosyasýna yazar.
		fprintf(lin,"%c",turkce[i][a]);
	}
	
	printf("\n\n LINEER DOSYA OLUSTURULDU \n\n");
	
	fclose(soz);
	fclose(lin);
	
	bitir=clock();
	
	printf(" TABLO BOYUTU      : %d satir\n",TABLO_BOYUTU);
	//DOSYA BOYUTU HESAPLAMA
	lin=fopen("lineer.txt", "r");
	fseek(lin,0L,SEEK_END);
	boyut=ftell(lin);
	fseek(lin,0L,SEEK_SET);
	
	printf(" DOSYA BOYUTU      : %ld byte\n",boyut);
	fclose(lin);
	//CAKISMA SAYISINI EKRANA YAZAR
	printf(" CAKISMA SAYISI    : %d\n",cakisma);
	//DOSYA OLUÞUM SÜRESÝNÝ EKRANA YAZAR
	printf(" OLUSTURULMA SURESI: %d.%d saniye\n",(bitir-basla)/1000,(bitir-basla)%1000);
	
	printf("\n-------------------------------------------------------------------------------\n");
}

void LineerKelimeSorgula(int TABLO_BOYUTU)
{
	lin = fopen("lineer.txt","r");
	
	char sorgu[ING_UZ];
	char lin_ing[TABLO_BOYUTU][ING_UZ];
	char lin_tr[TABLO_BOYUTU][TR_UZ];
	int kontrol=0;
	
	for(int i=0;i<ING_UZ;i++)
	{
		sorgu[i]=' ';
	}
	
	printf("Aranacak kelimeyi giriniz: ");
	gets(sorgu);
	gets(sorgu);
	
	int Adres=Hash(sorgu,TABLO_BOYUTU);
	
	fseek(lin,Adres*KAYDIR,0);
	fgets(lin_ing[0],ING_UZ,lin);
	fgets(lin_tr[0],TR_UZ,lin);
	
	for(int i=0;i<ING_UZ;i++)
	{
		if(sorgu[i]==lin_ing[0][i])
		kontrol++;
	}
	
	if(kontrol>=UYUM)
	{
		printf("\n%s kelimesinin karsiligi: %s\n",sorgu,lin_tr[0]);
	}
	else
	{
		for(int i=0;i<TABLO_BOYUTU;i++)
		{
			kontrol=0;
			Adres=(Adres+1)%TABLO_BOYUTU;
			fseek(lin,Adres*KAYDIR,0);
			fgets(lin_ing[i+1],ING_UZ,lin);
			fgets(lin_tr[i+1],TR_UZ,lin);
	
			for(int j=0;j<ING_UZ;j++)
			{
	 		 		if(sorgu[j]==lin_ing[i+1][j])
	 				kontrol++;
			}  
			
			if(kontrol>=UYUM)
			{
			 printf("\n\tKELIME BULUNDU.\n");
   			 printf("\n%s kelimesinin karsiligi: %s\n",sorgu,lin_tr[i+1]);
   			 break;
  			}
		}
		
		if(kontrol!=UYUM && kontrol<UYUM)
		printf("\nAradiginiz kelime bu sozlukte bulunmamaktadir.\n");
	}

	fclose(lin);
	
	printf("\n-------------------------------------------------------------------------------\n");
}

void LineerKelimeEkle(int TABLO_BOYUTU)
{
	lin=fopen("lineer.txt","r+");
	
	char karakter;
	char lin_ing[ING_UZ];
	char lin_tr[TR_UZ];
	int kontrol,Adres;
	
	for(int i=0;i<ING_UZ;i++)
	{
		lin_ing[i]=' ';
	}
	
	printf("\nEklemek istediginiz ingilizce kelimeyi girin: ");
	gets(lin_ing);
	gets(lin_ing);
	printf("Eklemek istediginiz turkce kelimeyi girin: ");
	gets(lin_tr);
	
	Adres=Hash(lin_ing,TABLO_BOYUTU);
	fseek(lin,(Adres*KAYDIR),0);
	karakter=fgetc(lin);
	kontrol=Adres;
	
	while(karakter!='*')
	{
		Adres=(Adres+1)%TABLO_BOYUTU;		//Adr deðiþkenini 1'er arttýrarak tablo oluþturur.
		
		if(Adres==kontrol)
		{
			printf("\n KELIME EKLENEMEDI - TABLO DOLU !\n\n");
			goto tablo_dolu;
		}
		
		fseek(lin,Adres*KAYDIR,0);	//tablodaki satýr dolu olduðundan baþka bir satýra yazmak için lineer metin belgesini Adr*KAYDIR karakter kadar kaydýrýr.
		karakter=fgetc(lin);		//bir sonraki karakteri okur ve int olarak c deðiþkeninde saklar.
	}
	
	fseek(lin,(Adres*KAYDIR),0);
	for(int x=0;x<ING_UZ-1;x++)
	fprintf(lin,"%c",lin_ing[x]);
	fprintf(lin,"%s",lin_tr);
	
	printf("\n KELIME TABLONUN %d. SATIRINA BASARIYLA EKLENDI.\n",Adres);
	
	tablo_dolu:
	
	fclose(lin);
	
	printf("\n-------------------------------------------------------------------------------\n");
}

void LineerKelimeSil(int TABLO_BOYUTU)
{
	lin = fopen("lineer.txt","r+");
	
	char sorgu[ING_UZ];
	char silme[KAYDIR];
	char lin_ing[TABLO_BOYUTU][ING_UZ];
	char lin_tr[TABLO_BOYUTU][TR_UZ];
	int kontrol=0;
	
	for(int i=0;i<ING_UZ;i++)
	{
		sorgu[i]=' ';
	}
	
	for(int i=0;i<KAYDIR;i++)
	{
		if(i==0)
		silme[i]='*';
		else
		silme[i]=' ';
	}
	
	printf("Silinecek ingilizce kelimeyi giriniz: ");
	gets(sorgu);
	gets(sorgu);
	
	int Adres=Hash(sorgu,TABLO_BOYUTU);
	
	fseek(lin,Adres*KAYDIR,0);
	fgets(lin_ing[0],ING_UZ,lin);
	fgets(lin_tr[0],TR_UZ,lin);
	
	for(int i=0;i<ING_UZ;i++)
	{
		if(sorgu[i]==lin_ing[0][i])
		kontrol++;
		
	}
	
	if(kontrol>=UYUM)
	{
		fseek(lin,Adres*KAYDIR,0);
		for(int x=0;x<KAYDIR;x++)
		fprintf(lin,"%c",silme[x]);
		
		printf("\n TABLONUN %d. SATIRINDA SILME ISLEMI GERCEKLESTI.\n",Adres);
	}
	else
	{
		for(int i=0;i<TABLO_BOYUTU;i++)
		{
			kontrol=0;
			Adres=(Adres+1)%TABLO_BOYUTU;
			fseek(lin,Adres*KAYDIR,0);
			fgets(lin_ing[i+1],ING_UZ,lin);
			fgets(lin_tr[i+1],TR_UZ,lin);
	
			for(int j=0;j<ING_UZ;j++)
			{
	 		 		if(sorgu[j]==lin_ing[i+1][j])
	 				kontrol++;
			} 
			
			if(kontrol>=UYUM)
			{
				fseek(lin,Adres*KAYDIR,0);
		  		for(int x=0;x<KAYDIR;x++)
				fprintf(lin,"%c",silme[x]);
		
				printf("\n TABLONUN %d. SATIRINDA SILME ISLEMI GERCEKLESTI.\n",Adres);
				break;
  			}
		}
		
		if(kontrol!=UYUM && kontrol<UYUM)
		printf("\nAradiginiz kelime bu sozlukte bulunmamaktadir.\n");
	}

	fclose(lin);
	
	printf("\n-------------------------------------------------------------------------------\n");
}

void QuadraticRelativeOlustur(int TABLO_BOYUTU)
{
	long int boyut;
	int cakisma=0;
	basla=clock();
	//QUADRATÝC RELATÝVE OLUÞTURMA
	soz = fopen("sozluk.txt", "r");
	qua = fopen("quadratic.txt", "w+");
	
	for(int i=0;i<TABLO_BOYUTU;i++)
	{
		fseek(qua,i*KAYDIR,0);
		fputc('*',qua);
	}
	
		for(int i=0;i<SATIR;i++)
	{
    	int sayac=0;
		
		fgets(ingilizce[i],ING_UZ,soz);
		fgets(turkce[i],TR_UZ,soz);
		
		for(int j=0;j<TR_UZ;j++)
		{
			if(turkce[i][j]!=10 && turkce[i][j+1]!=0)
			sayac++;
		}

		Adr = Hash(ingilizce[i],TABLO_BOYUTU);		
		fseek(qua,Adr*KAYDIR,0);  // okunan satýrý ilerletir bir sonrakine geçer
		c=fgetc(qua);
		
		Temp=Adr;
		int quad=1;
		
		while( c != '*')
		{
			Adr = (Adr+quad*quad) %TABLO_BOYUTU;
			cakisma++;
			
			if(Adr==Temp)
			{
				printf("TABLO DOLU ! \n");
				break;
			}

	    	fseek(qua,Adr*KAYDIR,0);	//tablodaki satýr dolu olduðundan baþka bir satýra yazmak için lineer metin belgesini Adr*KAYDIR karakter kadar kaydýrýr.
			c=fgetc(qua);			//bir sonraki karakteri okur ve int olarak c deðiþkeninde saklar.
			
			quad++;
		}
		
    	fseek(qua,Adr*KAYDIR,0);		//lineer metin belgesindeki imlecin yerini Adr*45 karakter kadar kaydýrýr.
		fprintf(qua,"%s",ingilizce[i]);			//ingilizce dizisindeki kelimeyi lineer.txt dosyasýna yazar.
		for(int a=0;a<sayac;a++)		//turkce dizisindeki kelimeyi lineer.txt dosyasýna yazar.
		fprintf(qua,"%c",turkce[i][a]);
	
	}
	
	printf("\n\n QUADRATIC DOSYA OLUSTURULDU \n\n");
	fclose(soz);
	fclose(qua);
	
	bitir=clock();
	
	printf(" TABLO BOYUTU      : %d satir\n",TABLO_BOYUTU);
	//DOSYA BOYUTU HESAPLAMA
	qua=fopen("quadratic.txt", "r");
	fseek(qua,0L,SEEK_END);
	boyut=ftell(qua);
	fseek(qua,0L,SEEK_SET);
	
	printf(" DOSYA BOYUTU      : %ld byte\n",boyut);
	fclose(qua);
	//CAKISMA SAYISINI EKRANA YAZAR
	printf(" CAKISMA SAYISI    : %d\n",cakisma);
	//DOSYA OLUÞUM SÜRESÝNÝ EKRANA YAZAR
	printf(" OLUSTURULMA SURESI: %d.%d saniye\n",(bitir-basla)/1000,(bitir-basla)%1000);
	
	printf("\n-------------------------------------------------------------------------------\n");
}

void QuadraticKelimeSorgula(int TABLO_BOYUTU)
{
	qua=fopen("quadratic.txt","r");
	
	char sorgu[ING_UZ];
	char qua_ing[TABLO_BOYUTU][ING_UZ];
	char qua_tr[TABLO_BOYUTU][TR_UZ];
	int kontrol=0;
	
	for(int i=0;i<ING_UZ;i++)
	{
		sorgu[i]=' ';
	}
	
	printf("Aranacak kelimeyi giriniz: ");
	gets(sorgu);
	gets(sorgu);
	
	int Adres=Hash(sorgu,TABLO_BOYUTU);
	
	fseek(qua,Adres*KAYDIR,0);
	fgets(qua_ing[0],ING_UZ,qua);
	fgets(qua_tr[0],TR_UZ,qua);
	
	for(int i=0;i<ING_UZ;i++)
	{
		if(sorgu[i]==qua_ing[0][i])
		kontrol++;
	}
	
	int quad=1;
	
	if(kontrol>=UYUM)
	{
		printf("\n%s kelimesinin karsiligi: %s\n",sorgu,qua_tr[0]);
	}
	else
	{
		for(int i=0;i<TABLO_BOYUTU;i++)
		{
			kontrol=0;
			Adres=(Adres+quad*quad)%TABLO_BOYUTU;
			
			fseek(qua,Adres*KAYDIR,0);
			fgets(qua_ing[i+1],ING_UZ,qua);
			fgets(qua_tr[i+1],TR_UZ,qua);
	
			for(int j=0;j<ING_UZ;j++)
			{
	 		 		if(sorgu[j]==qua_ing[i+1][j])
	 				kontrol++;
			}  
			
			if(kontrol>=UYUM)
			{
			 printf("\n\tKELIME BULUNDU.\n");
   			 printf("\n%s kelimesinin karsiligi: %s\n",sorgu,qua_tr[i+1]);
   			 break;
  			}
  			
  			quad++;
		}
		
		if(kontrol!=UYUM && kontrol<UYUM)
		printf("\nAradiginiz kelime bu sozlukte bulunmamaktadir.\n");
	}

	fclose(qua);
	
	printf("\n-------------------------------------------------------------------------------\n");
}

void QuadraticKelimeEkle(int TABLO_BOYUTU)
{
	qua=fopen("quadratic.txt","r+");
	
	char karakter;
	char qua_ing[ING_UZ];
	char qua_tr[TR_UZ];
	int kontrol,Adres;
	
	for(int i=0;i<ING_UZ;i++)
	{
		qua_ing[i]=' ';
	}
	
	printf("\nEklemek istediginiz ingilizce kelimeyi girin: ");
	gets(qua_ing);
	gets(qua_ing);
	printf("Eklemek istediginiz turkce kelimeyi girin: ");
	gets(qua_tr);
	
	Adres=Hash(qua_ing,TABLO_BOYUTU);
	fseek(qua,(Adres*KAYDIR),0);
	karakter=fgetc(qua);
	kontrol=Adres;
	int quad=1;
	
	while(karakter!='*')
	{
		Adres=(Adres+quad*quad) %TABLO_BOYUTU;
		
		if(Adres==kontrol)
		{
			printf("\n KELIME EKLENEMEDI - TABLO DOLU !\n\n");
			goto tablo_dolu;
		}
		
		fseek(qua,Adres*KAYDIR,0);	//tablodaki satýr dolu olduðundan baþka bir satýra yazmak için lineer metin belgesini Adr*KAYDIR karakter kadar kaydýrýr.
		karakter=fgetc(qua);		//bir sonraki karakteri okur ve int olarak c deðiþkeninde saklar.
		quad++;
	}
	
	fseek(qua,(Adres*KAYDIR),0);
	for(int x=0;x<ING_UZ-1;x++)
	fprintf(qua,"%c",qua_ing[x]);
	fprintf(qua,"%s",qua_tr);
	
	printf("\n KELIME TABLONUN %d. SATIRINA BASARIYLA EKLENDI.\n",Adres);
	
	tablo_dolu:
		
	fclose(qua);
	
	printf("\n-------------------------------------------------------------------------------\n");
}

void QuadraticKelimeSil(int TABLO_BOYUTU)
{
	qua=fopen("quadratic.txt","r+");
	
	char sorgu[ING_UZ];
	char silme[KAYDIR];
	char qua_ing[TABLO_BOYUTU][ING_UZ];
	char qua_tr[TABLO_BOYUTU][TR_UZ];
	int kontrol=0;
	
	for(int i=0;i<ING_UZ;i++)
	{
		sorgu[i]=' ';
	}
	
	for(int i=0;i<KAYDIR;i++)
	{
		if(i==0)
		silme[i]='*';
		else
		silme[i]=' ';
	}
	
	printf("Silinecek ingilizce kelimeyi giriniz: ");
	gets(sorgu);
	gets(sorgu);
	
	int Adres=Hash(sorgu,TABLO_BOYUTU);
	
	fseek(qua,Adres*KAYDIR,0);
	fgets(qua_ing[0],ING_UZ,qua);
	fgets(qua_tr[0],TR_UZ,qua);
	
	for(int i=0;i<ING_UZ;i++)
	{
		if(sorgu[i]==qua_ing[0][i])
		kontrol++;
	}
	
	int quad=1;
	
	if(kontrol>=UYUM)
	{
		fseek(qua,Adres*KAYDIR,0);
		for(int x=0;x<KAYDIR;x++)
		fprintf(qua,"%c",silme[x]);
		
		printf("\n TABLONUN %d. SATIRINDA SILME ISLEMI GERCEKLESTI.\n",Adres);
	}
	else
	{
		for(int i=0;i<TABLO_BOYUTU;i++)
		{
			kontrol=0;
			Adres=(Adres+quad*quad)%TABLO_BOYUTU;
			
			fseek(qua,Adres*KAYDIR,0);
			fgets(qua_ing[i+1],ING_UZ,qua);
			fgets(qua_tr[i+1],TR_UZ,qua);
	
			for(int j=0;j<ING_UZ;j++)
			{
	 		 		if(sorgu[j]==qua_ing[i+1][j])
	 				kontrol++;
			}  
			
			if(kontrol>=UYUM)
			{
			 fseek(qua,Adres*KAYDIR,0);
			 for(int x=0;x<KAYDIR;x++)
			 fprintf(qua,"%c",silme[x]);
		
			 printf("\n TABLONUN %d. SATIRINDA SILME ISLEMI GERCEKLESTI.\n",Adres);
   			 break;
  			}
  			
  			quad++;
		}
		
		if(kontrol!=UYUM && kontrol<UYUM)
		printf("\nAradiginiz kelime bu sozlukte bulunmamaktadir.\n");
	}

	fclose(qua);
	
	printf("\n-------------------------------------------------------------------------------\n");
}

void DoubleRelativeOlustur(int TABLO_BOYUTU)
{
	long int boyut;
	int cakisma=0;
	basla=clock();
	//DOUBLE RELATÝVE OLUÞTURMA
	soz = fopen("sozluk.txt", "r");
	dou = fopen("double.txt", "w+");
	
	for(int i=0;i<TABLO_BOYUTU;i++)
	{
		fseek(dou,i*KAYDIR,0);
		fputc('*',dou);
	}
	
	for(int i=0;i<SATIR;i++)
	{
	    int sayac=0;
		
		fgets(ingilizce[i],ING_UZ,soz);
		fgets(turkce[i],TR_UZ,soz);
		
		for(int j=0;j<TR_UZ;j++)
		{
			if(turkce[i][j]!=10 && turkce[i][j+1]!=0)
			sayac++;
		}

		Adr=Hash(ingilizce[i],TABLO_BOYUTU);
		fseek(dou,Adr*KAYDIR,0);  // okunan satýrý ilerletir bir sonrakine geçer
		c=fgetc(dou);
		
		Temp=Adr;
		
		int doub=1;
		
		while(c!='*')
		{
			Adr=Adr + ( doub*(dou_Hash(ingilizce[i],TABLO_BOYUTU)) );
			Adr=Adr%TABLO_BOYUTU;
			cakisma++;
			
			if(Adr==Temp)
			{
				printf("DOSYA DOLU ! \n");
				break;
			}

			fseek(dou,Adr*KAYDIR,0);	//tablodaki satýr dolu olduðundan baþka bir satýra yazmak için lineer metin belgesini Adr*KAYDIR karakter kadar kaydýrýr.
			c=fgetc(dou);			//bir sonraki karakteri okur ve int olarak c deðiþkeninde saklar.
			doub++;
		}	

		fseek(dou,Adr*KAYDIR,0);		//lineer metin belgesindeki imlecin yerini Adr*45 karakter kadar kaydýrýr.
		fprintf(dou,"%s",ingilizce[i]);			//ingilizce dizisindeki kelimeyi lineer.txt dosyasýna yazar.
		for(int a=0;a<sayac;a++)		//turkce dizisindeki kelimeyi lineer.txt dosyasýna yazar.
		fprintf(dou,"%c",turkce[i][a]);
	}
	
	printf("\n\n DOUBLE DOSYA OLUSTURULDU \n\n");
   	fclose(soz);
	fclose(dou);
	
	bitir=clock();
	
	printf(" TABLO BOYUTU      : %d satir\n",TABLO_BOYUTU);
	//DOSYA BOYUTU HESAPLAMA
	dou=fopen("double.txt", "r");
	fseek(dou,0L,SEEK_END);
	boyut=ftell(dou);
	fseek(dou,0L,SEEK_SET);
	
	printf(" DOSYA BOYUTU      : %ld byte\n",boyut);
	fclose(dou);
	//CAKISMA SAYISINI EKRANA YAZAR
	printf(" CAKISMA SAYISI    : %d\n",cakisma);
	//DOSYA OLUÞUM SÜRESÝNÝ EKRANA YAZAR
	printf(" OLUSTURULMA SURESI: %d.%d saniye\n",(bitir-basla)/1000,(bitir-basla)%1000);
	
	printf("\n-------------------------------------------------------------------------------\n");
}

void DoubleKelimeSorgula(int TABLO_BOYUTU)
{
	dou=fopen("double.txt","r");
	
	char sorgu[ING_UZ];
	char dou_ing[TABLO_BOYUTU][ING_UZ];
	char dou_tr[TABLO_BOYUTU][TR_UZ];
	int kontrol=0;
	
	for(int i=0;i<ING_UZ;i++)
	{
		sorgu[i]=' ';
	}
	
	printf("Aranacak kelimeyi giriniz: ");
	gets(sorgu);
	gets(sorgu);
	
	int Adres=Hash(sorgu,TABLO_BOYUTU);
	
	fseek(dou,Adres*KAYDIR,0);
	fgets(dou_ing[0],ING_UZ,dou);
	fgets(dou_tr[0],TR_UZ,dou);
	
	for(int i=0;i<ING_UZ;i++)
	{
		if(sorgu[i]==dou_ing[0][i])
		kontrol++;
	}
	
	int doub=1;
	
	if(kontrol>=UYUM)
	{
		printf("\n%s kelimesinin karsiligi: %s\n",sorgu,dou_tr[0]);
	}
	else
	{
		for(int i=0;i<TABLO_BOYUTU;i++)
		{
			kontrol=0;
			Adres=Adres + (doub*(dou_Hash(dou_ing[i],TABLO_BOYUTU)) );
			Adres=Adres%TABLO_BOYUTU;
			
			fseek(dou,Adres*KAYDIR,0);
			fgets(dou_ing[i+1],ING_UZ,dou);
			fgets(dou_tr[i+1],TR_UZ,dou);
	
			for(int j=0;j<ING_UZ;j++)
			{
	 		 		if(sorgu[j]==dou_ing[i+1][j])
	 				kontrol++;
			}  
			
			if(kontrol>=UYUM)
			{
			 printf("\n\tKELIME BULUNDU.\n");
   			 printf("\n%s kelimesinin karsiligi: %s\n",sorgu,dou_tr[i+1]);
   			 break;
  			}
  			
  			doub++;
		}
		
		if(kontrol!=UYUM && kontrol<UYUM)
		printf("\nAradiginiz kelime bu sozlukte bulunmamaktadir.\n");
	}

	fclose(dou);
	
	printf("\n-------------------------------------------------------------------------------\n");
}

void DoubleKelimeEkle(int TABLO_BOYUTU)
{
	dou=fopen("double.txt","r+");
	
	char karakter;
	char dou_ing[ING_UZ];
	char dou_tr[TR_UZ];
	int kontrol,Adres;
	
	for(int i=0;i<ING_UZ;i++)
	{
		dou_ing[i]=' ';
	}
	
	printf("\nEklemek istediginiz ingilizce kelimeyi girin: ");
	gets(dou_ing);
	gets(dou_ing);
	printf("Eklemek istediginiz turkce kelimeyi girin: ");
	gets(dou_tr);
	
	Adres=Hash(dou_ing,TABLO_BOYUTU);
	fseek(dou,(Adres*KAYDIR),0);
	karakter=fgetc(dou);
	kontrol=Adres;
	
	int doub=1;
	
	while(karakter!='*')
	{
		Adres=Adres + ( doub*(dou_Hash(dou_ing,TABLO_BOYUTU)) );
		Adres=Adres%TABLO_BOYUTU;
		
		if(Adres==kontrol)
		{
			printf("\n KELIME EKLENEMEDI - TABLO DOLU !\n\n");
			goto tablo_dolu;
		}
		
		fseek(dou,Adres*KAYDIR,0);	//tablodaki satýr dolu olduðundan baþka bir satýra yazmak için lineer metin belgesini Adr*KAYDIR karakter kadar kaydýrýr.
		karakter=fgetc(dou);		//bir sonraki karakteri okur ve int olarak c deðiþkeninde saklar.
		doub++;
	}
	
	fseek(dou,(Adres*KAYDIR),0);
	for(int x=0;x<ING_UZ-1;x++)
	fprintf(dou,"%c",dou_ing[x]);
	fprintf(dou,"%s",dou_tr);
	
	printf("\n KELIME TABLONUN %d. SATIRINA BASARIYLA EKLENDI.\n",Adres);
	
	tablo_dolu:
		
	fclose(dou);
	
	printf("\n-------------------------------------------------------------------------------\n");
}

void DoubleKelimeSil(int TABLO_BOYUTU)
{
	dou=fopen("double.txt","r+");
	
	char sorgu[ING_UZ];
	char silme[KAYDIR];
	char dou_ing[TABLO_BOYUTU][ING_UZ];
	char dou_tr[TABLO_BOYUTU][TR_UZ];
	int kontrol=0;
	
	for(int i=0;i<ING_UZ;i++)
	{
		sorgu[i]=' ';
	}
	
	for(int i=0;i<KAYDIR;i++)
	{
		if(i==0)
		silme[i]='*';
		else
		silme[i]=' ';
	}
	
	printf("Silinecek ingilizce kelimeyi giriniz: ");
	gets(sorgu);
	gets(sorgu);
	
	int Adres=Hash(sorgu,TABLO_BOYUTU);
	
	fseek(dou,Adres*KAYDIR,0);
	fgets(dou_ing[0],ING_UZ,dou);
	fgets(dou_tr[0],TR_UZ,dou);
	
	for(int i=0;i<ING_UZ;i++)
	{
		if(sorgu[i]==dou_ing[0][i])
		kontrol++;
	}
	
	int doub=1;
	
	if(kontrol>=UYUM)
	{
		fseek(dou,Adres*KAYDIR,0);
		for(int x=0;x<KAYDIR;x++)
		fprintf(dou,"%c",silme[x]);
		
		printf("\n TABLONUN %d. SATIRINDA SILME ISLEMI GERCEKLESTI.\n",Adres);
	}
	else
	{
		for(int i=0;i<TABLO_BOYUTU;i++)
		{
			kontrol=0;
			Adres=Adres + (doub*(dou_Hash(dou_ing[i],TABLO_BOYUTU)) );
			Adres=Adres%TABLO_BOYUTU;
			
			fseek(dou,Adres*KAYDIR,0);
			fgets(dou_ing[i+1],ING_UZ,dou);
			fgets(dou_tr[i+1],TR_UZ,dou);
	
			for(int j=0;j<ING_UZ;j++)
			{
	 		 		if(sorgu[j]==dou_ing[i+1][j])
	 				kontrol++;
			}  
			
			if(kontrol>=UYUM)
			{
			 fseek(dou,Adres*KAYDIR,0);
			 for(int x=0;x<KAYDIR;x++)
			 fprintf(dou,"%c",silme[x]);
		
			 printf("\n TABLONUN %d. SATIRINDA SILME ISLEMI GERCEKLESTI.\n",Adres);
   			 break;
  			}
  			
  			doub++;
		}
		
		if(kontrol!=UYUM && kontrol<UYUM)
		printf("\nAradiginiz kelime bu sozlukte bulunmamaktadir.\n");
	}

	fclose(dou);
	
	printf("\n-------------------------------------------------------------------------------\n");
}

void BonusSorgula()
{
	basla=clock();
	soz = fopen("sozluk.txt", "r");
	sor = fopen("sorgu.txt", "r");
	
	char kelime[ING_UZ];
	char sor_ing[2000][ING_UZ];
	char sor_tr[2000][TR_UZ];
	char soz_ing[5721][ING_UZ];
	char soz_tr[5721][TR_UZ];
	int sayac=0;
	
		for(int i=0;i<2000;i++)
	{
		fgets(sor_ing[i],ING_UZ,sor);
		fgets(sor_tr[i],TR_UZ,sor);
	}
		for(int i=0;i<5721;i++)
	{
		fgets(soz_ing[i],ING_UZ,soz);
		fgets(soz_tr[i],TR_UZ,soz);
	}
	
	for(int i=0;i<5721;i++)
	{
		for(int j=0;j<2000;j++)
		{
			if(strcmp(sor_ing[j],soz_ing[i])==0)
			{
			     sayac++;
				 break;
			}
		}
	}
	
	bitir=clock();
	
	printf("\n sorgu.txt dosyasinda bulunan 2000 kelimeden, \n %d'i sozluk.txt dosyasinda da bulunmakta.\n Kalan %d kelime sozluk.txt dosyasinda bulunamadi.\n",sayac,2000-sayac);
	
	//SORGU SÜRESÝNÝ EKRANA YAZAR
	printf("\n SORGULAMA SURESI: %d.%d saniye\n",(bitir-basla)/1000,(bitir-basla)%1000);
	
	printf("\n-------------------------------------------------------------------------------\n");
}

int RelativeOlustur(int TABLO_BOYUTU)
{
	int secim;
	
	do
	{
		
		printf(" \n");
		printf(" BAGIL DOSYA SEC \n");
		printf(" [1] LINEER \n");
		printf(" [2] QUADRATIC \n");
		printf(" [3] DOUBLE\n");
		printf(" [4] GERI\n");
		printf(" \n SECIMINIZ = ");
		scanf("%d",&secim);
		printf("\n\n");
		
		if(secim==1)
		{
		LineerRelativeOlustur(TABLO_BOYUTU);
		break;
		}
		if(secim==2)
		{
		QuadraticRelativeOlustur(TABLO_BOYUTU);
		break;
		}
		if(secim==3)
		{
		DoubleRelativeOlustur(TABLO_BOYUTU);
		break;
		}
		if(secim==4)
		{
		system("cls");
		break;
		}
		
	}while(1);
	
	return secim;
}

int main()
{
	int TABLO_BOYUTU=TabloBoyutuGir();
	int dosya_secimi=RelativeOlustur(TABLO_BOYUTU);
	int secim;
	
	int lineer_boyut,quad_boyut,double_boyut;
	
	switch(dosya_secimi)
	{
		case 1: lineer_boyut=TABLO_BOYUTU;
			 	break;
		case 2: quad_boyut=TABLO_BOYUTU;
			 	break;
		case 3: double_boyut=TABLO_BOYUTU;
			 	break;
	}

	do
	{

		printf(" \n");
		printf(" SOZLUK UYGULAMASI\n\n");
		printf(" [1] BAGIL DOSYA OLUSTUR \n");
		printf(" [2] KELIME SORGULA \n");
		printf(" [3] KELIME EKLE \n");
		printf(" [4] KELIME SIL \n");
		printf(" [5] CIKIS \n");
		printf(" \n SECIMINIZ = ");
		scanf("%d",&secim);
		printf("\n\n");
		
		switch(secim)
		{
			case 1: TABLO_BOYUTU=TabloBoyutuGir();
					dosya_secimi=RelativeOlustur(TABLO_BOYUTU);
					switch(dosya_secimi)
					{
					 case 1: lineer_boyut=TABLO_BOYUTU;
			 		 	  	 break;
					 case 2: quad_boyut=TABLO_BOYUTU;
			 		 	  	 break;
 				     case 3: double_boyut=TABLO_BOYUTU;
	   	  			  	     break;
 				    }
					break;
					
			case 2: int sorgu;
					printf(" [1] LINEER 	SORGU \n");
					printf(" [2] QUADRATIC 	SORGU \n");
					printf(" [3] DOUBLE 	SORGU \n");
					printf(" [4] BONUS      SORGU \n");
					printf(" \n SECIMINIZ = ");
					scanf("%d",&sorgu);
					printf("\n\n");
					switch(sorgu)
					{
						case 1: LineerKelimeSorgula(lineer_boyut);
								break;
						case 2: QuadraticKelimeSorgula(quad_boyut);
							 	break;
						case 3: DoubleKelimeSorgula(double_boyut);
							 	break;
				 	    case 4: BonusSorgula();
				 	    	 	break;
	 				    default: printf(" HATALI GIRIS !\n");
					}
					break;
					
			case 3: int ekle;
					printf(" [1] LINEER 	EKLE \n");
					printf(" [2] QUADRATIC 	EKLE \n");
					printf(" [3] DOUBLE 	EKLE \n");
					printf(" \n SECIMINIZ = ");
					scanf("%d",&ekle);
					printf("\n\n");
					switch(ekle)
					{
						case 1: LineerKelimeEkle(lineer_boyut);
							 	break;
				 	    case 2: QuadraticKelimeEkle(quad_boyut);
				 	    	 	break;
	   					case 3: DoubleKelimeEkle(double_boyut);
 							 	break;
	 				    default: printf(" HATALI GIRIS !\n");
					}
					break;
			
			case 4: int sil;
				 	printf(" [1] LINEER 	SIL \n");
					printf(" [2] QUADRATIC 	SIL \n");
					printf(" [3] DOUBLE 	SIL \n");
					printf(" \n SECIMINIZ = ");
					scanf("%d",&sil);
					printf("\n\n");
					switch(sil)
					{
						case 1: LineerKelimeSil(lineer_boyut);
							 	break;
	 				    case 2: QuadraticKelimeSil(quad_boyut);
	 				    	 	break;
			    	 	case 3: DoubleKelimeSil(double_boyut);
			    	 		 	break;
			    	 	default: printf(" HATALI GIRIS !\n");	 	
					}
					break;
					
			case 5: remove("lineer.txt");
				 	remove("quadratic.txt");
					remove("double.txt");
					return 0;
			
			default: printf(" HATALI GIRIS ! LUTFEN [1]-[2]-[3]-[4]-[5] GIRINIZ...\n");
		}
	}while(1);
}
