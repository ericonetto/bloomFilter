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

  // number of hash functions to use
  this->hash_count_ = this->calc_hash_count_(this->filter_size_,items_count);



  // Bit array of given size
  if (this->filter_ != 0) {
      this->filter_ = (bool*) realloc(this->filter_, this->hash_count_ * sizeof(bool));
  } else {
      this->filter_ = (bool*) malloc(this->hash_count_ * sizeof(bool));
  }

  // initialize all bits as 0
  memset(this->filter_, 0, sizeof(this->filter_));

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

bool BloomFilter::checkItem(char *strItem){
  /*
  Check for existence of an item in filter
  */
  uint8_t item[strlen(strItem)];
  memcpy(item,strItem,strlen(strItem));

  for (int i=0;i<=this->hash_count_;i++){
    int digest = murmur3_32(item,32,i) % this->filter_size_;
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

 int *digests;
 for (int i=0;i<=this->hash_count_;i++){

   // create digest for given item.
   // i work as seed to mmh3.hash() function
   // With different seed, digest created is different
   int digest=0;
   char from;

   uint8_t item[strlen(strItem)];
   memcpy(item,strItem,strlen(strItem));

   digest= murmur3_32(item,32,i) % this->filter_size_;

   // set the bit true in filter
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
