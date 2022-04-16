#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

int Lastnumber[]={0,0,0,0,0,0,0,0,0,0};    //Bu dizi son rakamlarin hangisinden kac tane oldugunu tutuyor 0.index sonu 0 ile biten kac sayi var onu tutuyor  vb

struct student{
	
	int number;
	char name[20];
	char surname[20];
	struct student *next;
	
};     

struct student *first = NULL;   
struct student *last = NULL;
struct student *gecici = NULL;                          

void showList(){                   		   //Anlik listeyi gosteren fonksiyon
	struct student *show;
	show=first;
	for(;show!=NULL;show=show->next)
		printf("%d - %s - %s\n",show->number,show->name,show->surname);
}

int addStudent(){                    // ogrenci ekleme fonksiyonu
	
	last->next= (struct student*) malloc(1*sizeof(struct student));
	last = last->next;
	last->next = NULL;
	printf("Ogrenci kayit ekleme:\n----------------------------------\n");	
	printf("Nu: "); scanf("%d",&last->number); 
	printf("Name: "); scanf("%s",last->name); 
	printf("Surname: "); scanf("%s",last->surname);
			
	printf("Ogrenci Kayit edilmistir.\n");
	return last->number%10;
}

int searchStudent(int searchNumber){                  //aranacak olan ogrencinin numarasini alan fonksiyon ogrenciyi ariyor listede
	
	int sayac=1;
	for(gecici=first;gecici!=NULL;gecici=gecici->next,sayac++){
		if(gecici->number==searchNumber) {
			printf("!!!! %d - %d ",gecici->number,searchNumber);
			return sayac;
		}
	}
	if(sayac==1) return 0;
	
}

void deleteStudent(int searchNumber){                //silinecek olan ogrenci numarasini parametle olarak alan foksniyon
	
	struct student *temp;
	gecici=first;
	
	for(;gecici!=NULL;gecici=gecici->next){
		if(first->number == searchNumber) {
			temp=first;
			first=gecici->next;
			free(temp);
			printf("Ogrenci Silinmistir .\n");
			break;
		}
		else if (gecici->next->number == searchNumber){
			if(gecici->next->next==NULL)    last=gecici;          //burada son elemani sildigimizde last degiskeni son elemanin referansini tuttugu icin gecici=lat yaptim

			temp=gecici->next;
			gecici->next = gecici->next->next;
			free(temp);
			printf("Ogrenci Silinmistir .\n");
			break;
		}	
	}
}

void addlastnumber(int rakam){                   //burda ogrenci eklendiginde listeye sonra rakamini alip o rakamin listedeki sayisini arttirir	
		for(int i=0;i<10;i++){
			if(i==rakam) Lastnumber[i]++;
		}
}

void removelastnumber(int rakam){                //burda ogrenci silindiginde silinen ogrenci numarasinin son rakaminin listedeki toplam sayisini azaltma fonksiyonu
	for(int i=0;i<10;i++){
			if(i==rakam) Lastnumber[i]--;
		}
}

void organizing(){                              //son rakami listede fazla olan elemani basa koyacak sekilde siralama kodu
	
	int sonrakam,sonrakam2;
	struct student *tutucu;
	
	tutucu=(struct student*) malloc(sizeof(struct student));
	gecici=first;
	while(gecici->next!=NULL){
		
		sonrakam=gecici->number%10; sonrakam2=gecici->next->number%10;    //burda siralarken karsilastirilen elemanlarin numarasinin son rakamini aliyorum
		printf("");
		for(int i=0;i<10;i++){
			if(i==sonrakam) sonrakam=Lastnumber[i];
		}
			 
		for(int i=0;i<10;i++){
			if(i==sonrakam2) sonrakam2=Lastnumber[i];
		}

  		   if(sonrakam<sonrakam2){                         //burda karsilastirma yapip yerlerini degistiriyorum 

  		   		tutucu->number=gecici->number;
  		   		strcpy(tutucu->name,gecici->name);
  		   		strcpy(tutucu->surname,gecici->surname);
  		   		
  		   		gecici->number=gecici->next->number;
  		   		strcpy(gecici->name,gecici->next->name);
  		   		strcpy(gecici->surname,gecici->next->surname);
  		   		
  		   		gecici->next->number=tutucu->number;
  		   		strcpy(gecici->next->name,tutucu->name);
  		   		strcpy(gecici->next->surname,tutucu->surname);
  		   		
				gecici=first;
			 }
			 else gecici=gecici->next;
		}
}


