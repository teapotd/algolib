#pragma once
#include "../template.h"
//!!EXCLUDE-FILE
//! Unchecked code taken from KACTL, probably doesn't even compile.
//! It was added to fill space before ICPC Moscow.

// --- POINT 3D
template<class T> struct Point3D {
	typedef Point3D P;
	typedef const P& R;
	T x, y, z;
	explicit Point3D(T a=0, T b=0, T c=0)
		: x(a), y(b), z(c) {}
	bool operator<(R p) const {
		return tie(x, y, z) < tie(p.x, p.y, p.z); }
	bool operator==(R p) const {
		return tie(x, y, z) == tie(p.x, p.y, p.z);}
	P operator+(R p) const {
		return P(x+p.x, y+p.y, z+p.z); }
	P operator-(R p) const {
		return P(x-p.x, y-p.y, z-p.z); }
	P operator*(T d) const {
		return P(x*d, y*d, z*d); }
	P operator/(T d) const {
		return P(x/d, y/d, z/d); }
	T dot(R p) const {
		return x*p.x + y*p.y + z*p.z; }
	P cross(R p) const {
		return P(y*p.z - z*p.y, z*p.x - x*p.z,
		         x*p.y - y*p.x);
	}
	T dist2() const { return x*x + y*y + z*z; }
	double dist() const {
		return sqrt((double)dist2()); }
	//Azimuthal angle (longitude) to x-axis
	double phi() const { // in interval [-pi, pi]
		return atan2(y, x); } 
	//Zenith angle (latitude) to the z-axis
	double theta() const { // in interval [0, pi]
		return atan2(sqrt(x*x+y*y),z); }
	P unit() const {
		return *this/(T)dist(); } //makes dist()=1
	//returns unit vector normal to *this and p
	P normal(P p) const {return cross(p).unit();}
	//returns point rotated 'angle' radians
	// ccw around axis
	P rotate(double angle, P axis) const {
		double s = sin(angle), c = cos(angle);
		P u = axis.unit();
		return u*dot(u)*(1-c) +
			(*this)*c - cross(u)*s;
	}
};

// --- HULL 3D (requires POINT 3D) O(n^2)
typedef Point3D<double> P3;

struct PR {
	void ins(int x) { (a == -1 ? a : b) = x; }
	void rem(int x) { (a == x ? a : b) = -1; }
	int cnt() { return (a != -1) + (b != -1); }
	int a, b;
};

struct F { P3 q; int a, b, c; };

vector<F> hull3d(const vector<P3>& A) {
	assert(sz(A) >= 4);
	vector<vector<PR>> E(sz(A), vector<PR>(sz(A),
		{-1, -1}));
#define E(x,y) E[f.x][f.y]
	vector<F> FS;
	auto mf = [&](int i, int j, int k, int l) {
		P3 q = (A[j] - A[i]).cross((A[k] - A[i]));
		if (q.dot(A[l]) > q.dot(A[i]))
			q = q * -1;
		F f{q, i, j, k};
		E(a,b).ins(k); E(a,c).ins(j);
		E(b,c).ins(i);
		FS.push_back(f);
	};
	rep(i,0,4) rep(j,i+1,4) rep(k,j+1,4)
		mf(i, j, k, 6 - i - j - k);

	rep(i,4,sz(A)) {
		rep(j,0,sz(FS)) {
			F f = FS[j];
			if(f.q.dot(A[i]) > f.q.dot(A[f.a])) {
				E(a,b).rem(f.c);
				E(a,c).rem(f.b);
				E(b,c).rem(f.a);
				swap(FS[j--], FS.back());
				FS.pop_back();
			}
		}
		int nw = sz(FS);
		rep(j,0,nw) {
			F f = FS[j];
#define C(a, b, c) if (E(a,b).cnt() != 2) \
				mf(f.a, f.b, i, f.c);
			C(a, b, c); C(a, c, b); C(b, c, a);
		}
	}
	for (F& it : FS) if ((A[it.b]-A[it.a]).cross(
		A[it.c] - A[it.a]).dot(it.q) <= 0)
			swap(it.c, it.b);
	return FS;
};

// --- DELAUNAY (requires POINT 3D and HULL 3D)
// Calls trifun for every triangle
template<class P, class F> // O(n^2)
void delaunay(vector<P>& ps, F trifun) {
	if (sz(ps) == 3) { int d =
		((ps[1]-ps[0]).cross(ps[2]-ps[0]) < 0);
		trifun(0,1+d,2-d); }
	vector<P3> p3;
	for (P p : ps)
		p3.emplace_back(p.x, p.y, p.len2());
	if (sz(ps) > 3) for(auto t:hull3d(p3))
		if ((p3[t.b]-p3[t.a]).
			cross(p3[t.c]-p3[t.a]).dot(P3(0,0,1)) <0)
		trifun(t.a, t.c, t.b);
}

