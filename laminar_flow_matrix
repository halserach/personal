//Laminar Flow Velocity in x-axis Calculator

//Program ini dapat mengestimasi vx suatu aliran dari persamaan laminar flow

//untuk mencari vx digunakan matriks tridiagonal dengan syarat batas vx(y=0) dan vx(y=L)
//metode yang digunakan program adalah direct approach; tidak ada tebakan awal untuk mendapat hasil

#include <iostream>
#include <iomanip> //diperlukan setprecision dari library iomanip
using namespace std;

int main()
{
// 1. Masukkan dari pengguna
	
	//Deklarasi variabel
	float L, Re, mu, rho, bottom, top;
	int  part;
	
	//Input
	cout << "Channel width L = "; cin >> L;
	cout << "Velocity of bottom plate = "; cin >> bottom;
	cout << "Velocity of top plate = "; cin >> top;
	cout << "Partition = "; cin >> part;
	cout << "Re = "; cin >> Re;
	cout << "Viscosity  = "; cin >> mu;
	cout << "Density  = "; cin >> rho;

	
// 2. Proses
	
	//A. Menentukan dy, dan nilai an serta bn
	float dy = L/(part-1);
	float an = -mu/(dy*dy); //nanti dipakai untuk bagian C
	float bn = 2*mu/(dy*dy); //nanti dipakai untuk bagian C

	
	
	//B. Memasukkan pressure drop ke dalam array result
	
		//Menentukan pressure drop 
		
		float v = (Re*mu)/(rho*L);
		float pd = ((24/Re)/L)*0.5*rho*v*v;
	
		//Deklarasi array result
		float result[part];
	
		//Digunakan loop for dari indeks 1 hingga (part-2)
		int i;
	
		for(i=1; i<(part-1); i++) {
			result[i] = pd;
		}
		
		//Karena vx(y=0) = bottom dan vx(y=L) = top, maka 
		result[0] = bottom;
		result[(part-1)] = top;
		
		//dengan alasan yang sama, nilai result[1] dan result[part-2] harus diubah sebagai berikut:
		result[1] -=an*bottom;
		result[(part-2)] -= an*top;
		
	//C. Membuat matriks dan mengisinya
	
		//Deklarasi matriks r
		//karena hanya digunakan tiga buah garis diagonal, maka matriks bisa direduksi menjadi sebesar new_part x 3
		
		//karena terdapat syarat batas vx(y=0) = bottom dan vx(y=L) = top,
		//maka hanya perlu mencari vx di antaranya saja,
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
		
	//F. Buat r menjadi matriks identitas sehingga result menghasilkan vx neutron
		
		//kita hanya ingin mendapat matriks vx, sehingga cukup result saja yang diubah
	
		for (i=0; i<new_part; i++) {
			result[i+1] = result[i+1]/r[i][1]; //S(i) = S(i)-b(i)
		}
	

//3. Output
	cout <<"\nx\tvx(x)\n";
	
	//kita gunakan loop for untuk mengeluarkan hasil 
	for (i=0; i<part; i++){
		cout << setprecision(4) << i*dy <<"\t" << setprecision (6) << result[i]<< "\n"; 
	}

	return 0;
}
