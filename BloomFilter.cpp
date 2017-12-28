/*
  BloomFilter.cpp - Bloom filter lib.
  *Creates a bloom filter from scrach
  *Filter items
  *Accept a already created filter
  Created by Erico Netto, December 22, 2017.
  Released into the public domain.
*/

#include "Arduino.h"
#include <math.h>
#include "murmur32.h"
#include "BloomFilter.h"

BloomFilter::BloomFilter(int items_count, float fp_prob){

  /*
  items_count : int
  Number of items expected to be stored in bloom filter
  fp_prob : float
  false Positive probability in decimal
  */
  // false posible probability in decimal
  this->fp_prob_ = fp_prob;

  // Size of bit array to use
  this->filter_size_ = this->calc_size_(items_count,fp_prob);
  delay(100);
  // number of hash functions to use
  this->hash_count_ = this->calc_hash_count_(this->filter_size_,items_count);
  delay(100);

  this->filter_.resize(this->filter_size_,false);
  delay(200);
}

BloomFilter::BloomFilter(int items_count, std::vector<bool> &filter){

  /*
  items_count : int
  Number of items expected to be stored in bloom filter
  fp_prob : float
  false Positive probability in decimal
  */
  // false posible probability in decimal
    // Size of bit array to use
  this->filter_size_ = filter.size();
  delay(100);

  this->fp_prob_ = calc_prob_(this->filter_size_,items_count);
  // number of hash functions to use
  this->hash_count_ = this->calc_hash_count_(this->filter_size_,items_count);
  delay(100);

  this->filter_=filter;
  delay(200);
}

BloomFilter::BloomFilter(int items_count, bool *filter, int sizeOfFilter){

  /*
  items_count : int
  Number of items expected to be stored in bloom filter
  fp_prob : float
  false Positive probability in decimal
  */
  // false posible probability in decimal
    // Size of bit array to use


  this->filter_size_ = sizeOfFilter;
  delay(100);

  this->fp_prob_ = calc_prob_(this->filter_size_,items_count);
  // number of hash functions to use
  this->hash_count_ = this->calc_hash_count_(this->filter_size_,items_count);
  delay(100);

  this->filter_.assign(filter, filter+this->filter_size_);
  delay(200);
}

int BloomFilter::calc_hash_count_(int m, int n){
  /*
  Return the hash function(k) to be used using
  following formula
  k = (m/n) * lg(2)

  m : int
  size of bit array
  n : int
  number of items expected to be stored in filter
  */
  int k = (m/n) * log(2);
  return k;
}

int BloomFilter::calc_size_(int n, float p){
  /*
  Return the size of bit array(m) to used using
  following formula
  m = -(n * lg(p)) / (lg(2)^2)
  n : int
  number of items expected to be stored in filter
  p : float
  false Positive probability in decimal
  */
  int m = -(n * log(p))/pow(log(2),2);
  return m;
}

float BloomFilter::calc_prob_(int m, int n){
  /*
  m : int
  size of bit array
  n : int
  number of items expected to be stored in filter
  */

  float p=pow(M_E,-(m*pow(log(2),2)/n));
  return p;
}

bool BloomFilter::checkItem(char *strItem){
  /*
  Check for existence of an item in filter
  */

  for (int i=0;i<=this->hash_count_;i++){
    int digest = murmur3_32((uint8_t*)strItem,strlen(strItem),i) % this->filter_size_;
    if (this->filter_[digest] == false){

      // if any of bit is false then,its not present
      // in filter
      // else there is probability that it exist
      return false;
    }
  }
  return true;
}

void BloomFilter::addItem(char *strItem){

 //Add an item in the filter
 //Serial.println("addItem: " +(String)strItem);

 for(int i=0;i<=this->hash_count_;i++){
   int *digests;
   int digest=0;
   digest= murmur3_32((uint8_t*)strItem,strlen(strItem),i) % this->filter_size_;
   this->filter_[digest] = true;
  }

}

int BloomFilter::getFilterSize(){
  return this->filter_size_;
}

float BloomFilter::getFalseProb(){
  return this->fp_prob_;
}

int BloomFilter::getHashCount(){
  return this->hash_count_;
}

std::vector<bool> BloomFilter::getFilter(){
  return this->filter_;
}
