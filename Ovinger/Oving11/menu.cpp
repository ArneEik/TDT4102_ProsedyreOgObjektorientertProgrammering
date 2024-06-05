#include "menu.h"
#include "myArray.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <stdexcept>
float go = true;
void mainMenu()
{
    int valg;
    cout<<
    "velg eit alternativ\n"
    "1) stoppeklokke meny\n"
    "2) optimalisering meny\n"
    "3) statistikk meny\n"
    "0) avslutt\n";
    cin>>valg;
    switch (valg)
    {
    case 0:
        cout<<"bye\n";
        go = false;
        break;
    case 1:
        stopwatchMenu();
        break;
    case 2:
        optimazationMenu();
        break;
    case 3:
        statisticsMenu();
        break;
    
    default:
        break;
    }
}

void stopwatchMenu()
{
    int valg;
    cout<<
    "velg eit alternativ\n"
    "1) stopwatchPointers()\n"
    "2) stopwatchArray()\n"
    "3) optimizeVector()\n"
    "0) tilbake\n";
    cin>>valg;
    switch (valg)
    {
    case 0:
        cout<<"main menu\n";
        break;
    case 1:
        stopwatchPointers();
        break;
    case 2:
        stopwatchArray();
        break;
    case 3:
        optimizeVector();
        break;
    
    default:
        break;
    }
}

void optimazationMenu()
{
    int valg;
    cout<<
    "velg eit alternativ\n"
    "1) template\n"
    "2)  testTemplateClass()\n"
    "3) \n"
    "0) tilbake\n";
    cin>>valg;
    switch (valg)
    {
    case 0:
        cout<<"main menu\n";
        break;
    case 1:
        runTemplate();
        break;
    case 2:
         testTemplateClass();
        break;
    case 3:
        break;
    
    default:
        break;
    }
}

void statisticsMenu()
{
    int valg;
    cout<<
    "velg eit alternativ\n"
    "1) optimizeVectorValues_experiment\n"
    "2) \n"
    "3) \n"
    "0) tilbake\n";
    cin>>valg;
    switch (valg)
    {
    case 0:
        cout<<"main menu\n";
        break;
    case 1:
        optimizeVectorValues_experiment(1000);
        break;
    case 2:
        break;
    case 3:
        break;
    
    default:
        break;
    }
}

void stopwatchPointers()
{   
const int repetitions = 10000000;
    Stopwatch stopwatch;
    
    // unique_ptr
    stopwatch.start();
    for(int i = 0; i < repetitions; i++) {
        std::unique_ptr<char> p1 = std::make_unique<char>('u');
    }
    double timeTakenSeconds = stopwatch.stop() / double(repetitions);
    std::cout << "make_unique time: " << timeTakenSeconds << std::endl;

    // shared_ptr
    stopwatch.start();
    for(int i = 0; i < repetitions; i++) {
        std::shared_ptr<char> p2 = std::make_shared<char>('s');
    }
    timeTakenSeconds = stopwatch.stop() / double(repetitions);
    std::cout << "make_shared time: " << timeTakenSeconds << std::endl;
}
void stopwatchArray(){
    constexpr int size = 10000;
    const int repetitions = 10000;
    
    Stopwatch stopwatch;
    
    // Stack allocation
    stopwatch.start();
    for(int i = 0; i < repetitions; i++){
        std::array<int, size> arr1;
    }
    double timeTakenSeconds = stopwatch.stop() / double(repetitions);
    std::cout << "Stack allocation time: " << timeTakenSeconds << std::endl;

    // Heap allocation
    stopwatch.start();
    for(int i = 0; i < repetitions; i++){
        std::array<int, size>* arr2 = new std::array<int, size>;
        delete arr2;
    }
    timeTakenSeconds = stopwatch.stop() / double(repetitions);
    std::cout << "Heap allocation time: " << timeTakenSeconds << std::endl;
}

void optimizeVector(){
    std::vector<int> vec;
    //vec.reserve(20); // reserverer plass til 20 elementer, kapasiteten blir 20
    //vec.resize(20);  // fyller vectoren med 20 elementer, både lengden og kapasiteten blir 20
    std::cout << "Length: " << vec.size() << "\t";
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    
    for (int i = 0; i < 20; i++){
        vec.push_back(i); // vec.at(i) = i; Når .resize() benyttes
        std::cout << "Length: " << vec.size() << "\t";
        std::cout << "Capacity: " << vec.capacity() << std::endl;
    }
    // Når lengden overskrider kapasiteten til det indre arrayet 
    // vil vektoren allokere et nytt array som er dobbelt så langt,
    // kopiere over elementene, og frigjøre minnet til det forrige arrayet
    
    // Optimalisering av std::vector
    Stopwatch stopwatch;
    stopwatch.start();
    std::vector<int> slowVec;

    for (int i = 0; i < 100000000; i++){
        slowVec.push_back(i);
    }
    std::cout << "Slow vector time: " << stopwatch.stop() << " sec" << std::endl;

    stopwatch.start();
    std::vector<int> reserveVec;
    // Optimaliserer ved å reservere minne til alle elementene fra start
    reserveVec.reserve(100000000);
    for (int i = 0; i < 100000000; i++){
        reserveVec.push_back(i);
    }
    std::cout << "Time when reserved: " << stopwatch.stop() << " sec" << std::endl;

    stopwatch.start();
    std::vector<int> resizeVec;
    // Optimaliserer ved å legge til alle elementene fra start
    reserveVec.resize(100000000);
    for (int i = 0; i < 100000000; i++){
        reserveVec.at(i) = i;
    }
    std::cout << "Time when resized: " << stopwatch.stop() << " sec" << std::endl;    
}

