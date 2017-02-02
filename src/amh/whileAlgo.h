#pragma once

namespace amh {
  template<class TIN>
  class whileAlgo : public algo<TIN> {
  public:
    whileAlgo(algo<TIN>& _step,
              algo<TIN>& _check) :
      step(_step), check(_check) {}

    TIN operator()(TIN& _in) {
      TIN out = _in;
      while (check.check(out))
        out = step(out);
      return out;
    }

    void operator<<(algo<TIN>& _algo) {
      add(_algo);
    }

  protected:
    algo<TIN>& step;
    algo<TIN>& check;
  };
}