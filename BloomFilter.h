/*
  BloomFilter.h - Bloom filter lib.
  *Creates a bloom filter from scrach
  *Filter items
  *Accept a already created filter
  Created by Erico Netto, December 22, 2017.
  Released into the public domain.
*/
#ifndef BloomFilter_h
#define BloomFilter_h
#include <vector>
class BloomFilter
{
  public:
    BloomFilter(int items_count, float fp_prob_);
    BloomFilter(int items_count, std::vector<bool> &filter);
     ~BloomFilter();
    void addItem(char *strItem);
    _Bool checkItem(char *strItem);
    int getFilterSize();
    float getFalseProb();
    int getHashCount();
    std::vector<bool> getFilter();
  private:
    float fp_prob_;
    int filter_size_;
    std::vector<bool> filter_;
    int hash_count_;
    int calc_hash_count_(int m, int n);
    int calc_size_(int n, float p);
    float calc_prob_(int n, int m);
};

#endif