// Funksjon for å beregne gjennomsnittet
double mean(const std::vector<double>& v) {
    return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

// Funksjon for å beregne standardavviket
double standard_deviation(const std::vector<double>& v, double mean) {
    double sum = 0.0;
    for (double value : v) {
        sum += (value - mean) * (value - mean);
    }
    return std::sqrt(sum / (v.size() - 1));
}

// Funksjon for å utføre en t-test
double t_test(double mean1, double mean2, double sd1, double sd2, int n1, int n2) {
    double pooled_sd = std::sqrt((sd1 * sd1 / n1) + (sd2 * sd2 / n2));
    return (mean1 - mean2) / pooled_sd;
}

// Funksjon for å beregne 95% konfidensintervall
std::pair<double, double> confidence_interval(double mean, double sd, int n, double alpha) {
    double t_value = 2.262; // t-verdi for 95% konfidensintervall og df = n-1
    double margin_of_error = t_value * sd / std::sqrt(n);
    return {mean - margin_of_error, mean + margin_of_error};
}

// Funksjon for å optimalisere std::vector
double optimizeVectorValues() {
    // Placeholder for å unngå kompilering av ufullstendig funksjon
    return 0.0;
}

// Funksjon for å kjøre målingene og analysene
void optimizeVectorValues_experiment(int iterations) {
    std::vector<double> normal_times;
    std::vector<double> reserve_times;
    std::vector<double> resize_times;

    for (int i = 0; i < iterations; ++i) {
        Stopwatch stopwatch;

        // Normal
        stopwatch.start();
        std::vector<int> slowVec;
        for (int i = 0; i < iterations*1000; i++) {
            slowVec.push_back(i);
        }
        normal_times.push_back(stopwatch.stop());

        // Reserve
        stopwatch.start();
        std::vector<int> reserveVec;
        reserveVec.reserve(iterations*1000);
        for (int i = 0; i < iterations*1000; i++) {
            reserveVec.push_back(i);
        }
        reserve_times.push_back(stopwatch.stop());

        // Resize
        stopwatch.start();
        std::vector<int> resizeVec;
        resizeVec.resize(iterations*1000);
        for (int i = 0; i < iterations*1000; i++) {
            resizeVec.at(i) = i;
        }
        resize_times.push_back(stopwatch.stop());
    }

    // Beregn gjennomsnitt og standardavvik
    double mean_normal = mean(normal_times);
    double mean_reserve = mean(reserve_times);
    double mean_resize = mean(resize_times);

    double sd_normal = standard_deviation(normal_times, mean_normal);
    double sd_reserve = standard_deviation(reserve_times, mean_reserve);
    double sd_resize = standard_deviation(resize_times, mean_resize);

    // Utfør t-test
    double t_statistic = t_test(mean_reserve, mean_resize, sd_reserve, sd_resize, iterations, iterations);

    // Beregn konfidensintervall
    auto [ci_lower, ci_upper] = confidence_interval(mean_reserve - mean_resize, std::sqrt((sd_reserve * sd_reserve / iterations) + (sd_resize * sd_resize / iterations)), iterations, 0.05);

    // Print resultater
    std::cout << "Gjennomsnittlig tid (normal): " << mean_normal << " sekunder\n";
    std::cout << "Gjennomsnittlig tid (reserve): " << mean_reserve << " sekunder\n";
    std::cout << "Gjennomsnittlig tid (resize): " << mean_resize << " sekunder\n";
    std::cout << "T-statistikk: " << t_statistic << "\n";
    std::cout << "95% konfidensintervall for forskjellen mellom reserve og resize: [" << ci_lower << ", " << ci_upper << "]\n";

    // Hypotese test resultat
    if (std::abs(t_statistic) > 2.262) { // Kritisk verdi for t-test med df = n-1 og alpha = 0.05
        std::cout << "Hypotesetesten avviser nullhypotesen: Reservering av minne er bedre enn resize\n";
    } else {
        std::cout << "Hypotesetesten avviser ikke nullhypotesen: Reservering av minne er ikke bedre enn resize\n";
    }
}

void testTemplateClass(){
    myArray<int, 5> arr;
    std::cout<< arr.at(2) << std::endl;
    int value = 10;
    arr.fill(value); // Fyller arrayet med verdien 10

    for (int i = 0; i < arr.getSize(); ++i) {
        std::cout << arr.at(i) << " "; // Leser verdier fra arrayet
    }
    std::cout << std::endl;

}

