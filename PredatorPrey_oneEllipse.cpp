#include <iostream>
#include <vector>
#include <iomanip>
#include <valarray>
using namespace std;

#ifdef WIN32
#define GNUPLOT_NAME "C:\\gnuplot\\bin\\gnuplot -persist"
#else
#define GNUPLOT_NAME "gnuplot -persist"
#endif
int main() {
#ifdef WIN32
    FILE* pipe = _popen(GNUPLOT_NAME, "w");
#else
    FILE* pipe = popen(GNUPLOT_NAME, "w");
#endif
    double v0; cin>>v0;
    double k0; cin>>k0;
    double alpha1, beta1;
    cin>>alpha1>>beta1;
    double alpha2, beta2;
    cin>>alpha2>> beta2;
    int time, points;
    cin>>time>>points;
    vector<double> t;
    double segment = double(time)/double(points);
    cout<<"t:"<<endl;
    for(double counter = 0; counter<=time; counter+=segment){
        t.push_back(counter);
        cout<<fixed<<setprecision(2)<<counter<<" ";
    }
    cout<<endl<<"v:"<<endl;
    double v_t, k_t;
    double root = sqrt(alpha1*alpha2);
    double frac1 = alpha1/beta1;
    double frac2 = alpha2/beta2;
    vector<float> victims, killers;
    for(double t_i : t){
        v_t = (v0 - frac2)*cos(root*t_i)-(k0-frac1)*((sqrt(alpha2)*beta1)/(beta2*sqrt(alpha1)))*sin(root*t_i)+frac2;
        victims.push_back(v_t);
    }
    cout<<endl<<"k:"<<endl;
    for(double t_i: t){
        k_t = (v0-frac2)*((sqrt(alpha1)*beta2)/(beta1*sqrt(alpha2)))*sin(root*t_i) + (k0-frac1)*cos(root*t_i)+frac1;
        killers.push_back(k_t);
    }
    fprintf(pipe, "set xlabel \"t\"\n");
    fprintf(pipe, "set ylabel \"n\"\n");
    fprintf(pipe, "set yrange [0:150]\n");
    fprintf(pipe, "plot '-' with lines\n");
    for(int i = 0; i< victims.size(); i++){
        fprintf(pipe, "%f %f\n", killers[i], victims[i]);
    }
    fprintf(pipe, "e\n");
    fflush(pipe);
#ifdef WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif
    return 0;
}

/*
80 20
0.1 0.002 0.2 0.0025
100
1000
 */
