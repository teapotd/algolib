//!!EXCLUDE-FILE
//! Unchecked code taken from old UJ notebook, probably doesn't even compile.
//! It was added to fill space before ICPC Moscow.

// P = punkt 2D lub 3D, K = double
// --- GEOMETRIA 3D ~Bartosz Walczak
// Kat pomiedzy dwoma wektorami. Zawsze >=0.
// Zalozenie: a,b!=0
K angle3(const xyz &a, const xyz &b)
	{ return atan2(sqrt(cross(b,a).norm()),a*b);}
struct plane { // plaszczyzna {v: n*v=c}
	xyz n; K c; // (n - wektor normalny)
	plane(const xyz &ni, K ci) : n(ni), c(ci) {}
	plane() {}
};
// Czy punkt lezy na plaszczyznie?
bool on_plane(const xyz &a, const plane &p)
	{ return fabs(p.n*a - p.c) < EPS; }
// Plaszczyzna rozpieta przez 3 punkty ccw.
// Zalozenie: a,b,c niezalezne
plane span3(const xyz &a, const xyz &b,
		const xyz &c)
  { xyz n = cross(c-a, b-a);
  	return plane(n, n*a); }
// Plaszczyzna symetralna odcinka.
// Zalozenie: a!=b
plane median3(const xyz &a, const xyz &b)
  { return plane(b-a, (b-a)*(b+a)*0.5); }
// Plaszczyzna rownolegla przez punkt
plane parallel3(const xyz &a, const plane &p)
	{ return plane(p.n, p.n*a); }
// Odleglosc punktu od plaszczyzny
K dist3(const xyz &a, const plane &p)
  { return fabs(p.n*a-p.c)/sqrt(p.n.norm()); }
struct line3 { // prosta {v: cross(v,u)=w}
    xyz u, w; // (u - wektor kierunku)
    // UWAGA! konstruktor dwuargumentowy
    // nie tworzy prostej przechodzacej
    // przez 2 punkty,
    // w tym celu nalezy uzyc span3!
    line3(const xyz &ui, const xyz &wi)
    	: u(ui), w(wi) {}
    line3() {}
};
// Czy punkt lezy na prostej?
bool on_line3(const xyz &a, const line3 &p)
  { return (cross(a,p.u)-p.w).norm() < EPS; }
// Prosta rozpieta przez 2 punkty. Zał.: a!=b
line3 span3(const xyz &a, const xyz &b)
  { return line3(b-a, cross(a, b-a)); }
// Plaszczyzna rozpieta przez prosta i
// punkt ccw. Zalozenie: cross(a,p.u)!=p.w
plane span3(const line3 &p, const xyz &a)
  { return plane(cross(a,p.u)-p.w, p.w*a); }
// Prosta przeciecia dwoch plaszczyzn
line3 intersection3(const plane &p,
		const plane &q) {
	xyz u=cross(q.n, p.n);
	if (u.norm() < EPS) throw "rownolegle";
	return line3(u, q.n*p.c-p.n*q.c);
}
// Punkt przeciecia plaszczyzny i prostej
xyz intersection3(const plane &p,
		const line3 &q) {
	K d = q.u*p.n;
	if (fabs(d) < EPS) throw "rownolegle";
	return (q.u*p.c + cross(p.n, q.w))/d;
}
// Prosta prostopadla do plaszczyzny
// przechodzaca przez punkt
line3 perp3(const xyz &a, const plane &p)
	{ return line3(p.n, cross(a, p.n)); }
// Plaszczyzna prostopadla do prostej
// przechodzaca przez punkt
plane perp3(const xyz &a, const line3 &p)
	{ return plane(p.u, p.u*a); }
// Odleglosc punktu od prostej
K dist3(const xyz &a, const line3 &p)
	{ return sqrt((cross(a,p.u)-p.w).norm()) /
		sqrt(p.u.norm()); }
// Odleglosc 2 prostych od siebie.
// Zalozenie: cross(q.u,p.u)!=0
// (niestabilne przy bliskim 0)
K dist3(const line3 &p, const line3 &q)
	{ return fabs(p.u*q.w + q.u*p.w) /
		sqrt(cross(q.u, p.u).norm()); }

