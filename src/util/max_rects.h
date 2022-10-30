#pragma once
#include "../template.h"

struct MaxRect {
	// begin = first column of rectangle
	// end = first column after rectangle
	// hei = height of rectangle
	// touch = columns of height hei inside
	int begin, end, hei;
	vi touch; // sorted increasing
};

// Given consecutive column heights find
// all inclusion-wise maximal rectangles
// contained in "drawing" of columns; time O(n)
vector<MaxRect> getMaxRects(vi hei) {
	hei.insert(hei.begin(), -1);
	hei.pb(-1);
	vi reach(sz(hei), sz(hei)-1);
	vector<MaxRect> ans;

	for (int i = sz(hei)-1; --i;) {
		int j = i+1, k = i;
		while (hei[j] > hei[i]) j = reach[j];
		reach[i] = j;

		while (hei[k] > hei[i-1]) {
			ans.pb({ i-1, 0, hei[k], {} });
			auto& rect = ans.back();

			while (hei[k] == rect.hei) {
				rect.touch.pb(k-1);
				k = reach[k];
			}
			rect.end = k-1;
		}
	}
	return ans;
}
