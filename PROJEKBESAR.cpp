#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
//Sistem Ojek daring terintegrasi dengan Uang Virtual

using namespace std;
struct account
{
	int id;
	char nama[40];
	char email[40];
	char nohp[15];
	char password[40];
	char norek[40];
	long saldo=0;
};

typedef struct
{
	int rating;
	int order;
	bool nyupir;
	struct account acc;	
}drivers;

typedef struct
{
	int order;
	struct account acc;
}consumers;

typedef struct
{
	char pengemudi[30];
	char penumpang[30];
	int cost;
	char asal[50];
	char tujuan[50];
	int jarak;
	char kendara[10];
}pesanan;

drivers driver[40];
consumers consumer[40];
pesanan pesan[100];
FILE *d;

int main();
void dashboarddriver(char* session);
void dashboarduser(char* session);
void findingdriver(int kendara, char* session);

void profile(char* subject, char* session)
{
	if(subject=="driver")
	{
		drivers driver[40];
		drivers temp;
		system("cls");
		printf("===================Halaman Profil Pengemudi===================");
		printf("\nID\tEmail\t\tNama\t\tNo. HP\t\tRating\tSaldo");
		d = fopen("driver.txt", "a+");
		int i=0;
		while (fread(&temp, sizeof(temp), 1, d))
		{
			driver[i] = temp;
			i++;
		}
		
		for(int j=0; j<i; j++)
		{
			if(strcmp(session, driver[j].acc.email)==0)
				printf("\n%d\t%s\t\t%s\t\t%s\t\t%d\t%d", driver[j].acc.id, driver[j].acc.email, driver[j].acc.nama, driver[j].acc.nohp, driver[j].rating, driver[j].acc.saldo);
		}	
		fclose(d);	
	}
	
	else if(subject=="customer")
	{
		consumers customer[40];
		consumers temp;
		system("cls");
		printf("===================Halaman Profil Penumpang===================");
		printf("\nID\tEmail\t\tNama\t\tNo. HP\tSaldo");
		FILE *qq;
		qq = fopen("consumer.txt", "a+");
		sleep(0);
		int i=0;
		while (fread(&temp, sizeof(temp), 1, qq))
		{
			customer[i] = temp;
			i++;
		}
		
		for(int j=0; j<i; j++)
		{
			if(strcmp(session, customer[j].acc.email)==0)
				printf("\n%d\t%s\t\t%s\t\t%s\t%d", customer[j].acc.id, customer[j].acc.email, customer[j].acc.nama, customer[j].acc.nohp, customer[j].acc.saldo);
		}		
		fclose(qq);
	}
	
	char balik[1];
	printf("\nKembali ? (y/n) :");
	scanf("%s", &balik);
	if(strcmp(strlwr(balik), "y")==0)
		subject == "driver" ? dashboarddriver(session) : dashboarduser(session);
}

void lihatorder(char* session)
{
	pesanan pesan[100];
	pesanan temp;
	system("cls");
	printf("===================Halaman Profil Pengemudi===================");
	printf("\n\t\tData Order Dengan Email : %s", session);
	printf("\n\nKonsumen\tBiaya\tAsal\tTujuan\tJarak\tJenis Kendaraan");
	d = fopen("order.txt", "a+");
	int i=0;
	while (fread(&temp, sizeof(temp), 1, d))
	{
		pesan[i] = temp;
		i++;
	}
		
	for(int j=0; j<i; j++)
	{
		if(strcmp(session, pesan[j].pengemudi)==0)
			printf("\n%s\tRp%d\t%s\t%s\t%d\t%s", pesan[j].penumpang, pesan[j].cost, pesan[j].asal, pesan[j].tujuan, pesan[j].jarak, pesan[j].kendara);
	}
	fclose(d);
	char balik[1];
	printf("\n\nKembali ? (y/n) :");
	scanf("%s", &balik);
	if(strcmp(strlwr(balik), "y")==0)
		dashboarddriver(session);
}

