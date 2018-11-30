//Laminar Flow Velocity in x-axis Calculator

//Program ini dapat mengestimasi vx suatu aliran dari persamaan laminar flow

//untuk mencari vx digunakan metode Gauss-Siedel dengan syarat batas vx(y=0) dan vx(y=L)
//kemudian dilakukan iterasi perhitungan hingga hasil vx semuanya konvergen 

#include <iostream>
#include <iomanip> //diperlukan setprecision dari library iomanip
using namespace std;

int main()
{
// 1. Masukkan dari pengguna
	
	//Deklarasi variabel
	float L, Re, mu, rho, max_error, guess_vx, bottom, top;
	int max_iter, part;
	
	//Input
	cout << "Channel width L = "; cin >> L;
	cout << "Velocity of bottom plate = "; cin >> bottom;
	cout << "Velocity of top plate = "; cin >> top;
	cout << "Partition = "; cin >> part;
	cout << "Re = "; cin >> Re;
	cout << "Viscosity  = "; cin >> mu;
	cout << "Density  = "; cin >> rho;
	cout << "Inital guess of Vx = "; cin >> guess_vx;
	cout << "Max. iteration = "; cin >> max_iter;
	cout << "Max. error = "; cin >> max_error;
	
	
// 2. Proses
	
	//A. Menentukan dy
	float dy = L/(part-1);
	
	//B. Memasukkan tebakan vx dalam guess_vx ke dalam array vx
	
		//Deklarasi array vx
		float vx[part];
	
		//Digunakan loop for dari indeks 0 hingga (part-1)
		int i;
	
		for(i=0; i<part; i++) {
			vx[i] = guess_vx;
		}
	
		//Karena vx(y=0) = bottom dan vx(y=L) = top, maka 
		vx[0] = bottom;
		vx[(part-1)] = top;
		
		
	//C. Mencari nilai-nilai vx dengan metode Gauss-Siedel
		
		//Menentukan pressure drop 
		
		float v = (Re*mu)/(rho*L);
		float pd = ((24/Re)/L)*0.5*rho*v*v;
	
		float error; //menampung error dari selisih vx lama dan baru
		float a,b; //a untuk nilai di kiri indeks, b untuk nilai di kanan indeks
		bool flag = 0; //flag 0 berarti masih terdapat error > max_error; flag = 1 berarti error sudah acceptable
		float old_vx; //vx lama sebelum diganti
		int iter = 0;
		while ((flag == 0) and (iter<max_iter)) {
			flag = 1;
			//for dimulai dari indeks 1 hingga [part-2], karena indeks 0 dan [part-1] adalah syarat batas
			for (i=1; i<(part-1); i++) {
				a = vx[(i-1)]; 
				b = vx[(i+1)];
				old_vx = vx[i];
				
				vx[i]=((a+b)/2)+ 0.5 * (1/mu) * pd * dy * dy;
				
				//menguji error
				error = vx[i]-old_vx;
				if ((error > max_error) or (error < -max_error)) {flag = 0;}
				
				
			}	
			iter++;
		}

//3. Output
	if (iter==max_iter){
		cout << "\nSetelah iterasi mencapai maksimum (" <<max_iter<<" iterasi), didapat:\n";
	} else {
		cout << "\nSetelah "<<iter<<" iterasi, didapat:\n";
	}
	
	cout <<"y\tvx(y)\n";
	
	//kita gunakan loop for untuk mengeluarkan hasilnya
	for (i=0; i<part; i++){
		cout << setprecision(4) << i*dy <<"\t" << setprecision (6) << vx[i]<< "\n"; 
	}
		
	return 0;
}
