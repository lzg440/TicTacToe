#include <reg51.h>
#include <stdio.h>

sbit buton1 = P0^0;//Butonlari tanimliyoruz
sbit buton2 = P0^1;
sbit buton3 = P0^2;
sbit buton4 = P0^3;
sbit buton5 = P0^4;
sbit buton6 = P0^5;
sbit buton7 = P0^6;
sbit buton8 = P0^7;
sbit buton9 = P3^2;

sbit sariLed1 = P1^0;//Sari led durumlarini tanimliyoruz
sbit sariLed2 = P1^1;
sbit sariLed3 = P1^2;
sbit sariLed4 = P1^3;
sbit sariLed5 = P1^4;
sbit sariLed6 = P1^5;
sbit sariLed7 = P1^6;
sbit sariLed8 = P1^7;
sbit sariLed9 = P3^0;

sbit kizilLed1 = P2^0;//Kizil Led durumlarini tanimliyoruz
sbit kizilLed2 = P2^1;
sbit kizilLed3 = P2^2;
sbit kizilLed4 = P2^3;
sbit kizilLed5 = P2^4;
sbit kizilLed6 = P2^5;
sbit kizilLed7 = P2^6;
sbit kizilLed8 = P2^7;
sbit kizilLed9 = P3^1;

sbit sira = P3^3;// Siranin hangi renkte oldugunu g�steriyor(0 ise Sari - 1 ise Kizil)

//Skorlari tutan bitler(Maximum 4'e kadar saydirabiliyoruz)
sbit sariSifir = P3^4; //Sari'nin skorunun 0. biti
sbit sariBir = P3^5;	//Sari'nin skorunun 1. biti
sbit kizilSifir = P3^6; //Kizil'in skorunun 0. biti
sbit kizilBir = P3^7; //Kizil'in skorunun 1. biti

void kesme() interrupt 1{// Butona basma anlarında tekrarlama olmasın diye oyun esnasında kısa aralıklar veriyor
	int i;
	for(i=0; i<50;i++){
		TMOD = 0x01; //timer0 mod 1'de �alisacak
		TH0= 0xFC;  				
		TL0 = 0x66;		
	}
}
void bekle(){// Gecikme - Delay
	int i;
	for(i=0; i<150;i++){
		TMOD = 0x10; //timer1 mod 1'de �alisacak
		TH1= 0xFC;  				
		TL1 = 0x66;
		TR1=1;
		while(TF1==0);
		TF1=0;
		TR1=0;
	}
}
void sifirla(){// Skor hari� b�t�n pinler sifirlanir
	P0=0x00;
	P1=0x00;
	P2=0x00;
	sariLed9=0;
	kizilLed9=0;
	buton9=0;
	sira=0;
}
void skorSifirla(){// Skor sifirlanir
	sariBir = 0;
	sariSifir = 0;
	kizilBir = 0;
	kizilSifir=0;
}

void sariHesapla(){//Sarinin skorunun hesaplanmasi
	if(sariBir ==0 && sariSifir== 0){
		sariSifir = 1;
	}else if(sariBir ==0 && sariSifir== 1){
		sariBir = 1;
		sariSifir=0;
	}else if(sariBir ==1 && sariSifir== 0){
		sariSifir = 1;
	}else{
		skorSifirla();
	}
}
void kizilHesapla(){ //Kizil'in skorunun hesaplanmasi
	if(kizilBir ==0 && kizilSifir== 0){
		kizilSifir = 1;
	}else if(kizilBir ==0 && kizilSifir== 1){
		kizilBir = 1;
		kizilSifir = 0;
	}else if(kizilBir ==1 && kizilSifir== 0){
		kizilSifir = 1;
	}else{
		skorSifirla();
	}
}

