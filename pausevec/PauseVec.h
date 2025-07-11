#ifndef PAUSEVEC_H
#define PAUSEVEC_H

#include <cstddef>
#include <stdexcept>


class PauseVec {
private:
  int* data;
  bool* removed;
  size_t cap;
  size_t numLeft;
  size_t minRemovedInd;


public:
  PauseVec();
  ~PauseVec();

  size_t capacity() const;
  size_t count() const;

  int    lookup(size_t index);
  int    remove(size_t index);
  void	 remove_val(int x);
  void   append(int value);
};

PauseVec* create_pausevec();

#endif
