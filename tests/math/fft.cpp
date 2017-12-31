#include "../../lib/math/fft.h"
#include "../testing.h"

int main() {
	Vfft data(1 << 3);
	initFFT(sz(data));

	each(d, data) d = complex<double>(rf(-1000.0, 1000.0), rf(-1000.0, 1000.0));

	Vfft transform = data;
	fft(transform, false);

	Vfft inverse = transform;
	fft(inverse, true);

	each(x, inverse) x /= sz(data);

	deb(data);
	deb(transform);
	deb(inverse);
	return 0;
}
