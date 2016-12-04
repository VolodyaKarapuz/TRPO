#include <iostream>
#include <cmath>
using namespace std;

double F(double x, double y){
        return 3*sin(2*y)+x;			
}

int main() {
        double a=0; double b=1; double h=0.1;
        double n=(b-a)/h;
        double X[(int)11];
        double Y1[(int)11];
        double Y[(int)11];
        //calculate
        X[0]=a; Y[0]=2;
        for(int i=1; i<=n; i++){
                X[i]=a+i*h;
                Y1[i]=Y[i-1]+h*F(X[i-1],Y[i-1]);
                Y[i]=Y[i-1]+h*(F(X[i-1],Y[i-1])+F(X[i],Y1[i]))/2.0;
        }
        //print results
        for(int i=0; i<=n; i++){
                cout << "X["<<i<<"]="<<X[i] <<" ";
        }
        cout << endl;
        for(int i=0; i<=n; i++){
                cout << "Y["<<i<<"]="<<Y[i] << " ";
        }
        return 0;
}