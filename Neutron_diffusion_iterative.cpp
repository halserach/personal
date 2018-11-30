//Program Neutron Diffusion 

//Program ini dapat mengestimasi flux neutron dari persamaan difusi neutron satu dimensi
// dengan nilai source yang uniform di sepanjang batang satu dimensi (kecuali di ujung-ujung batang)

//untuk mencari flux di titik-titik sepanjang batang satu dimensi digunakan metode Gauss-Siedel
//kemudian dilakukan iterasi perhitungan hingga hasil flux semuanya konvergen 

#include <iostream>
#include <iomanip> //diperlukan setprecision dari library iomanip
using namespace std;

int main()
{
// 1. Masukkan dari pengguna
	
	//Deklarasi variabel
	float L, sigma_a, D,  max_error, S, guess_flux;
	int max_iter, part;
	
	//Input
	cout << "Panjang batang L = "; cin >> L;
	cout << "Jumlah partisi = "; cin >> part;
	cout << "Cross section absorpsi sigma(a) = "; cin >> sigma_a;
	cout << "Koefisien difusi D = "; cin >> D;
	cout << "Max iter = "; cin >> max_iter;
	cout << "Max error = "; cin >> max_error;
	cout << "Source = "; cin >> S;
	cout << "Tebakan awal flux = "; cin >> guess_flux;
	
// 2. Proses
	
	//A. Menentukan dt
	float dt = L/(part-1);
	
	//B. Memasukkan tebakan flux dalam guess_flux ke dalam array flux
	
		//Deklarasi array flux 
		float flux[part];
	
		//Digunakan loop for dari indeks 0 hingga (part-1)
		int i;
	
		for(i=0; i<part; i++) {
			flux[i] = guess_flux;
		}
	
		//Karena ada syarat batas flux(x=0)=flux(x=L)=0, maka: 
		flux[0] = flux[(part-1)]= 0;

		
	//C. Mencari nilai-nilai flux dengan metode Gauss-Siedel
	
		float error; //menampung error dari selisih flux lama dan baru
		float a,b; //a untuk nilai di kiri indeks, b untuk nilai di kanan indeks
		bool flag = 0; //flag 0 berarti masih terdapat error > max_error; flag = 1 berarti error sudah acceptable
		float old_flux; //flux lama sebelum diganti
		int iter = 0;
		while ((flag == 0) and (iter<max_iter)) {
			flag = 1;
			//for dimulai dari indeks 1 hingga [part-2], karena indeks 0 dan [part-1] adalah syarat batas
			for (i=1; i<(part-1); i++) {
				a = flux[(i-1)]; 
				b = flux[(i+1)];
				old_flux = flux[i];
				
				flux[i]=(((a+b)/(dt*dt))+(S/D))/((sigma_a/D)+(2/(dt*dt)));
				
				//menguji error
				error = flux[i]-old_flux;
				if ((error > max_error) or (error < -max_error)) {flag = 0;}
				
				
			}	
			iter++;
		}

//3. Output
	if (iter==max_iter){
		cout << "\nSetelah iterasi mencapai maksimum (" <<max_iter<<"), didapat:\n";
	} else {
		cout << "\nSetelah "<<iter<<" iterasi, didapat:\n";
	}
	
	cout <<"x\tflux(x)\n";
	
	//kita gunakan loop for untuk mengeluarkan hasilnya
	for (i=0; i<part; i++){
		cout << setprecision(4) << i*dt <<"\t" << setprecision (6) << flux[i]<< "\n"; 
	}
		
	return 0;
}
