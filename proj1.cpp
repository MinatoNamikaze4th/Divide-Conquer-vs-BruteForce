#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <limits>
#include <ctime>
#include <sys/time.h>
#include <unordered_set>
#include <iomanip>
#include <random> 
using namespace std;

struct Point {
    int x, y;
};

double calculateDistance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

float BruteForce(const vector<Point>& points, Point& p1, Point& p2) {
    float minDist = numeric_limits<float>::max();
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            float dist = calculateDistance(points[i], points[j]);
            if (dist < minDist) {
                minDist = dist;
                p1 = points[i];
                p2 = points[j];
            }
        }
    }
    return minDist;
}

float stripClosest(const vector<Point>& strip, float d, Point& p1, Point& p2) {
    float minDist = d;
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j) {
            float dist = calculateDistance(strip[i], strip[j]);
            if (dist < minDist) {
                minDist = dist;
                p1 = strip[i];
                p2 = strip[j];
            }
        }
    }
    return minDist;
}

float DivideAndConquer(const vector<Point>& points, Point& p1, Point& p2) {
    vector<Point> sortedPoints = points; // Create a copy for sorting
    sort(sortedPoints.begin(), sortedPoints.end(), [](const Point& a, const Point& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y); // Sort by x, then by y
    });
    
    float minDist = numeric_limits<float>::max();
    for (size_t i = 0; i < sortedPoints.size() - 1; ++i) {
        for (size_t j = i + 1; j < sortedPoints.size(); ++j) {
            if (sortedPoints[j].x - sortedPoints[i].x >= minDist)
                break;
            float dist = calculateDistance(sortedPoints[i], sortedPoints[j]);
            if (dist < minDist) {
                minDist = dist;
                p1 = sortedPoints[i];
                p2 = sortedPoints[j];
            }
        }
    }
    return minDist;
}

int main() {
    const int m = 1; // number of iterations
    const int max_n = 20000; // maximum number of points
    struct timeval start, end;
    
    vector<int> ns;
    for (int n = 10000; n <= max_n; n += 5000) {
        ns.push_back(n);
    }
    
    vector<double> t_avg_ALG1(ns.size(), 0);
    vector<double> t_avg_ALG2(ns.size(), 0);
    
    // Seed for random number generation
    srand(time(NULL));

    for (int n_index = 0; n_index < ns.size(); ++n_index) {
        int n = ns[n_index];
        for (int j = 0; j < m; ++j) {
            // Generate random points
            vector<Point> points;
            for (int k = 0; k < n; ++k) {
                Point p;
                p.x = rand() % 32767; // Adjust upper bound according to your needs
                p.y = rand() % 32767;
                points.push_back(p);
            }
            
            // Compute ALG1:EmpiricalRT
            gettimeofday(&start, NULL);
            Point p1_dc, p2_dc;
            float minDistance_dc = DivideAndConquer(points, p1_dc, p2_dc);
            gettimeofday(&end, NULL);
            double t1 = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
            t_avg_ALG1[n_index] += t1;
            
            // Compute ALG2:EmpiricalRT
            gettimeofday(&start, NULL);
            Point p1_bf, p2_bf;
            float minDistance_bf = BruteForce(points, p1_bf, p2_bf);
            gettimeofday(&end, NULL);
            double t2 = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
            t_avg_ALG2[n_index] += t2;
        }
        
        // Compute average times
        t_avg_ALG1[n_index] /= m;
        t_avg_ALG2[n_index] /= m;
    }
    
    // Output results
    cout << "n\tALG1:DAC EmpiricalRT\tALG2:BF EmpiricalRT\n";
    for (int i = 0; i < ns.size(); ++i) {
        cout << ns[i] << "\t" << t_avg_ALG1[i] <<setprecision(6)<< "ms\t\t\t" << t_avg_ALG2[i] <<setprecision(6)<< "ms\n";
    }

    return 0;
}