void read(char* status, char* session, int based)
{
	if(status=="driver")
	{
		drivers temp;
		drivers tmp;
		d = fopen("driver.txt", "a+");
		int i=0;
		while (fread(&temp, sizeof(temp), 1, d))
		{
			driver[i] = temp;
			i++;
		}
		
		for(int k=0; k<i-1; k++)
		{
			for(int j=0; j<i-1-k; j++)
			{
				if(based==1) //id
				{
					if(driver[j].acc.id>driver[j+1].acc.id)
					{
						tmp = driver[j];
						driver[j] = driver[j+1];
						driver[j+1] = tmp;
					}
				}
				
				else if(based==2) //rating
				{
					if(driver[j].rating>driver[j+1].rating)
					{
						tmp = driver[j];
						driver[j] = driver[j+1];
						driver[j+1] = tmp;
					}
				}
				
				else if(based==3) //nama
				{
					if(strcmp(driver[j].acc.email, driver[j+1].acc.email)>0)
					{
						tmp = driver[j];
						driver[j] = driver[j+1];
						driver[j+1] = tmp;
					}
				}
								
				else if(based==4) //nama
				{
					if(strcmp(driver[j].acc.nama, driver[j+1].acc.nama)>0)
					{
						tmp = driver[j];
						driver[j] = driver[j+1];
						driver[j+1] = tmp;
					}
				}
			}
		}
		fclose(d);
		printf("\nID\tEmail\t\tNama\t\tNo. HP\t\tRating");
		for(int j=0; j<i; j++)
		{
			printf("\n%d\t%s\t\t%s\t\t%s\t\t%d", driver[j].acc.id, driver[j].acc.email, driver[j].acc.nama, driver[j].acc.nohp, driver[j].rating);
		}
	}
	
	else if(status=="customer")
	{
		consumers temp;
		consumers tmp;
		d = fopen("consumer.txt", "a+");
		int i=0;
		while (fread(&temp, sizeof(temp), 1, d))
		{
			consumer[i] = temp;
			i++;
		}
		
		for(int k=0; k<i-1; k++)
		{
			for(int j=0; j<i-1-k; j++)
			{
				if(based==1) //id
				{
					if(consumer[j].acc.id>consumer[j+1].acc.id)
					{
						tmp = consumer[j];
						consumer[j] = consumer[j+1];
						consumer[j+1] = tmp;
					}
				}
				
				else if(based==2) //nohp
				{
					if(consumer[j].acc.nohp>consumer[j+1].acc.nohp)
					{
						tmp = consumer[j];
						consumer[j] = consumer[j+1];
						consumer[j+1] = tmp;
					}
				}
				
				else if(based==3) //nama
				{
					if(strcmp(consumer[j].acc.email, consumer[j+1].acc.email)>0)
					{
						tmp = consumer[j];
						consumer[j] = consumer[j+1];
						consumer[j+1] = tmp;
					}
				}
								
				else if(based==4) //nama
				{
					if(strcmp(consumer[j].acc.nama, consumer[j+1].acc.nama)>0)
					{
						tmp = consumer[j];
						consumer[j] = consumer[j+1];
						consumer[j+1] = tmp;
					}
				}
			}
		}
		fclose(d);
		printf("\nID\tEmail\t\tNama\t\tNo. HP");
		for(int j=0; j<i; j++)
		{
			printf("\n%d\t%s\t\t%s\t\t%s", consumer[j].acc.id, consumer[j].acc.email, consumer[j].acc.nama, consumer[j].acc.nohp);
		}
		
		char keyword[40];
		printf("\n\nCari nama driver : (ketik n untuk menghiraukan pesan) : ");
		cin.ignore(); cin.getline(keyword, sizeof(keyword));
		if(strcmp(strlwr(keyword), "n")==0)
		{
			system("cls"); dashboarduser(session);
		}
		
		else
		{
			printf("\nID\tEmail\t\tNama\t\tNo. HP");
			for(int j=0; j<i; j++)
			{
				if(strstr(consumer[j].acc.nama, keyword))
				{
					printf("\n%d\t%s\t\t%s\t\t%s", consumer[j].acc.id, consumer[j].acc.email, consumer[j].acc.nama, consumer[j].acc.nohp);
				}
			}
		}
		
	}
	
	char balik[1];
	printf("\n\nKembali ? (y/n) :");
	scanf("%s", &balik);
	if(strcmp(strlwr(balik), "y")==0)
		status=="driver" ? dashboarddriver(session) : dashboarduser(session);
}