// --- GEOMETRIA SFER W 3D ~Bartosz Walczak
struct sphere {
	xyz c; K r; // srodek, promien
	sphere(const xyz &ci, K ri=0)
		: c(ci), r(ri) {}
	sphere() {}
	// pole powierzchni
	K area() const { return 4*M_PI*r*r; }
	// objetosc kuli
	K volume() const { return 4*M_PI*r*r*r/3; }
};
// Czy punkt lezy na sferze?
bool on_sphere(const xyz &a, const sphere &s)
	{ return fabs((a-s.c).norm()-s.r*s.r) < EPS;}
// Czy sfera/punkt lezy wewnatrz lub na brzegu?
bool in_sphere(const sphere &a, const sphere&b)
	{ return b.r+EPS > a.r && (a.c-b.c).norm() <
		(b.r-a.r)*(b.r-a.r)+EPS; }
// Przeciecie sfery i prostej.
// Zwraca liczbe punktow przeciecia
int intersection3(const sphere &s,
	const line3 &p, xyz I[]/*OUT*/) {
	K d = p.u.norm(), a = (cross(s.c,p.u)-p.w).
		norm()/(d*d), r = s.r*s.r/d;
	if (a >= r+EPS) return 0;
	xyz u = (p.u*(p.u*s.c)+cross(p.u,p.w))/d;
	if (a > r-EPS) { I[0] = u; return 1; }
	K h = sqrt(r-a);
	I[0] = u+p.u*h; I[1] = u-p.u*h; return 2;
}
// Przeciecie sfery i plaszczyzny.
// Zwraca true, jesli sie przecinaja. Wtedy u,r
// sa odp. srodkiem i promieniem okregu
// przeciecia. Zalozenie: s1.c!=s2.c
bool intersection3(const sphere &s,
		const plane &p, xyz &u, K &r) {
	K d = p.n.norm(), a = (p.n*s.c-p.c)/d;
	u = s.c-p.n*a; a *= a; K r1 = s.r*s.r/d;
	if (a >= r1+EPS) return false;
	r = a > r1-EPS ? 0 : sqrt(r1-a)*sqrt(d);
	return true;
}
// Przeciecie dwoch sfer.
// Zwraca true, jesli sie przecinaja.
// Wtedy u,r sa odp. srodkiem i promieniem
// okregu przeciecia. Zalozenie: s1.c!=s2.c
bool intersection3(const sphere &s1,
		const sphere &s2, xyz &u, K &r) {
	K d = (s2.c-s1.c).norm(), r1 = s1.r*s1.r/d,
		r2 = s2.r*s2.r/d;
	u = s1.c*((r2-r1+1)*0.5) +
		s2.c*((r1-r2+1)*0.5);
	if (r1 > r2) swap(r1, r2);
	K a = (r1-r2+1)*0.5; a *= a;
	if (a >= r1+EPS) return false;
	r = a > r1-EPS ? 0 : sqrt(r1-a)*sqrt(d);
	return true;
}

// --- GEOMETRIA NA SFERZE ~Bartosz Walczak
// Odleglosc dwoch punktow na sferze
K distS(const xyz &a, const xyz &b)
	{ return atan2(sqrt(cross(b,a).norm()),a*b);}
struct circleS { // okrag na sferze
	xyz c; K r; // srodek, promien katowy
	circleS(const xyz &ci, K ri) : c(ci), r(ri){}
	circleS() {}
	K area() const { return 2*M_PI*(1-cos(r)); }
};
// Okrag rozpiety przez 3 punkty.
// Zalozenie: punkty sa parami rozne
circleS spanS(xyz a, xyz b, xyz c) {
    int tmp = 1;
    if ((a-b).norm() > (c-b).norm())
    	{ swap(a, c); tmp = -tmp; }
    if ((b-c).norm() > (a-c).norm())
    	{ swap(a, b); tmp = -tmp; }
    xyz v = cross(c-b, b-a);
    v = v*(tmp/sqrt(v.norm()));
    return circleS(v, distS(a,v));
}
// Przeciecie 2 okregow na sferze.
// Zalozenie: cross(c2.c,c1.c)!=0
int intersectionS(const circleS &c1,
		const circleS &c2, xyz I[]/*OUT*/) {
	xyz n = cross(c2.c, c1.c),
		w = c2.c*cos(c1.r)-c1.c*cos(c2.r);
	K d = n.norm(), a = w.norm()/d;
	if (a >= 1+EPS) return 0;
	xyz u = cross(n,w)/d;
	if (a > 1-EPS) { I[0] = u; return 1; }
	K h = sqrt(1-a)/sqrt(d);
	I[0] = u+n*h; I[1] = u-n*h; return 2;
}
