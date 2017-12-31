#include "../../lib/math/fft.h"
#include "../testing.h"

int main() {
	Vfft data(1 << 3);
	initFFT(sz(data));

	each(d, data) d = complex<double>(rf(-1000.0, 1000.0), rf(-1000.0, 1000.0));

	Vfft transform = data;
	fft<1>(transform);

	Vfft inve = transform;
	fft<-1>(inve);

	deb(data);
	deb(inve);
	deb(transform);
	return 0;
}