void butunLedlerSari(){//B�t�n ledler sari yanar
	P1=0xFF;
	sariLed9=1;
	P2=0x00;
	kizilLed9=0;
}
void butunLedlerKizil(){//B�t�n ledler kizil yanar
	P1=0x00;
	sariLed9=0;
	P2=0xFF;
	kizilLed9=1;
}
void butunLedlerSonuk(){// B�t�n ledler s�ner
	P1=0x00;
	sariLed9=0;
	P2=0x00;
	kizilLed9=0;
}
void sariKontrol(){//Sari'nin kazanma kontrol�
	if(
		(sariLed1 ==1 && sariLed2 ==1 && sariLed3 ==1) || 
		(sariLed4 ==1 && sariLed5 ==1 && sariLed6 ==1) ||
		(sariLed7 ==1 && sariLed8 ==1 && sariLed9 ==1) ||
		(sariLed1 ==1 && sariLed4 ==1 && sariLed7 ==1) ||
		(sariLed2 ==1 && sariLed5 ==1 && sariLed8 ==1) ||
		(sariLed3 ==1 && sariLed6 ==1 && sariLed9 ==1) ||
		(sariLed1 ==1 && sariLed5 ==1 && sariLed9 ==1) ||
		(sariLed3 ==1 && sariLed5 ==1 && sariLed7 ==1))
	{
		long x;
		for( x = 0; x<3; x++){
			butunLedlerSari();
			bekle();
			butunLedlerSonuk();
			bekle();
		}
		sariHesapla();
		sifirla();
	}
}
void kizilKontrol(){//Kizil'nin kazanma kontrol�
	if(
		(kizilLed1 ==1 && kizilLed2 ==1 && kizilLed3 ==1) || 
		(kizilLed4 ==1 && kizilLed5 ==1 && kizilLed6 ==1) ||
		(kizilLed7 ==1 && kizilLed8 ==1 && kizilLed9 ==1) ||
		(kizilLed1 ==1 && kizilLed4 ==1 && kizilLed7 ==1) ||
		(kizilLed2 ==1 && kizilLed5 ==1 && kizilLed8 ==1) ||
		(kizilLed3 ==1 && kizilLed6 ==1 && kizilLed9 ==1) ||
		(kizilLed1 ==1 && kizilLed5 ==1 && kizilLed9 ==1) ||
		(kizilLed3 ==1 && kizilLed5 ==1 && kizilLed7 ==1))
	{
		long x;
		for( x = 0; x<3; x++){
			butunLedlerKizil();
			bekle();
			butunLedlerSonuk();
			bekle();
		}
		kizilHesapla();
		sifirla();
	}
}
void beraberlikKontrol(){ //Beraberlik durumunu kontrol eder ve eger berabere ise ledleri s�nd�r�r.
	if((kizilLed1 == 1 || sariLed1==1) &&
		(kizilLed2 == 1 || sariLed2==1) &&
		(kizilLed3 == 1 || sariLed3==1) &&
		(kizilLed4 == 1 || sariLed4==1) &&
		(kizilLed5 == 1 || sariLed5==1) &&
		(kizilLed6 == 1 || sariLed6==1) &&
		(kizilLed7 == 1 || sariLed7==1) &&
		(kizilLed8 == 1 || sariLed8==1) &&
		(kizilLed9 == 1 || sariLed9==1))
		{
			sifirla();
			bekle();
			bekle();
		}
}

void main(void){
	TMOD = 0x01; //timer0 mod 1'de �alisacak (kesme işlemi için)
	TH0= 0xFC;  //ayarlanıyor
	TL0 = 0x66; //ayarlanıyor
	ET0=1; //timer kesmesi aktif
	EA=1; //kesmeler aktif
	TR0 = 1;  //timer 1 akfif
	
	sifirla(); //Ledler ve butonlar sıfırlanır
	skorsifirla(); // Skor sifirlanır
	while(1){
		if(buton1 == 1){
			if(sariLed1 != 1 && kizilLed1 != 1){
				if(sira==0){
					sariLed1=1;
					kizilLed1=0;
					sira =1;
				}else{
					sariLed1=0;
					kizilLed1=1;
					sira =0;
				}
			}
		}
		if(buton2 == 1){
			if(sariLed2 != 1 && kizilLed2 != 1){
				if(sira==0){
						sariLed2=1;
						kizilLed2=0;
						sira =1;
				}else{
					sariLed2=0;
					kizilLed2=1;
					sira =0;
				}
			}
		}
		if(buton3 == 1){
			if(sariLed3 != 1 && kizilLed3 != 1){
				if(sira==0){
						sariLed3=1;
						kizilLed3=0;
						sira =1;
				}else{
					sariLed3=0;
					kizilLed3=1;
					sira =0;
				}
			}
		}
		if(buton4 == 1){
			if(sariLed4 != 1 && kizilLed4 != 1){
				if(sira==0){
						sariLed4=1;
						kizilLed4=0;
						sira =1;
				}else{
					sariLed4=0;
					kizilLed4=1;
					sira =0;
				}
			}
		}
		if(buton5 == 1){
			if(sariLed5 != 1 && kizilLed5 != 1){
				if(sira==0){
						sariLed5=1;
						kizilLed5=0;
						sira =1;
				}else{
					sariLed5=0;
					kizilLed5=1;
					sira =0;
				}
			}
		}
		if(buton6 == 1){
			if(sariLed6 != 1 && kizilLed6 != 1){
				if(sira==0){
						sariLed6=1;
						kizilLed6=0;
						sira =1;
				}else{
					sariLed6=0;
					kizilLed6=1;
					sira =0;
				}
			}
		}
		if(buton7 == 1){
			if(sariLed7 != 1 && kizilLed7 != 1){
				if(sira==0){
						sariLed7=1;
						kizilLed7=0;
						sira =1;
				}else{
					sariLed7=0;
					kizilLed7=1;
					sira =0;
				}
			}
		}
		if(buton8 == 1){
			if(sariLed8 != 1 && kizilLed8 != 1){
				if(sira==0){
						sariLed8=1;
						kizilLed8=0;
						sira =1;
				}else{
					sariLed8=0;
					kizilLed8=1;
					sira =0;
				}
			}
		}
		if(buton9 == 1){
			if(sariLed9 != 1 && kizilLed9 != 1){
				if(sira==0){
						sariLed9=1;
						kizilLed9=0;
						sira =1;
				}else{
					sariLed9=0;
					kizilLed9=1;
					sira =0;
				}
			}
		}
		kizilKontrol();
		sariKontrol();
		beraberlikKontrol();
	}
}