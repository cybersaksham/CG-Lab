#include <iostream>
using namespace std;

void WindowtoViewport(int x_w, int y_w,
	int x_wmax, int y_wmax, int x_wmin, int y_wmin,
	int x_vmax, int y_vmax, int x_vmin, int y_vmin) {
	// point on viewport
	int x_v, y_v;

	// scaling factors for x coordinate and y coordinate
	float sx, sy;

	// calculating Sx and Sy
	sx = (float)(x_vmax - x_vmin) / (x_wmax - x_wmin);
	sy = (float)(y_vmax - y_vmin) / (y_wmax - y_wmin);

	// calculating the point on viewport
	x_v = x_vmin + (float)((x_w - x_wmin) * sx);
	y_v = y_vmin + (float)((y_w - y_wmin) * sy);

	cout << "The point on viewport: ("<<x_v <<","<< y_v<<")" << endl;
}

int main() {
	int x_wmax, y_wmax, x_wmin, y_wmin;
	int x_vmax, y_vmax, x_vmin, y_vmin;
	int x_w, y_w;
	
	WindowtoViewport(30, 80, 80, 80, 20, 40, 60, 60, 30, 40);
 	WindowtoViewport(30, 80, 80, 80, -20, -40, 60, 60, 30, 40);
 	WindowtoViewport(30, 80, 70, 100, 20, 40, 60, 60, 30, 40);
 	WindowtoViewport(30, 80, 80, 80, 20, 40, 80, 80, 30, 30);
	
	return 0;
}
