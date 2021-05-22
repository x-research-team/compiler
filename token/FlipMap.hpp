#pragma once

#include <map>

using namespace std;

class FlipMap {
  protected:
    template <typename A, typename B>
    pair<B, A> static flip_pair(const pair<A, B> &p) {
      return pair<B, A>(p.second, p.first);
    }

    template <typename A, typename B> map<B, A> flip_map(const map<A, B> &src) {
      map<B, A> dst;
      transform(src.begin(), src.end(), inserter(dst, dst.begin()),
                flip_pair<A, B>);
      return dst;
    }
};