void pilihsorting(char* status, char*session)
{
	int pilih;
	printf("=============================================================");
	if(status=="driver")
	{
		printf("\n1. Berdasarkan ID");
		printf("\n2. Berdasarkan Rating");
		printf("\n3. Berdasarkan Email");
		printf("\n4. Berdasarkan Nama");
	}
	
	else if(status=="customer")
	{
		printf("\n1. Berdasarkan ID");
		printf("\n2. Berdasarkan No. HP");
		printf("\n3. Berdasarkan Email");
		printf("\n4. Berdasarkan Nama");
	}
	printf("\nPilih : ");
	scanf("%d", &pilih);
	read(status, session, pilih);
}

void dashboarddriver(char* session)
{
	int pilih;
	system("cls");
	printf("===================Halaman Utama Pengemudi===================");
	printf("\n1. Lihat Profil");
	printf("\n2. Lihat Data Pesanan");
	printf("\n3. Lihat Seluruh Driver");
	printf("\n4. Cairkan Saldo");
	printf("\n5. Log Out");
	printf("\nPilih : ");
	scanf("%d", &pilih);
	switch(pilih)
	{
		case 1:
			profile("driver", session); break;
		case 2:
			lihatorder(session); break;
		case 3:
			pilihsorting("driver", session); break;
		case 4:
		//	cairkan("driver", session); break;
		case 5:
			system("cls"); main(); break;
	}
}

void findingdriver(int kendara, char* session)
{
	drivers driver[40];
	drivers temp;
	consumers tmp;
	consumers consumer[40];
	char asal[40], tujuan[40];
	int jarak, waktu, biaya;
	printf("Masukkan Tempat Asal : ");
	scanf("%s", &asal);
	printf("Masukkan Tempat Tujuan : ");
	scanf("%s", &tujuan);
	printf("Sedang mencari pengemudi...");
	sleep(3);
	system("cls");
	
	srand(time(0));
	jarak = (rand()%60);
	waktu = kendara == 1 ? 5*jarak : kendara == 2 ? 4*jarak : 3*jarak ;
	biaya = kendara == 1 ? 2300*jarak : kendara == 2 ? 3500*jarak : 5000*jarak;
	d = fopen("driver.txt", "a+");
	int i=0;
	while (fread(&temp, sizeof(temp), 1, d))
	{
		driver[i] = temp;
		i++;
	}
	
	fclose(d);
	
	char vehicle[30];
	if(kendara==1)
		strcpy(vehicle,"Motor");
	else if(kendara==2)
		strcpy(vehicle,"Mobil");
	else
		strcpy(vehicle,"Taksi");
		
	
	FILE *e;
	e = fopen("consumer.txt", "a+");
	int j=0;
	while (fread(&tmp, sizeof(tmp), 1, e))
	{
		consumer[j] = tmp;
		j++;
	}
	fclose(e);
	
	int k=0;
	while(k<j)
	{
		if(strcmp(consumer[k].acc.email, session)==0)
			j=0;
		k++;
	}
	
	int random = rand()%i;
	drivers drivermu = driver[random];
	printf("Selamat! Anda menemukan driver");
	printf("\n\nDetail Pesanan");
	printf("\n=================================================");
	printf("\nNama Driver\t: %s", drivermu.acc.nama);
	printf("\nAsal\t\t: %s", asal);
	printf("\nTujuan\t\t: %s", tujuan);
	printf("\nJarak\t\t: %dkm", jarak);
	printf("\nBiaya\t\t: Rp%d", biaya);
	if(waktu>=60)
		printf("\nEstimasi Sampai\t: %d jam %d menit", waktu/60, waktu%60);
	else
		printf("\nEstimasi Sampai\t: %d menit", waktu);
		
	printf("\nKendaraan\t: %s", vehicle);
	printf("\nSaldo Anda\t: Rp%d", consumer[k].acc.saldo);
	printf("\n=================================================");
	
		pesanan psn;
		strcpy(psn.pengemudi, drivermu.acc.nama);
		strcpy(psn.asal, asal);
		strcpy(psn.tujuan, tujuan);
		psn.jarak=jarak;
		strcpy(psn.kendara, vehicle);
		psn.cost=biaya;
		strcpy(psn.penumpang, consumer[k].acc.nama);
		FILE *z;
		z = fopen("order.txt", "a+");
		fwrite(&psn, sizeof(psn), 1, z);
		fclose(z);
		
		printf("\nKembali ke menu? (y/n) :");
		char balik[1];
		scanf("%s", &balik);
		if(strcmp(strlwr(balik),"y")==0)
		{
			system("cls"); dashboarduser(session);
		}
}