int main(){
	
	FILE *fp = fopen("List.txt","w");                 //onceden olusmus gibi acilan text dosyasi
	 
	fprintf(fp,"53 Ali Eksioglu\n");
	fprintf(fp,"3130 Emin Azimaltin\n");
	fprintf(fp,"105 Batuhan Cicek\n");
	fprintf(fp,"55 Osman Eksioglu\n");
	fclose(fp);
	
	FILE *gp = fopen("List.txt","r");                 
	
	for(int i=0;i<4;i++){                            //listede 4 eleman oldugu icin 4 defa donen bir dongu
		
		int numbertutucu;   
		char nametutucu[20];
		char surnametutucu[20];
		
		if(first==NULL){
			
			first = (struct student*) malloc(sizeof(struct student));
			fscanf(gp,"%d",&numbertutucu);fscanf(gp,"%s",nametutucu);fscanf(gp,"%s",surnametutucu);

			first->number=numbertutucu;
			strcpy(first->name,nametutucu);
			strcpy(first->surname,surnametutucu);
			first->next = NULL;
			last=first;
			addlastnumber(numbertutucu%10);               //Eklenecek olan kissin numarasinin son numarasi hangi rakam oldugunu kayit ediyorum
			organizing(); 								//listeyi numarasinin son rakaminin sayisi fazla olucak sekilde duzenleme yapiliyor
		}
		else{
			
			last->next= (struct student*) malloc(sizeof(struct student));
			last = last->next;

			fscanf(gp,"%d",&numbertutucu);  fscanf(gp,"%s",nametutucu);  fscanf(gp,"%s",surnametutucu);
			last->number=numbertutucu;
			strcpy(last->name,nametutucu);
			strcpy(last->surname,surnametutucu);
			
			last->next = NULL;
			addlastnumber(numbertutucu%10);            //Eklenecek olan kissin numarasinin son rakamini listedeki sayisini arttiriyorum
			organizing(); 								//listeyi numarasinin son rakaminin sayisi fazla olucak sekilde duzenleme yapiliyor
		}
	}

	fclose(gp);
	
	while(1){
		
		int cevap=0;
		
		printf("\nNe yapmak isterseniz numarasini yaziniz\n"); 
		printf("1-)Listeye ogrenci eklemek\n2-)Listeden ogrenci cikarma\n3-)Listede ogrenci numarasi ile arama\n4-)Listeyi goster\n5-)Cikis\n");
		scanf("%d",&cevap); printf("\n");
		
		switch (cevap)                 //bir menu olusturdum
		{ 
			case 1:{
				addlastnumber(addStudent());
				organizing();
				getch(); system("CLS");
				break;
			}
			case 2:{
				int searchNumber,kontrol;           
				printf("Silinecek olan ogrenci numarasi:"); scanf("%d",&searchNumber);
                     
				if(searchStudent(searchNumber)!=0){				//silinecek ogrenci numarasini listede varmi kontrol ediliyor deger 0 dan farklý dondururse bulunmustur dondurmezse bulamamistir
					deleteStudent(searchNumber);                  //sonra silinecek numara siliyor
					removelastnumber(searchNumber%10);			  //silinen numaranin son rakaminin genel listedeki sayisi 1 azaltiliyor 
					organizing();                                 //ve liste tekrardan duzenleniyor
				}
				else printf("Aradiginiz numara bulunamadi..!"); 
				getch(); system("CLS");
				break;
			}
			case 3:{
				int searchNumber,kontrol;
				printf("Aranacak ogrenci numarasi: ");  scanf("%d",&searchNumber);
				kontrol=searchStudent(searchNumber);
				if(kontrol!=0) {
					printf("\nAradiginiz kisi %d adimda bulundu:\n",kontrol);
					printf("%d %s %s \n",gecici->number,gecici->name,gecici->surname);
				}
				
				else printf("Aradiginiz numara ile bir kayit bulunamadi..!\n");
				getch(); system("CLS");
				break;
			}
			case 4:{
				showList();
				getch(); system("CLS");
				break; 
			}
			case 5:{
				printf("\nCikis yapildi..!");
				FILE *yaz = fopen("List.txt","w");
				gecici=first;
				for(;gecici!=NULL;gecici=gecici->next){
					fprintf(yaz,"%d %s %s\n",gecici->number,gecici->name,gecici->surname); //son halini txt dosyasina yazzdiriyorum
				}
				exit(0);
				break;
			}
			default: {
				printf("Gecersiz islem");
				exit(0);
				break;
			}
		}
	}
	
	return 0;
 }		