// --- FAST DELAUNAY (requires our vec2)
// O(n log n)
#include "../geometry/vec2.h"
typedef vec2i P;
typedef struct Quad* Q;
// (can be ll if coords are < 2e4)
typedef __int128_t lll;
// not equal to any other point
P arb(LLONG_MAX,LLONG_MAX);

struct Quad {
	Q rot, o; P p = arb; bool mark;
	Quad(Q q) {rot=q;}
	P& F() { return r()->p; }
	Q& r() { return rot->rot; }
	Q prev() { return rot->o->rot; }
	Q next() { return r()->prev(); }
} *H;

ll cross(P x, P a, P b) {
	return (a-x).cross(b-x);
}
bool circ(P p, P a, P b, P c) {
	lll p2 = p.len2(), A = a.len2()-p2,
	    B = b.len2()-p2, C = c.len2()-p2;
	return cross(p,a,b)*C + cross(p,b,c)*A +
		cross(p,c,a)*B > 0;
}
Q makeEdge(P orig, P dest) {
	Q r = H ? H : new Quad{new Quad{new Quad{
		new Quad{0}}}};
	H = r->o; r->r()->r() = r;
	rep(i,0,4) r = r->rot, r->p = arb,
		r->o = i & 1 ? r : r->r();
	r->p = orig; r->F() = dest;
	return r;
}
void splice(Q a, Q b) {
	swap(a->o->rot->o, b->o->rot->o);
	swap(a->o, b->o);
}
Q connect(Q a, Q b) {
	Q q = makeEdge(a->F(), b->p);
	splice(q, a->next());
	splice(q->r(), b);
	return q;
}

pair<Q,Q> rec(const vector<P>& s) {
	if (sz(s) <= 3) {
		Q a = makeEdge(s[0], s[1]), b =
			makeEdge(s[1], s.back());
		if (sz(s) == 2) return { a, a->r() };
		splice(a->r(), b);
		auto side = cross(s[0], s[1], s[2]);
		Q c = side ? connect(b, a) : 0;
		return {side < 0 ? c->r() : a, side < 0 ?
			c : b->r() };
	}

#define H(e) e->F(), e->p
#define valid(e) (cross(e->F(), H(base)) > 0)
	Q A, B, ra, rb;
	int half = sz(s) / 2;
	tie(ra, A) = rec({all(s) - half});
	tie(B, rb) = rec({sz(s) - half + all(s)});
	while ((cross(B->p, H(A)) < 0 &&
		(A = A->next())) ||
	       (cross(A->p, H(B)) > 0 &&
	       	(B = B->r()->o)));
	Q base = connect(B->r(), A);
	if (A->p == ra->p) ra = base->r();
	if (B->p == rb->p) rb = base;

#define DEL(e, init, dir) Q e = init->dir; \
	if (valid(e)) \
		while (circ(e->dir->F(),H(base),e->F())) {\
			Q t = e->dir; \
			splice(e, e->prev()); \
			splice(e->r(), e->r()->prev()); \
			e->o = H; H = e; e = t; \
		}
	for (;;) {
		DEL(LC, base->r(), o); DEL(RC,base,prev());
		if (!valid(LC) && !valid(RC)) break;
		if (!valid(LC) || (valid(RC) &&
				circ(H(RC), H(LC))))
			base = connect(RC, base->r());
		else
			base = connect(base->r(), LC->r());
	}
	return { ra, rb };
}

vector<P> triangulate(vector<P> pts) {
	sort(all(pts));  assert(unique(all(pts))
		== pts.end());
	if (sz(pts) < 2) return {};
	Q e = rec(pts).first;
	vector<Q> q = {e};
	int qi = 0;
	while (cross(e->o->F(), e->F(), e->p)
		< 0) e = e->o;
#define ADD { Q c = e; do { c->mark = 1; \
		pts.push_back(c->p); \
		q.push_back(c->r()); c = c->next(); } \
		while (c != e); }
	ADD; pts.clear();
	while (qi < sz(q))
		if (!(e = q[qi++])->mark) ADD;
	return pts;
}

// --- POLYGON CENTER OF MASS
#undef P //!HIDE
#define P P______ //!HIDE
typedef vec2d P; // (requires our vec2d)
P polygonCenter(const vector<P>& v) {
	P res(0, 0); double A = 0;
	for (int i = 0, j = sz(v) - 1;
			i < sz(v); j = i++) {
		res = res + (v[i]+v[j]) * v[j].cross(v[i]);
		A += v[j].cross(v[i]);
	}
	return res / A / 3;
}
