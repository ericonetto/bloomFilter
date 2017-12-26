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

class BloomFilter
{
  public:
    BloomFilter(int items_count, float fp_prob_);
    void addItem(char *strItem);
    bool checkItem(char *strItem);
    int getFilterSize();
    float getFalseProb();
    int getHashCount();
  private:
    float fp_prob_;
    int filter_size_;
    bool *filter_;
    int hash_count_;
    int calc_hash_count_(int m, int n);
    int calc_size_(int n, float p);
};

#endif
