//Program Neutron Diffusion 

//Program ini dapat mengestimasi flux neutron dari persamaan difusi neutron satu dimensi
// dengan nilai source yang uniform di sepanjang batang satu dimensi (kecuali di ujung-ujung batang)

//untuk mencari flux di titik-titik sepanjang batang satu dimensi digunakan matriks tridiagonal
//program ini menggunakan direct approach, yang berarti program tidak melakukan tebakan, namun langsung mengkalkulasi hasilnya

#include <iostream>
#include <iomanip> //diperlukan setprecision dari library iomanip
using namespace std;

int main()
{
// 1. Masukkan dari pengguna
	
	//Deklarasi variabel
	float L, sigma_a, D,  S;
	int part;
	
	//Input
	cout << "Panjang batang L = "; cin >> L;
	cout << "Jumlah partisi = "; cin >> part;
	cout << "Cross section absorpsi sigma(a) = "; cin >> sigma_a;
	cout << "Koefisien difusi D = "; cin >> D;
	cout << "Source = "; cin >> S;
	
// 2. Proses
	
	//A. Menentukan dt, dan nilai an serta bn
	float dt = L/(part-1);
	float an = -D/(dt*dt); //nanti dipakai untuk bagian C
	float bn = sigma_a + (2*D/(dt*dt)); //nanti dipakai untuk bagian C
	
	//B. Memasukkan source ke dalam array result
	
		//Deklarasi array result
		float result[part];
	
		//Digunakan loop for dari indeks 1 hingga (part-2)
		int i;
	
		for(i=1; i<(part-1); i++) {
			result[i] = S;
		}
		
		result[0] = result[(part-1)] = 0; // karena syarat batas
		
	//C. Membuat matriks dan mengisinya
	
		//Deklarasi matriks r
		//karena hanya digunakan tiga buah garis diagonal, maka matriks bisa direduksi menjadi sebesar new_part x 3
		
		//karena terdapat syarat batas bahwa fluks(x=0) = fluks(x=L) = 0
		//dan S(x=0) = S(x=l) = 0, maka hanya perlu mencari fluks di antaranya saja
		//sehingga jumlah nilai yang harus dicari adalah sebanyak new_part:
		
		int new_part = part-2; 
		
		float r[new_part][3];
	
	
		for (i=0; i<new_part; i++){
			r[i][0] = r[i][2] = an;
			r[i][1] = bn;
			
		}
	
	//D. Eliminasi diagonal bawah (seluruh r[i][0])
	
		//pada saat mengeliminasi kolom 1 pada r, nilai source juga diubah
		
		float k;
		for (i=0; i<(new_part-1); i++) {
		k = r[i+1][0]/r[i][1]; //nilai rasio a(n+1)/bn
		
		r[i+1][0]-=r[i][1]*k; //reduksi a indeks i+1 dengan b indeks i * k
		r[i+1][1] -=r[i][2]*k; //reduksi b indeks i+1 dengan c indeks i * k
		result[i+2]-=result[i+1]*k; //reduksi nilai S(i+1) dengan S(i)*k
			
		}


	//E. Eliminasi diagonal atas (seluruh r[i][3])
		
		//pada saat mengeliminasi kolom 3 pada r, nilai source diubah
		//k telah dideklarasi
		
		for (i=(new_part-1); i>0; i--) {
		k = r[i-1][2]/r[i][1]; //nilai rasio c(n-1)/bn
		
		r[i-1][2]-=r[i][1]*k; //reduksi c indeks i-1 dengan b indeks i * k
		result[i]-=result[i+1]*k; //reduksi nilai S(i-1) dengan S(i)*k
	 
		}
		
	//F. Buat r menjadi matriks identitas sehingga result menghasilkan flux neutron
		
		//kita hanya ingin mendapat matriks flux, sehingga cukup result saja yang diubah
	
		for (i=0; i<new_part; i++) {
			result[i+1] = result[i+1]/r[i][1]; //S(i) = S(i)-b(i)
		}
	

//3. Output
	cout <<"\nx\tflux(x)\n";
	
	//kita gunakan loop for untuk mengeluarkan hasil 
	for (i=0; i<part; i++){
		cout << setprecision(4) << i*dt <<"\t" << setprecision (6) << result[i]<< "\n"; 
	}

	return 0;
}