void bonceng(char* session)
{
	int pilih;
	system("cls");
	printf("Pilih Kendaraan");
	printf("\n1. Motor");
	printf("\n2. Mobil");
	printf("\n3. Taksi");
	printf("\nPilih : ");
	scanf("%d", &pilih);
	if(pilih>=1 and pilih<=3)
		findingdriver(pilih, session);
	else
		printf("Angka tidak valid");
}

void dashboarduser(char* session)
{
	int pilih;
	system("cls");
	printf("===================Halaman Utama Penumpang===================");
	printf("\n1. Mbonceng");
	printf("\n2. Lihat Profil");
	printf("\n3. Cari Data Penumpang");
	printf("\n4. Top Up");
	printf("\n5. Log Out");
	printf("\nPilih : ");
	scanf("%d", &pilih);
	switch(pilih)
	{
		case 1:
			bonceng(session); break;
		case 2:
			profile("customer", session); break;
		case 3:
			pilihsorting("customer", session); break;
		case 4:
			printf("\nSaat ini, menu Top UP masih dalam pengembangan"); break;
		case 5:
			system("cls"); main();
	}
}

void isLogin(char* subject, char* session)
{
	if(subject=="driver")
		dashboarddriver(session);
	else
		dashboarduser(session);
}

void AsDriver(char* status)
{
	system("cls");
	drivers temp;
	char file[30] = "driver.txt";
	
	if(status=="register") //register
	{
		drivers regis;
		printf("===================Daftar Sebagai Pengemudi===================");
		printf("\nEmail\t\t : ");
		scanf("%s", &regis.acc.email);
		printf("Password\t : ");
		scanf("%s", &regis.acc.password);
		printf("Nama\t\t : ");
		cin.ignore(); cin.getline(regis.acc.nama, sizeof(regis));
		printf("No. HP\t\t : ");
		scanf("%s", &regis.acc.nohp);	
		printf("No. Rekening\t : ");
		scanf("%s", &regis.acc.norek);	
		
		int i=0;
		d = fopen(file, "a+");
		while (fread(&temp, sizeof(temp), 1, d))
		{
			driver[i] = temp;
			i++;
		}
	
		bool exist=false;
		int j=0;
		while(j<i and !exist)
		{
			exist = strcmp(regis.acc.email, driver[j].acc.email)==0 ? true : false;
			j++;
		}
		
		regis.acc.id = i+1;
		if(!exist)
		{
			fwrite(&regis, sizeof(regis), 1, d);
			fclose(d);
			isLogin("driver", regis.acc.email);
		}
		else
			printf("Email telah terdaftar sebelumnya");
		
		char balik[1];
		printf("\n\nIngin coba lagi? (y/n) : ");
		scanf("%s", &balik);
		if(strcmp(strlwr(balik), "y")==0)
		{
			system("cls"); main();
		}
	}
	
	else
	{
		drivers tmp;
		drivers drive[40];
		char email[40], password[40];
		printf("===================Masuk Sebagai Pengemudi===================");
		printf("\nEmail\t : ");
		scanf("%s", &email);
		printf("Password : ");
		scanf("%s", &password);
		
		int i=0;
		d = fopen(file, "a+");
		int found = 0;
		while (fread(&tmp, sizeof(tmp), 1, d) == 1)
		{
			drive[i] = tmp;
			i++;
		}
		
		for(int j=0; j<i; j++)
		{
			if((strcmp(email, drive[j].acc.email)==0)) 
			{
				if (strcmp(password, drive[j].acc.password)==0)
					found = 2;
				else
					found = 1;
				j=i;
			}
		}
		
		if (found==2)
			isLogin("driver", email);
		else if(found==1)
			printf("password tidak sesuai");			
		else
			printf("Email tidak terdaftar");
		char balik[1];
		printf("\n\nIngin coba lagi? (y/n) : ");
		scanf("%s", &balik);
		if(strcmp(strlwr(balik), "y")==0)
		{
			system("cls"); main();
		}
	}
}

