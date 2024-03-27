#pragma once
#include "../template.h"

istream& operator>>(istream& i, __int128& x) {
	char s[50], *p = s;
	for (i >> s, x = 0, p += *p < 48; *p;)
		x = x*10 + *p++ - 48;
	if (*s == 45) x = -x;
	return i;
}

// Note: Doesn't work for INT128_MIN!
ostream& operator<<(ostream& o, __int128 x) {
	if (x < 0) o << '-', x = -x;
	char s[50] = {}, *p = s+49;
	for (; x > 9; x /= 10) *--p = char(x%10+48);
	return o << ll(x) << p;
}