void AsUser(char* status)
{
	system("cls");
	consumers temp;
	char file[30] = "consumer.txt";
	
	if(status=="register") //register
	{
		consumers regis;
		printf("===================Daftar Sebagai Penumpang===================");
		printf("\nEmail\t\t : ");
		scanf("%s", &regis.acc.email);
		printf("Password\t : ");
		scanf("%s", &regis.acc.password);
		printf("Nama\t\t : ");
		cin.ignore(); cin.getline(regis.acc.nama, sizeof(regis));
		printf("No. HP\t\t : ");
		scanf("%s", &regis.acc.nohp);
		printf("No. Rekening\t : ");
		scanf("%s", &regis.acc.norek);	
		
		int i=0;
		d = fopen(file, "a+");
		while (fread(&temp, sizeof(temp), 1, d))
		{
			consumer[i] = temp;
			i++;
		}
		regis.acc.id = i+1;
		bool exist=false;
		int j=0;
		while(j<i and !exist)
		{
			exist = strcmp(regis.acc.email, consumer[j].acc.email)==0 ? true : false;
			j++;
		}
		
		if(!exist)
		{
			fwrite(&regis, sizeof(regis), 1, d);
			fclose(d);
			isLogin("consumer", regis.acc.email);
		}
		else
			printf("Email telah terdaftar sebelumnya");
		
		char balik[1];
		printf("\n\nIngin coba lagi? (y/n) : ");
		scanf("%s", &balik);
		if(strcmp(strlwr(balik), "y")==0)
		{
			system("cls"); main();
		}
	}
	
	else
	{
		consumers tmp;
		consumers consume[40];
		char email[40], password[40];
		printf("===================Masuk Sebagai Penumpang===================");
		printf("\nEmail\t : ");
		scanf("%s", &email);
		printf("Password : ");
		scanf("%s", &password);
		
		int i=0;
		d = fopen(file, "a+");
		int found = 0;
		while (fread(&tmp, sizeof(tmp), 1, d) == 1)
		{
			consume[i] = tmp;
			i++;
		}
		
		for(int j=0; j<i; j++)
		{
			if((strcmp(email, consume[j].acc.email)==0)) 
			{
				if (strcmp(password, consume[j].acc.password)==0)
					found = 2;
				else
					found = 1;
				j=i;
			}
		}
		
		if (found==2)
			isLogin("consumer", email);
		else if(found==1)
			printf("password tidak sesuai");			
		else
			printf("Email tidak terdaftar");
		char balik[1];
		printf("\n\nIngin coba lagi? (y/n) : ");
		scanf("%s", &balik);
		if(strcmp(strlwr(balik), "y")==0)
		{
			system("cls"); main();
		}		
	}
	fclose(d);		
}

void signup()
{
	int pilih;
	system("cls");
	printf("=============MENU=============");
	printf("\n1. Daftar Sebagai Pengemudi");
	printf("\n2. Daftar Sebagai Penumpang");
	printf("\n3. Kembali");
	printf("\nPilih : ");
	scanf("%d", &pilih);
	switch(pilih)
	{
		case 1:
			AsDriver("register"); break;
		case 2:
			AsUser("register"); break;
		case 3:
			system("cls"); main(); break;
	}
} 

void signin()
{
	int pilih;
	system("cls");
	printf("=============MENU=============");
	printf("\n1. Masuk Sebagai Pengemudi");
	printf("\n2. Masuk Sebagai Penumpang");
	printf("\n3. Kembali");
	printf("\nPilih : ");
	scanf("%d", &pilih);
	switch(pilih)
	{
		case 1:
			AsDriver("login"); break;
		case 2:
			AsUser("login"); break;
		case 3:
			system("cls"); main(); break;
	}
} 

int main()
{
	int log;
	printf("=============MENU=============");
	printf("\n1. Daftar");
	printf("\n2. Masuk");
	printf("\n3. Keluar");
	printf("\nPilih : ");
	scanf("%d", &log);
	switch(log)
	{
		case 1:
			signup(); break;
		case 2:
			signin(); break;
	}
	fclose(d);
}
